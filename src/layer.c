#include "../include/layer.h"
#include <stdio.h>
#include <stdlib.h>

void initWeights(FloatMatrix *_input) {
    srand(time(NULL));

    _input->values = malloc(sizeof(float) * (_input->cols * _input->rows));
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _input->values[index] = (float)(rand() % 40000) / 10000;
    }
}

void initBiases(FloatMatrix *_input) {
    srand(time(NULL));

    _input->values = malloc(sizeof(float) * (_input->cols * _input->rows));
    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _input->values[index] = ((float)(rand() % 40000) / 10000) - 2.0;
    }
}

Layer *initLayer(int _inputs, int _nodes, LayerType _type) {
    Layer *netLayer = malloc(sizeof(Layer));

    netLayer->inputs = _inputs;
    netLayer->nodes = _nodes;

    // create a 1d matrix to store the biases, 1 for each node
    FloatMatrix *biasesMatrix = malloc(sizeof(FloatMatrix));
    biasesMatrix->values = malloc(sizeof(float) * _nodes);
    biasesMatrix->cols = 1;
    biasesMatrix->rows = _nodes;
    netLayer->biases = biasesMatrix;
    initBiases(biasesMatrix);

    // create a 2d matrix to store the weights, # inputs number for each node
    FloatMatrix *weightsMatrix = malloc(sizeof(FloatMatrix));
    weightsMatrix->values = malloc(sizeof(float) * _inputs * _nodes);
    weightsMatrix->cols = _inputs;
    weightsMatrix->rows = _nodes;
    netLayer->weights = weightsMatrix;
    initWeights(weightsMatrix);

    switch (_type) {
    case STANDART:
        netLayer->layerFunction = dotProductFloat;
    case CONVOLUTIONAL:
        // TODO: change this when convolutional function is implemented
        // printf("convolutional not implemented yet");
    }
    return netLayer;
}
