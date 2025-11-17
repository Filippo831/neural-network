#pragma once

#include <stdint.h>
#include <stdio.h>

#define IMAGE_HEADER_SIZE 16
#define LABEL_HEADER_SIZE 8

typedef struct DatasetMetadata {
    uint32_t length;
    uint32_t rowSize;
    uint32_t colSize;
} DatasetMetadata;

/*
 * @param
 * _imageFile: pointer to the image file
 * _labelFile: pointer to the label file
 *
 * @body
 * following the rules below get the information about the dataset
 *
 * IMAGE DATASET
 * Offset (Bytes)       Content                      Description
 *
 * 0 - 3            Magic number       2051 (0x803 in hex)
 * 4 - 7            Number of images   Total images in the dataset
 * 8 - 11           Rows               Should be 28
 * 12 - 15          Columns            Should be 28
 * 16 - ***         Pixel data         Each pixel is an unsigned value (0-255)
 *
 * LABEL DATASET
 * Offset (Bytes)        Content                    Description
 * ---------------- ------------------- -----------------------------------
 * 0 - 3             Magic number        2049 (0x801 in hex)
 * 4 - 7             Number of labels    Total labels in the dataset
 * 8 - ***           Label Data          Each label is a single byte (0-9)
 *
 *
 */
DatasetMetadata *readMetadata(FILE *_imageFile, FILE *_labelFile);

/*
 * @param
 * _batchSize: how many images there are per _batch
 * _batchIndex: get the offset from where to start reading the images
 * _imageFile: the file from where read the images
 *
 * @body
 * read the images and store them inside an array of array
 * the array will have size _bathSize and in every position there is a pointer
 * to another array with size 28*28*1 bytes = 784
 *
 * @return
 * return the array with the images written, the array is stored in the heap
 * if the amound of byte read is less than the batch size write a white pixel as
 * last value to signal that it happened
 *
 */

// TODO: maybe insert a metadata variable as input to make the sizes of the
// images variable if using a different dataset
uint8_t *readImageBatch(size_t _batchSize, uint32_t _batchIndex,
                        FILE *_imageFile);

/*
 * @param
 * _batchSize: how many images there are per _batch
 * _batchIndex: get the offset from where to start reading the images
 * _labelFile: the file from where read the labels
 *
 * @body
 * read the labels and write them into an array written on the heap. Every label
 * is 1 byte long
 *
 * @return
 * return the array where the labels are written
 *
 */

uint8_t *readLabelBatch(size_t _batchSize, uint32_t _batchIndex,
                        FILE *_labelFile);
