#include "../include/data_convertion.h"

FloatMatrix *uint8_tArrayToFloatMatrix(uint8_t *_input, uint32_t _size) {
    FloatMatrix *returnMatrix = malloc(sizeof(FloatMatrix));

    returnMatrix->rows = _size;
    returnMatrix->cols = 1;
    returnMatrix->values = malloc(sizeof(float) * _size);
    
    for (uint32_t i = 0; i < _size; i++) {
        returnMatrix->values[i] = _input[i];
    }

    return returnMatrix;
}
