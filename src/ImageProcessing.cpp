#include "ImageProcessing.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void ReadFile(const string &filepath, ImageData &imageData)
{
    ifstream imageBinary;
    imageBinary.open(filepath, ios::binary | ios::in);

    if (!imageBinary.is_open()) {
        cout << "Error while opening the file: " << filepath << endl;
        return;
    }

    imageBinary.read(&imageData.header.idLength, sizeof(imageData.header.idLength));
    imageBinary.read(&imageData.header.colorMapType, sizeof(imageData.header.colorMapType));
    imageBinary.read(&imageData.header.dataTypeCode, sizeof(imageData.header.dataTypeCode));

    imageBinary.read((char*)&imageData.header.colorMapOrigin, sizeof(imageData.header.colorMapOrigin));
    imageBinary.read((char*)&imageData.header.colorMapLength, sizeof(imageData.header.colorMapLength));

    imageBinary.read(&imageData.header.colorMapDepth, sizeof(imageData.header.colorMapDepth));

    imageBinary.read((char*)&imageData.header.xOrigin, sizeof(imageData.header.xOrigin));
    imageBinary.read((char*)&imageData.header.yOrigin, sizeof(imageData.header.yOrigin));

    imageBinary.read((char*)&imageData.header.width, sizeof(imageData.header.width));
    imageBinary.read((char*)&imageData.header.height, sizeof(imageData.header.height));

    // Debug
    // cout << "Width:" << imageData.header.width << endl;
    // cout << "Height:" << imageData.header.height << endl;

    imageBinary.read(&imageData.header.bitsPerPixel, sizeof(imageData.header.bitsPerPixel));
    imageBinary.read(&imageData.header.imageDescriptor, sizeof(imageData.header.imageDescriptor));

    int totalPixels = imageData.header.width * imageData.header.height;

    for (int i = 0; i < totalPixels; i++) {
        Pixel pixel;
        imageBinary.read((char*)&pixel.blue, sizeof(pixel.blue));
        imageBinary.read((char*)&pixel.green, sizeof(pixel.green));
        imageBinary.read((char*)&pixel.red, sizeof(pixel.red));

        imageData.pixels.push_back(pixel);
    }
    
    imageBinary.close();
}

void WriteFile(const string &filepath, ImageData &imageData)
{
    ofstream imageBinary(filepath, ios::out | ios::binary);

    imageBinary.write(&imageData.header.idLength, sizeof(imageData.header.idLength));
    imageBinary.write(&imageData.header.colorMapType, sizeof(imageData.header.colorMapType));
    imageBinary.write(&imageData.header.dataTypeCode, sizeof(imageData.header.dataTypeCode));

    imageBinary.write((char*)&imageData.header.colorMapOrigin, sizeof(imageData.header.colorMapOrigin));
    imageBinary.write((char*)&imageData.header.colorMapLength, sizeof(imageData.header.colorMapLength));

    imageBinary.write(&imageData.header.colorMapDepth, sizeof(imageData.header.colorMapDepth));

    imageBinary.write((char*)&imageData.header.xOrigin, sizeof(imageData.header.xOrigin));
    imageBinary.write((char*)&imageData.header.yOrigin, sizeof(imageData.header.yOrigin));

    imageBinary.write((char*)&imageData.header.width, sizeof(imageData.header.width));
    imageBinary.write((char*)&imageData.header.height, sizeof(imageData.header.height));

    imageBinary.write(&imageData.header.bitsPerPixel, sizeof(imageData.header.bitsPerPixel));
    imageBinary.write(&imageData.header.imageDescriptor, sizeof(imageData.header.imageDescriptor));



    for (int i = 0; i < imageData.pixels.size(); i++) {
        Pixel pixel = imageData.pixels[i];
        imageBinary.write((char*)&pixel.blue, sizeof(pixel.blue));
        imageBinary.write((char*)&pixel.green, sizeof(pixel.green));
        imageBinary.write((char*)&pixel.red, sizeof(pixel.red));
    }

    imageBinary.close();
}

int MultiplyHelper(int pixel1, int pixel2)
{
    int value = ((pixel1 * pixel2) / 255.0) + 0.5;
    if (value > 255) {
        value = 255;
    } else if (value < 0) {
        value = 0;
    }
    return value;
}

void Multiply(const ImageData &image1, const ImageData &image2, ImageData &result)
{
    result.header = image1.header;
    for (int i = 0; i < image1.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = MultiplyHelper(image1.pixels[i].red, image2.pixels[i].red);
        pixel.green = MultiplyHelper(image1.pixels[i].green, image2.pixels[i].green);
        pixel.blue = MultiplyHelper(image1.pixels[i].blue, image2.pixels[i].blue);

        result.pixels.push_back(pixel);
    }
}

int SubtractHelper(int pixel1, int pixel2)
{
    int value = pixel1 - pixel1;
    if (value > 255) {
        value = 255;
    } else if (value < 0) {
        value = 0;
    }
    return value;
}

void Subtract(const ImageData &image1, const ImageData &image2, ImageData &result)
{
    result.header = image1.header;
    for (int i = 0; i < image1.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = SubtractHelper(image1.pixels[i].red, image2.pixels[i].red);
        pixel.green = SubtractHelper(image1.pixels[i].green, image2.pixels[i].green);
        pixel.blue = SubtractHelper(image1.pixels[i].blue, image2.pixels[i].blue);

        result.pixels.push_back(pixel);
    }
}

int ScreenHelper(int pixel1, int pixel2)
{
    int value = (((255 - pixel1) * (255 - pixel2)) / 255.0) + 0.5;
    if (value > 255) {
        value = 255;
    } else if (value < 0) {
        value = 0;
    }
    return 255 - value;
}

