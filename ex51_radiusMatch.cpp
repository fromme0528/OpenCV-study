/*
Feture Detector , Descriptor : SIFT, SURF
Matcher : FlannBasedMatcher
DescriptorMathcer::radiuxMatch
*/

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex51(){

	
	Mat src1 = imread("book1.jpg",IMREAD_GRAYSCALE);
	Mat src2 = imread("book2.jpg",IMREAD_GRAYSCALE);
	
	if(src1.empty() || src2.empty()){
		cout << "Cannot read imgs"<<endl;
		return -1;
	}

	/* Detect KeyPoints */
	vector<KeyPoint> keypoints1,keypoints2;
	
	SurfFeatureDetector detector(400);//SURF
	detector.detect(src1,keypoints1);
	detector.detect(src2,keypoints2);
	KeyPointsFilter::retainBest(keypoints1,10);

	//Calulate descriptors
	Mat descriptor1, descriptor2;
	SurfDescriptorExtractor extractor;

	extractor.compute(src1,keypoints1,descriptor1);
	extractor.compute(src2,keypoints2,descriptor2);	
	
	//Matching descriptor vectors;
	vector<vector<DMatch>> matches;
	
	float maxDist = 0.5;
	FlannBasedMatcher matcher;
	matcher.radiusMatch(descriptor1,descriptor2,matches,maxDist);
	cout <<"matches.size()="<<matches.size()<<endl;

	vector<DMatch> goodMatches;
	for (int i = 0; i<matches.size(); i++){


		goodMatches.clear();
		cout <<"matches["<<i<<"].size()="<<matches[i].size()<<endl;
		for (int j = 0 ; j<matches[i].size();j++){
			goodMatches.push_back(matches[i][j]);
		}

		cout <<"goodMatches.size()="<<goodMatches.size()<<endl;

		//draw good_matches
		Mat imgMatches;
		drawMatches(src1,keypoints1, src2, keypoints2, goodMatches,imgMatches, Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		Point ptCenter1, ptCenter2;
		if(matches[i].size()>0){
			ptCenter1 = keypoints2[matches[i][0].trainIdx].pt;
			ptCenter1 += Point(src1.cols,0);
			circle(imgMatches,ptCenter1, 5,Scalar(0,255,255),2);
		}
		if(matches[i].size()>1){
			ptCenter2 = keypoints2[matches[i][1].trainIdx].pt;
			ptCenter2 += Point(src1.cols,0);
			circle(imgMatches,ptCenter2, 5,Scalar(0,255,255),2);
		}
		imshow("Good Matches",imgMatches);
		waitKey();
	}


	return 0;
}
