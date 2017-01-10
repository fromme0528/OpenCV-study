/*

Histogram Equializaiton : Color Image

*/


#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex09(){

	Mat img = imread("MyPic.jpg",CV_LOAD_IMAGE_COLOR);

	if (img.empty()){
		cout <<"Error :: Image cannot be loaded.." <<endl;
		return -1;
	}

	vector<Mat> channels;
	Mat img_hist_equalized;

	cvtColor(img,img_hist_equalized,CV_BGR2YCrCb); //change color image from BGR to YCrCb format

	split(img_hist_equalized,channels); //split the image into channels

	equalizeHist(channels[0],channels[0]); //equalize histogram on the 1st channel (Y)

	merge(channels,img_hist_equalized); //merge 3 channels including the modified 1st channel into one image

	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); // to display image properly


	namedWindow("Original Image",CV_WINDOW_NORMAL);
	namedWindow("Hist Equal",CV_WINDOW_NORMAL);

	imshow("Original Image",img);
	imshow("Hist Equal",img_hist_equalized);

	waitKey(0);

	destroyAllWindows();

	return 0;
}