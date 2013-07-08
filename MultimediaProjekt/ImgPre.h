#ifndef IMG_PRE_H
#define IMG_PRE_H

#include "OpLib.h"
#include <stdio.h>
#include <array>
#include <vector>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"


namespace ImgPre
{

	//IMAGELOADER

	void loadImagesFromPackage(std::string folderPath, std::vector<cv::Mat> loadedImages);

	void getLoadedImages(std::vector<cv::Mat> loadedImages, std::vector<OpLib::WorkingObject> *working_array);

	//IMAGESCALER

	void scaleImageToScaledArray(cv::Mat input_image, std::vector<cv::Mat> *scaled_images);

	double* computeScaleFactors(int stepsPerOctave);
}

#endif