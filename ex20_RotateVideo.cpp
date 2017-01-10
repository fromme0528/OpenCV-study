
/*

Rotate a Video

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex20(){

	VideoCapture cap("BesideMe.mp4");

	if(!cap.isOpened()){
		cout << "Error : Cannot open the video file.."<<endl;
		return -1;
	}

	const char* pzOriginalWindowName = "Origianl Video";
	namedWindow(pzOriginalWindowName, CV_WINDOW_AUTOSIZE);

	const char* pzRotatingWindowName = "Rotated Video";
	namedWindow(pzRotatingWindowName, CV_WINDOW_AUTOSIZE);

	int iAngle = 180;
	createTrackbar("Angle",pzRotatingWindowName,&iAngle,360);

	while (true){

		Mat matOriginalFrame;

		bool bSuccess = cap.read(matOriginalFrame);
		if (!bSuccess){
			cout << "Error : Cannot read the frame from video file.."<<endl;
			break;
		}

		imshow(pzOriginalWindowName,matOriginalFrame);

		Mat matRotation = getRotationMatrix2D(Point(matOriginalFrame.cols/2,matOriginalFrame.rows/2),(iAngle-180),1);

		Mat matRotatedFrame;

		warpAffine(matOriginalFrame, matRotatedFrame,matRotation, matOriginalFrame.size());

		imshow(pzRotatingWindowName,matRotatedFrame);

		if (waitKey(30) == 27){
			cout <<"ESC key is pressed by user"<<endl;
			break;
		}
	}

	return 0;
}

