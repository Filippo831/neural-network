#include "../include/math_functions.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_dot_product_correct(void) {
    // ------------------- Setup Matrix A (2x2) -------------------
    // A = | 1.0  2.0 |
    //     | 3.0  4.0 |
    FloatMatrix a;
    float aArray[] = {1.0, 2.0, 3.0, 4.0};
    a.values = aArray;
    a.rows = 2;
    a.cols = 2;

    // ------------------- Setup Matrix B (2x1) -------------------
    // B = | 5.0 |
    //     | 6.0 |
    FloatMatrix b;
    float bArray[] = {5.0, 6.0};
    b.values = bArray;
    b.rows = 2;
    b.cols = 1;

    // ------------------- Expected Result (2x1) -------------------
    // R = A * B = | (1*5 + 2*6) | = | 17.0 |
    //             | (3*5 + 4*6) |   | 39.0 |
    float expectedResult[] = {17.0, 39.0};
    int expectedRows = 2;
    int expectedCols = 1;

    // ------------------- Perform Dot Product -------------------
    FloatMatrix c;
    int error = dotProductFloat(&a, &b, &c);

    // ------------------- Check for Errors -------------------
    if (error != NO_ERROR) {
        CU_FAIL("dotProductFloat returned an error");
        return;
    }

    // ------------------- Check Result Matrix Dimensions -------------------
    CU_ASSERT_EQUAL(c.rows, expectedRows);
    CU_ASSERT_EQUAL(c.cols, expectedCols);

    // ------------------- Check Result Matrix Values -------------------
    int isGood = 1;
    int totalElements = expectedRows * expectedCols;

    for (int index = 0; index < totalElements; index++) {
        // Use a small epsilon for floating point comparison (e.g., 0.0001)
        if (fabs(expectedResult[index] - c.values[index]) > 1e-4) {
            isGood = 0;
            break;
        }
    }

    CU_ASSERT_EQUAL(isGood, 1);
}

// create another test for the dot product with different sizes but still
// correct
void test_dot_product_correct_2(void) {
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

    FloatMatrix c;

    int error = dotProductFloat(&a, &b, &c);

    CU_ASSERT_EQUAL(error, NO_ERROR);

    float expectedResult[] = {58.0, 64.0, 139.0, 154.0};
    int expectedRows = 2;
    int expectedCols = 2;

    CU_ASSERT_EQUAL(c.rows, expectedRows);
    CU_ASSERT_EQUAL(c.cols, expectedCols);

    int isGood = 1;
    int totalElements = expectedRows * expectedCols;
    for (int index = 0; index < totalElements; index++) {
        if (fabs(expectedResult[index] - c.values[index]) > 1e-4) {
            isGood = 0;
            break;
        }
    }

    CU_ASSERT_EQUAL(isGood, 1);
}

// test the function dotProductFloat to see if it works as indended checking if
// the result is correct
void test_dot_product_wrong_sizes(void) {
    // ------------------- Setup Matrix A (2x2) -------------------
    FloatMatrix a;
    float aArray[] = {1.0, 2.0, 3.0, 4.0};
    a.values = aArray;
    a.rows = 2;
    a.cols = 2;

    // ------------------- Setup Matrix B (3x1) -------------------
    FloatMatrix b;
    float bArray[] = {5.0, 6.0, 7.0};
    b.values = bArray;
    b.rows = 3;
    b.cols = 1;

    // ------------------- Perform Dot Product -------------------
    FloatMatrix c;
    int error = dotProductFloat(&a, &b, &c);

    // ------------------- Check for WRONG_SIZES Error -------------------
    CU_ASSERT_EQUAL(error, WRONG_SIZES);
}

void test_loss_function(void) {
    // ------------------- Setup Data -------------------
    FloatMatrix predicted;
    float predictedValues[] = {1.5, 2.5, 3.5};
    predicted.cols = 1;
    predicted.rows = 3;
    predicted.values = predictedValues;

    FloatMatrix actual;
    float actualValues[] = {1.0, 2.0, 3.0};
    actual.cols = 1;
    actual.rows = 3;
    actual.values = actualValues;

    // ------------------- Expected Result -------------------
    // Calculated manually: ( (1.5-1.0)^2 + (2.5-2.0)^2 + (3.5-3.0)^2 ) / 3 =
    // 0.25
    float expectedLoss = 0.25;

    // ------------------- Calculate Loss -------------------
    float calculatedLoss = loss(&predicted, &actual);

    // ------------------- Check Result -------------------
    // Use an absolute tolerance (epsilon) for floating point comparison
    // to avoid failures due to minor precision issues.
    float tolerance = 1e-6;

    // CU_ASSERT_DOUBLE_EQUAL is typically the best choice for CUnit/similar
    // frameworks CU_ASSERT_DOUBLE_EQUAL(calculatedLoss, expectedLoss,
    // tolerance);

    // If CU_ASSERT_DOUBLE_EQUAL isn't available, use this manual check:
    int isGood = (fabs(calculatedLoss - expectedLoss) < tolerance);
    CU_ASSERT_EQUAL(isGood, 1);
}

// write a test for the matrices addition function
void test_matrix_addition(void) {
    // ------------------- Setup Matrix A (2x2) -------------------
    FloatMatrix a;
    float aArray[] = {1.0, 2.0, 3.0, 4.0};
    a.values = aArray;
    a.rows = 2;
    a.cols = 2;

    // ------------------- Setup Matrix B (2x2) -------------------
    FloatMatrix b;
    float bArray[] = {5.0, 6.0, 7.0, 8.0};
    b.values = bArray;
    b.rows = 2;
    b.cols = 2;

    // ------------------- Expected Result (2x2) -------------------
    // R = A + B = | (1+5) (2+6) | = | 6.0  8.0 |
    //             | (3+7) (4+8) |   | 10.0 12.0 |
    float expectedResult[] = {6.0, 8.0, 10.0, 12.0};
    int expectedRows = 2;
    int expectedCols = 2;

    // ------------------- Perform Matrix Addition -------------------
    matrixAdditionFloat(&a, &b);

    // ------------------- Check Result Matrix Dimensions -------------------
    CU_ASSERT_EQUAL(a.rows, expectedRows);
    CU_ASSERT_EQUAL(a.cols, expectedCols);

    // ------------------- Check Result Matrix Values -------------------
    int isGood = 1;
    int totalElements = expectedRows * expectedCols;

    for (int index = 0; index < totalElements; index++) {
        // Use a small epsilon for floating point comparison (e.g., 0.0001)
        if (fabs(expectedResult[index] - a.values[index]) > 1e-4) {
            isGood = 0;
            break;
        }
    }

    CU_ASSERT_EQUAL(isGood, 1);
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

    if ((CU_add_test(pSuite, "Test Dot Product Calculation correct case",
                     test_dot_product_correct)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((CU_add_test(pSuite, "Test Dot Product Calculation correct case #2",
                     test_dot_product_correct_2)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "Test Dot Product Calculation wrong sizes case",
                     test_dot_product_wrong_sizes)) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "Test loss function", test_loss_function)) ==
        NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((CU_add_test(pSuite, "Test matrix addition function",
                     test_matrix_addition)) == NULL) {
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
