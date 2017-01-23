/*
Feture Detector , Descriptor : SIFT, SURF
Matcher : FlannBasedMatcher
DescriptorMathcer::knnmatch
*/

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex50(){

	
	Mat src1 = imread("book1.jpg",IMREAD_GRAYSCALE);
	Mat src2 = imread("book2.jpg",IMREAD_GRAYSCALE);
	
	if(src1.empty() || src2.empty()){
		cout << "Cannot read imgs"<<endl;
		return -1;
	}

	/* Detect KeyPoints */
	vector<KeyPoint> keypoints1,keypoints2;
	
	SiftFeatureDetector detector(500,5);//SIFT
	//SurfFeatureDetector detector(400);//SURF
	detector.detect(src1,keypoints1);
	detector.detect(src2,keypoints2);

	//Calulate descriptors
	Mat descriptor1, descriptor2;
	SiftDescriptorExtractor extractor;
	//SurfDescriptorExtractor extractor;

	extractor.compute(src1,keypoints1,descriptor1);
	extractor.compute(src2,keypoints2,descriptor2);	
	//Matching descriptor vectors;
	vector<vector<DMatch>> matches;
	
	int k = 2;
	float maxDist = 0.5;
	FlannBasedMatcher matcher;
	matcher.knnMatch(descriptor1,descriptor2,matches,k);
	cout <<"matches.size()="<<matches.size()<<endl;

	vector<DMatch> goodMatches;
	float nndrRatio = 0.6f;
	for (int i = 0; i<matches.size(); i++){
		if(matches.at(i).size() == 2 && matches.at(i).at(0).distance <= nndrRatio * matches.at(i).at(1).distance){
			goodMatches.push_back(matches[i][0]);
		}
	}

	cout <<"goodMatches.size()="<<goodMatches.size()<<endl;

	//draw good_matches
	Mat imgMatches;
	drawMatches(src1,keypoints1, src2, keypoints2, goodMatches,imgMatches, Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//find Homography between keypoints1, keypoints2
	vector<Point2f> obj;
	vector<Point2f> scene;

	for (int i =0 ; i<goodMatches.size(); i++){
		//Get the keypoints from the good matches
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj,scene, CV_RANSAC);


	vector<Point2f> objP(4);
	objP[0] = cvPoint(0,0);
	objP[1] = cvPoint(src1.cols,0);
	objP[2] = cvPoint(src1.cols,src1.rows);
	objP[3] = cvPoint(0,src1.rows);

	vector<Point2f> sceneP(4);
	perspectiveTransform(objP,sceneP,H);

	//draw sceneP in imgMatches
	for (int i = 0; i<4; i++){
		sceneP[i] += Point2f(src1.cols,0);
	}
	for (int i = 0; i<4; i++){
		line(imgMatches,sceneP[i],sceneP[(i+1)%4],Scalar(255,0,0),4);
	}
	imshow("imgMatches",imgMatches);

	waitKey(0);

	return 0;
}
