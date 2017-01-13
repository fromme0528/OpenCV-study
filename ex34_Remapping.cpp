
/*

Remapping
 * @author OpenCV team
*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src34, dst34;
//Mapping function in x, y direction
Mat map_x34, map_y34;
char* remap_window = "Remap demo";
int ind = 0;

void update_map();


int ex34(){

	//Load an image
	src34 = imread("testimage.jpg");

	if (!src34.data){
		return -1;
	}

	dst34.create(src34.size(), src34.type());
	map_x34.create(src34.size(),CV_32FC1);
	map_y34.create(src34.size(),CV_32FC1);

	namedWindow(remap_window, WINDOW_AUTOSIZE);

	while (true){

		int c = waitKey(1000);

		if ((char) c == 27){
			break;
		}
		
		//Update map_x34 and map_y34. Then Apply it!
		update_map();
		remap(src34,dst34, map_x34, map_y34, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0));
		imshow(remap_window,dst34);

	}

	return 0;
}

void update_map(){


	ind = ind %4;

	for( int j = 0; j <src34.rows; j++){
		for (int i = 0; i<src34.cols; i++){

			switch(ind){

			case 0:
				if (i> src34.cols*0.25 && i < src34.cols*0.75 && j> src34.rows * 0.25 && j < src34.rows * 0.75){
					map_x34.at<float>(j,i) = 2*(i - src34.cols*0.25 ) + 0.5;
					map_y34.at<float>(j,i) = 2*(j - src34.rows*0.25 ) + 0.5;
				}
				else{
					map_x34.at<float>(j,i) = 0;
					map_y34.at<float>(j,i) = 0;
				}
				break;
			case 1:
				map_x34.at<float>(j,i) = i;
				map_y34.at<float>(j,i) = src34.rows - j;
				break;

			case 2:
				map_x34.at<float>(j,i) = src34.cols-i;
				map_y34.at<float>(j,i) = j;
				break;
				
			case 3:
				map_x34.at<float>(j,i) = src34.cols - i;
				map_y34.at<float>(j,i) = src34.rows-  j;
				break;
			}
		}
	}
	ind ++;

}