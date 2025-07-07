#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kstr.c"
#include "kbg.c"

int main() {

    kstr *s = kstr_new("hello world!");
    kstr_goto_end(s);
    kstr_prev_by(s, 2);
    kstr_dbg(s);



    


    return EXIT_SUCCESS;
}