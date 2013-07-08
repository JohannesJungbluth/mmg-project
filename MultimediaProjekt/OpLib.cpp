#include "OpLib.h"

using namespace cv;
using namespace std;

namespace OpLib
{
	//	return true if overlap between correctRectangle and hypothesisRectangle exceeds 50%
	
	bool checkForOverlap(cv::Rect rect_1, cv::Rect rect_2)
	{	
		if(rect_1.width != rect_2.width || rect_1.height != rect_2.height)
			return false;

		int dHeight = abs(rect_1.y - rect_2.y);
		int dWidth = abs(rect_1.x - rect_2.x);
	
		return dHeight < 0.5 * rect_1.height && dWidth < 0.5 * rect_1.width;
	}
}