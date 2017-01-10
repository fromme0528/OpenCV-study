/*

Homogenous Smoothing

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex10(){
	namedWindow("Original Image", CV_WINDOW_NORMAL);
	namedWindow("Smoothed Image", CV_WINDOW_NORMAL);

	Mat src = imread("MyPic.jpg",1);

	imshow("Original Image",src);

	Mat dst;
	char zBuffer[35];

	for (int i =1; i<31; i= i+2){

		//copy the text to the zBuffer
		_snprintf_s(zBuffer,35, "Kernel Size : %d x %d",i,i);

		//smooth the image in the src and save it to dst
		blur(src,dst,Size(i,i),Point(-1,-1), BORDER_REFLECT_101);

		putText( dst, zBuffer, Point (src.cols/4, src.rows/8), CV_FONT_HERSHEY_COMPLEX, 6, Scalar(0, 0, 255),5 );
		imshow("Smoothed Image",dst);

		int c = waitKey(2000);

		if ( c ==27){
			return 0;
		}
	}

	dst = Mat::zeros(src.size(),src.type());
	_snprintf_s(zBuffer,35,"Press Any Key to Exit");

	putText(dst, zBuffer,Point(src.cols/4,src.rows/2),CV_FONT_HERSHEY_COMPLEX,1,Scalar(255,255,255));

	imshow("Smoothed Image",dst);

	waitKey(0);
	return 0;

}