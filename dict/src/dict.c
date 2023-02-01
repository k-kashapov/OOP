#include <stdio.h>
#include <string.h>
#include "dict.h"

#define INIT_LEN 100

int dict_init(struct dict_t *dict) {
    dict->arr = (struct word *)calloc(INIT_LEN, sizeof(struct word_t));
    dict->len = 0;

    return dict->arr == NULL;
}

int dict_add(struct dict_t *dict, struct word_t *word) {
    printf("Adding word: |%.*s| of len (%d)\n", word->len, word->text,
           word->len);

    return 0;
}

void dict_print(struct dict_t *dict) {
    printf(__FILE__ " (%d) - Print Not implemented!\n", __LINE__);
    return;
}
