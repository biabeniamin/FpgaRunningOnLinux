#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "Relay.h"
#include "DataTypes.h"
#include "FrameChecker.h"

using namespace std;
using namespace cv;

int main(){
    	Mat image;
	    image = imread("biden.jpg", CV_LOAD_IMAGE_UNCHANGED);   // Read the fil
imwrite("/var/www/html/biden.jpg", image);
	cout << image.rows << " " << image.cols <<  " " << image.step[0]<<" " << image.step[1] << "\n";
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			DWORD address = (DWORD)image.data + image.step[0] * i + image.step[1] * j;
			printf("%x, ", *((PDWORD)address));
		}
		printf("\n");
	}
	//return 0;


	cout << "start\n";
	VideoCapture cap;
	cout <<"opening stream\n";
	cap.open(0);//"http://192.168.0.107:8081");
	cout<<"stream opened\n";
	Point p1(0,0);
	Point p2(100,100);



//!!!!!!!!!!!!!
DWORD curFrame = (0x2e100000);
DWORD lastFrame = (0x2e200000);

PDWORD curFrameMapped = MapPhysicalMemory(curFrame);
PDWORD lastFrameMapped = MapPhysicalMemory(lastFrame);

DWORD index = 0;
BYTE motionDetected = 0;

while(1)
{
//cout<<"taking picture\n";
cap >> image;
//cout<<"picture taken\n";



memcpy(lastFrameMapped, curFrameMapped, 1000);
memcpy(curFrameMapped, image.data, 1000);

//Dump(lastFrameMapped);
//Dump(curFrameMapped);

DWORD changes = GetPixelsDelta(curFrame, lastFrame, 500);
if(0x9FF < changes)
{
	motionDetected = 1;
}
else if((1 ==motionDetected) && (0x9FF > changes))
{
	printf("pixels changed[%x] %x \n", index, changes);
	char text[]= "/var/www/html/motion/biden00.jpg";
	text[27] += index % 10;
	text[26] += index / 10;
	imwrite(text, image);
	printf("text %s\n ", text);
	index++;

	motionDetected = 0;
}




line(
image,       // image to draw on
p1,    // starting end point of line segment of type cv::Point
p2,   // other end of line segment
Scalar(0, 255, 0), //green colour
1,         // thickness of line
CV_AA     // anti aliased line type
);


//imwrite("/var/www/html/biden.jpg", image);
//TurnOnLight();

//sleep(1);
//TurnOffLight();
//sleep(1);
}
cout <<"adas\n";
sleep(1);
cout <<"adas\n";

//	cout << image;

/*    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);   
*/
      return 0;
}
