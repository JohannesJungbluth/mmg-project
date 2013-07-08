#include "HOG.h"

namespace HOG
{
	using namespace std;
	using namespace cv;

	// HOG_TRANSFORMER

	void extractHOGFeatures(cv::Mat input_img, float feature_array[])
	{
		Mat img = Mat(input_img.rows, input_img.cols, CV_32FC3);
		input_img.convertTo(img, CV_32FC3);

		float scale = 255.f;
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				for(int i=0; i<img.channels(); i++)
				{
					if(input_img.channels() == 1)
					{
						img.ptr<float>(y)[x+i] /= scale;
					}
				}
			}
		}

		imshow("input", input_img);

		float* frame = (float*)malloc(img.rows * img.cols * img.channels() * sizeof(float));
		for(int y=0; y<img.rows; y++)
		{
			for(int x=0; x<img.cols; x++)
			{
				for(int i=0; i<img.channels(); i++)
				{
					// vlfeat farbarray: erst alle blauen, dann alle grünen und dann alle roten pixel hintereinander
					// opencv RGB passt das so?
					if(img.channels() > 1)
					{
						int corrector = 0;
						if(i == 1)
							corrector = 1;
						else if(i == 0)
							corrector = 2;
						frame[img.cols*img.rows*corrector + x*y] = img.ptr<float>(y)[x+i];
					}
					else
						frame[x*img.rows + y*(i+1)] = img.ptr<float>(y)[x+i];
				}
			}
		}


		VlHog* hog =  vl_hog_new(VlHogVariantDalalTriggs, vl_size(18), VL_FALSE) ;
		vl_hog_put_image(hog, frame, vl_size(img.cols), vl_size(img.rows), vl_size(img.channels()), vl_size(8));
		free(frame);

		vl_size hogWidth = vl_hog_get_width(hog);
		vl_size hogHeight = vl_hog_get_height(hog);
		vl_size hogDimenison = vl_hog_get_dimension(hog);

		float* hogArray = (float*)vl_malloc(hogWidth * hogHeight * hogDimenison * sizeof(float));
		vl_hog_extract(hog, hogArray);

		vl_size glyphSize = vl_hog_get_glyph_size(hog);
		vl_size imageHeight = glyphSize * hogHeight;
		vl_size imageWidth = glyphSize * hogWidth;

		float* result = (float*)vl_malloc(imageWidth * imageHeight * sizeof(float)) ;
		vl_hog_render(hog, result, hogArray, hogWidth, hogHeight);
		vl_free(hogArray);
	
		Mat res = Mat((int)imageHeight, (int)imageWidth, CV_32FC1);
		vl_hog_delete(hog);
		for(int y=0; y<res.rows; y++)
		{
			for(int x=0; x<res.cols; x++)
			{
				res.ptr<float>(y)[x] = result[x*imageHeight + y];
			}
		}
		vl_free(result);

		resize(res, res, Size(img.cols, img.rows),0,0,1);

		imshow("hog", res);
	
		for (int y = 0; y < res.rows; y++)
		{
			for (int x = 0; x < res.cols; x++)
			{
				res.ptr<float>(y)[x] *= scale;
			}
		}
	}

	// SLIDING_WINDOW_GENERATOR

	void createWindowedHOGs(float feature_array[], float array_of_windowed_features)
	{

	}
}