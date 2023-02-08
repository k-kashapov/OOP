#ifndef WORD_H
#define WORD_H

#include <stdlib.h>

struct word_t {
    char                *text;
    int                  len;
    int                  count;
    struct word_methods *methods;
};

struct word_methods {
    char *type_name;
    int  (*word_parse)(char *str, struct word_t *dest);
    void (*word_free) (struct word_t *word);
};

void word_std_free (struct word_t *word);

#endif // WORD_H
