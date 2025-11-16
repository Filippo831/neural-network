#include "../include/dataset.h"
#include <CUnit/CUnit.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

datasetMetadata *readMetadata(FILE *_imageFile, FILE *_labelFile) {
    //FIX: there is a segmentation fault somewhere
    datasetMetadata *metadata = malloc(sizeof(datasetMetadata));

    // _imageFile
    // read the bytes from 0 to 15
    int bytesPerChunk = 4;
    uint32_t imageData[IMAGE_HEADER_SIZE / bytesPerChunk];
    size_t readBytes = fread(imageData, sizeof(imageData[0]),
                             IMAGE_HEADER_SIZE / bytesPerChunk, _imageFile);
    CU_ASSERT_EQUAL(readBytes, IMAGE_HEADER_SIZE / bytesPerChunk)

    // check that the bytes 0-3 contains the value 2051 (0x803 in hex)
    CU_ASSERT_EQUAL(imageData[0], 0x803);
    // get the number of images written in bytes from 4-7
    metadata->length = imageData[1];
    // get number of pixel in row written in bytes from 8-11
    metadata->rowSize = imageData[2];
    CU_ASSERT_EQUAL(imageData[2], 28);
    // get number of pixel in column written in bytes from 12-15
    metadata->colSize = imageData[3];
    CU_ASSERT_EQUAL(imageData[3], 28);

    return metadata;
}
