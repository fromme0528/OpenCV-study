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

Mat src3; Mat src3_gray;
int thresh3 = 100;
int max_thresh3 = 255;
RNG rng2(12345);

/// Function header
void thresh_callback3(int, void* );

/**
 * @function main
 */
int ex24()
{
  /// Load source image
  src3 = imread("testimage.jpg", IMREAD_COLOR);
  if (src3.empty())
  {
    cerr << "No image supplied ..." << endl;
    return -1;
  }

  /// Convert image to gray and blur it
  cvtColor( src3, src3_gray, COLOR_BGR2GRAY );
  blur( src3_gray, src3_gray, Size(11,11) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src3 );

  createTrackbar( " Canny thresh:", "Source", &thresh3, max_thresh3, thresh_callback3 );
  thresh_callback3( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function thresh_callback
 */
void thresh_callback3(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src3_gray, canny_output, thresh3, thresh3*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng2.uniform(0, 255), rng2.uniform(0,255), rng2.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 2, 16, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );

}