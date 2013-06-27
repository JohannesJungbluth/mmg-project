#include <vector>
#include "opencv2\imgproc\imgproc.hpp"
#include "HierElement.h"

namespace OpLib{

	using namespace cv;

	class WorkImage : public HierElement{
	private:



	public: 

		//!	Low scaled version of the parent window
		Mat scaled_img;

		//!	The extracted hog features of the image
		float * hog_features;

		//!	The scale factor of the scaled image. 1.0 means no scaling applied.
		float scale_factor;

		vector<HierElement *> getWindowedHOGObjects(){
			return this->getLowerElements();
		}


	};
}