
/*

Tracking Red Objects

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex22(){

	VideoCapture cap("RedObject.mp4");

	if(!cap.isOpened()){
		cout << "Error : Cannot open the video file.."<<endl;
		return -1;
	}

	const char* ControlledWindowname = "Control";
	namedWindow(ControlledWindowname, CV_WINDOW_AUTOSIZE);

	namedWindow("Thresholded Image",CV_WINDOW_AUTOSIZE);
	namedWindow("Original",CV_WINDOW_AUTOSIZE);

	int iLowH = 170;
	int iHighH= 179;

	int iLowS = 150;
	int iHighS = 255;

	int iLowV = 60;
	int iHighV = 255;

	cvCreateTrackbar("LowH",ControlledWindowname,&iLowH,179);
	cvCreateTrackbar("HighH",ControlledWindowname,&iHighH,179);

	cvCreateTrackbar("LowS",ControlledWindowname,&iLowS,255);
	cvCreateTrackbar("HighS",ControlledWindowname,&iHighS,255);

	cvCreateTrackbar("LowV",ControlledWindowname,&iLowV,255);
	cvCreateTrackbar("HighV",ControlledWindowname,&iHighV,255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);
	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(),CV_8UC3);

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

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		 // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dArea > 10000){

			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;
			
			if(iLastX >= 0 && iLastX>=0 && posX>=0 && posY >=0){
				//Draw a red line from the previous point to the current point
				line(imgLines,Point(posX,posY),Point(iLastX,iLastY),Scalar(0,0,255),2);
			}
			iLastX = posX;
			iLastY = posY;
		}

		imshow("Thresholded Image", imgThresholded);

		matOriginalFrame = matOriginalFrame + imgLines;
		imshow("Original",matOriginalFrame);
		
		if (waitKey(30) == 27){
			cout <<"ESC key is pressed by user"<<endl;
			break;
		}
	}

	return 0;
}

