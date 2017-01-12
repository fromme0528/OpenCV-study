
/*

Detect Edge using Canny function

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src31, src_gray31;
Mat dst31, detected_edges31;

int edgeThresh = 1;
int lowThreshold ;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size =3;
char* window_name31 = "Edge Map";


//function
//thresholds input wit a ratio 1:3
void CannyThreshold (int, void*){

	//Reduce noise
	blur (src_gray31, detected_edges31, Size(3,3));

	//Canny detector
	Canny(detected_edges31, detected_edges31, lowThreshold, lowThreshold*ratio, kernel_size);

	//Using Canny's output as a mask, we display our result

	//dst31 has all black color
	dst31 = Scalar::all(0);
	
	//Edge is represented and other side is black.
	src31.copyTo(dst31,detected_edges31);
	imshow(window_name31, dst31);
}

int ex31(){

	//Load an image
	src31 = imread("canny.jpg");

	if (!src31.data){
		return -1;
	}

	//Create a matrix of the same type and size as src
	dst31.create(src31.size(), src31.type());

	//Convert the image to grayscale
	cvtColor(src31,src_gray31,COLOR_BGR2GRAY);

	//Create a window
	namedWindow(window_name31,WINDOW_AUTOSIZE);
	namedWindow("test",WINDOW_AUTOSIZE);
	//Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold", window_name31, &lowThreshold, max_lowThreshold, CannyThreshold);

	CannyThreshold(0,0);

	waitKey(0);
	return 0;
}

