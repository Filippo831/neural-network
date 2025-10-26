#include "../include/main.h"
#include "../include/nn.h"

#include <stdio.h>

int main(int argc, char **argv) {
    NeuralNetwork *nn = createNeuralNetwork(2, 10, 10);

    Layer *layer1 = initLayer(10, 10, STANDART);
    addLayer(nn, layer1);

    Layer *layer2 = initLayer(10, 5, STANDART);
    addLayer(nn, layer2);

    FloatMatrix input;
    input.cols = 1;
    input.rows = 10;
    float inputValues[] = {10, 3, 8, 6, 7, 9, 7, 8, 9, 9};
    input.values = inputValues;

    feedForward(&input, nn);

    printf("\n");
    for (int index = 0; index < 10; index++) {
        printf("%f, ", nn->output->values[index]);
    }
    printf("\n");
    

    free(layer1->biases);
    free(layer1->weights);
    free(layer1);
    free(layer2->biases);
    free(layer2->weights);
    free(layer2);
    free(nn);
    return 0;
}
