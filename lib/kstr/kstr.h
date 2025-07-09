


#ifndef KSTR_H
#define KSTR_H

#include <stdlib.h>
#include "kbool.h"

/// count the number of utf-8 characters in a series of bytes
size_t kstr_utf8_char_length(unsigned char byte);

/// a utf-8 string type with cursor-based traversing
struct kstr {
    size_t byte_count;
    size_t char_count;
    size_t position;
    char *string;
};

/// quality of life typedef
typedef struct kstr kstr;

/// get the cursor position from the provided kstr
size_t kstr_pos(kstr *s);

/// returns KTRUE if the kstr position is equal to 0
kbool kstr_at_start(kstr *s);

/// return KTRUE if the kstr position is at the end of our bytes
kbool kstr_at_end(kstr *s);

/// moves our kstr position to the end of our bytes
void kstr_goto_end(kstr *s);

/// moves our kstr position to the start of our bytes
void kstr_goto_start(kstr *s);

/// returns KTRUE if the kstr position is out of bounds
kbool kstr_out_of_bounds(kstr *s);

/// get the last utf-8 character from the kstr
unsigned char kstr_last_char(kstr *s);

/// moves our kstr position to a specific position
void kstr_goto_pos(kstr *s, size_t pos);

/// count the number of utf-8 characters in a kstr
size_t kstr_char_count(kstr *s);

/// move the kstr position to the start of the next utf-8 char
void kstr_next(kstr *s);

/// create a heap-allocated kstr
kstr *kstr_onheap(char *str);

/// create a stack-allocated kstr
kstr kstr_onstack(char *str);

/// move the kstr position forward by a certain number of utf-8 chars
void kstr_next_by(kstr *s, size_t by);

/// move the kstr position backwards by one utf-8 char
void kstr_prev(kstr *s);

/// move the kstr position backwards by a certain number of utf-8 chars
void kstr_prev_by(kstr *s, size_t by);

/// extract bytes from a certain character range
kstr *kstr_bytes_from_rng(kstr *s, size_t start, size_t end);

/// extract bytes from the start the the kstr until the current position
kstr *kstr_bytes_from_start(kstr *s);

/// extract bytes from the current position to the end of the kstr
kstr *kstr_bytes_from_end(kstr *s);

/// print the kstr to the terminal
void kstr_dbg(kstr *s);

/// free a heap-allocated kstr
void kstr_free(kstr *s);

#endif
