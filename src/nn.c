#include "../include/nn.h"
#include <stdlib.h>

NeuralNetwork *createNeuralNetwork(int _totalLayersNumber, int _inputSize,
                                   int _outputSize) {
    NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));

    nn->totalLayersNumber = _totalLayersNumber;

    nn->layers = malloc(sizeof(Layer) * _totalLayersNumber);

    nn->input = malloc(sizeof(FloatMatrix));

    nn->input->cols = _inputSize;
    nn->input->rows = 1;
    float *inputArray = (float *)malloc(sizeof(float) * _inputSize);
    nn->input->values = inputArray;

    nn->output = malloc(sizeof(NeuralNetwork));
    nn->output->cols = _outputSize;
    nn->output->rows = 1;
    nn->output->values = (float *)malloc(sizeof(float) * _outputSize);

    return nn;
}

void addLayer(NeuralNetwork *_network, Layer *_layer) {
    _network->layers[_network->currentLayersNumber++] = *_layer;
}

void feedForward(FloatMatrix *_input, NeuralNetwork *_network) {

    FloatMatrix *result = malloc(sizeof(FloatMatrix));

    result->values =
        (float *)malloc(sizeof(float) * (_input->cols * _input->rows));
    result->cols = _input->cols;
    result->rows = _input->rows;

    if (_input->values != result->values) {
        for (int index = 0; index < _input->cols * _input->rows; index++) {
            result->values[index] = _input->values[index];
        }
    }

    sigmoid(result);


    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of this.

    for (int index = 0; index < _network->currentLayersNumber; index++) {
        FloatMatrix *temp;
        LayerFunctionErrors error = _network->layers[index].layerFunction(
            _network->layers[index].weights, result, temp);

        free(result->values);
        // free(result);
        //     
        result = temp;
        //
        // // TODO: fix with something nicer
        // if (error != 0) {
        //     printf("error in the feed forwand computation");
        // }

        // matrixAdditionFloat(result, _network->layers[index].biases, temp);

        // free(result->values);
        // free(result);
        //     
        // result = temp;
        sigmoid(result);
    }

    _network->output = result;
}
