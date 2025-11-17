#include "dataset.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_database_metadata_readings(void) {
    FILE *trainImages = fopen(
        "~/Desktop/projects/neural_network/dataset/t10k-images-idx3-ubyte",
        "rb");
    FILE *trainLabels = fopen(
        "~/Desktop/projects/neural_network/dataset/t10k-labels-idx1-ubyte",
        "rb");

    DatasetMetadata *result = readMetadata(trainImages, trainLabels);

    CU_ASSERT_EQUAL(result->colSize, 28);
    CU_ASSERT_EQUAL(result->rowSize, 28);
    CU_ASSERT_EQUAL(result->length, 10000);
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
    CU_pSuite pSuite =
        CU_add_suite("Vector Math Suite", init_suite, clean_suite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "test metadata readings",
                     test_database_metadata_readings)) == NULL) {
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
