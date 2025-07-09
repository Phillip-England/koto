

/// kerr.h - an error type with file and line number tracing built in
#ifndef KERR_H
#define KERR_H

#include <stdlib.h>

#include "kbool.h"
#include "kstr.h"

/// kerr enables us to quickly track down where errors in our application have occurred
/// can be heap or stack allocated
/// quality of life macros: KERR_ONSTACK, KERR_ONHEAP, KERR_PANIC, ect
typedef struct {
    size_t line;
    char *file;
    char *message;
} kerr;

/// allocated a new instance of kerr on the stack
kerr kerr_onstack(char *message, char* file, size_t line);

/// allocated a new instance of kerr on the heap
kerr *kerr_onheap(char *message, char* file, size_t line);

/// free a heap allocated kerr
void kerr_free(kerr *err);

/// returns KTRUE if the error is empty
kbool kerr_is_empty(kerr err);

/// returns a kerr represented as a kstr
kstr kerr_str(kerr err);

/// print out a kerr in the terminal
void kerr_dbg(kerr err);

/// a macro to auto-insert the __FILE__ and __LINE__ with kerr_onstack()
#define KERR_ONSTACK(message) kerr_onstack(message, __FILE__, __LINE__)

/// a macro to auto-insert the __FILE__ and __LINE__ with kerr_onheap()
#define KERR_ONHEAP(message) kerr_onheap(message, __FILE__, __LINE__)

/// a macro for generating a kerr, printing it, and then exiting the program
#define KERR_PANIC(message) \
    do { \
        kerr kerr_panic_queen = KERR_ONSTACK(message); \
        kerr_dbg(kerr_panic_queen); \
        printf("💣 PANICKING! SHUTTING DOWN..\n"); \
        exit(EXIT_FAILURE); \
    } while(0)

/// a macro to quickly shutdown on test failure
#define KERR_PANIC_TEST_FAILURE() KERR_PANIC("TEST FAILURE")

#endif