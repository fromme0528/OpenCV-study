/*

How to Detect Mouse Clicks and Moves

*/


#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src;

void MyCallbackForBrightness(int iValueForBrightness, void *userData){

	Mat dst;
	int iValueForContrast = *(static_cast<int*>(userData));

	int iBrightness = iValueForBrightness - 50;
	double dContrast = iValueForContrast / 50.0;

	cout << "MyCallbackForBrightness : Contrast=" << dContrast << ", Brightness=" <<iBrightness <<endl;

	src.convertTo(dst,-1,dContrast,iBrightness);

	imshow("My Window",dst);

}

void MyCallbackForContrast(int iValueForContrast, void *userData){

	Mat dst;
	int iValueForBrightness = *(static_cast<int*>(userData));

	int iBrightness = iValueForBrightness - 50;
	double dContrast = iValueForContrast / 50.0;

	cout << "MyCallbackForContrast: Contrast=" << dContrast << ", Brightness=" <<iBrightness <<endl;

	src.convertTo(dst,-1,dContrast,iBrightness);

	imshow("My Window",dst);
}


int ex15(){

	src = imread("testimage.jpg");

	if(!src.data){
		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}

	namedWindow("My Window", 1);

	int iValueForBrightness = 50;
	int iValueForContrast = 50;

	createTrackbar("Brightness","My Window",&iValueForBrightness,100,MyCallbackForBrightness,&iValueForContrast);

	createTrackbar("Contrast","My Window",&iValueForContrast,100,MyCallbackForContrast,&iValueForBrightness);


	imshow("My Window",src);

	waitKey(0);

	return 0;

}