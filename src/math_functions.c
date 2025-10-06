#include "../include/math_functions.h"
#include <math.h>

/*
 * @param
 * _input: x value of the function
 *
 *   flatten the value to a range from -1 to 1
 *
 */
float sigmoid(float _input) {
    float result = 1 / (1 + exp(_input));
    return result;
}
