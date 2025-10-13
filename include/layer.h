#pragma once
#include "./math_functions.h"
#include <stdlib.h>
#include <time.h>

typedef enum LayerType {
    STANDART,
    CONVOLUTIONAL
} LayerType;

/*
 *   @params
 *   inputs: how many nodes are in the previous layer
 *   nodes: nodes of this layer
 *   biases: store the value of the biases for each node
 *   weights: store the value fo the weights for each connection coming from the
 * previous layer
 *
 *   activationFunction: attach the function that will be used to process input data
 */
typedef struct Layer {
    int inputs;
    int nodes;

    FloatMatrix *biases;
    FloatMatrix *weights;

    LayerFunctionErrors (*layerFunction)(FloatMatrix *, FloatMatrix *, FloatMatrix *);
} Layer;

/*
 *   @params
 *   _inputs: define the number of layer in the previous layer
 *   _nodes: define the amount of nodes in this layer
 *
 */

Layer *initLayer(int _inputs, int _nodes, LayerType _type);

/*
 * function that initialize the weights with a value
 * that ranges from -2 to 2
 */
void initWeights(FloatMatrix *_input);

/*
 * init biases to 0
 */
void initBiases(FloatMatrix *_input);
