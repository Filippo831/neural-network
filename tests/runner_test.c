#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

int math_main(void);
int dataset_main(void);

int main() {
    CU_initialize_registry();

    math_main();
    dataset_main();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return 0;
}
