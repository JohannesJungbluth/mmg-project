#include "ImgPre.h"

namespace ImgPre 
{
	using namespace std;
	using namespace cv;

	//IMAGELOADER

	void loadImagesFromPackage(string folderPath, vector<Mat> loadedImages)
	{
	
	}

	void getLoadedImages(vector<Mat> loadedImages, vector<OpLib::WorkingObject> *working_array)
	{
		working_array->clear();

		for (vector<Mat>::iterator it = loadedImages.begin() ; it != loadedImages.end(); ++it)
		{
			OpLib::WorkingObject obj = OpLib::WorkingObject();
			obj.source_image = *it;
			working_array->push_back(obj);
		}
	}

	//IMAGESCALER

	void scaleImageToScaledArray(cv::Mat input_image, std::vector<cv::Mat> *scaled_images)
	{
		int stepsPerOctave = 5;
		int minImgSize = 8*2;

		double* array = computeScaleFactors(stepsPerOctave);
		int length = 7*stepsPerOctave;
		Mat tmp;

		for(int i=1; i <= length; i++)
		{
			if(minImgSize != -1 && input_image.cols*(1.0/array[i])*input_image.rows*(1.0/array[i]) < minImgSize)
			{
				return;
			}

			Mat img;
			img = Mat((int)(input_image.cols*(1.0/array[i])), (int)(input_image.rows*(1.0/array[i])), input_image.type());

			if(i == 1 || i%stepsPerOctave == 0)
			{
				resize(input_image, img, Size(img.cols, img.rows), 0, 0, 1);
			}
			else
			{
				resize(tmp, img, Size(img.cols, img.rows), 0, 0, 1);
			}
			tmp = img;

			scaled_images->push_back(tmp);
		}
	}
	
	double* computeScaleFactors(int stepsPerOctave)
	{
		double* array = 0;

		if(stepsPerOctave < 1)
		{
			array[0] = 1.0;
			return array;
		}

		const int max = 7*stepsPerOctave;
		array = new double [max];

		double scale = pow(2.0, 1.0/stepsPerOctave);

		array[0] = 1.0;
		for(int i=0; i < 7; i++)
		{
			for(int j=0; j <stepsPerOctave; j++)
			{
				array[i*stepsPerOctave + j +1] = (double) array[i*stepsPerOctave + j]*scale;
			}
		}

		return array;
	}
}