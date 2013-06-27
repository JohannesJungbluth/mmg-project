#include <vector>
#include "opencv2\imgproc\imgproc.hpp"
#include "HierElement.h"

namespace OpLib{

	using namespace cv;

	class WindowedHOG : public HierElement{
	private:



	public: 

		//!	The HOG Features of this part of the image, created with sliding window.
		float * windowed_hog;

		//!	Determines, if this is a positive example.
		bool positive_classified;

		//!	The rectangle that describes were the sliding window was placed.
		Rect window_rect;
			
	};
}