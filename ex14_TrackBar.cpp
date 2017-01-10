/*

Simple TrackBar

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex14(){

	Mat src = imread("testimage.jpg");
	if(!src.data){

		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}


	namedWindow("My Window", CV_WINDOW_AUTOSIZE);

	int iSliderValue1 = 50;
	createTrackbar("Brightness","My Window",&iSliderValue1,100);

	int iSliderValue2 = 50;
	createTrackbar("Contrast","My Window",&iSliderValue2,100);

	while(true){
		Mat dst;

		int iBrightness = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		src.convertTo(dst,-1,dContrast,iBrightness);


		imshow("My Window",dst);

		int iKey = waitKey(50);

		if (iKey ==27){
			break;
		}
	}

	return 0;

}