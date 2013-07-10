#include "HOG.h"

namespace HOG
{
	using namespace std;
	using namespace cv;

	// HOG_TRANSFORMER

	void extractHOGFeatures(Mat input_img, float feature_array[], int hogOrientations, int cellSize)
	{
		Mat img = input_img;
				imshow("input", input_img);

		float* frame = (float*)malloc(img.rows * img.cols * img.channels() * sizeof(float));
		for (int x=0; x<img.cols*img.rows; x++){
			if (img.type() == CV_32FC1)
				frame[x] = img.at<float>(x/img.rows, x%img.cols);
			else if (img.type() == CV_8UC3)
				for (int i=0; i<3; i++){
					frame[x+i*img.cols*img.rows] = (float)img.at<Vec3b>(x/img.rows, x%img.cols)[i]/255.0;
				}
		}

		// VlHogVariantUoctti - VlHogVariantDalalTriggs
		VlHog* hog =  vl_hog_new(VlHogVariantUoctti, vl_size(hogOrientations), VL_FALSE) ;
		vl_hog_put_image(hog, frame, vl_size(img.cols), vl_size(img.rows), vl_size(img.channels()), vl_size(cellSize));
		free(frame);

		vl_size hogWidth = vl_hog_get_width(hog);
		vl_size hogHeight = vl_hog_get_height(hog);
		vl_size hogDimenison = vl_hog_get_dimension(hog);

		float* hogArray = (float*)vl_malloc(hogWidth * hogHeight * hogDimenison * sizeof(float));
		vl_hog_extract(hog, hogArray);

		//convert_hog_array(hogArray, (int)hogDimenison, (int)hogOrientations, (int)hogWidth, (int)hogHeight, input_img.cols-2, input_img.rows-2);

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

		feature_array = result;
		vl_free(result);

		//resize(res, res, Size(img.cols, img.rows),0,0,1);

		imshow("hog", res);
	}

	// SLIDING_WINDOW_GENERATOR

	void createWindowedHOGs(float feature_array[], float array_of_windowed_features)
	{

	}
}