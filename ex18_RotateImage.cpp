
/*

Rotate Image

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int ex18(){

	Mat imgOriginal = imread("testimage.jpg",1);

	if(!imgOriginal.data){
		cout << "Error : image cannot be loaded.."<<endl;
		return -1;
	}

	const char* pzOriginalImage = "Original Image";
	namedWindow(pzOriginalImage, CV_WINDOW_AUTOSIZE);
	imshow(pzOriginalImage,imgOriginal);

	const char* pzRotateImage = "Rotate Image";
	namedWindow(pzRotateImage, CV_WINDOW_AUTOSIZE);

	int iAngle= 180;
	createTrackbar("Angle",pzRotateImage,&iAngle,360);

	int iImageHeight = imgOriginal.rows/2;
	int iImageWidth = imgOriginal.cols/2;

	while (true){
		Mat matRotation = getRotationMatrix2D( Point(iImageWidth, iImageHeight),(iAngle-180), 1);

		Mat imgRotated;
		warpAffine(imgOriginal,imgRotated,matRotation,imgOriginal.size());

		imshow(pzRotateImage,imgRotated);

		int iRet=waitKey(30);
		if(iRet == 27){
			break;
		}

	}

	return 0;

}

