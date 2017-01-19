
/*

Compare Histogram
 * @author OpenCV team
*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int ex37(){

	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
	Mat src_test2, hsv_test2;
	Mat hsv_half_down;


	//Load an image
	src_base = imread("cookie.jpg");
	src_test1 = imread("MyPic.jpg");
	src_test2 = imread("testimage.jpg");

	if (!src_base.data || !src_test1.data || !src_test2.data){
		return -1;
	}

	//convert to hsv
	cvtColor(src_base,hsv_base,COLOR_BGR2HSV);
	cvtColor(src_test1,hsv_test1,COLOR_BGR2HSV);
	cvtColor(src_test2,hsv_test2,COLOR_BGR2HSV);

	//Create an image of half the base image(in HSV format)
	hsv_half_down = hsv_base(Range(hsv_base.rows/2, hsv_base.rows-1), Range(0,hsv_base.cols - 1));

	//Using 50 bins for hue and 60 for for saturation
	int h_bins = 50; int s_bins = 60;
	int histSize[] = {h_bins , s_bins };

	//hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = {0,180};
	float s_ranges[] = {0,256};

	const float* ranges[] = {h_ranges,s_ranges};

	//Use the channel 0, 1
	int channels[] = {0,1};

	//Histogram
	MatND hist_base;
	MatND hist_half_down;
	MatND hist_test1;
	MatND hist_test2;

	//Calculate the histograms for the HSV images
	calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0,1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
	normalize(hist_half_down, hist_half_down, 0,1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	normalize(hist_test1, hist_test1, 0,1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
	normalize(hist_test2, hist_test2, 0,1, NORM_MINMAX, -1, Mat());

	for( int i =0; i<4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(hist_base, hist_base, compare_method);
		double base_half = compareHist(hist_base, hist_half_down, compare_method);
		double base_test1 = compareHist(hist_base, hist_test1, compare_method);
		double base_test2 = compareHist(hist_base, hist_test2, compare_method);

		printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
	}
	printf("Done \n");

	return 0;
}