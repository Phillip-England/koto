#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kstr.h"
#include "kbg.h"
#include "kbool.h"
#include "kerr.c"


void test_kerr(void) {

    // testing basic comparison
    kerr err = kerr_onstack("some err", __FILE__, __LINE__);
    if (strcmp(err.message, "some err\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }

    // testing macro generation
    kerr err_again = KERR_ONSTACK("another err");
    if (strcmp(err_again.message, "another err\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }

    // testing kout in error state
    kout out = KOUT_FAIL(KERR_ONHEAP("a test error"));
    if (kout_is_err(out) == KFALSE) {
        KERR_PANIC_TEST_FAILURE();
    }
    kerr *out_err = kout_err(out);
    if (strcmp(out_err->message, "a test error\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }
    kerr_free(out_err);

    // testing kout in data state
    kout another_out = KOUT_OK(KERR_ONHEAP("fake err"));
    kerr *fake_err = kout_data(another_out);
    if (strcmp(fake_err->message, "fake err\0") != 0) {
        KERR_PANIC_TEST_FAILURE();
    }
    kerr_free(fake_err);

}





int main() {
    test_kerr();
    // test_kstr();
    return EXIT_SUCCESS;
}



