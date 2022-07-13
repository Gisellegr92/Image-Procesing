#pragma once
#include <vector>
#include <string>

using namespace std;

struct ImageProcessing
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

};

struct ImageData
{
    ImageProcessing header;
    vector<Pixel> pixels;
};

void ReadFile(const string &filepath, ImageData &imageData);

void WriteFile(const string &filepath, ImageData &imageData);

void Multiply(const ImageData &image1, const ImageData &image2, ImageData &result);

void Subtract(const ImageData &image1, const ImageData &image2, ImageData &result);

void Screen(const ImageData &image1, const ImageData &image2, ImageData &result);

void Overlay(const ImageData &image1, const ImageData &image2, ImageData &result);

void AddGreen(const ImageData &image, int amount, ImageData &result);

void ScaleRed(const ImageData &image, int amount, ImageData &result);

void ScaleBlue(const ImageData &image, int amount, ImageData &result);

void ExtractRed(const ImageData &image, ImageData &result);

void ExtractGreen(const ImageData &image, ImageData &result);

void ExtractBlue(const ImageData &image, ImageData &result);

void CombineRGB(const ImageData &redImage, const ImageData &greenImage, 
    const ImageData &blueImage, ImageData &result);

void Rotate180(const ImageData &image, ImageData &result);

void CombineFourImages(const ImageData &image1, const ImageData &image2,
    const ImageData &image3, const ImageData &image4, ImageData &result);