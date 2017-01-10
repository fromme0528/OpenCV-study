/*

Histogram Equializaiton

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex08(){

	Mat img = imread("MyPic.jpg",CV_LOAD_IMAGE_COLOR);

	if (img.empty()){
		cout <<"Error :: Image cannot be loaded.." <<endl;
		return -1;
	}

	cvtColor(img,img,CV_BGR2GRAY);

	Mat img_hist_equalized;
	equalizeHist(img,img_hist_equalized);

	namedWindow("Original Image",CV_WINDOW_NORMAL);
	namedWindow("Hist Equal",CV_WINDOW_NORMAL);

	imshow("Original Image",img);
	imshow("Hist Equal",img_hist_equalized);

	waitKey(0);

	destroyAllWindows();

	return 0;
}