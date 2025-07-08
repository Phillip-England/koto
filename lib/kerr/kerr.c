
#include <stdlib.h>

#include "kbool.h"

typedef struct {
    size_t line;
    char *file;
    char *message;
} kerr;

kerr kerr_onstack(char *message, char* file, size_t line) {
    kerr err;
    err.message = message;
    err.file = file;
    err.line = line;
    return err;
}

kerr *kerr_onheap(char *message, char* file, size_t line) {
    kerr *err = malloc(sizeof(kerr));
    err->file = strdup(file);
    err->line = line;
    err->message = strdup(message);
    return err;
}

void kerr_free(kerr *err) {
    if (err) {
        if (err->message) {
            free(err->message);
        }
        if (err->file) {
            free(err->file);
        }
        free(err);
    }
}

kbool kerr_is_empty(kerr err) {
    if (strcmp(err.message, "")) {
        return KTRUE;
    }
    return KFALSE;
}

void kerr_dbg(kerr err) {
    printf("🚨 (%s %ld) %s\n", err.file, err.line, err.message);
}

#define KERR_ONSTACK(message) kerr_onstack(message, __FILE__, __LINE__)
#define KERR_ONHEAP(message) kerr_onheap(message, __FILE__, __LINE__)

#define KERR_PANIC(message) \
    do { \
        kerr kerr_panic_queen = KERR_ONSTACK(message); \
        kerr_dbg(kerr_panic_queen); \
        printf("💣 PANICKING! SHUTTING DOWN..\n"); \
        exit(EXIT_FAILURE); \
    } while(0)

#define KERR_PANIC_TEST_FAILURE() KERR_PANIC("TEST FAILURE")
        

typedef struct {
    void *err;
    void *data;
} kout;

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

void *kout_err(kout out) {
    if (kout_is_err(out) == KFALSE) {
        KERR_PANIC("KOUT: attempted to unwrap an error when no error exists");
    }
    return out.err;
}

void *kout_data(kout out) {
    if (kout_is_err(out)) {
        KERR_PANIC("KOUT: attempted to unwrap data when no data exists");
    }
    return out.data;
}

#define KOUT_OK(void_data) kout_ok((void *)void_data);
#define KOUT_FAIL(void_err) kout_fail((void *)void_err);

