#ifndef HOG_H
#define HOG_H

#include "OpLib.h"

#include <stdio.h>
#include <array>
#include <vector>

#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"

#include "vl\hog.h"
#include "vl\mathop.h"

#include "hog_util.h"

namespace HOG
{

	// HOG_TRANSFORMER

	void extractHOGFeatures(cv::Mat input_img, float feature_array[], int hogOrientations, int cellSize);

	// SLIDING_WINDOW_GENERATOR

	void createWindowedHOGs(float feature_array[], float array_of_windowed_features);

}

#endif