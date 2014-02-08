//author: Trevor Sherrard
//project: SortME

#include "peopleFollower.h"
#include <opencv2/opencv.hpp>
using namespace cv;

/**
* \fn peopleFollower::PeopleFollow(cv::Mat frame)
* \brief PeopleFollow() tracks people in a Mat image.
* \param frame the Cv::Mat containing the person to be tracked 
* \return int The person's x cordinate 
*/
int peopleFollower::PeopleFollow(Mat frame)
{
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;
    hog.detectMultiScale(frame, found, 0, Size(8,8), Size(32,32), 1.05, 2);
    size_t i, j;
    for (i=0; i<found.size(); i++) 
    {
       Rect r = found[i];
       for (j=0; j<found.size(); j++) 
            if (j!=i && (r & found[j]) == r)
                    break;
            if (j== found.size())
                found_filtered.push_back(r);
    }
 
    for (i=0; i<found_filtered.size(); i++) 
    {
       Rect r = found_filtered[i];
       r.x += cvRound(r.width*0.1);
       r.width = cvRound(r.width*0.8);
       r.y += cvRound(r.height*0.07);
       r.height = cvRound(r.height*0.8);
       int x =(r.x + (r.width/2));
       if(x > 320)
       {
	  x = 160; // mid screen
       }
       else if(x < 0)
       {
	  x = 160; // mid screen
       }
       return x;
    }
}
