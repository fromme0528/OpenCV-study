/*
	SIFT detect
*/

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex47(){

	Mat srcImage = imread("balloon.jpg",IMREAD_GRAYSCALE);
	if(srcImage.empty()){
		return -1;
	}

	GaussianBlur(srcImage, srcImage, Size(5,5),0.0);
	
	vector<KeyPoint> keypoints;
	Mat descriptor;
	
	SIFT siftF(50,5);
	siftF.detect(srcImage,keypoints);
	cout<< "keypoints.size()="<<keypoints.size()<<endl;

	siftF.compute(srcImage,keypoints, descriptor);

	FileStorage fs("Keypoints.yml", FileStorage::WRITE);
	write(fs,"keypoints",keypoints);
	write(fs,"descriptors",descriptor);
	fs.release();

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage,keypoints,dstImage);

	KeyPoint element;
	for (int k =0 ; k<keypoints.size(); k++){
		element = keypoints[k];
		circle(dstImage,element.pt, cvRound(element.size/2), Scalar(0,0,255),2);
	}
	imshow("dstImage",dstImage);
	waitKey(0);

	return 0;
}
