#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kstr.h"
#include "kbg.h"
#include "kbool.h"

int main() {
    test_kstr();
    return EXIT_SUCCESS;
}

void test_kstr() {
    kstr *s = kstr_new("hello world!");
    kstr_goto_end(s);
    kstr_prev_by(s, 2);
    kstr_dbg(s);
}