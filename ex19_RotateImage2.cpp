
/*

Another Rotate Image

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int iAngle = 180;
int iScale = 50;
int iBorderMode = 0;
Mat imgOriginal;
int iImageCenterY = 0;
int iImageCenterX = 0;
const char* pzRotatedImage = "Rotated Image";

void CallBackForTrackBar(int, void*){

	Mat matRotation = getRotationMatrix2D( Point(iImageCenterX, iImageCenterY), (iAngle-180),iScale/50.0);

	Mat imgRotated;
	warpAffine(imgOriginal, imgRotated, matRotation, imgOriginal.size(), INTER_LINEAR, iBorderMode, Scalar());

	imshow(pzRotatedImage, imgRotated);
}


int ex19(){

	imgOriginal = imread("testimage.jpg",1);

	if(!imgOriginal.data){
		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}

	iImageCenterX = imgOriginal.rows/2;
	iImageCenterY = imgOriginal.cols/2;

	const char* pzOriginalImage = "Original Image";
	namedWindow(pzOriginalImage, CV_WINDOW_AUTOSIZE);
	imshow(pzOriginalImage,imgOriginal);

	namedWindow(pzRotatedImage, CV_WINDOW_AUTOSIZE);
	createTrackbar("Angle",pzRotatedImage, &iAngle, 360, CallBackForTrackBar);
	createTrackbar("Scale",pzRotatedImage, &iScale, 100, CallBackForTrackBar);
	createTrackbar("Border Mode",pzRotatedImage, &iBorderMode, 5, CallBackForTrackBar);

	int iDummy = 0;

	CallBackForTrackBar(iDummy, &iDummy);
	waitKey(0);

	return 0;

}

