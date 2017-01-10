/*
In this program, I created a 3 channel image with 500 height and 1000 width. 
8 bit unsigned integer is allocated for each pixel in each channel. (8x3 = 24 bits per each pixel)  
And each pixel is assigned with (0,0,100) scalar value. 
That means 1st channel is all zero, 2nd channel is also all zero and the 3rd channel is all 100. 
Therefore we can see a red image as the output of the program.
*/

#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex02(){

	Mat img(500, 1000, CV_8UC3,Scalar(0,0,100)); //B,G,R

	if (img.empty()){
		cout<<"Error: image cannot be loaded"<<endl;
		return -1;
	}

	namedWindow("MyWindow",CV_WINDOW_NORMAL);
	imshow("MyWindow",img);

	waitKey(0);//milisecond

	destroyWindow("MyWindow");
	return 0;
}
