
/*

Scharr Derivatives to detect edges(3x3)

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex29(){

	Mat src, src_gray;
	Mat dst;

	char* window_name = "Sobel Demo - Simple Edge Detector";
	
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	//Load an image
	src = imread("testimage.jpg");

	if (!src.data){
		return -1;
	}

	GaussianBlur (src, src, Size(3,3), 0,0,BORDER_DEFAULT);
	
	//Convert it to gray
	cvtColor(src,src_gray,COLOR_RGB2GRAY);

	//Create Window
	namedWindow(window_name,CV_WINDOW_AUTOSIZE);

	//generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	//Gradient X
	Scharr(src_gray,grad_x,ddepth, 1,0,scale,delta,BORDER_DEFAULT);
//	Sobel(src_gray, grad_x, ddepth,1,0,3,scale,delta,BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	//Gradient Y
	
	Scharr(src_gray,grad_y,ddepth,0,1,scale,delta,BORDER_DEFAULT);
//	Sobel(src_gray,grad_y,ddepth,0,1,3,scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y,abs_grad_y);

	addWeighted (abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	imshow(window_name,dst);
	waitKey(0);
	return 0;
}

