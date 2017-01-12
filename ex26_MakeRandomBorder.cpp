
/*

Adding borders to image using copyMakeBorder function

*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int ex26(){

	Mat src, dst;
	int top, bottom, left, right;
	int borderType;
	Scalar value;
	char* window_name = "copyMakeBorder Demo";
	RNG rng(12345);

	int c;

	//Load an image
	src = imread("testimage.jpg");

	if (!src.data){
		return -1;
	}

	//Brief how-to
	printf( "\n \t copyMakeBorder Demo: \n" );
	printf( "\t -------------------- \n" );
	printf( " ** Press 'c' to set the border to a random constant value \n");
	printf( " ** Press 'r' to set the border to be replicated \n");
	printf( " ** Press 'ESC' to exit the program \n");
	
	namedWindow(window_name,CV_WINDOW_AUTOSIZE);

	top = (int) (0.05*src.rows); bottom = (int) (0.05*src.rows);
	left = (int) (0.05 * src.cols); right = (int) (0.05 * src.cols);

	dst = src;
	imshow(window_name,dst);


	while(true){


		c= waitKey(500);
		if ( c== 28){
			break;
		}else if((char)c =='c'){
			borderType = BORDER_CONSTANT;
		}else if ((char)c == 'r')
		{
			borderType = BORDER_REPLICATE;
		}

		value = Scalar( rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);

		imshow( window_name, dst);
	}
	return 0;
}

