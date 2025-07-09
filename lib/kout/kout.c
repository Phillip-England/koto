
#include <stdlib.h>

#include "kbool.h"
#include "kout.h"


kout kout_ok(void *data) {
    kout out;
    out.data = data;
    out.err = NULL;
    return out;
}

kbool kout_is_err(kout out) {
    if (out.err) {
        return KTRUE;
    }
    return KFALSE;
}

kout kout_fail(void *err) {
    kout out;
    out.data = NULL;
    out.err = err;
    return out;
}

void *kout_get_err(kout out) {
    if (kout_is_err(out) == KFALSE) {
        KERR_PANIC("KOUT: attempted to unwrap an error when no error exists");
    }
    return out.err;
}

void *kout_get_data(kout out) {
    if (kout_is_err(out)) {
        KERR_PANIC("KOUT: attempted to unwrap data when no data exists");
    }
    return out.data;
}

#define KOUT_OK(void_data) kout_ok((void *)void_data);
#define KOUT_FAIL(void_err) kout_fail((void *)void_err);

