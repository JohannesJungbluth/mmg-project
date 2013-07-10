#include "hog_util.h"
#include <math.h>

#ifndef M_PI
	#define M_PI 3.141592653589793
#endif

// @TODO: magic constants; should be made parameters of the functions instead
const int num_orientations = 9;
const int num_normalization_factors = 4;
const int hog_descriptor_size = 31;
// precomputed permutation for Uoctti variant of VLHOG (v0.9.16)
const int hog_cell_permutation_vlfeat[31] = {
	9,
	8,
	7,
	6,
	5,
	4,
	3,
	2,
	1,
	0,
	17,
	16,
	15,
	14,
	13,
	12,
	11,
	10,
	18,
	26,
	25,
	24,
	23,
	22,
	21,
	20,
	19,
	28,
	27,
	30,
	29
};

cv::Mat convert_hog_array(float* features, int hogDimension, int numOrientations, int hogArrayWidth, int hogArrayHeight, int cols_needed, int rows_needed)
{
	int hogStride = hogArrayWidth * hogArrayHeight ;
	int k,y,x;

	cv::Mat featureMat = cv::Mat(cols_needed * rows_needed, hogDimension, CV_32FC1);

	int feature_idx = 0;

	// code copied from vl/hog.c (vl_hog_extract)
	for (y = 0 ; y < (signed)hogArrayHeight ; ++y) {
		for (x = 0 ; x < (signed)hogArrayWidth ; ++x) {

			float* oiter = features + x + hogArrayWidth * y ;

			if (y > rows_needed - 1 || x > cols_needed - 1)
			{
				// this descriptor is not fully contained in the image
				oiter += numOrientations * hogStride ;
				oiter += 2 * hogStride * numOrientations ;
				oiter += hogStride ;
				oiter += hogStride ;
				oiter += hogStride ;
				oiter += hogStride ;
			}
			else
			{
				float* cell_descriptor = featureMat.ptr<float>(feature_idx);

				for (k = 0 ; k < (signed)numOrientations ; ++k) {
					cell_descriptor[k] = *oiter;
					cell_descriptor[k + numOrientations] = *(oiter + hogStride * numOrientations);
					cell_descriptor[k + 2 * numOrientations] =  *(oiter + 2 * hogStride * numOrientations);

					oiter += hogStride ;
				}

				oiter += 2 * hogStride * numOrientations ;
				int norm_factor_offset = 3 * numOrientations;
				cell_descriptor[norm_factor_offset] = *oiter; oiter += hogStride ;
				cell_descriptor[norm_factor_offset + 1] = *oiter; oiter += hogStride ;
				cell_descriptor[norm_factor_offset + 2] = *oiter; oiter += hogStride ;
				cell_descriptor[norm_factor_offset + 3] = *oiter; oiter += hogStride ;

				++feature_idx;
			}
		}
	}

	return featureMat;
}

float* hog_glyphs(int glyph_size)
{
  int o,i;

  /*
   Create glyphs for representing the HOG features/ filters. The glyphs
   are simple bars, oriented orthogonally to the gradients to represent
   image edges. If the object is configured to work on transposed image,
   the glyphs images are also stored in column-major.
   */
  float* glyphs = new float[glyph_size * glyph_size * num_orientations];
	for(i = 0; i < glyph_size * glyph_size * num_orientations; ++i)
	{
		glyphs[i] = 0;
	}

#define atglyph(x,y,k) glyphs[(x) + glyph_size * (y) + glyph_size * glyph_size * (k)]

  for (o = 0 ; o < (signed)num_orientations ; ++o) {
    double angle = fmod(o * M_PI / num_orientations + M_PI/2, M_PI) ;
    double x2 = glyph_size * cos(angle) / 2 ;
    double y2 = glyph_size * sin(angle) / 2 ;

    if (angle <= M_PI / 4 || angle >= M_PI * 3 / 4) {
      /* along horizontal direction */
      double slope = y2 / x2 ;
      double offset = (1 - slope) * (glyph_size - 1) / 2 ;
      int skip = (int)(1 - fabs(cos(angle))) / 2 * glyph_size ;
      int i, j ;
      for (i = skip ; i < (signed)glyph_size - skip ; ++i) {
				j = cvRound(slope * i + offset) ;
        //if (! self->transposed) {
          atglyph(i,j,o) = 1 ;
        //} else {
        //  atglyph(j,i,o) = 1 ;
        //}
      }
    } else {
      /* along vertical direction */
      double slope = x2 / y2 ;
      double offset = (1 - slope) * (glyph_size - 1) / 2 ;
      int skip = (int)(1 - sin(angle)) / 2 * glyph_size ;
      int i, j ;
      for (j = skip ; j < (signed)glyph_size - skip; ++j) {
        i = cvRound(slope * j + offset) ;
        //if (! self->transposed) {
          atglyph(i,j,o) = 1 ;
        //} else {
        //  atglyph(j,i,o) = 1 ;
        //}
      }
    }
  }

	return glyphs;
}

