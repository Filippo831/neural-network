#include "../include/math_functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sigmoid(FloatMatrix *_input) {
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        // x = 1 / (1 + e^(-x))
        _input->values[index] = 1 / (1 + exp(_input->values[index]));
    }
}

void sigmoidDerivative(FloatMatrix *_input) {
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        // x = x * (1 - x)
        _input->values[index] =
            _input->values[index] * (1 - _input->values[index]);
    }
}

float getIndexMatrix(int _row, int _col, FloatMatrix *_matrix) {
    return _matrix->values[_row * _matrix->cols + _col];
};

MatrixErrors dotProductFloat(FloatMatrix *_left, FloatMatrix *_right,
                             FloatMatrix *_result) {

    if (_left->cols != _right->rows) {
        return WRONG_SIZES;
    }

    float *resultMatrix = malloc(sizeof(float) * (_left->rows * _right->cols));

    int matrixIndex = 0;

    for (int r = 0; r < _left->rows; r++) {
        for (int c = 0; c < _right->cols; c++) {
            float intermediateResult = 0;
            for (int index = 0; index < _left->cols; index++) {
                intermediateResult += getIndexMatrix(r, index, _left) *
                                      getIndexMatrix(index, c, _right);
            }
            resultMatrix[matrixIndex++] = intermediateResult;
        }
    }

    // FIX: for some reason you need this to make the tests work
    fflush(stdin);

    _result->rows = _left->rows;
    _result->cols = _right->cols;

    _result->values = resultMatrix;
    return NO_ERROR;
}

float loss(FloatMatrix *_predicted, FloatMatrix *_actual) {
    float lossValue = 0;

    for (int index = 0; index < _predicted->cols * _predicted->rows; index++) {
        lossValue += pow(_predicted->values[index] - _actual->values[index], 2);
    }

    lossValue = lossValue / (_predicted->cols * _predicted->rows);

    return lossValue;
}

void matrixAdditionFloat(FloatMatrix *_left, FloatMatrix *_right,
                         int _dividingFactor) {
    // sum element by element and override the _left matrix
    for (int index = 0; index < _left->rows * _left->cols; index++) {
        _left->values[index] =
            _left->values[index] + (_right->values[index] / _dividingFactor);
    }
}

void meanSquaredError(FloatMatrix *_predictions, FloatMatrix *_targets) {
    for (int index = 0; index < _predictions->cols; index++) {
        _predictions->values[index] =
            pow(_predictions->values[index] - _targets->values[index], 2);
    }
}

MatrixErrors transposeDotProductFloat(FloatMatrix *_left, FloatMatrix *_right) {

    if (_left->rows != _right->rows) {
        return WRONG_SIZES;
    }

    float *resultMatrix = malloc(sizeof(float) * (_left->rows * _right->cols));

    int matrixIndex = 0;

    for (int r = 0; r < _left->rows; r++) {
        for (int c = 0; c < _right->cols; c++) {
            float intermediateResult = 0;
            for (int index = 0; index < _left->cols; index++) {
                intermediateResult += getIndexMatrix(index, r, _left) *
                                      getIndexMatrix(index, c, _right);
            }
            resultMatrix[matrixIndex++] = intermediateResult;
        }
    }

    _right->rows = _left->cols;

    _right->values = resultMatrix;
    return NO_ERROR;
}
