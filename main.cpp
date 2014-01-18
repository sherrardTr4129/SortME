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
#include "RobotServer.h"
#include "peopleFollower.h"


using namespace std;
//TODO add user input. more funtion calls to more vision operations




int main(int argc, char** argv)
{
    int camID;
    string cmID, task;

    cout << "enter Cam ID" << endl;
    cin >> cmID;
    camID = atoi(cmID.c_str());
 
    cout << "enter task: p for people tracking or b for block sorting" << endl;
    cin >> task;
   
    RobotServer server;
    NumberExtractor extract;
    peopleFollower follow;
    VideoCapture cap;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

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
       if(task == "b" || task == "B")
       {
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
       }
       else if(task == "p" || task == "P")
       {
           int x = follow.PeopleFollow(frame);
           if(x/2 <= 140)
	   {
              server.send('r');
           }
           else if(x/2 >= 180)
           {
              server.send('l');
           }
       }// end else if
    }//end while
}//end main
