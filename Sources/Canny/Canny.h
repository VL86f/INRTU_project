//Canny.h

#ifndef CANNY_H
#define CANNY_H

void gauss_fliter_func( int width, int height, int** input, int** output, double sigma);

void sobel_vectors_func(int width, int height, int** input, int** output, int** vector_tt);

void vectors_check(int** image, int height, int width, int** vector_in, int** output);

void Double_porog (int height, int width, int** input, int** output, int porog_min, int porog_max);

void border_track (int** input, int** image, int height, int width);

#endif
