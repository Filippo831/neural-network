#include "../include/math_functions.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

void test_dot_product(void) {
    FloatMatrix a;
    float aArray[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    a.values = aArray;
    a.rows = 2;
    a.cols = 3;

    FloatMatrix b;
    float bArray[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    b.values = bArray;
    b.rows = 3;
    b.cols = 2;

    float result[] = {58.0, 64.0, 139.0, 154.0};

    float *functionResult = dotProductFloat(&a, &b);

    int isGood = 1;
    for (int index = 0; index < a.rows * b.cols; index++) {
        if (result[index] != functionResult[index]) {
            isGood = 0;
            break;
        }
    }

    CU_ASSERT_EQUAL(isGood, 0);
    // if (isGood == 1) {
    //     printf("test passed");
    // } else {
    //     printf("test not passed");
    // }
}

/* Suite Initialization and Cleanup Functions (optional, but good practice) */
int init_suite(void) {
    // Setup logic here (e.g., initializing a resource)
    return 0; // Return 0 on success
}

int clean_suite(void) {
    // Cleanup logic here (e.g., freeing a resource)
    return 0; // Return 0 on success
}

int main(void) {
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

    // Add the test case to the suite
    if ((CU_add_test(pSuite, "Test Dot Product Calculation",
                     test_dot_product)) == NULL) {
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
