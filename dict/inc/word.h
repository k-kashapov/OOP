#ifndef WORD_H
#define WORD_H

#include <stdlib.h>

struct word_t {
    char                *text;
    int                  len;
    struct word_methods *methods;
};

struct word_methods {
    char *type_name;
    
    struct word_t * (*word_alloc)(size_t len);
    struct word_t * (*word_parse)(char *str);
    void            (*word_free) (struct word_t *word);
};

struct word_t *word_std_alloc(size_t len);
void           word_std_free (struct word_t *word);

#endif // WORD_H
