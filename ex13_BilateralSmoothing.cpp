/*

Bilateral Smoothing

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex13(){

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);

	Mat src = imread("testimage.jpg",CV_LOAD_IMAGE_UNCHANGED);
	imshow("Original Image",src);

	Mat dst;
	char zBuffer[35];

	for (int i =1; i<31; i= i+2){

		//copy the text to the zBuffer
		_snprintf_s(zBuffer,35, "Kernel Size : %d x %d",i,i);

		//smooth the image in the src and save it to dst
		bilateralFilter(src,dst,i,i,i);

		putText( dst, zBuffer, Point (src.cols/4, src.rows/8), CV_FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255),2 );
		imshow("Smoothed Image",dst);

		int c = waitKey(2000);

		if ( c ==27){
			return 0;
		}
	}

	dst = Mat::zeros(src.size(),src.type());
	_snprintf_s(zBuffer,35,"Press Any Key to Exit");

	putText(dst, zBuffer,Point(src.cols/4,src.rows/2),CV_FONT_HERSHEY_COMPLEX,2,Scalar(255,255,255),2);

	imshow("Smoothed Image",dst);

	waitKey(0);
	return 0;

}