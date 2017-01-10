
/*

TrackBar with Callback Function

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){

	if (event == EVENT_LBUTTONDOWN){
		cout<<"Left Button of the mouse is clicked - position ("<<x<<","<<y<<")"<<endl;
	}else if (event == EVENT_RBUTTONDOWN){
		cout<<"Right Button of the mouse is clicked - position ("<<x<<","<<y<<")"<<endl;
	}else if (event == EVENT_MBUTTONDOWN){
		cout<<"Middel Button of the mouse is clicked - position ("<<x<<","<<y<<")"<<endl;
	}else if (event == EVENT_MOUSEMOVE){
		cout<<"Mouse move over the window - position ("<<x<<","<<y<<")"<<endl;
	}

}

int ex16(){

	Mat src = imread("testimage.jpg");

	if(!src.data){
		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}

	namedWindow("My Window", 1);

	setMouseCallback("My Window",CallBackFunc,NULL);

	imshow("My Window",src);

	waitKey(0);

	return 0;

}

