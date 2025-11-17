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
    uint8_t bytesPerChunk = 4;
    uint32_t imageData[IMAGE_HEADER_SIZE / bytesPerChunk];
    // FIX: change the endianess of the reading somehow
    size_t readBytes = fread(imageData, sizeof(imageData[0]),
                             IMAGE_HEADER_SIZE / bytesPerChunk, _imageFile);

    assert(readBytes == IMAGE_HEADER_SIZE / bytesPerChunk);

    // check that the bytes 0-3 contains the value 2051 (0x803 in hex)
    printf("numero magico: %b\n", imageData[0]);
    assert(imageData[0] == 0x803);
    // get the number of images written in bytes from 4-7
    metadata->length = imageData[1];
    // get number of pixel in row written in bytes from 8-11
    metadata->rowSize = imageData[2];
    assert(imageData[2] == 28);
    // get number of pixel in column written in bytes from 12-15
    metadata->colSize = imageData[3];
    assert(imageData[3] == 28);

    return metadata;
}
