#include "Camera.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "DataTypes.h"
#include "Light.h"
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

Light _light2;

Camera::Camera()
{
	GetAllocatedAddress();
	
	cout << "start\n";
	
	cout << "opening stream\n";

	_capture.open(0);// "http://192.168.0.107:8081");

	cout << "stream opened\n";

	_currentFrameMapped = MapPhysicalMemory(_currentFramePhysAddress);
	_lastFrameMapped = MapPhysicalMemory(_lastFramePhysAddress);

	_facialRecognitionResult = fopen("result", "rw");
	_facialRecognitionProcess = fopen("process", "w");
	_facialRecognitionDone = fopen("facialDone", "r");
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

		fseek(_facialRecognitionProcess, 0, SEEK_SET);
		fprintf(_facialRecognitionProcess, "1");

		fseek(_facialRecognitionResult, 0, SEEK_SET);
		fprintf(_facialRecognitionResult, "0");

		FILE *ff2 = fopen("toProcess", "w");
		fprintf(ff2, "%s", text);
		fclose(ff2);

		BYTE hasDone = 0;
		do
		{
			fseek(_facialRecognitionDone, 0, SEEK_SET);
			fscanf(_facialRecognitionDone, "%d", &hasDone);
			printf("wainting fac to done %x \n", hasDone);
		} while (0 == hasDone);

		fseek(_facialRecognitionProcess, 0, SEEK_SET);
		fprintf(_facialRecognitionProcess, "0");

		fseek(_facialRecognitionResult, 0, SEEK_SET);
		fscanf(_facialRecognitionResult, "%d", &hasDone);
		printf("Facial recognition result %d\n", hasDone);
		if (1 == hasDone)
		{
			_light2.TurnOn();
			
		}
		else
			_light2.TurnOff();

		_index++;

		motionDetected = 0;

		
	}
	

	return;
}
