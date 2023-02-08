#ifndef LIST_H
#define LIST_H

#include "word.h"

struct list_t {
    struct word_t *arr;
    size_t len;
    size_t cap;
};

int  list_init (struct list_t  list);
int  list_add  (struct list_t *list, struct word_t *word);
void list_print(struct list_t *list);
void list_free (struct list_t *list);

#endif // LIST_H