void hog_render(float* image, int num_channels, float const* descriptor, int glyph_size, int hog_array_width, int hog_array_height)
{
	int x, y, k, cx, cy ;
	int hogStride = hog_array_width * hog_array_height ;

	float* glyphs = hog_glyphs(glyph_size);

	for (y = 0 ; y < (signed)hog_array_height ; ++y) {
		for (x = 0 ; x < (signed)hog_array_width ; ++x) {
			float minWeight = 0 ;
			float maxWeight = 0 ;

			for (k = 0 ; k < (signed)num_orientations ; ++k) {
				float weight;
				float const * glyph = glyphs + k * (glyph_size*glyph_size) ; // glyth for the k-th orientation
				float * glyphImage = image + glyph_size * x + y * hog_array_width * (glyph_size*glyph_size);

				// original code
				//weight =
				//descriptor[k * hogStride] +
				//descriptor[(k + num_orientations) * hogStride] +
				//descriptor[(k + 2 * num_orientations) * hogStride] ;
				
				// the first 18 bins store contrast sensitive features, followed by 9 bins for the contrast 
				// insensitive features
				// --
				int cell_offset = (y * hog_array_width + x) * hog_descriptor_size;
				weight =
				descriptor[cell_offset + k] +
				descriptor[cell_offset + k + num_orientations] +
				descriptor[cell_offset + k + 2 * num_orientations] ;
				// --

				maxWeight = std::max(weight, maxWeight) ;
				minWeight = std::min(weight, minWeight);

				for (cy = 0 ; cy < (signed)glyph_size ; ++cy) {
					for (cx = 0 ; cx < (signed)glyph_size ; ++cx) {
						*glyphImage++ += weight * (*glyph++) ;
					}
					glyphImage += (hog_array_width - 1) * glyph_size  ;
				}
			} /* next orientation */

			{
				float * glyphImage = image + glyph_size * x + y * hog_array_width * (glyph_size*glyph_size) ;
				for (cy = 0 ; cy < (signed)glyph_size ; ++cy) {
					for (cx = 0 ; cx < (signed)glyph_size ; ++cx) {
						float value = *glyphImage ;
						*glyphImage++ = std::max(minWeight, std::min(maxWeight, value)) ;
					}
					glyphImage += (hog_array_width - 1) * glyph_size;
				}
			}

			// original code
			//++descriptor;
		} /* next column of cells (x) */
	} /* next row of cells (y) */

	delete[] glyphs;
}

int* compute_hog_cell_permutation_mmc()
{
	int* permutation = new int[hog_descriptor_size];
	for(int ii = 0; ii < hog_descriptor_size; ++ii)
	{
		permutation[ii] = -INT_MAX;
	}

	for(int o = 0 ; o < (signed)num_orientations ; ++o) {
		int op = num_orientations - o - 1;
		permutation[o] = op;
		permutation[o + num_orientations] = (op + num_orientations) % (2*num_orientations) ;
		permutation[o + 2*num_orientations] = (op % num_orientations) + 2*num_orientations ;
	}
	for(int k = 0 ; k < num_normalization_factors ; ++k) {
		// the texture features correspond to four displaced block around
		// a cell. these permute with a lr flip as for DalalTriggs.
		int blockx = k % 2 ;
		int blocky = k / 2 ;
		int q = (1 - blockx) + blocky * 2 ;
		permutation[k + num_orientations * 3] = q + num_orientations * 3;
	}

	return permutation;
}

void permute_hog_cell_descriptor(float const* src, float* dst)
{
	//int* permutation = compute_hog_cell_permutation_mmc();

	// a permutation specifies how to permute elements in a HOG descriptor to flip 
	// it horizontally. 
	for(int ii = 0; ii < hog_descriptor_size; ++ii)
	{
		//printf("\npermutation [%d] > [%d]", ii, hog_cell_permutation_vlfeat[ii]);
		dst[hog_cell_permutation_vlfeat[ii]] = src[ii];
	}

	//delete[] permutation;
}

void permute_hog_cell_descriptor(double const* src, double* dst)
{
	//int* permutation = compute_hog_cell_permutation_mmc();

	// a permutation specifies how to permute elements in a HOG descriptor to flip 
	// it horizontally. 
	for(int ii = 0; ii < hog_descriptor_size; ++ii)
	{
		//printf("\npermutation [%d] > [%d]", ii, hog_cell_permutation_vlfeat[ii]);
		dst[hog_cell_permutation_vlfeat[ii]] = src[ii];
	}

	//delete[] permutation;
}

