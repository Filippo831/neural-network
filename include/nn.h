#pragma once

#include "layer.h"

/*
 *   @params
 *   totalLayersNumber: the amount of layers in the neural network, need to be
 * defined at creation, not dynamic layers: pointer to a layers array that will
 * contain all the layers
 *
 * currentLayersNumber: amount of layers added to the neural network. Used to keep track at what intex to add the new inserted layers
 *   input: pointer to a matrix that will include all the input values
 *   output: pointer to a matrix that will include all the output values
 *
 */

typedef struct NeuralNetwork {
    int totalLayersNumber;
    Layer *layers;

    int currentLayersNumber;

    FloatMatrix *input;
    FloatMatrix *output;
} NeuralNetwork;

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
