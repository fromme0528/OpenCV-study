/*
Change Brightness of Image
*/

#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex07(){
	
	Mat img = imread("MyPic.jpg",CV_LOAD_IMAGE_COLOR);

	if (img.empty()){
		cout <<"Error :: Image cannot be loaded.." <<endl;
		return -1;
	}

	//Mat imgH = img + Scalar(75,75,75);
	Mat imgH;
	img.convertTo(imgH,-1,1,75);

	Mat imgL = img + Scalar(-75,-75,-75);
	//img.convertTo(imgL,-1,1,-75);

	namedWindow("Original Image",CV_WINDOW_NORMAL);
	namedWindow("High Brightness",CV_WINDOW_NORMAL);
	namedWindow("Low Brightness",CV_WINDOW_NORMAL);

	imshow("Original Image",img);
	imshow("High Brightness",imgH);
	imshow("Low Brightness",imgL);

	waitKey(0);

	destroyAllWindows();

	return 0;
}