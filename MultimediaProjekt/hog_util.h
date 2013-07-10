#pragma once
#ifndef __HOG_UTIL_H_
#define __HOG_UTIL_H_

#include "opencv\cv.h"

/**
 * Most of the code is taken from hog.c (VLFEAT v0.9.16)
 */

// input: vlfeat storage of hogArrayWidth times hogArrayHeight many cell descriptors
// output: matrix with hogArrayWidth times hogArrayHeight many rows. each row 
// stores one cell descriptor, i.e. the descriptor at grid pos. (r,c) is put in
// row (r * hogArrayWidth) + c
// Note: cols_needed and rows_needed must be less or equal than hogArrayWidth and
// hogArrayHeight respectively; since VLFeat extracts features for cells that slightly
// extend over the image boundaries one can use these parameters to ensure that
// only cells fully contained in the image are contained in the cv::Mat retured
// by this function
cv::Mat convert_hog_array(float* features, int hogDimension, int numOrientations, int hogArrayWidth, int hogArrayHeight, int cols_needed, int rows_needed);
float* hog_glyphs(int glyph_size);
void hog_render(float* image, int num_channels, float const* descriptor, int glyph_size, int hog_array_width, int hog_array_height);
void permute_hog_cell_descriptor(float const* src, float* dst);
void permute_hog_cell_descriptor(double const* src, double* dst);

#endif
