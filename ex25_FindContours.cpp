/**
 * @function findContours_Demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage, Mat& Result)
{

    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for(int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for(int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i]
                         -current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}

int ex25(){
	Mat img = imread("testimage.jpg");

	namedWindow("Imagen Original",CV_WINDOW_AUTOSIZE);
	imshow("Imagen Original",img);

	Mat sharpimg;

	Sharpen(img,sharpimg);
	namedWindow("Changed",CV_WINDOW_AUTOSIZE);
	imshow("Changed",sharpimg);

	waitKey(0);
	return 0;
}