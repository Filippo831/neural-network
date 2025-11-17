#pragma once

#include <stdint.h>
#include <stdio.h>

#define IMAGE_HEADER_SIZE 16
#define LABER_HEADER_SIZE 8

typedef struct DatasetMetadata{
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
