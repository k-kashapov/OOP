#include "dict.h"
#include <stdio.h>
#include <string.h>

#define INIT_LEN 100

int dict_init(struct dict_t *dict) {
    dict->len = 0;
    dict->arr = (struct word_t *)calloc(INIT_LEN, sizeof(struct word_t));

    return dict->arr == NULL;
}

int dict_read(struct dict_t *dict, char *str, struct word_methods *meth) {
    struct word_t word;
    word.methods = meth;

    int added = 0;

    int res = meth->word_parse(str, &word);

    for (; res > 0; added++) {
        int add_err = dict_add(dict, &word);

        if (add_err) {
            fprintf(stderr, "ERROR while adding word to dictionary!\n");
            break;
        }

        str += res;
    }

    return added;
}

int dict_add(struct dict_t *dict, struct word_t *word) {
    printf("Adding word: |%.*s| of len (%d)\n", word->len, word->text,
           word->len);

    for (size_t i = 0; i < dict->len; i++) {
        if (!strncmp(dict->arr[i].text, word->text, word->len)) {
            printf("found word |%.*s| at (%ld)\n", word->len, word->text, i);
            return 0;
        }
    }

    dict->arr[dict->len] = *word;
    dict->len++;

    return 0;
}

void dict_print(struct dict_t *dict) {
    (void)dict;
    printf(__FILE__ " (%d) - Print Not implemented!\n", __LINE__);
    return;
}

void dict_free(struct dict_t *dict) {
    for (size_t i = 0; i < dict->len; i++) {
        dict->arr[i].methods->word_free(&dict->arr[i]);
    }

    free(dict->arr);
}
