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
Mat src41, src_gray41;
int thresh41 = 100;
int max_thrash41 = 255;
RNG rng41(12345);


void ex41_callback(int, void*);

/**
 * @function main
 */
int ex41()
{

  /// Load source image and convert it to gray
  src41 = imread( "balloon.jpg", 1);
  cvtColor( src41, src_gray41, COLOR_BGR2GRAY );
  blur(src_gray41,src_gray41, Size(3,3));

  //Create Window
  char* source_window = "Source";
  namedWindow(source_window, WINDOW_AUTOSIZE);
  imshow(source_window, src41);

  createTrackbar("Threshold :", "Source", &thresh41, max_thrash41, ex41_callback);
  ex41_callback(0,0);

  waitKey(0);
  return(0);
}

void ex41_callback(int, void*){
	Mat src_copy = src41.clone();
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Detect edges usin gThreshold
	threshold(src_gray41,threshold_output, thresh41, 255, THRESH_BINARY);

	//Find contours
	findContours(threshold_output,contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

	//Approximate contours to polygons + get bounding rects and circles

	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect (contours.size());
	vector<Point2f> center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i<contours.size(); i++){
		approxPolyDP(Mat(contours[i]), contours_poly[i],3,true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i]);
	}


	//Drow polygonal contours + bounding rects + circles
	Mat drawing = Mat::zeros(threshold_output.size(),CV_8UC3);
	for (int i= 0; i<contours.size(); i++){

		Scalar color = Scalar(rng41.uniform(0,255), rng41.uniform(0,255), rng41.uniform(0,255));
		drawContours(drawing, contours_poly, i, color, 1,8,vector<Vec4i>(),0,Point());
		rectangle(drawing, boundRect[i].tl(),boundRect[i].br(), color, 2,8,0);
		circle(drawing,center[i],(int)radius[i],color,2,8,0);

	}

	namedWindow("Contours",WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

}