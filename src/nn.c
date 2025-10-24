#include "../include/nn.h"
#include <stdio.h>
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

    FloatMatrix *input = malloc(sizeof(FloatMatrix));

    input->values =
        (float *)malloc(sizeof(float) * (_input->cols * _input->rows));

    input->cols = _input->cols;
    input->rows = _input->rows;

    for (int index = 0; index < _input->cols * _input->rows; index++) {
        input->values[index] = _input->values[index];
    }

    sigmoid(input);

    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of this.

    FloatMatrix *toFree;
    for (int index = 0; index < _network->currentLayersNumber; index++) {
        // printf("\n");
        // for (int i = 0; i < input->rows * input->cols; i++) {
        //     printf("%f ", input->values[i]);
        // }
        // printf("\n");
        FloatMatrix *temp = malloc(sizeof(FloatMatrix));
        LayerFunctionErrors error = _network->layers[index].layerFunction(
            _network->layers[index].weights, input, temp);


        printf("\n");
        for (int i = 0; i < temp->rows * temp->cols; i++) {
            printf("%f ", temp->values[i]);
        }
        printf("\n");

        printf("\n");
        toFree = input;
        input = temp;
        free(toFree->values);
        free(toFree);

        // TODO: fix with something nicer
        if (error != 0) {
            printf("error in the feed forwand computation");
        }

        FloatMatrix *temp2 = malloc(sizeof(FloatMatrix));
        matrixAdditionFloat(input, _network->layers[index].biases, temp2);

        toFree = input;
        input = temp2;
        sigmoid(input);

        free(toFree->values);
        free(toFree);
    }

    // copy to output element by element
    for (int i = 0; i < input->rows * input->cols; i++) {
        _network->output->values[i] = input->values[i];
    }

    // print output matrix
    printf("\n\n");
    for (int i = 0; i < _network->output->rows * _network->output->cols; i++) {
        printf("%f ", _network->output->values[i]);
    }
    printf("\n");

    free(input);
}
