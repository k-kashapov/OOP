#ifndef WORD_ENG_H
#define WORD_ENG_H

#include "word.h"

struct word_t *word_eng_alloc(size_t len);
struct word_t *word_eng_parse(char *str);
void           word_eng_free (struct word_t *word);

#endif // WORD_ENG_H