void Screen(const ImageData &image1, const ImageData &image2, ImageData &result)
{
    result.header = image2.header;
    for (int i = 0; i < image1.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = ScreenHelper(image1.pixels[i].red, image2.pixels[i].red);
        pixel.green = ScreenHelper(image1.pixels[i].green, image2.pixels[i].green);
        pixel.blue = ScreenHelper(image1.pixels[i].blue, image2.pixels[i].blue);

        result.pixels.push_back(pixel);
    }
}

int OverlayHelper(int pixel1, int pixel2)
{
    int value;
    if (pixel2 <= 255 / 2) {
        value = (2 * ((pixel1 * pixel2) / 255.0)) + 0.5;
    } else {
        value = 255.0 - (2 * (((255 - pixel1) * (255 - pixel2)) / 255.0)) + 0.5;
    }

    if (value > 255) {
        value = 255;
    } else if (value < 0) {
        value = 0;
    }
    return value;
}

void Overlay(const ImageData &image1, const ImageData &image2, ImageData &result)
{
    result.header = image2.header;
    for (int i = 0; i < image1.pixels.size(); i++) {
        Pixel pixel;
        pixel.red =  OverlayHelper(image1.pixels[i].red, image2.pixels[i].red);
        pixel.green = OverlayHelper(image1.pixels[i].green, image2.pixels[i].green);
        pixel.blue = OverlayHelper(image1.pixels[i].blue, image2.pixels[i].blue);

        result.pixels.push_back(pixel);
    }
}

void AddGreen(const ImageData &image, int amount, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = image.pixels[i].red;
        int value = image.pixels[i].green + amount;
        if (value > 255) {
            value = 255;
        }
        pixel.green = value;
        pixel.blue = image.pixels[i].blue;

        result.pixels.push_back(pixel);
    }
}

void ScaleRed(const ImageData &image, int amount, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        int value = image.pixels[i].red * amount;
        if (value > 255) {
            value = 255;
        }
        pixel.red = value;
        pixel.green = image.pixels[i].green;
        pixel.blue = image.pixels[i].blue;

        result.pixels.push_back(pixel);
    }
}

void ScaleBlue(const ImageData &image, int amount, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = image.pixels[i].red;
        pixel.green = image.pixels[i].green;
        int value =  image.pixels[i].blue * amount;
        if (value > 255) {
            value = 255;
        }
        pixel.blue = value;
        
        result.pixels.push_back(pixel);
    }
}

void ExtractRed(const ImageData &image, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = image.pixels[i].red;
        pixel.green = image.pixels[i].red;
        pixel.red = image.pixels[i].red;
        
        result.pixels.push_back(pixel);
    }
}

void ExtractGreen(const ImageData &image, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = image.pixels[i].green;
        pixel.green = image.pixels[i].green;
        pixel.blue = image.pixels[i].green;
        
        result.pixels.push_back(pixel);
    }
}

void ExtractBlue(const ImageData &image, ImageData &result)
{
    result.header = image.header;
    for (int i = 0; i < image.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = image.pixels[i].blue;
        pixel.green = image.pixels[i].blue;
        pixel.blue = image.pixels[i].blue;
        
        result.pixels.push_back(pixel);
    }
}

void CombineRGB(const ImageData &redImage, const ImageData &greenImage, 
    const ImageData &blueImage, ImageData &result) 
{
    result.header = redImage.header;
    for (int i = 0; i < redImage.pixels.size(); i++) {
        Pixel pixel;
        pixel.red = redImage.pixels[i].red;
        pixel.green = greenImage.pixels[i].green;
        pixel.blue = blueImage.pixels[i].blue;
        
        result.pixels.push_back(pixel);
    }
}

void Rotate180(const ImageData &image, ImageData &result)
{
    result.header = image.header;
    for (int i = image.pixels.size() - 1; i >= 0 ; i--) {
        result.pixels.push_back(image.pixels[i]);
    }
}

void CombineFourImages(const ImageData &image1, const ImageData &image2,
    const ImageData &image3, const ImageData &image4, ImageData &result)
{
    result.header = image1.header;
    result.header.width *= 2;
    result.header.height *= 2;

    int counter1 = 0,
        counter2 = 0,
        counter3 = 0,
        counter4 = 0;

    int currWidth = 0,
        currHeight = 0;

    for (int i = 0; i < 4 * image1.pixels.size(); i++)
    {
        Pixel pixel;

        if (currHeight < image1.header.height) {
            if (currWidth < image3.header.width) {
                pixel.red = image3.pixels[counter3].red;
                pixel.green = image3.pixels[counter3].green;
                pixel.blue = image3.pixels[counter3].blue;
                counter3++;
            }
            else {
                pixel.red = image4.pixels[counter4].red;
                pixel.green = image4.pixels[counter4].green;
                pixel.blue = image4.pixels[counter4].blue;
                counter4++;
            }
        } else {
            if (currWidth < image1.header.width) {
                pixel.red = image1.pixels[counter1].red;
                pixel.green = image1.pixels[counter1].green;
                pixel.blue = image1.pixels[counter1].blue;
                counter1++;
            }
            else {
                pixel.red = image2.pixels[counter2].red;
                pixel.green = image2.pixels[counter2].green;
                pixel.blue = image2.pixels[counter2].blue;
                counter2++;
            }
        }

        currWidth++;

        if(currWidth == result.header.width) {
            currWidth = 0;
            currHeight++;
        }
        result.pixels.push_back(pixel);
    }
}