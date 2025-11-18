#include "dataset.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

void test_database_metadata_readings(void) {
    FILE *trainImages = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-images-idx3-ubyte",
                              "rb");
    if (!trainImages) {
        CU_FAIL("error reading image file");
    }
    FILE *trainLabels = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-labels-idx1-ubyte",
                              "rb");
    if (!trainLabels) {
        CU_FAIL("error reading label file");
    }

    DatasetMetadata *result = readMetadata(trainImages, trainLabels);

    CU_ASSERT_EQUAL(result->colSize, 28);
    CU_ASSERT_EQUAL(result->rowSize, 28);
    CU_ASSERT_EQUAL(result->length, 10000);

    fclose(trainImages);
    fclose(trainLabels);
}

void test_database_label_reading(void) {
#define BATCH_SIZE 16
    FILE *trainLabels = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-labels-idx1-ubyte",
                              "rb");

    uint8_t *batchArray = readLabelBatch(BATCH_SIZE, 3, trainLabels);

    uint8_t expected[] = {4, 4, 6, 3, 5, 5, 6, 0, 4, 1, 9, 5, 7, 8, 9, 3};

    for (int i = 0; i < BATCH_SIZE; i++) {
        if (batchArray[i] != expected[i]) {
            CU_FAIL("labels reading not correct");
        }
    }
}

void test_database_image_reading(void) {
    #define IMAGE_BATCH_SIZE 16
    FILE *trainImages = fopen("/home/filippoa/Desktop/projects/neural_network/"
                              "dataset/t10k-images-idx3-ubyte",
                              "rb");
    FILE *outputFile = fopen("/home/filippoa/Desktop/projects/neural_network/dataset/test-samples/t10k-images-16batch-8index-trim", "rb");
    uint8_t expectedImageArray[IMAGE_BATCH_SIZE * 28 * 28];
    fread(expectedImageArray, sizeof(uint8_t), IMAGE_BATCH_SIZE * 28 * 28, outputFile);

    uint8_t *imageBatchArray = readImageBatch(IMAGE_BATCH_SIZE, 8,  trainImages);

    for (int i = 0; i < IMAGE_BATCH_SIZE * 28 * 28; i++) {
        if (imageBatchArray[i] != expectedImageArray[i]) {
            CU_FAIL("image reading not correct");
        }
    }

}

int init_suite(void) {
    // Setup logic here (e.g., initializing a resource)
    return 0; // Return 0 on success
}

int clean_suite(void) {
    // Cleanup logic here (e.g., freeing a resource)
    return 0; // Return 0 on success
}

int dataset_main(void) {
    // Initialize CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("dataset Suite", init_suite, clean_suite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "test metadata readings",
                     test_database_metadata_readings)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "test label batch reading",
                     test_database_label_reading)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "test image batch reading",
                     test_database_image_reading)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Get failure count and cleanup
    unsigned int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    // Return the number of failures as the exit code
    return (int)num_failures;
}
