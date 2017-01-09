/*

Ex03
At first, this program captures a video from a file. 
Then the program enters into a infinite loop. 
In that loop, it grabs frames from the captured video sequentially, decodes it, shows it in a window and waits for 30 milliseconds. 
If the video file has no more frames or if the user presses the 'esc' key, the program will break the infinite loop.

*/

#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex03(){

	VideoCapture cap("C:\\BesideMe.mp4");

	if (!cap.isOpened()){

		cout <<"Cannot open the video"<<endl;
		return -1;
	}

	cap.set(CV_CAP_PROP_POS_MSEC,1000*60*3);

	double fps = cap.get(CV_CAP_PROP_FPS);
	
	cout << "Frame per seconds :" <<fps <<endl;

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
