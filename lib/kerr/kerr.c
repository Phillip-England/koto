
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
    return err.message && strlen(err.message) > 0 ? KTRUE : KFALSE;
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
        
