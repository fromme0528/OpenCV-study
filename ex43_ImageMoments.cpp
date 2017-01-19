/*

Image Moments

*/


#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src43, src_gray43;
int thresh43 = 100;
int max_thrash43 = 255;
RNG rng43(12345);


void ex43_callback(int, void*);

/**
 * @function main
 */
int ex43()
{

  /// Load source image and convert it to gray
  src43 = imread( "balloon.jpg", 1);
  if(!src43.data){
	  return -1;
  }
  cvtColor( src43, src_gray43, COLOR_BGR2GRAY );
  blur(src_gray43,src_gray43, Size(3,3));

  //Create Window
  char* source_window = "Source";
  namedWindow(source_window, WINDOW_AUTOSIZE);
  imshow(source_window, src43);
  createTrackbar("Canny Threshold :", "Source", &thresh43, max_thrash43, ex43_callback);
  ex43_callback(0,0);

  waitKey(0);
  return(0);
}

void ex43_callback(int, void*){

	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Detect edges usin Canny
	Canny(src_gray43,canny_output, thresh43, thresh43*2,3);
	//Find contours
	findContours(canny_output,contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
	//Get the moments
	vector<Moments> mu(contours.size());
	for (int i =0; i<contours.size(); i++){
		mu[i] = moments(contours[i],false);
	}
	//get the mass centers;
	vector<Point2f>mc(contours.size());
	for(int i=0; i<contours.size(); i++){
		mc[i] = Point2f(mu[i].m10 / mu[1].m00 , mu[1].m01 / mu[i].m00);
	}
	//Draw contours
	Mat drawing = Mat::zeros(canny_output.size(),CV_8UC3);
	for (int i= 0; i<contours.size(); i++){

		Scalar color = Scalar(rng43.uniform(0,255), rng43.uniform(0,255), rng43.uniform(0,255));
		//contour
		drawContours(drawing, contours, i, color, 2,8,hierarchy,0,Point());
		circle(drawing,mc[i],4,color,-1,8,0);
	}
	namedWindow("Contours",WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	//Calculate the area with moments 00 and compare with the result of the OpenCV function
	cout<< "\t Info: Area and Contour Lenght"<<endl;
	for (int i =0; i<contours.size();i++){
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
		Scalar color = Scalar(rng43.uniform(0,255), rng43.uniform(0,255), rng43.uniform(0,255));
		drawContours(drawing, contours, i, color, 2,8,hierarchy,0,Point());
		circle(drawing,mc[i],4,color,-1,8,0);
	}

}