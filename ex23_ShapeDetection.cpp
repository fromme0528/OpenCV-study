#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;


int ex23(){

	int cTriangles = 0, cSquares = 0, cHeptagons = 0;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	Mat img = imread("FindingContours.png");

	namedWindow("Imagen Original",CV_WINDOW_AUTOSIZE);
	imshow("Imagen Original",img);

	// Converion de imagen original a escala de grises
	Mat imgGray;
	cvtColor(img,imgGray,CV_RGB2GRAY);

	// Umbralado imagen gris
	threshold(imgGray, imgGray, 128, 255, CV_THRESH_BINARY);

	//vector contornos; // Crea vector para guardar area de todos los contornos
	findContours(imgGray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	contours.resize(contours.size());

	for (size_t k = 0; k < contours.size(); k++)
	{
		approxPolyDP(Mat(contours[k]), contours[k], 5, true);
		//drawContours(img, contours, k, Scalar(0, 255, 0), 2, CV_AA, hierarchy, abs(1));
		if (contours[k].size() == 3){
			++cTriangles;
			drawContours(img, contours, k, Scalar(255, 0, 0), 2, CV_AA, hierarchy, abs(1));
		}
		else if (contours[k].size() == 4){
			++cSquares;
			drawContours(img, contours, k, Scalar(0, 255, 0), 2, CV_AA, hierarchy, abs(1));
		}
		else if (contours[k].size() == 7){
			++cHeptagons;
			drawContours(img, contours, k, Scalar(0, 0, 255), 2, CV_AA, hierarchy, abs(1));
		}
	}

	cout << "There are " << cTriangles << " Triangles, " << cSquares << " squares and " << cHeptagons << " Heptagons." << endl;

	imshow("contours", img);
	waitKey(0);

	return 0;
}