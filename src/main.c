#include "../include/main.h"
#include "../include/nn.h"

#include <stdio.h>

int main(int argc, char **argv) {
    NeuralNetwork *nn = createNeuralNetwork(3, 10, 10);

    Layer *layer1 = initLayer(10, 100, STANDART);
    addLayer(nn, layer1);

    Layer *layer2 = initLayer(100, 20, STANDART);
    addLayer(nn, layer2);

    Layer *layer3 = initLayer(20, 10, STANDART);
    addLayer(nn, layer3);

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
    

    freeNeuralNetwork(nn);
    return 0;
}
