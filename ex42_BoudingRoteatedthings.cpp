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
Mat src42, src_gray42;
int thresh42 = 100;
int max_thrash42 = 255;
RNG rng42(12345);


void ex42_callback(int, void*);

/**
 * @function main
 */
int ex42()
{

  /// Load source image and convert it to gray
  src42 = imread( "balloon.jpg", 1);
  cvtColor( src42, src_gray42, COLOR_BGR2GRAY );
  blur(src_gray42,src_gray42, Size(3,3));

  //Create Window
  char* source_window = "Source";
  namedWindow(source_window, WINDOW_AUTOSIZE);
  imshow(source_window, src42);

  createTrackbar("Threshold :", "Source", &thresh42, max_thrash42, ex42_callback);
  ex42_callback(0,0);

  waitKey(0);
  return(0);
}

void ex42_callback(int, void*){

	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Detect edges usin gThreshold
	threshold(src_gray42,threshold_output, thresh42, 255, THRESH_BINARY);

	//Find contours
	findContours(threshold_output,contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

	//find the rotated rectangles anellipses for each contour
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());

	for (int i = 0; i<contours.size(); i++){
		minRect[i] = minAreaRect( Mat(contours[i]));
		if(contours[i].size()>5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}

	//contours[i].size()가 5보다 작으면, 아래 포문에서 에러나지 않나?



	//Drow polygonal contours + bounding rects + circles
	Mat drawing = Mat::zeros(threshold_output.size(),CV_8UC3);
	for (int i= 0; i<contours.size(); i++){

		Scalar color = Scalar(rng42.uniform(0,255), rng42.uniform(0,255), rng42.uniform(0,255));
		//contour
		drawContours(drawing, contours, i, color, 1,8,vector<Vec4i>(),0,Point());
		//ellipse
		ellipse(drawing, minEllipse[i],color, 2,8);
		//rotated rectanglie
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		for(int j= 0;j<4; j++){
			line(drawing,rect_points[j],rect_points[(j+1)%4],color,1,8);
		}
	}

	namedWindow("Contours",WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

}