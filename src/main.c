#include "../include/main.h"
#include "data_convertion.h"
#include "dataset.h"
#include "math_functions.h"
#include "nn.h"
#include <stdio.h>

int main() {
    FILE *trainImages = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-images-idx3-ubyte",
                              "rb");
    if (!trainImages) {
        printf("error opening trainImage file\n");
        return 0;
    }
    FILE *trainLabels = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-labels-idx1-ubyte",
                              "rb");
    if (!trainLabels) {
        printf("error opening trainLabels file\n");
        return 0;
    }

    DatasetMetadata *result = readMetadata(trainImages, trainLabels);

    uint8_t *image = readImageBatch(1, 1, trainImages);

    NeuralNetwork *nn = createNeuralNetwork(3, 784, 10);

    Layer *layer1 = initLayer(784, 100, STANDART);
    addLayer(nn, layer1);

    Layer *layer2 = initLayer(100, 20, STANDART);
    addLayer(nn, layer2);

    Layer *layer3 = initLayer(20, 10, STANDART);
    addLayer(nn, layer3);

    FloatMatrix *input = uint8_tArrayToFloatMatrix(image, result->colSize * result->rowSize);


    feedForward(input, nn);

    for (int index = 0; index < 10; index++) {
        printf("%d: %f\n", index, nn->output->values[index]);
    }

    int parameters[] = {10};
    convolutionFloat(NULL, NULL, NULL, parameters);

    return 0;
}
