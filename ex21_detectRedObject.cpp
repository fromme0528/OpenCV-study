
/*

Simple Example of Detecting a Red Object

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex21(){

	VideoCapture cap("RedObject.mp4");

	if(!cap.isOpened()){
		cout << "Error : Cannot open the video file.."<<endl;
		return -1;
	}
	const char* ControlledWindowname = "Control";
	namedWindow(ControlledWindowname, CV_WINDOW_AUTOSIZE);

	namedWindow("Thresholded Image",CV_WINDOW_AUTOSIZE);
	namedWindow("Original",CV_WINDOW_AUTOSIZE);

	int iLowH = 0;
	int iHighH= 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	int iAngle = 180;

	cvCreateTrackbar("LowH",ControlledWindowname,&iLowH,179);
	cvCreateTrackbar("HighH",ControlledWindowname,&iHighH,179);

	cvCreateTrackbar("LowS",ControlledWindowname,&iLowS,255);
	cvCreateTrackbar("HighS",ControlledWindowname,&iHighS,255);

	cvCreateTrackbar("LowV",ControlledWindowname,&iLowV,255);
	cvCreateTrackbar("HighV",ControlledWindowname,&iHighV,255);

	while (true){

		Mat matOriginalFrame;

		bool bSuccess = cap.read(matOriginalFrame);
		if (!bSuccess){
			cout << "Error : Cannot read the frame from video file.."<<endl;
			break;
		}

		Mat imgHSV;

		cvtColor(matOriginalFrame, imgHSV,COLOR_BGR2HSV);

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS, iHighV),imgThresholded); //threshhold the image

		//morphological opening(remove small objects from the foreground
		erode (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		dilate (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

		dilate (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		erode (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

		imshow("Thresholded Image", imgThresholded);
		imshow("Original",matOriginalFrame);
		
		if (waitKey(30) == 27){
			cout <<"ESC key is pressed by user"<<endl;
			break;
		}
	}

	return 0;
}

