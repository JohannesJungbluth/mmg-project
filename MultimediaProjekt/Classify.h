#ifndef	CLASSIFY_H
#define	CLASSIFY_H

#include "opencv\cv.h"
#include "opencv\highgui.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

namespace Classify
{
	//	TRAINER
	void		createClassificator(float window_feature[], cv::Rect window_rect, cv::Rect positive_rects[]);

	//	SVM
	void		train();
	void		classify();

	//	AnnotatedImageComposer
	void		deleteOverlappingPositiveHits();
	void		composeImage(cv::Mat final_image);




	void		showAndAnnotateImg(std::string filepath, std::string text);
	void		writeFile(std::string text, std::string path);
	std::string	readFile(std::string filepath);
}

#endif