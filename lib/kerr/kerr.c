
#include <stdlib.h>

#include "kbool.h"

typedef struct {
    size_t line;
    char *file;
    char *message;
    size_t code;
} kerr;

kerr kerr_new(char *message, size_t code, char* file, size_t line) {
    kerr err;
    err.message = message;
    err.file = file;
    err.line = line;
    err.code = code;
    return err;
}

kbool kerr_is_empty(kerr err) {
    if (strcmp(err.message, "") == 0 && err.code == 0) {
        return KTRUE;
    }
    return KFALSE;
}

void kerr_dbg(kerr err) {
    printf("🚨 (%s %ld) %s\n", err.file, err.line, err.message);
}

#define KERR_NEW(message, code) kerr_new(message, code, __FILE__, __LINE__)

#define KERR_PANIC(message) \
    do { \
        kerr kerr_panic_queen = KERR_NEW(message, 0); \
        kerr_dbg(kerr_panic_queen); \
        printf("💣 PANICKING! SHUTTING DOWN..\n"); \
        exit(EXIT_FAILURE); \
    } while(0)

#define KERR_PANIC_TEST_FAILURE() KERR_PANIC("TEST FAILURE")
        

typedef struct {
    kerr err;
    void *data;
} kout;

kout kout_ok(void *data) {
    kout out;
    out.data = data;
    out.err = KERR_NEW("", 0);
    return out;
}

kbool kout_is_err(kout out) {
    if (out.data == NULL && !kerr_is_empty(out.err)) {
        return KTRUE;
    }
    return KFALSE;
}

kout kout_err(kerr err) {
    kout out;
    out.data = NULL;
    out.err = err;
    return out;
}

kerr kout_err_unwrap(kout out) {
    if (!kout_is_err(out)) {
        KERR_PANIC("KOUT: attempted to unwrap an error when no error exists");
    }
    return out.err;
}

void *kout_data_unwrap(kout out) {
    if (kout_is_err(out)) {
        KERR_PANIC("KOUT: attempted to unwrap data when no data exists");
    }
    return out.data;
}

