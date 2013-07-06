#include "OpLib.h"

using namespace cv;
using namespace std;

namespace OpLib
{
	//	return true if overlap between correctRectangle and hypothesisRectangle exceeds 50%
	
	bool isHypothesisRight(Point cPointMin, Point cPointMax, Point hPointMin, Point hPointMax)
	{
		int height = abs(cPointMin.y - cPointMax.y);
		int width = abs(cPointMin.x - cPointMax.x);
		
		int dHeightMin = abs(cPointMin.y - hPointMin.y);
		int dHeightMax = abs(cPointMax.y - hPointMax.y);
		
		int dWidthMin = abs(cPointMin.x - hPointMin.x);
		int dWidthMax = abs(cPointMax.x - hPointMax.x);
	
		return dHeightMin < 0.5 * height && dHeightMax < 0.5 * height
			&& dWidthMin < 0.5 * width && dWidthMin < 0.5 * width;
	}
}