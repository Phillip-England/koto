#include <stdlib.h>

#include "kbool.h"
#include "kstr.h"

size_t kstr_utf8_char_length(unsigned char byte) {
    if ((byte & 0x80) == 0x00) {
        return 1;
    } else if ((byte & 0xE0) == 0xC0) {
        return 2;
    } else if ((byte & 0xF0) == 0xE0) {
        return 3;
    } else if ((byte & 0xF8) == 0xF0) {
        return 4;
    } else {
        return 0;
    }
}

size_t kstr_pos(kstr *s) {
    return s->position;
}

kbool kstr_at_start(kstr *s) {
    if (s->position == 0) {
        return KTRUE;
    }
    return KFALSE;
}

kbool kstr_at_end(kstr *s) {
    if (s->position >= s->byte_count) {
        return KTRUE;
    }
    return KFALSE;
}

void kstr_goto_end(kstr *s) {
    while (kstr_at_end(s) == KFALSE) {
        kstr_next(s);
    }
}


void kstr_goto_start(kstr *s) {
    s->position = 0;
}

kbool kstr_out_of_bounds(kstr *s) {
    if (s->position > s->byte_count-1) {
        return KTRUE;
    }
    return KFALSE;
}

unsigned char kstr_last_char(kstr *s) {
    if (s->byte_count == 0) {
        return s->string[0];
    }
    return s->string[s->byte_count-1];
}

void kstr_goto_pos(kstr *s, size_t pos) {
    if (pos > s->byte_count) {
        kstr_goto_end(s);
        return;
    }
    s->position = pos;
}

size_t kstr_char_count(kstr *s) {
    size_t start = kstr_pos(s);
    kstr_goto_start(s);
    size_t count = 0;
    while (kstr_at_end(s) == KFALSE) {
        kstr_next(s);
        count += 1;
    }
    kstr_goto_pos(s, start);
    return count;
}

unsigned char kstr_char(kstr *s) {
    if (kstr_out_of_bounds(s) == KTRUE) {
        return 0;
    }
    unsigned char c = s->string[s->position];
    return c;
}


void kstr_next(kstr *s) {
    size_t char_len = kstr_utf8_char_length(kstr_char(s));
    s->position = s->position + char_len;
    if (kstr_out_of_bounds(s) == KTRUE) {
        kstr_goto_end(s);
    }
}


kstr *kstr_new(char *str) {
    size_t str_len = strlen(str);
    kstr *s = malloc(sizeof(kstr));
    if (!s) {
        return NULL;
    }
    s->byte_count = str_len+1;
    s->string = strdup(str);
    s->position = 0;
    if (kstr_last_char(s) != 0x00) {
        printf("KSTR: attempted to create a heap-allocated kstr, but the input is not null-terminated\n");
        return NULL;
    }
    s->char_count = kstr_char_count(s);
    return s;
}


void kstr_next_by(kstr *s, size_t by) {
    size_t count = 0;
    while (count != by) {
        kstr_next(s);
        count += 1;
    }
}

void kstr_prev(kstr *s) {
    while ((s->string[s->position] & 0xC0) == 0x80) {
        if (s->position == 0) break;
        s->position--;
    }

    if (s->position == 0) {
        return;
    } 
    s->position = s->position - 1;
    while (kstr_utf8_char_length(kstr_char(s)) == 0) {
        s->position = s->position - 1;
    }
}

void kstr_prev_by(kstr *s, size_t by) {
    size_t count = 0;
    while (count != by) {
        kstr_prev(s);
        count += 1;
    }
}

kstr *kstr_from_rng(kstr *s, size_t start, size_t end) {
    if (end > s->byte_count-1) {
        end = s->byte_count-1;
    }
    if (start > end) {
        start = end;
    }
    size_t len = end - start+1;
    char *buffer = malloc(len+1);
    if (!buffer) {
        return NULL;
    }
    memcpy(buffer, &s->string[start], len);
    buffer[len] = '\0';
    return kstr_new(buffer);
}


kstr *kstr_from_start(kstr *s) {
    if (s->position == 0) {
        char *buffer = malloc(1);
        buffer[0] = '\0';
        kstr *out = kstr_new(buffer);
        return out;
    }
    size_t len = s->position + 1;
    char *buffer = malloc(len+1);
    memcpy(buffer, &s->string[0], len);
    buffer[len] = '\0';
    return kstr_new(buffer);
}

kstr *kstr_from_end(kstr *s) {
    if (kstr_at_end(s)) {
        char *buffer = malloc(1);
        buffer[0] = '\0';
        kstr *out = kstr_new(buffer);
        return out;
    }
    size_t byte_count = s->byte_count;
    char *buffer = malloc(byte_count+1);
    memcpy(buffer, &s->string[s->position], byte_count);
    buffer[byte_count] = '\0';
    return kstr_new(buffer);
}

void kstr_dbg(kstr *s) {
    printf("DEBUGGING: kstr\n");
    printf("BYTE COUNT: %ld\n", s->byte_count);
    printf("CHAR COUNT: %ld\n", s->char_count);
    printf("POSITION: %ld\n", s->position);
    printf("STRING: %s\n", s->string);
    printf("CHAR: %c\n", kstr_char(s));
}

void kstr_free(kstr *s) {
    if (!s) return;
    if (s->string) free(s->string);
    free(s);
}


