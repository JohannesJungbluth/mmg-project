#ifndef	CLASSIFY_H
#define	CLASSIFY_H

#include "opencv\cv.h"
#include "opencv\highgui.h"

#include <iostream>
#include <fstream>
#include <string.h>

namespace Classify {

		void		showAndAnnotateImg(std::string filepath, std::string text);
		void		writeFile(std::string text, std::string path);
		std::string	readFile(std::string filepath);

}

#endif