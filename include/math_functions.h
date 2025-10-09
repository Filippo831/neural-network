#pragma once
#include <gsl/gsl_matrix.h>
#include <math.h>

typedef struct FloatMatrix {
    float *values;
    int rows;
    int cols;
} FloatMatrix;

/*
 *  @params
 *  row: row to index
 *  col: column to index
 *  matrix: matrix to index
 *
 *  @return
 *  return the value indexed
 */
float getIndexMatrix(int _row, int _cols, FloatMatrix *_matrix);

float sigmoid(float _input);

/*
 *   @params
 *   left: left matrix
 *   right: right matrix
 *
 *   return
 *   correct: return enum with error specific to this calculation
 */

typedef enum DotProductFloatErrors {
    NO_ERROR,
    WRONG_SIZES,
} DotProductFloatErrors;

DotProductFloatErrors dotProductFloat(FloatMatrix *_left, FloatMatrix *_right,
                                      FloatMatrix *_result);
