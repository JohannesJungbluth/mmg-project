#include "opencv2\highgui\highgui.hpp"
#include <vector>
#include "HierElement.h"


namespace OpLib{

	using namespace cv;

	class WorkingObject : public HierElement{
	private:



	public: 

		//!	The source image.
		Mat source_image;

		//!	the coordinates of the detected objects in this image.
		vector<Rect> found_objects;

		vector<HierElement *> getLowscaledImageObjects(){
			return this->getLowerElements();
		}
	};
}