
/*

Bac Projection

 * @author OpenCV team
*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat src38, hsv38, hue38;
int bins38 = 25;

void Hist_and_Backproj38(int, void*);

int ex38
	(){

	src38 = imread("Back_Projection_Theory2.jpg");
	if(!src38.data){
		cout << "no image"<<endl;
		return -1;

	}
	cvtColor(src38,hsv38, COLOR_BGR2HSV);

	//Use only the Hue value
	hue38.create(hsv38.size(),hsv38.depth());
	int ch[] = {0,0};
	mixChannels(&hsv38,1,&hue38,1,ch,1);

	//Create Trackbar to enter the number of bins;
	char* window_image = "Source image";
	namedWindow(window_image,WINDOW_AUTOSIZE);
	createTrackbar("* Hue bins: ", window_image, &bins38, 180, Hist_and_Backproj38); 
	Hist_and_Backproj38(0,0);

	imshow(window_image, src38);

	waitKey(0);

	return 0;
}

//Callback
void Hist_and_Backproj38(int, void*){

	MatND hist;
	int histSize = MAX(bins38,2);
	float hue_range[] = {0,180};
	const float* ranges = {hue_range};

	//Get the Histogram and normalize it
	calcHist(&hue38, 1,0,Mat(),hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	// Get Backprojection
	MatND backproj;
	calcBackProject( &hue38, 1, 0 ,hist, backproj, &ranges, 1, true);

	imshow("BackProj", backproj);

	int w = 400; int h = 400;
	int bin_w = cvRound((double) w/ histSize);
	Mat histImg = Mat::zeros(w,h,CV_8UC3);

	for( int i =0; i<bins38; i++){
		rectangle (histImg, Point (i*bin_w, h ), Point( (i+1)* bin_w, h- cvRound(hist.at<float>(i)*h/255.0)), Scalar(0,0,255), -1);
	}
	imshow("Histogram",histImg);
}