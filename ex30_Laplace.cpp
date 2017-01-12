
/*

Detect Edge using Laplace function

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex30(){

	Mat src, src_gray, dst;

	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	char* window_name = "Sobel Demo - Simple Edge Detector";
	
	int c;

	//Load an image
	src = imread("laplace.jpg");

	if (!src.data){
		return -1;
	}

	GaussianBlur (src, src, Size(3,3), 0,0,BORDER_DEFAULT);
	
	//Convert it to gray
	cvtColor(src,src_gray,COLOR_RGB2GRAY);

	//Create Window
	namedWindow(window_name,CV_WINDOW_AUTOSIZE);

	//Apply Laplace function
	Mat abs_dst;

	Laplacian(src_gray,dst,ddepth,kernel_size,scale,delta,BORDER_DEFAULT);
	convertScaleAbs(dst,abs_dst);

	imshow(window_name,abs_dst);
	waitKey(0);
	return 0;
}

