#pragma once

#include "layer.h"

/*
 *   @params
 *   totalLayersNumber: the amount of layers in the neural network, need to be
 * defined at creation, not dynamic layers: pointer to a layers array that will
 * contain all the layers
 *
 * currentLayersNumber: amount of layers added to the neural network. Used to
 * keep track at what intex to add the new inserted layers input: pointer to a
 * matrix that will include all the input values output: pointer to a matrix
 * that will include all the output values
 *
 */

typedef struct NeuralNetwork {
    int totalLayersNumber;
    Layer *layers;

    int currentLayersNumber;

    // NOTE: for now these 2 values are not used because the feedForward
    // function uses a param as input and return as output
    FloatMatrix *input;
    FloatMatrix *output;

} NeuralNetwork;

/*
 *  @params
 *  _totalLayersNumber: amount of layers to add to the neural network
 *  _inputSize: size of input layer
 *  _outputSize: size of output layer
 *
 *  @body
 *  init the neural network and define the input and output sizes
 *
 *  @return
 *  return the pointer to the neural network created in the heap
 *
 */
NeuralNetwork *createNeuralNetwork(int _totalLayersNumber, int _inputSize,
                                   int _outputSize);

/*
 *  @params
 *  _network: the network where I want to add this layer
 *  _layer: layer to add
 *
 *  @body
 *  append the layer to the layer list and add the list
 *
 * CAREFUL
 * no control on amount of layers added, so you need to be careful when using
 * this function
 */
void addLayer(NeuralNetwork *_network, Layer *_layer);

/*
 * @params
 * _input: matrix containing input data
 * _network: network that will process that data
 *
 * @output
 * Matrix containing the result matrix
 *
 * @body
 * this function will pass every sigle layer of the neural network making the
 * calculation and passing the result to the next layer
 *
 */
void feedForward(FloatMatrix *_input, NeuralNetwork *_network);

/*
 * @params
 * _network: network to free the values from
 *
 * @body
 * free whatever was allocated to make the neural network work
 *
 * list of elements to free:
 * foreach layer:
 * - _network->layers->biasesMatrix->values
 * - _network->layers->biasesMatrix
 * - _network->layers->weightsMatrix->values
 * - _network->layers->weightsMatrix
 * end
 *
 * - _network->layers
 * - _network->input->values
 * - _network->values
 * - _network->output->values
 * - _network->output
 *
 */
void freeNeuralNetwork(NeuralNetwork *_network);
