#include "word_eng.h"

struct word_t *word_eng_alloc(size_t len)
{
    return word_std_alloc(len);
}

struct word_t *word_eng_parse(char *str, struct word_t *word)
{
    return word;
}

void word_eng_free(struct word_t *word)
{
    word_std_free(word);
}
