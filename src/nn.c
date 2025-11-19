#include "../include/nn.h"
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

    nn->output = malloc(sizeof(FloatMatrix));
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

    normalizeInput(input);

    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of this.

    FloatMatrix *prev_input;
    prev_input = input;

    for (int index = 0; index < _network->currentLayersNumber; index++) {

        FloatMatrix *linear_output = malloc(sizeof(FloatMatrix));

        // dot product with the weights
        MatrixErrors result = _network->layers[index].layerFunction(_network->layers[index].weights,
                                              prev_input, linear_output);
        printf("error result %d\n", result);

        free(prev_input->values);
        free(prev_input);

        // add the biases
        matrixAdditionFloat(linear_output, _network->layers[index].biases, 1);

        sigmoid(linear_output);

        prev_input = linear_output;
    }

    input = prev_input;

    // copy to output element by element
    for (int i = 0; i < input->rows * input->cols; i++) {
        _network->output->values[i] = input->values[i];
    }

    free(input->values);
    free(input);
}

void feedForwandSaveIntermediate(FloatMatrix *_input, NeuralNetwork *_network,
                                 FloatMatrix *_results) {
    _results[0].values = malloc(sizeof(float) * (_input->cols * _input->rows));

    _results[0].cols = _input->cols;
    _results[0].rows = _input->rows;

    for (int index = 0; index < _input->cols * _input->rows; index++) {
        _results[0].values[index] = _input->values[index];
    }

    // WARNING: I don't know if this is correct, could raise a problem
    normalizeInput(&_results[0]);

    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of
    // this.

    for (int index = 0; index < _network->currentLayersNumber; index++) {

        FloatMatrix *linear_output = malloc(sizeof(FloatMatrix));

        // dot product with the weights
        _network->layers[index].layerFunction(_network->layers[index].weights,
                                              &_results[index],
                                              &_results[index + 1]);

        // add the biases
        matrixAdditionFloat(linear_output, _network->layers[index].biases, 1);

        sigmoid(&_results[index + 1]);
    }

    // copy to output element by element
#define NET_OUTPUT _results[_network->currentLayersNumber + 1]
    for (int i = 0; i < NET_OUTPUT.rows * NET_OUTPUT.cols; i++) {
        _network->output->values[i] = NET_OUTPUT.values[i];
    }
}

void backPropagation(float _learningRate, NeuralNetwork *_network,
                     FloatMatrix _input[], FloatMatrix _output[],
                     int _batchSize) {
    // allocate memory to save biases variation
    FloatMatrix *biasesVariation =
        malloc(sizeof(FloatMatrix) * _network->currentLayersNumber);

    // allocate a delta matrix for each layer
    for (int index = 0; index < _network->currentLayersNumber; index++) {
        biasesVariation[index].cols = 1;
        biasesVariation[index].rows = _network->layers[index].nodes;
        biasesVariation[index].values =
            malloc(sizeof(float) * _network->layers[index].nodes);
    }

    // allocate memory to save weights variation
    FloatMatrix *weightsVariation =
        malloc(sizeof(FloatMatrix) * _network->currentLayersNumber);

    // allocate a delta matrix for each layer
    for (int index = 0; index < _network->currentLayersNumber; index++) {
        weightsVariation[index].cols = _network->layers[index].inputs;
        weightsVariation[index].rows = _network->layers[index].nodes;
        weightsVariation[index].values =
            malloc(sizeof(float) * _network->layers[index].nodes *
                   _network->layers[index].inputs);
    }

    // TODO: make this iterate _batchSize number of times, make the input an
    // array of arrays and understand how to cope with the training data as
    // input and how to save the status of the neural network maybe (like
    // writing things on a file and then loading them). You also need to update
    // the values of weights and biases at the end of every batch

    // make _batchSize passes to train the neural network
    for (int batchIndex = 0; batchIndex < _batchSize; batchIndex++) {
        // allocate memory to save intermediate results, add "+ 1" because we
        // want to include the input to this
        FloatMatrix *intermediateResult =
            malloc(sizeof(FloatMatrix) * (_network->currentLayersNumber + 1));

        for (int index = 1; index < _network->currentLayersNumber; index++) {
            intermediateResult[index].cols = 1;
            intermediateResult[index].rows = _network->layers[index].nodes;
            intermediateResult[index].values =
                malloc(sizeof(float) * _network->layers[index].nodes);
        }

        // forward propagation to find the calculated result and keep the
        // intermediate values
        feedForwandSaveIntermediate(&_input[batchIndex], _network,
                                    intermediateResult);

        // calculate the first error to the output
        meanSquaredError(_network->output, &_output[batchIndex]);

        // for each layer from the last to first
        for (int index = _network->currentLayersNumber - 1; index >= 0;
             index--) {
            // multiply the cost result with the derivative of the activation
            // function
            sigmoidDerivative(_network->output);
            multiplicationFloat(_network->output, &intermediateResult[index]);

            // update the biases variation average
            matrixAdditionFloat(&biasesVariation[index], _network->output,
                                _batchSize);
            FloatMatrix *tempDelta = NULL;
            tempDelta->cols = _network->output->cols;
            tempDelta->rows = _network->output->rows;
            tempDelta->values =
                malloc(sizeof(float) * tempDelta->cols * tempDelta->rows);

            // copy the value of delta into a temporary matrix
            for (int deltaIndex = 0;
                 deltaIndex < tempDelta->cols * tempDelta->rows; deltaIndex++) {
                tempDelta->values[deltaIndex] =
                    _network->output->values[deltaIndex];
            }
            // update the weights variation average
            transposeDotProductFloat(&intermediateResult[index], tempDelta);
            matrixAdditionFloat(&weightsVariation[index], tempDelta, 1);

            // dot prouct the previous result with the transpose of the weights
            // matrix to get the next error
            transposeDotProductFloat(_network->layers[index].weights,
                                     _network->output);
        }
    }

    // update the weigths and the biases for each layer
    for (int index = _network->currentLayersNumber - 1; index >= 0; index--) {
        matrixAdditionFloat(_network->layers[index].weights,
                            &weightsVariation[index], 1 / _learningRate);
        matrixAdditionFloat(_network->layers[index].biases,
                            &biasesVariation[index], 1 / _learningRate);
    }
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
