#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv) {
	
	if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

	Point org = cvPoint(image.cols * 0.1, image.rows * 0.2);
	putText(image, "Hello World", org, FONT_HERSHEY_DUPLEX, 2, Scalar(255,255,255), 2, CV_AA);

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.

    waitKey(0);             // Wait for a keystroke in the window
	return 0;
}