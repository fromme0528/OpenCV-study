
/*

Hough Circle Transform

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;

int ex33(){

	Mat src, src_gray;
	//Load an image
	src = imread("houghline.jpg");

	if (!src.data){
		return -1;
	}

	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	//you can shange kernel size
	GaussianBlur(src_gray,src_gray,Size(9,9),2,2);

	vector<Vec3f> circles;

	HoughCircles(src_gray,circles,CV_HOUGH_GRADIENT, 1, src_gray.rows/8,200,100,0,0);

	for (size_t i = 0; i<circles.size(); i++){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(src,center,3,Scalar (0,255,0),-1,8,0);
		circle(src,center,radius,Scalar(0,0,255),3,8,0);
	}

	namedWindow("Hough Circle Transform Demo",WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo",src);

	waitKey(0);
	return 0;
}

