#include "word.h"

void word_std_free(struct word_t *word) {
    if (!word)
        return;
    free(word->text);
    return;
}
