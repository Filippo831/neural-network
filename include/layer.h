#pragma once

/*
 *   @params
 *   inputs: how many nodes are in the previous layer
 *   nodes: nodes of this layer
 *   biases: store the value of the biases for each node
 *   weights: store the value fo the weights for each connection coming from the
 * previous layer
 */
typedef struct Layer {
    int inputs;
    int nodes;
    float *biases;
    float *weights;
} Layer;

/*
 *   @params
 *   _inputs: define the number of layer in the previous layer
 *   _nodes: define the amount of nodes in this layer
 *
 */

Layer *initLayer(int _inputs, int _nodes);
