#include "../include/main.h"
#include "dataset.h"
#include <stdio.h>

int main(int argc, char **argv) {
    FILE *trainImages = fopen("/home/filippoa/Desktop/projects/neural_network/dataset/t10k-images-idx3-ubyte", "rb");
    if (!trainImages) {
        printf("error opening trainImage file\n");
        return 0;
    }
    FILE *trainLabels = fopen("/home/filippoa/Desktop/projects/neural_network/dataset/t10k-labels-idx1-ubyte", "rb");
    if (!trainLabels) {
        printf("error opening trainLabels file\n");
        return 0;
    }

    DatasetMetadata *result = readMetadata(trainImages, trainLabels);

    return 0;
}
