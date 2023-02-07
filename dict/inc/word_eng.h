#ifndef WORD_ENG_H
#define WORD_ENG_H

#include "word.h"

int  word_eng_parse(char *str, struct word_t *dest);
void word_eng_free (struct word_t *word);

#endif // WORD_ENG_H
