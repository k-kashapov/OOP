#ifndef DICT_H
#define DICT_H

#include "word.h"

struct dict_t {
    struct list_t *arr;
    size_t cap;
};

int  dict_init (struct dict_t *dict);
int  dict_read (struct dict_t *dict, char *str, struct word_methods *meth);
int  dict_add  (struct dict_t *dict, struct word_t *word);
void dict_print(struct dict_t *dict);
void dict_free (struct dict_t *dict);

#endif // DICT_H
