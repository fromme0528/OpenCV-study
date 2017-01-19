/*

Convex Hull Example
The performance varies depending on the picture...

*/


#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src40, src_gray40;
int thresh40 = 100;
int max_thrash40 = 255;
RNG rng40(12345);


void ex40_callback(int, void*);

/**
 * @function main
 */
int ex40()
{

  /// Load source image and convert it to gray
  src40 = imread( "Back_Projection_Theory2.jpg", 1);
  cvtColor( src40, src_gray40, COLOR_BGR2GRAY );
  blur(src_gray40,src_gray40, Size(3,3));

  //Create Window
  char* source_window = "Source";
  namedWindow(source_window, WINDOW_AUTOSIZE);
  imshow(source_window, src40);

  createTrackbar("Threshold :", "Source", &thresh40, max_thrash40, ex40_callback);
  ex40_callback(0,0);

  waitKey(0);
  return(0);
}

void ex40_callback(int, void*){
	Mat src_copy = src40.clone();
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Detect edges usin gThreshold
	threshold(src_gray40,threshold_output, thresh40, 255, THRESH_BINARY);

	//Find contours
	findContours(threshold_output,contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

	//Find the convex hull object for each contour
	vector<vector<Point>> hull (contours.size());
	for(int i=0; i<contours.size(); i++){
		convexHull(Mat(contours[i]),hull[i],false);
	}

	//Drow contours and hull results
	Mat drawing = Mat::zeros(threshold_output.size(),CV_8UC3);
	for (int i= 0; i<contours.size(); i++){

		Scalar color = Scalar(rng40.uniform(0,255), rng40.uniform(0,255), rng40.uniform(0,255));
		drawContours(drawing, contours, i, color, 1,8,vector<Vec4i>(),0,Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(),0,Point());

	}

	namedWindow("Hull demo",WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);

}