#include "HOG.h"

namespace HOG
{
	using namespace std;
	using namespace cv;

	// HOG_TRANSFORMER

	void extractHOGFeatures(Mat input_img, float feature_array[], int hogOrientations, int cellSize)
	{
		imshow("input", input_img);
		
		input_img.convertTo(input_img, CV_8UC1);

		/*float* frame = (float*)malloc(input_img.rows * input_img.cols * input_img.channels() * sizeof(float));
		for (int x=0; x<input_img.cols*input_img.rows; x++)
		{
			if (input_img.type() == CV_32FC1)
				frame[x] = input_img.at<float>(x/input_img.rows, x%input_img.cols);
			else if (input_img.type() == CV_8UC3)
				for (int i=0; i<3; i++)
				{
					frame[x+i*input_img.cols*input_img.rows] = (float)input_img.at<Vec3b>(x/input_img.rows, x%input_img.cols)[i]/255.f;
				}
		}*/

		// VlHogVariantUoctti - VlHogVariantDalalTriggs
		VlHog* hog =  vl_hog_new(VlHogVariantUoctti, vl_size(hogOrientations), VL_FALSE) ;
		vl_hog_put_image(hog, input_img.ptr<float>(0), vl_size(input_img.cols), vl_size(input_img.rows), vl_size(input_img.channels()), vl_size(cellSize));
		free(frame);

		vl_size hogWidth = vl_hog_get_width(hog);
		vl_size hogHeight = vl_hog_get_height(hog);
		vl_size hogDimenison = vl_hog_get_dimension(hog);

		float* hogArray = (float*)vl_malloc(hogWidth * hogHeight * hogDimenison * sizeof(float));
		vl_hog_extract(hog, hogArray);

		//Mat test = convert_hog_array(hogArray, (int)hogDimenison, (int)hogOrientations, (int)hogWidth, (int)hogHeight, (int)hogWidth, (int)hogHeight);
		//imshow("hog_render", test);

		vl_size glyphSize = vl_hog_get_glyph_size(hog);
		vl_size imageHeight = glyphSize * hogHeight;
		vl_size imageWidth = glyphSize * hogWidth;

		Mat result = Mat::zeros(imageHeight, imageWidth, CV_32FC1);
		vl_hog_render(hog, result.ptr<float>(0), hogArray, hogWidth, hogHeight);
		vl_free(hogArray);
		vl_hog_delete(hog);

		//resize(res, res, Size(img.cols, img.rows),0,0,1);

		imshow("hog", result);
		//feature_array = result;
	}

	// SLIDING_WINDOW_GENERATOR

	void createWindowedHOGs(float feature_array[], float array_of_windowed_features)
	{

	}
}