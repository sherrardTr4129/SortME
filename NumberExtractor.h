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

using namespace std;
using namespace cv;

class NumberExtractor
{
    public: 
        Mat GetBlockFace(Mat frame);
        int NumberExtract(Mat blockFace, vector<Mat> imageList);
};
