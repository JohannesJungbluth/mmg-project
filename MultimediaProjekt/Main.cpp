#include "ImgPre.h"
#include "HOG.h"

using namespace cv;

int main(int argc, char ** argv){

	/* TEST - getLoadedImages

	std:vector<Mat> vector;
	Mat mat = imread("C:/Users/Johannes/Downloads/INRIAPerson/96X160H96/Train/pos/crop_000010a.png");
	vector.push_back(mat);
	mat = imread("C:/Users/Johannes/Downloads/INRIAPerson/96X160H96/Train/pos/crop_000011a.png");
	vector.push_back(mat);
	mat = imread("C:/Users/Johannes/Downloads/INRIAPerson/96X160H96/Train/pos/crop_000603a.png");
	vector.push_back(mat);

	std::vector<OpLib::WorkingObject> array;
	ImgPre::getLoadedImages(vector, &array);
	for (std::vector<OpLib::WorkingObject>::iterator it = array.begin() ; it != array.end(); ++it)
	{
		imshow("Image", it->source_image);
		waitKey();
	}*/

	/* TEST - scaleImageToScaledArray
	
	Mat mat = imread("C:/Users/Johannes/Downloads/INRIAPerson/96X160H96/Train/pos/crop_000010a.png");
	vector<Mat> array = vector<Mat>();
	ImgPre::scaleImageToScaledArray(mat, &array);
	int i = 0;
	for (std::vector<Mat>::iterator it = array.begin() ; it != array.end(); ++it)
	{
		std::stringstream name;
		name << "Image: " << i;
		imshow(name.str(), *it);
		waitKey();
		i++;
	}
	*/

	/* TEST - extractHOGFeatures

	*/
	Mat mat = imread("C:/Users/Johannes/Dropbox/Uni/Studium/5_SS_13/Multimedia Projekt/Blatt_3/lena.jpg");
	float *float_array = 0;
	HOG::extractHOGFeatures(mat, float_array);
	waitKey();

	return 0;
}