//author: Trevor Sherrard
//project: SortME

#include <opencv2/opencv.hpp>
using namespace cv;

class square
{
    private:
        Point findCenter(vector<Point>  contours);
    public:
	int findSquare( const Mat& image, vector<vector<Point> >& squares);
};
