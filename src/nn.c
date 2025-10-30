#include "../include/nn.h"
#include <stdio.h>
#include <stdlib.h>

NeuralNetwork *createNeuralNetwork(int _totalLayersNumber, int _inputSize,
                                   int _outputSize) {
    NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));

    nn->totalLayersNumber = _totalLayersNumber;
    nn->currentLayersNumber = 0;

    nn->layers = malloc(sizeof(Layer) * _totalLayersNumber);

    nn->input = malloc(sizeof(FloatMatrix));

    nn->input->cols = _inputSize;
    nn->input->rows = 1;
    nn->input->values = malloc(sizeof(float) * _inputSize);

    nn->output = malloc(sizeof(NeuralNetwork));
    nn->output->cols = _outputSize;
    nn->output->rows = 1;
    nn->output->values = malloc(sizeof(float) * _outputSize);

    return nn;
}

void addLayer(NeuralNetwork *_network, Layer *_layer) {
    _network->layers[_network->currentLayersNumber++] = *_layer;
}

void feedForward(FloatMatrix *_input, NeuralNetwork *_network) {

    FloatMatrix *input = malloc(sizeof(FloatMatrix));

    input->values = malloc(sizeof(float) * (_input->cols * _input->rows));

    input->cols = _input->cols;
    input->rows = _input->rows;

    for (int index = 0; index < _input->cols * _input->rows; index++) {
        input->values[index] = _input->values[index];
    }

    sigmoid(input);

    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of this.

    FloatMatrix *prev_input = input;

    for (int index = 0; index < _network->currentLayersNumber; index++) {

        FloatMatrix *linear_output = malloc(sizeof(FloatMatrix));
        _network->layers[index].layerFunction(_network->layers[index].weights,
                                              prev_input, linear_output);

        free(prev_input->values);
        free(prev_input);

        FloatMatrix *biased_output = malloc(sizeof(FloatMatrix));
        matrixAdditionFloat(linear_output, _network->layers[index].biases,
                            biased_output);

        free(linear_output->values);
        free(linear_output);

        sigmoid(biased_output);

        prev_input = biased_output;
    }

    input = prev_input;

    // copy to output element by element
    for (int i = 0; i < input->rows * input->cols; i++) {
        _network->output->values[i] = input->values[i];
    }

    free(input->values);
    free(input);
}

void backPropagation(float _learningRate, NeuralNetwork *_nn,
                     FloatMatrix *_input, FloatMatrix *_output,
                     int _batchSize) {
    // allocate memory to save the deltas values
    FloatMatrix *deltas =
        malloc(sizeof(FloatMatrix) * _nn->currentLayersNumber);

    // allocate a delta matrix for each layer
    for (int index = 0; index < _nn->currentLayersNumber; index++) {
        deltas[index].cols = 1;
        deltas[index].rows = _nn->layers[index].nodes;
        deltas[index].values = malloc(sizeof(float) * _nn->layers[index].nodes);
    }

    // forward propagation to find the calculated result
    feedForward(_input, _nn);

    // calculate the first error to the output


    // for each layer

    // multiply the cost result with the derivative of the activation function

    // sum the value got to the delta matrix by the previous values and itself
    // divided by the batch size to make an average

    // dot prouct the previous result with the transpose of the weights matrix
    // to get the next error
}

void freeNeuralNetwork(NeuralNetwork *_network) {
    free(_network->input->values);
    free(_network->input);
    free(_network->output->values);
    free(_network->output);

    for (int index = 0; index < _network->currentLayersNumber; index++) {
        free(_network->layers[index].biases->values);
        free(_network->layers[index].biases);
        free(_network->layers[index].weights->values);
        free(_network->layers[index].weights);
    }
    free(_network->layers);
    free(_network);
}
