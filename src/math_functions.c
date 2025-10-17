#include "../include/math_functions.h"
#include <math.h>
#include <stdio.h>

void sigmoid(FloatMatrix *_input) {
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _input->values[index] = 1 / (1 + exp(_input->values[index]));
    }
}

float getIndexMatrix(int _row, int _cols, FloatMatrix *_matrix) {
    return _matrix->values[_row * _matrix->cols + _cols];
};

LayerFunctionErrors dotProductFloat(FloatMatrix *_left, FloatMatrix *_right,
                                    FloatMatrix *_result) {

    if (_left->cols != _right->rows) {
        return WRONG_SIZES;
    }

    _result->rows = _left->rows;
    _result->cols = _right->cols;

    float *resultMatrix =
        malloc(sizeof(float) * (_result->rows * _result->cols));
    // float resultMatrix[_result->rows * _result->cols];
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
                         FloatMatrix *_result) {

    _result->cols = _left->cols;
    _result->rows = _left->rows;

    // float resultMatrix[_result->rows * _result->cols];
    float *resultMatrix =
        malloc(sizeof(float) * (_result->rows * _result->cols));

    int matrixIndex = 0;

    for (int index = 0; index < _result->rows * _result->cols; index++) {
        resultMatrix[matrixIndex++] =
            _left->values[index] + _right->values[index];
        printf("%.2f + %.2f = %.2f\n", _left->values[index],
               _right->values[index], resultMatrix[index]);
    }

    fflush(stdin);

    _result->values = resultMatrix;
}
