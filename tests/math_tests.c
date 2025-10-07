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
    for (int index = 0; index < a.rows * b.cols; index++){
        if (result[index] != functionResult[index]) {
            isGood = 0;
            break;
        }
    }

    CU_ASSERT_EQUAL(isGood, 1);
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

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    // Args: Suite Name, Init Function, Cleanup Function
    pSuite = CU_add_suite("AddTestSuite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the test to the suite */
    // Args: Suite Pointer, Test Name, Test Function
    if (NULL == CU_add_test(pSuite, "Test of add() function", test_dot_product)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Set the running mode and run the tests */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Clean up the registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
