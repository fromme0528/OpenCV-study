/*
	FAST(Features from Accelerated Segment Test

*/


#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2\calib3d.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;


int ex45(){

	Mat srcImage = imread("FindingContours.png",IMREAD_GRAYSCALE);
	if(srcImage.empty()){
		return -1;
	}

	GaussianBlur(srcImage, srcImage,Size(5,5), 0,0,4);
	
	vector<KeyPoint> keypoints;

	int type = FastFeatureDetector::TYPE_9_16;
	FASTX(srcImage,keypoints,10,true,type);
	FAST(srcImage, keypoints, 10, true);

	FastFeatureDetector fastF(10,true);
	fastF.detect(srcImage,keypoints);
	cout << "keypoints.size() = "<<keypoints.size()<<endl;

	KeyPointsFilter::removeDuplicated(keypoints);
	cout << "keypoints.size() = "<<keypoints.size()<<endl;

//	KeyPointsFilter::runByKeypointSize(keypoints,10);
//	cout << "keypoints.size() = "<<keypoints.size()<<endl;

//	KeyPointsFilter::retainBest(keypoints,10);
//	cout << "keypoints.size() = "<<keypoints.size()<<endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	
	KeyPoint element;
	for(int k = 0; k<keypoints.size(); k++){

		element = keypoints[k];
		cout << element.pt << "," <<element.response;
		cout << "," << element.angle << "," << element.size << "," << element.class_id << endl;
		circle ( dstImage, element.pt, cvRound(element.size/2), Scalar(0,0,255),2);

	}

	imshow("dstImage",dstImage);
	waitKey(0);


	return 0;
}
