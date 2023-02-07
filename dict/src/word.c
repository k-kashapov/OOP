#include "word.h"

struct word_t *word_std_alloc(size_t len)
{
    struct word_t *res = (struct word_t *)malloc(sizeof(struct word_t));

    res->text = (char *)malloc(len);
    res->len  = 0;

    return res;
}

void word_std_free(struct word_t *word)
{
    if (!word) return;
    free(word->text);
    free(word);
    return;
}

