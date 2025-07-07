#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kstr.h"
#include "kbg.h"
#include "kbool.h"
#include "kerr.c"


void test_kerr(void) {

    // testing basic comparison
    kerr err = kerr_new("some err", 0, __FILE__, __LINE__);
    if (strcmp(err.message, "some err\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }

    // testing macro generation
    kerr err_again = KERR_NEW("another err", 0);
    if (strcmp(err_again.message, "another err\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }

    // testing kout in error state
    kout out = kout_err(KERR_NEW("a test error", 0));
    if (!kout_is_err(out)) {
        KERR_PANIC_TEST_FAILURE();
    }
    kerr out_err = kout_err_unwrap(out);
    if (strcmp(out_err.message, "a test error\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }

    // testing kout in data state
    int *num = malloc(sizeof(int));
    num = 2;
    // kout another_out = kout_ok((void *)num);
    // int *num_unwrapped = (int *)kout_data_unwrap(another_out);
    // if (*num_unwrapped != 2) {
    //     KERR_PANIC_TEST_FAILURE();
    // }


}





int main() {
    test_kerr();
    // test_kstr();
    return EXIT_SUCCESS;
}



