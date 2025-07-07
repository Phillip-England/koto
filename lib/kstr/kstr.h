


#ifndef KSTR_H
#define KSTR_H

#include <stdlib.h>
#include "kbool.h"

size_t kstr_utf8_char_length(unsigned char byte);

struct kstr {
    size_t byte_count;
    size_t char_count;
    size_t position;
    char *string;
};

typedef struct kstr kstr;

size_t kstr_pos(kstr *s);
kbool kstr_at_start(kstr *s);
kbool kstr_at_end(kstr *s);
void kstr_goto_end(kstr *s);
void kstr_goto_start(kstr *s);
kbool kstr_out_of_bounds(kstr *s);
unsigned char kstr_last_char(kstr *s);
void kstr_goto_pos(kstr *s, size_t pos);
size_t kstr_char_count(kstr *s);
unsigned char kstr_char(kstr *s);
void kstr_next(kstr *s);
kstr *kstr_new(char *str);
void kstr_next_by(kstr *s, size_t by);
void kstr_prev(kstr *s);
void kstr_prev_by(kstr *s, size_t by);
kstr *kstr_from_rng(kstr *s, size_t start, size_t end);
kstr *kstr_from_start(kstr *s);
kstr *kstr_from_end(kstr *s);
void kstr_dbg(kstr *s);
void kstr_free(kstr *s);

#endif
