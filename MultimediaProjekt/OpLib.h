#ifndef	OPLIB_H
#define	OPLIB_H

#pragma once

#include "WindowedHOG.cpp"
#include "WorkImage.cpp"
#include "WorkingObject.cpp"

#include "opencv\cv.h"
#include "opencv\highgui.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

namespace
{
	bool	checkForOverlap(cv::Rect rect_1, cv::Rect rect_2);
}

#endif

