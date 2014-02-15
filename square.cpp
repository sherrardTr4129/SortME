//author: Trevor Sherrard
//project: SortME

#include "square.h"
#include <opencv2/opencv.hpp>
using namespace cv;

Mat grey2;
float Distance;
Rect rect;

int thresh = 50, N = 11;
const char* wndname = "Trevor Sherrard Square Tracking ";

Point FinalPt;

//TODO more Docs.

// helper function:
// finds the center or gravity, and makes a cvPoint using 
// it's x and y cordinates.
// returns: cv::Point
Point square::findCenter(vector<Point>  contours)
{
	vector<Point> convex_hull;
	//what we will return
	Point result;
	
	// convex hull
	convexHull(contours, convex_hull, false);
	
	// center of gravity
	cv::Moments mo = cv::moments(convex_hull);
	result = cv::Point(mo.m10/mo.m00 , mo.m01/mo.m00);
	return result;
}
//helper function:
//finds the squares in the image
//
int square::findSquare( const Mat& image, vector<vector<Point> >& squares)
{
    squares.clear();
    
    int max_width = 0;
    int max_height = 0;
    int max_square_idx = 0;
    const int n_points = 4;
    
    Mat pyr, timg, gray0(image.size(), CV_8U), gray;
    
    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;
    vector<vector<Point> > Fincontours;
    
    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);
        
        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }
	
            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx; 


            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {


                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                
                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 4000 &&
                    isContourConvex(Mat(approx)) && fabs(contourArea(Mat(approx))) < 30000 )
                {
		
		    //find rectangle dimensions of contours    
		    rect = boundingRect(contours[i]);
        		
                    //find center point of rectangle	    
		    FinalPt = findCenter(contours[i]);
	            return FinalPt.x;

     
                }
            }
        }
    }
}


