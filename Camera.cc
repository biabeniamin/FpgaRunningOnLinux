#include "Camera.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "DataTypes.h"
#include "FrameChecker.h"

using namespace std;
using namespace cv;

VideoCapture _capture;
DWORD _currentFramePhysAddress;
DWORD _lastFramePhysAddress;

PDWORD _currentFrameMapped;
PDWORD _lastFrameMapped;

DWORD _index = 0;
BYTE motionDetected = 0;

Camera::Camera()
{
	GetAllocatedAddress();
	
	cout << "start\n";
	
	cout << "opening stream\n";

	_capture.open("http://192.168.0.107:8081");

	cout << "stream opened\n";

	_currentFrameMapped = MapPhysicalMemory(_currentFramePhysAddress);
	_lastFrameMapped = MapPhysicalMemory(_lastFramePhysAddress);

}

void Camera::GetAllocatedAddress()
{
	FILE *file;


	file = fopen("AllocatedAddress", "r");

	fscanf(file, "%d %d", &_currentFramePhysAddress, &_lastFramePhysAddress);

	fclose(file);

	printf("%x %x file\n", _currentFramePhysAddress, _lastFramePhysAddress);
}

void Camera::Check()
{
	Mat image;

	_capture >> image;

	memcpy(_lastFrameMapped, _currentFrameMapped, 1000);
	memcpy(_currentFrameMapped, image.data, 1000);

	DWORD changes = GetPixelsDelta(_currentFramePhysAddress, _lastFramePhysAddress, 500);
	if (0x9FF < changes)
	{
		motionDetected = 1;
	}
	else if ((1 == motionDetected) && (0x9FF > changes))
	{
		printf("pixels changed[%x] %x \n", _index, changes);
		char text[] = "/var/www/html/motion/biden00.jpg";
		text[27] += _index % 10;
		text[26] += _index / 10;
		imwrite(text, image);
		printf("text %s\n ", text);


		FILE *ff = fopen("process", "w");
		fprintf(ff, "1");
		fclose(ff);

		FILE *ff2 = fopen("toProcess", "w");
		fprintf(ff2, "%s", text);
		fclose(ff2);

		_index++;

		motionDetected = 0;
	}
	

	return;
}
