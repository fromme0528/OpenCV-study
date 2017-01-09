/*
When running this program, the image of 'MyPic.JPG' is loaded into the variable, 'img' of type Mat. 
Then a window named 'MyWindow' is opened. After that  'img' is loaded to that window.
The window with the image will be displayed until any key is pressed.
*/


#include <iostream>
#include "opencv2\highgui\highgui.hpp"

using namespace cv;
using namespace std;

int ex01(){

	Mat img = imread("C:\\Users\\user\\Pictures\\testpic.jpg", CV_LOAD_IMAGE_COLOR);

	if (img.empty()){
		cout <<"Error : image cannot be loaded" << endl;
		return -1;
	}

	namedWindow("MyWindow",CV_WINDOW_NORMAL);
	imshow("MyWindow",img);

	waitKey(0);//milisecond

	destroyWindow("MyWindow");
	return 0;
}
