#pragma once
#include "../include/math_functions.h"
#include <stdint.h>

/*
 * @params
 * _input: the array of uint8_t values from which create the matrix
 * _size: the length of the array
 *
 * @body
 * create a column (used for input data for the neural network) matrix
 * (FLoatMatrix) with the values inside the heap
 *
 * @return
 * return the pointer to the matrix location
 *
 */

FloatMatrix *uint8_tArrayToFloatMatrix(uint8_t *_input, uint32_t _size);
