#include <iostream>

#include "ImageProcessing.h"

using namespace std;

/* TASK1:
	Use the Multiply blending mode to combine 
	“layer1.tga” (top layer) with 
	“pattern1.tga” (bottom layer)
*/
void PerformTask1() {	
	ImageData image1;
	ImageData image2;

	ReadFile("input/layer1.tga", image1);

	ReadFile("input/pattern1.tga", image2);

	ImageData result;
	Multiply(image1, image2, result);

	WriteFile("output/part1.tga", result);
}

/* TASK2:
	Use the Subtract blending mode to combine 
	“layer2.tga” (top layer) with 
	“car.tga” (bottom layer). 
	This mode subtracts the top layer from the bottom layer
*/
void PerformTask2() {	
	ImageData image1;
	ImageData image2;

	ReadFile("input/layer2.tga", image1);

	ReadFile("input/car.tga", image2);

	ImageData result;
	Subtract(image1, image2, result);

	WriteFile("output/part2.tga", result);
}

void PerformTask3() {	
	ImageData image1;
	ImageData image2;

	ReadFile("input/layer1.tga", image1);

	ReadFile("input/pattern2.tga", image2);

	ImageData temp;
	Multiply(image1, image2, temp);

	ImageData image3;
	ReadFile("input/text.tga", image3);

	ImageData result;
	Screen(image3, temp, result);

	WriteFile("output/part3.tga", result);
}

void PerformTask4() {
	ImageData image1;
	ImageData image2;

	ReadFile("input/layer2.tga", image1);

	ReadFile("input/circles.tga", image2);

	ImageData temp;
	Multiply(image1, image2, temp);

	ImageData image3;
	ReadFile("input/pattern2.tga", image3);

	ImageData result;
	Subtract(image3, temp, result);

	WriteFile("output/part4.tga", result);
}

void PerformTask5() {	
	ImageData image1;
	ImageData image2;

	ReadFile("input/layer1.tga", image1);

	ReadFile("input/pattern1.tga", image2);

	ImageData result;
	Overlay(image1, image2, result);

	WriteFile("output/part5.tga", result);
}

void PerformTask6() {	
	ImageData image;

	ReadFile("input/car.tga", image);

	ImageData result;
	AddGreen(image, 200, result);

	WriteFile("output/part6.tga", result);
}

void PerformTask7() {	
	ImageData image;

	ReadFile("input/car.tga", image);

	ImageData temp;
	ScaleRed(image, 4, temp);

	ImageData result;
	ScaleBlue(temp, 0, result);

	WriteFile("output/part7.tga", result);
}

void PerformTask8() {	
	ImageData image;

	ReadFile("input/car.tga", image);

	ImageData result1;
	ImageData result2;
	ImageData result3;
	ExtractRed(image, result1);
	ExtractGreen(image, result2);
	ExtractBlue(image, result3);

	WriteFile("output/part8_r.tga", result1);
	WriteFile("output/part8_g.tga", result2);
	WriteFile("output/part8_b.tga", result3);
}

void PerformTask9() {	
	ImageData image1;
	ImageData image2;
	ImageData image3;

	ReadFile("input/layer_red.tga", image1);
	ReadFile("input/layer_green.tga", image2);
	ReadFile("input/layer_blue.tga", image3);

	ImageData result;
	CombineRGB(image1, image2, image3, result);

	WriteFile("output/part9.tga", result);
}

void PerformTask10() {	
	ImageData image;

	ReadFile("input/text2.tga", image);

	ImageData result;
	Rotate180(image, result);

	WriteFile("output/part10.tga", result);
}

void PerformExtraCredit() {
	ImageData image1;
	ImageData image2;
	ImageData image3;
	ImageData image4;

	ReadFile("input/car.tga", image1);
	ReadFile("input/circles.tga", image2);
	ReadFile("input/text.tga", image3);
	ReadFile("input/pattern1.tga", image4);

	ImageData result;
	CombineFourImages(image1, image2, image3, image4, result);

	WriteFile("output/extracredit.tga", result);
}

int main() {

	 cout << "Running Task1 ..." << endl << endl;
	 PerformTask1();

	 cout << "Running Task2 ..." << endl << endl;
	 PerformTask2();

	 cout << "Running Task3 ..." << endl << endl;
	 PerformTask3();

	 cout << "Running Task4 ..." << endl << endl;
	 PerformTask4();

	 cout << "Running Task5 ..." << endl << endl;
	 PerformTask5();

	 cout << "Running Task6 ..." << endl << endl;
	 PerformTask6();

	 cout << "Running Task7 ..." << endl << endl;
	 PerformTask7();

	 cout << "Running Task8 ..." << endl << endl;
	 PerformTask8();

	 cout << "Running Task9 ..." << endl << endl;
	 PerformTask9();

	 cout << "Running Task10 ..." << endl << endl;
	 PerformTask10();

	cout << "Running Extra Credit Task ..." << endl << endl;
	PerformExtraCredit();

	return 0;
}