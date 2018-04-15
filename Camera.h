#ifndef CAMERA_H
#define CAMERA_H

#include "DataTypes.h"
#include <stdio.h>
#include <stdlib.h>

class Camera
{

public:

	Camera();

	void Check();
private:
	void GetAllocatedAddress();

};

#endif // !CAMERA_H