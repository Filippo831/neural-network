#include "../include/dataset.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

DatasetMetadata *readMetadata(FILE *_imageFile, FILE *_labelFile) {
    DatasetMetadata *metadata = malloc(sizeof(DatasetMetadata));

    // _imageFile
    // read the bytes from 0 to 15
    uint8_t imageData[IMAGE_HEADER_SIZE];

    size_t readBytes =
        fread(imageData, sizeof(imageData[0]), IMAGE_HEADER_SIZE, _imageFile);

    assert(readBytes == IMAGE_HEADER_SIZE);

    // check that the bytes 0-3 contains the value 2051 (0x803 in hex)
    assert(imageData[0] == 0 && imageData[1] == 0 &&
           imageData[2] == (0x803 & 0xff00) >> 8 &&
           imageData[3] == (0x803 & 0xff));

    // get the number of images written in bytes from 4-7
    uint32_t length = imageData[7] + (imageData[6] << 8) + (imageData[5] << 8) +
                      (imageData[4] << 8);
    metadata->length = length;

    // get number of pixel in row written in bytes from 8-11
    metadata->rowSize = imageData[11];
    assert(imageData[11] == 28);

    // get number of pixel in column written in bytes from 12-15
    metadata->colSize = imageData[15];
    assert(imageData[15] == 28);

    // label file
    uint8_t labelData[LABEL_HEADER_SIZE];
    readBytes =
        fread(imageData, sizeof(labelData[0]), LABEL_HEADER_SIZE, _labelFile);

    assert(readBytes == LABEL_HEADER_SIZE);

    // check that the bytes 0-3 contains the value 2049 (0x801 in hex)
    assert(imageData[0] == 0 && imageData[1] == 0 &&
           imageData[2] == (0x801 & 0xff00) >> 8 &&
           imageData[3] == (0x801 & 0xff));

    // get the number of images written in bytes from 4-7
    length = imageData[7] + (imageData[6] << 8) + (imageData[5] << 8) +
             (imageData[4] << 8);

    // check if it's equal to the previous found value
    assert(length == metadata->length);

    return metadata;
}

uint8_t *readImageBatch(size_t _batchSize, uint32_t _batchIndex,
                        FILE *_imageFile) {
    // allocate the array where the images batch will be stored
    uint8_t *images = malloc(sizeof(uint8_t) * 28 * 28 * _batchSize);

    // move forward by the header plus the batchSize * 28*28 (28*28 bytes per
    // image) * _batchIndex
    fseek(_imageFile, IMAGE_HEADER_SIZE + _batchSize * 28 * 28 * _batchIndex,
          SEEK_SET);

    size_t bytesRead =
        fread(images, sizeof(uint8_t), _batchSize * 28 * 28, _imageFile);

    // if I'm at the end of the file to read, write a code as last pixel to
    // signal that the dataset is over
    if (bytesRead < 28 * 28 * _batchSize) {
        images[28 * 28 * _batchSize - 1] = 0xff;
    }

    return images;
}

uint8_t *readLabelBatch(size_t _batchSize, uint32_t _batchIndex,
                        FILE *_labelFile) {
    // allocate the array where the labels batch will be stored
    uint8_t *labels = malloc(sizeof(uint8_t) * _batchSize);

    fseek(_labelFile, LABEL_HEADER_SIZE + _batchSize * _batchIndex, SEEK_SET);

    fread(labels, sizeof(uint8_t), _batchSize, _labelFile);

    return labels;
}
