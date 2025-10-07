#pragma once
#include <gsl/gsl_matrix.h>
#include <math.h>

typedef struct FloatMatrix {
    float *values;
    int rows;
    int cols;
} FloatMatrix;

float sigmoid(float _input);

float *dotProductFloat(FloatMatrix *left, FloatMatrix *right);
