#ifndef	CLASSIFY_H
#define	CLASSIFY_H

#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

#define FILENAME "imgData.txt"
#define FILEPATH "lena.jpg"

namespace Classify {

		void		showAndAnnotateImg(std::string text);
		void		writeFile(cv::Point p1, cv::Point p2);
		std::string	readFile();

}

#endif