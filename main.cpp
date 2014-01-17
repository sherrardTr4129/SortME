//Author: Trevor Sherrard
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
#include "RobotServer.h"

//TODO add user input. more funtion calls to more vision operations


void printUsage(const char* programName)
{
    cout << "Usage: " << programName << " [options]"
         << endl
         << endl
         << "Options:\n"
         << endl
         << "\t-t TASK       specifies the vision task to be performed"
         << "\t-c CAMID      specifies the camera ID"
         << "\t-h HELP       prints this help message;
}


int main(int argc, char** argv)
{

    int camID = 0;
    if (console::find_argument(argc, argv, "-h") >= 0)
    {
        printUsage(argv[0]);
        return 0;
    }
    if (console::find_argument(argc, argv, "-c") >= 0)
    {
        camID = atoi(argv[0]);
    }
   
    RobotServer server;
    NumberExtractor extract;
    VideoCapture cap;

    cap.open(camID);
    Mat frame;
    vector<Mat> imageList;
    for(int i = 0; i <=9; i++)
    {
        stringstream stream;
        stream << i << ".jpg";
        string filename = stream.str();
        imageList.push_back(imread(filename));
    }

    if(!cap.isOpened())
    {
	std::cout<< " could not open cam!" << std::endl; return -1;
    }
    while(cap.isOpened())
    {
       if(!cap.isOpened())
       {
          std::cout<< " could not open cam!" << std::endl; return -1;
       }
       bool capTest = cap.read(frame);
       if(!capTest)
       {
          break;
       }
       //etract face of block from sceene
       Mat blockFace = extract.GetBlockFace(frame);
       //check if frame and block are the same Mat
       if(norm(blockFace, frame) < .00001)
       {
         //extract number from blockface useing SURF
	 int num = extract.NumberExtract(blockFace, imageList);
         //check if extracted number is even or odd, then send to arduino
         server.send(num);         
       }
    }//end while
}//end main
