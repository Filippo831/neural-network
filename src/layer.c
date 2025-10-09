#include "../include/layer.h"
#include <stdlib.h>

void initWeights(FloatMatrix *_input) {
    srand(time(NULL));

    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _input->values[index] = (float)(rand() % 40000) / 10000;
    }
}

void initBiases(FloatMatrix *_input) {
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _input->values[index] = 0;
    }
}

Layer *initLayer(int _inputs, int _nodes) {
    Layer *netLayer;

    netLayer->inputs = _inputs;
    netLayer->nodes = _nodes;

    // create a 1d matrix to store the biases, 1 for each node
    FloatMatrix biasesMatrix;
    biasesMatrix.cols = 1;
    biasesMatrix.rows = _nodes;
    netLayer->biases = &biasesMatrix;

    // create a 2d matrix to store the weights, # inputs number for each node
    FloatMatrix weightsMatrix;
    weightsMatrix.cols = 1;
    weightsMatrix.rows = _nodes;
    netLayer->weights = &weightsMatrix;

    return netLayer;
}
