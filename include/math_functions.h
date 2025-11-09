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
 * @param
 * matrix on which caluclate the derivative
 *
 * @body
 * calculate the derivative and overwrite the matrix since the input matrix will
 * be the error matrix and is note used anymore. You only need to keep track of
 * the deltas to calculate the weigths change after the batch runs
 *
 */
void sigmoidDerivative(FloatMatrix *_input);

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

typedef enum MatrixErrors {
    NO_ERROR,
    WRONG_SIZES,
} MatrixErrors;

MatrixErrors dotProductFloat(FloatMatrix *_left, FloatMatrix *_right,
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
 *   @param
 *   _left: left operand matrix, keeps the result
 *   _right: right operand matrix, not changed
 *   _result: result matrix
 *
 *   @body
 *   compute the sum of 2 matrices
 */

void matrixAdditionFloat(FloatMatrix *_left, FloatMatrix *_right,
                         int _dividingFactor);

/*
 *   @param
 *   _predictions: value got from the feed forward process
 *   _targets: right result
 *   _output: output matrix
 *
 *   @body
 *   compute the mean squared error of the predicted result compared to the
 * actual result. Override the _predictions matrix since we don't need it
 * anymore and the sizes are the same
 *
 */

void meanSquaredError(FloatMatrix *_predictions, FloatMatrix *_targets);

/*
 *
 * @param
 * _left: transpose matrix, not modified
 * _right: fixed matrix, gets modified with the result
 *
 * @body
 * calculate the transpose defining a new matrix in memory to save the previous
 * values intact.
 *
 */
MatrixErrors transposeDotProductFloat(FloatMatrix *_left, FloatMatrix *_right);

/*
 * @param
 * _input: matrix to normalize. It will be also the output
 *
 * @body
 * perform a min-max normalization to set the values to a range from 0 to 1.
 *
 */
void normalizeInput(FloatMatrix *_input);

/*
 * @param
 * _left: left operator, modified
 * _right: right operator, not modified
 *
 * @body
 * element-wise multiplication
 */
void multiplicationFloat(FloatMatrix *_left, FloatMatrix *_right);
