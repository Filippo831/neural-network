#include "../include/layer.h"
#include <stdlib.h>


Layer *initLayer(int _inputs, int _nodes) {
    Layer *netLayer;

    netLayer->inputs = _inputs;
    netLayer->nodes = _nodes;

    // create a 1d array to store the biases, 1 for each node
    float biasesList[_nodes];
    netLayer->biases = biasesList;

    // create a 2d array to store the weights, # inputs number for each node
    float weightList[_nodes * _inputs];
    netLayer->weights = weightList;

    return netLayer;
}
