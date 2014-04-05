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


#include "UDP.h"
#include "peopleFollower.h"
#include "square.h"



using namespace std;
using namespace cv;
//TODO add user input. more funtion calls to more vision operations

int main(int argc, char** argv)
{
    int camID;
    string cmID, task;

    cout << "enter Cam ID" << endl;
    cin >> cmID;
    camID = atoi(cmID.c_str());
 
    cout << "enter task: p for people tracking, s for square tracking" << endl;
    cin >> task;
   

    UDP udp;
    const char* IP = "";
    peopleFollower follow;
    square sqr;
    VideoCapture cap;
    vector<vector<Point> > squares;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    cap.open(camID);
    Mat frame;

    if(!cap.isOpened())
    {
	std::cout<< " could not open cam!" << std::endl; return -1;
    }
    int state = 0;
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
       else if(task == "p" || task == "P")
       {
           Rect r = follow.PeopleFollow(frame);
           int x =(r.x + (r.width/2));
           if(x > 700 || x < 0)
           {
               x = 320; //midscreen
           }

           if(x < 200 && state != 1)
           {
              udp.send("r", IP);
              cout << "right" << endl;
              cout << x << endl;
              state = 1;
           }
           else if(x > 400 && state !=2 )
           {
              udp.send("l", IP);
              cout << "left" << endl;
              cout << x << endl;
              state = 2;
           }
           else if(x >= 200 && x <= 400 && state != 3)
           {
              udp.send("s", IP);
              cout << "stop" << endl;
              cout << x << endl;
              state = 3;
           }
           cout << state <<"s" << endl;
           cout << "x: "<< x <<endl;
           rectangle(frame, r, Scalar(0,255,0), 8);
           imshow("people", frame);
           waitKey(1);
       }// end else if
       else if(task == "s" || task == "S")
       {
           int xSquare = sqr.findSquare(frame, squares);
           if(xSquare > 700 || xSquare < 0)
           {
               xSquare = 320; //midscreen
           }

           if(xSquare < 200 && state != 1)
           {
              udp.send("r", IP);
              cout << "right" << endl;
              cout << xSquare << endl;
              state = 1;
           }
           else if(xSquare > 400 && state !=2 )
           {
              udp.send("l", IP);
              cout << "left" << endl;
              cout << xSquare << endl;
              state = 2;
           }
           else if(xSquare >= 200 && xSquare <= 400 && state != 3)
           {
              udp.send("s", IP);
              cout << "stop" << endl;
              cout << xSquare << endl;
              state = 3;
           }
           cout << state <<"s" << endl;
           cout << "x: "<< xSquare <<endl;
           circle(frame, Point(xSquare, 120), 1, Scalar(0,255,0), 8);
           imshow("squares", frame);
           waitKey(1);
       }//end else if
    }//end while
}//end main
