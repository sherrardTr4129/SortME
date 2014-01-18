//author: Trevor Sherrard
//project: SortME
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

#include "NumberExtractor.h"

using namespace std;
using namespace cv;


/**
* \fn NumberExtractor::GetBlockFace(cv::Mat frame)
* \brief getblockface() looks for square in the frame provided .
* \param Mat frame, the mat containing the sqaure block frame
* \return a Mat containing only the square face of the block.
*/
Mat NumberExtractor::GetBlockFace(Mat frame){
    Rect rect;
    Mat pyr, timg, gray0(frame.size(), CV_8U), gray;
    vector<vector<Point> > contours;
    pyrDown(frame, pyr, Size(frame.cols/2, frame.rows/2));
    pyrUp(pyr, timg, frame.size());
    Canny(timg, gray, 0, 50, 5);
    dilate(gray, gray, Mat(), Point(-1,-1));
    findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    vector<Point> approx;
    for( size_t i = 0; i < contours.size(); i++ )
    {
         approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                
          // square contours should have 4 vertices after approximation
         if( approx.size() == 4 && fabs(contourArea(Mat(approx))) > 4000 &&
             isContourConvex(Mat(approx)) && fabs(contourArea(Mat(approx))) < 30000 )
         {
		
              //find rectangle dimensions of contours    
              rect = boundingRect(contours[i]);
	 }
    }
    Mat blockFaceTemp = frame(rect);
    Mat blockFace;
    blockFaceTemp.copyTo(blockFace);
    return blockFace;
}

enum block {BlOCK0 = 0, BlOCK1 = 1 ,BlOCK2 = 2 ,BlOCK3 = 3 ,BlOCK4 = 4, 
BlOCK5 = 5 ,BlOCK6 = 6 ,BlOCK7 = 7,BlOCK8 = 8 ,BlOCK9 = 9 };


/**
* \fn NumberExtractor::NumberExtract(cv::Mat blockFace, std::vector<cv::Mat> imageList)
* \brief NumberExtract() extracts the number from the block face useing SURF descriptors from the provided imageList
* \param the mat containing only the block face.
  \param a list of images containg .jpg's of the blocks faces
* \return the int containing the number on the block 
*/
int NumberExtractor::NumberExtract(Mat blockFace, vector<Mat> imageList)
{
    int FoundNumber = 0;
    SurfFeatureDetector detector( 400 );	
    vector<KeyPoint> keypointsBlockFace, keypointsNumber;
    for(int i = 0; i < imageList.size(); i++)
    {
		
         //calculate features for the block face and each number
         detector.detect(blockFace, keypointsBlockFace);
         detector.detect(imageList[i], keypointsNumber);
         //calculate desriptors
         SurfDescriptorExtractor extractor;

         Mat descriptorsBlockFace, descriptorsNumber;

         extractor.compute( blockFace, keypointsBlockFace, descriptorsBlockFace );
	 extractor.compute( imageList[i], keypointsNumber, descriptorsNumber );
 	 //match desriptor vectors using FLANN matcher
	 FlannBasedMatcher matcher;
	 vector< DMatch > matches;
	 matcher.match( descriptorsNumber, descriptorsBlockFace, matches );
         double minDist = 100; 
         double maxDist = 0;

	 //calculate min and max distances for keeping matches
	 for( int i = 0; i < descriptorsNumber.rows; i++ )
         { 
            double dist = matches[i].distance;
	    if( dist < minDist ) minDist = dist;
	    if( dist > maxDist ) maxDist = dist;
         }
          
         //only keep good matches
         vector< DMatch > goodMatches;
         for( int i = 0; i < descriptorsNumber.rows; i++ )
         { 
            if( matches[i].distance < 3*minDist )
	    { 
		return FoundNumber; 
            }
	 }
    }
}

