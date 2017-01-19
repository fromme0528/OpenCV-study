
/*

Bac Projection2

 * @author OpenCV team
*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat src39, hsv39, mask39;

int lo = 20; int up = 20;
const char* window_image = "Source image";

void Hist_and_Backproj2();
void pickPoint(int event, int  x, int y, int, void*);

int ex39(){

	src39 = imread("Back_Projection_Theory2.jpg",IMREAD_COLOR);
	if(!src39.data){
		cout << "no image"<<endl;
		return -1;
	}

	cvtColor(src39,hsv39, COLOR_BGR2HSV);

	namedWindow(window_image, WINDOW_AUTOSIZE);
	imshow(window_image, src39);

	//
	createTrackbar("Low Thresh",window_image, &lo,255,0);
	createTrackbar("High Thresh",window_image, &up, 255, 0);

	//
	setMouseCallback(window_image, pickPoint,0);

	waitKey(0);
	return 0;
}

void pickPoint(int event, int x, int y, int, void*){

	if(event!= EVENT_LBUTTONDOWN){
		return;
	}

	Point seed  = Point(x,y);

	int newMaskVal = 255;
	Scalar newVal = Scalar (120,120,120);

	int connectivity = 8;
	//?
	int flags = connectivity + (newMaskVal<<8) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	Mat mask2 = Mat::zeros(src39.rows+2,src39.cols+2,CV_8UC1);
	floodFill( src39, mask2, seed, newVal, 0, Scalar(lo,lo,lo), Scalar(up,up,up),flags);
	mask39 = mask2(Range(1,mask2.rows -1), Range(1,mask2.cols-1));

	imshow("Mask",mask39);

	Hist_and_Backproj2();
}

void Hist_and_Backproj2(){
	MatND hist;
	int h_bins= 30, s_bins =32;
	int histSize[] = {h_bins, s_bins};

	float h_range[] = {0,179};
	float s_range[] = {0,255};
	const float* ranges[] = {h_range, s_range};

	int channels[] = {0,1};

	calcHist(&hsv39, 1, channels, mask39, hist, 2, histSize, ranges, true, false);

	normalize(hist,hist,0,255,NORM_MINMAX, -1, Mat());

	MatND backproj;
	calcBackProject(&hsv39,1,channels,hist, backproj, ranges, 1, true);

	imshow("backproj",backproj);

}


