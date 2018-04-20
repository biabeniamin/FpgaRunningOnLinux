#include "Camera.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "DataTypes.h"
#include "Door.h"
#include "Notifications.h"
#include "FrameChecker.h"

using namespace std;
using namespace cv;

VideoCapture _capture;
DWORD _currentFramePhysAddress;
DWORD _lastFramePhysAddress;

PDWORD _currentFrameMapped;
PDWORD _lastFrameMapped;

DWORD _index = 0;
DWORD _indexFacialRecognition = 0;
BYTE motionDetected = 0;

FILE *_facialRecognitionResult;
FILE *_facialRecognitionProcess;
FILE *_facialRecognitionDone;


Camera::Camera()
{
	GetAllocatedAddress();
	
	cout << "start\n";
	
	cout << "opening stream\n";

	_capture.open(0);// "http://192.168.0.107:8081");

	cout << "stream opened\n";

	_currentFrameMapped = MapPhysicalMemory(_currentFramePhysAddress);
	_lastFrameMapped = MapPhysicalMemory(_lastFramePhysAddress);

	_facialRecognitionResult = fopen("result", "w+");
	_facialRecognitionProcess = fopen("process", "r+");
	_facialRecognitionDone = fopen("facialDone", "w+");
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
	//image = imread("../tmp2/face.jpg");

	

	memcpy(_lastFrameMapped, _currentFrameMapped, 2000);
	memcpy(_currentFrameMapped, image.data, 2000);

	DWORD changes = GetPixelsDelta(_currentFramePhysAddress, _lastFramePhysAddress, 2000);

	if (0xB000 < changes)
	{
		motionDetected = 1;
	}
	else if ((1 == motionDetected) && (0xA000 > changes))
	{
		printf("pixels changed[%x] %x \n", _index, changes);
		char text[] = "/var/www/html/motion/biden00.jpg";
		text[27] += _index % 10;
		text[26] += _index / 10;
		imwrite(text, image);
		printf("text %s\n ", text);
		_index++;

		
		

		fseek(_facialRecognitionResult, 0, SEEK_SET);
		fprintf(_facialRecognitionResult, "0");
		fflush(_facialRecognitionResult);

		FILE *ff2 = fopen("toProcess", "w");
		fprintf(ff2, "%s", text);
		fclose(ff2);

		fseek(_facialRecognitionDone, 0, SEEK_SET);
		fprintf(_facialRecognitionDone, "0");
		fflush(_facialRecognitionDone);

		fseek(_facialRecognitionProcess, 0, SEEK_SET);
		fprintf(_facialRecognitionProcess, "1");
		fflush(_facialRecognitionProcess);

		printf("facial started \n");

		
		BYTE hasDone = 0;
		DWORD itterations = 0;
		do
		{
			fseek(_facialRecognitionDone, 0, SEEK_SET);
			fscanf(_facialRecognitionDone, "%d", &hasDone);
			//printf("wainting fac to done %x \n", hasDone);
			itterations++;

			if (2000 < itterations)
			{
				printf("Timeout!\n");
				return;
			}
			usleep(1 * 1000);
		} while (0 == hasDone);

		printf("Done!\n");

		
		//fseek(_facialRecognitionProcess, 0, SEEK_SET);
		//fprintf(_facialRecognitionProcess, "0");
		
		fseek(_facialRecognitionResult, 0, SEEK_SET);
		fscanf(_facialRecognitionResult, "%d", &hasDone);
		printf("Facial recognition result %d\n", hasDone);
		if (1 == hasDone)
		{
			Door::GetInstance()->Unlock();
			Notifications::GetInstance()->SendNotification(1);
		}
		else
			

		motionDetected = 0;

		
	}
	

	return;
}
