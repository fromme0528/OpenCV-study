/*

Ex04 : Capture Video From Camera
You need connected camera whose device number is 0!

*/

#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex04(){

	VideoCapture cap(0); //open the video camera no.0

	if (!cap.isOpened()){

		cout <<"Cannot open the video"<<endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size : " <<dWidth <<"x"<<dHeight <<endl;

	namedWindow("MyVideo",CV_WINDOW_NORMAL);
	
	while(1){

		Mat frame;
		bool bSuccess = cap.read(frame);

		if(!bSuccess){
			cout << "Cannot read the frame from video file"<<endl;

			break;
		}

		imshow("MyVideo", frame);
		if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl; 
			break; 
		}
	}
	return 0;
}
