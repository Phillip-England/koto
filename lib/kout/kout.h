
/// kbg.h - utilities for debugging values quickly
#ifndef KOUT_H
#define KOUT_H

#include <stdlib.h>

#include "kbool.h"

/// represents the outcome of an operation and may contain an error or data
typedef struct {
    void *err;
    void *data;
} kout;

/// generate a stack-allocted kout with a pointer to void *data
kout kout_ok(void *data);

/// check if an instance of kout contains an error
kbool kout_is_err(kout out);

/// generate a stack-allocated kout with a pointer to void *err
kout kout_fail(void *err);

/// extract the err from an instance of kout
void *kout_get_err(kout out);

/// extract the data from an instance of kout
void *kout_get_data(kout out);

/// auto-convert the data passed into kout_ok() into a void*
#define KOUT_OK(void_data) kout_ok((void *)void_data);

/// auto-convert the data passed into kout_fail() into a void*
#define KOUT_FAIL(void_err) kout_fail((void *)void_err);

#endif