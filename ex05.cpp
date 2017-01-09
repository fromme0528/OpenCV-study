/*

Ex05 : Write Image to File
This program creates an yellowish image ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50,000, 50,000) assigned for BGR channels). 
Because the image has 16 bit depth, you can use values between 0 and 65535 for each element in each channel. 
I have used 50,000 for each element in the green and red planes which gives the yellowish color. 
You can try different values. Then it specifies the compressing technique. I have used JPEG as the compression technique in the above example. 
Then it saves the image in the "D:/TestImage.jpg" location. 
Then it displays the newly created image in a window and wait indefinitely until an user presses a key.
*/

#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex05(){

	Mat img(650,600,CV_16UC3,Scalar(0,50000,50000));

	if (img.empty()){
		cout <<"ERROR : Image cannot be loaded"<<endl;
		return -1;
	}

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(98);

	bool bSuccess = imwrite("C:\\MyPic.jpg",img,compression_params);

	if(!bSuccess){
		cout << "Cannot read the image file"<<endl;
	}

	namedWindow("MyWindow",CV_WINDOW_NORMAL);
	imshow("MyWindow",img);

	waitKey(0);

	destroyWindow("MyWindow");
	return 0;


}
