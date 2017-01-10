
/*

Detect Mouse Clicks While Pressing a Key

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MyCallBackFuncForMouse2(int event, int x, int y, int flags, void* userdata){

	if (flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON)){
		cout<<"Left Button of the mouse is clicked while pressing CTRL key - position ("<<x<<","<<y<<")"<<endl;
	}else if (flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_RBUTTON)){
		cout<<"Right Button of the mouse is clicked while pressing SHIFT key - position ("<<x<<","<<y<<")"<<endl;
	}else if (flags == (EVENT_FLAG_ALTKEY + EVENT_MOUSEMOVE)){
		cout<<"Mouse is moved over the window while presing ALT key - position ("<<x<<","<<y<<")"<<endl;
	}
}

int ex17(){

	Mat src = imread("testimage.jpg");

	if(!src.data){
		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}

	namedWindow("My Window", 1);

	setMouseCallback("My Window",MyCallBackFuncForMouse2,NULL);

	imshow("My Window",src);

	waitKey(0);

	return 0;

}

