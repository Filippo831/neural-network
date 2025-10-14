#include "../include/nn.h"

void addLayer(NeuralNetwork *_network, Layer *_layer) {
    _network->layers[_network->currentLayersNumber++] = *_layer;
}

FloatMatrix *feedForward(FloatMatrix *_input, NeuralNetwork *_network) {
    FloatMatrix *result;
    result = _input;

    // NOTE: using currentLayersNumber instead of totalLayersNumber because
    // probably it's safer but see if there is a better implementation of this.
    for (int index = 0; index < _network->currentLayersNumber; index++) {
        LayerFunctionErrors error = _network->layers[index].layerFunction(
            _network->layers[index].weights, result, result);

        // TODO: fix with something nicer
        if (error != 0) {
            printf("error in the feed forwand computation");
        }
        sigmoid(result);
    }

    return result;
}
