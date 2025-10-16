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

/*
 * @param
 * _input: input matrix where to calculate all the sigmoid output
 *
 *   flatten the value to a range from -1 to 1, changes the input pointer, does
 * not copy the value to a new matrix
 *
 */

void sigmoid(FloatMatrix *_input);

/*
 *   @params
 *   left: left matrix
 *   right: right matrix
 *
 *   @body
 *   compute the dot product between 2 matrices
 *
 *   @return
 *   correct: return enum with error specific to this calculation
 */

// TODO: change this to general matrices computation errors so you can use the
// same for the matrices addition
typedef enum LayerFunctionErrors {
    NO_ERROR,
    WRONG_SIZES,
} LayerFunctionErrors;

LayerFunctionErrors dotProductFloat(FloatMatrix *_left, FloatMatrix *_right,
                                    FloatMatrix *_result);

/*
 *  @param
 *  _predicted: predicted values that came from the NN
 *  _actual: right prediction
 *
 *  @body
 *  compute the loss function using the MSE tecnique
 *
 *  @return
 *  loss value
 */

float loss(FloatMatrix *_predicted, FloatMatrix *_actual);

/*
 *
 *   @param
 *   _left: left operand matrix
 *   _right: right operand matrix
 *   _result: result matrix
 *
 *   @body
 *   compute the sum of 2 matrices
 */

void matrixAdditionFloat(FloatMatrix *_left, FloatMatrix *_right,
                    FloatMatrix *_result);
