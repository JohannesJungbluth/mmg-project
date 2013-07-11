#include "ImgPre.h"
#include <boost\filesystem.hpp>

namespace fs = boost::filesystem;




namespace ImgPre 
{
	using namespace std;
	using namespace cv;

	//IMAGELOADER

	/*! Checks for every file in the directory and tries to make a CV::Mat out of it. Each Mat is appended to the vector
	*@param folderPath The path containing the images
	*@param loadedImages The vector where the created mats are stored
	*/
	void loadImagesFromPackage(string folderPath, vector<Mat> *loadedImages)
	{
		fs::path someDir(folderPath);
		fs::directory_iterator end_iter;
		if (fs::exists(someDir) && fs::is_directory(someDir))
		{
			for(fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
			{
				Mat image = imread(dir_iter->path().string(), CV_LOAD_IMAGE_COLOR);
				loadedImages->push_back(image);
			}
		}
	}

	/*! Converts all images stored in the vector into a @WorkingObject and stores those objects in the working_array
	*@param loadedImages The vector containing images in a Mat
	*@param working_array The vector which will be filled with the @WorkingObject
	*/
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
	/*! Takes an image and creates all the scaled down versions of it. Every new octave the
	* image is resized from source, else it is resized from the image one step earlier 
	*/
	void scaleImageToScaledArray(cv::Mat input_image, std::vector<cv::Mat> *scaled_images)
	{
		//Lambda
		int stepsPerOctave = 5;
		//Size of the smallest image which is about to be created, 2 pixels times 8 pixels 
		int minImgSize = 2*8;

		double* array = computeScaleFactors(stepsPerOctave);
		//Warum 7? 7 Oktaven? Abbruchbedingung müsste doch eigentlich minImgSize sein?
		int length = 7*stepsPerOctave;
		//Output
		Mat tmp;

		for(int i=1; i <= length; i++)
		{
			if(minImgSize != -1 && input_image.cols*(1.0/array[i])*input_image.rows*(1.0/array[i]) < minImgSize)
			{
				return;
			}
			//Downscaled image
			Mat img;
			img = Mat((int)(input_image.cols*(1.0/array[i])), (int)(input_image.rows*(1.0/array[i])), input_image.type());

			if(i == 1 || i%stepsPerOctave == 0)
			//New octave => resize image from source
			{
				resize(input_image, img, Size(img.cols, img.rows), 0, 0, 1);
			}
			else
			//Old octave => resize image from one step earlier
			{
				resize(tmp, img, Size(img.cols, img.rows), 0, 0, 1);
			}
			tmp = img;

			scaled_images->push_back(tmp);
		}
	}
	
	/** Creates the scale factors neccesary to scale all the images. 
	* @return An array containing all the factors
	*/
	double* computeScaleFactors(int stepsPerOctave)
	{
		double* array = 0;

		if(stepsPerOctave < 1)
		{
			array[0] = 1.0;
			return array;
		}
		//Woher kommen die 7? Sind das nicht potentiell zu wenig Oktaven?
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