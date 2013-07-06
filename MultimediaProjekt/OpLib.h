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
	bool	checkForOverlap(cv::Point cPointMin, cv::Point cPointMax, cv::Point hPointMin, cv::Point hPointMax);
}

#endif

