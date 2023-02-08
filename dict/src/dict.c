#include "dict.h"
#include <stdio.h>
#include <string.h>

#define INIT_CAP 2

#define DICT_AT(idx) (dict->arr[idx])
#define TEXT_AT(idx) (DICT_AT(idx).text)
#define LEN_AT(idx) (DICT_AT(idx).len)
#define COUNT_AT(idx) (DICT_AT(idx).count)

int dict_init(struct dict_t *dict) {
    dict->len = 0;
    dict->cap = INIT_CAP;
    dict->arr = (struct word_t *)calloc(INIT_CAP, sizeof(struct word_t));

    return dict->arr == NULL;
}

int dict_read(struct dict_t *dict, char *str, struct word_methods *meth) {
    static int line = 0;

    struct word_t word;
    word.methods = meth;
    word.count = 1;
    word.line = ++line;

    int added = 0;

    int res = meth->word_parse(str, &word);
    printf("res = (%d)\n", res);

    for (; res > 0; added++) {
        int add_err = dict_add(dict, &word);
        if (add_err) {
            fprintf(stderr, "ERROR while adding word to dictionary!\n");
            break;
        }

        printf("dict add worked!\n");

        str += res;

        printf("str left = %s\n", str);

        res = meth->word_parse(str, &word);
        printf("res = (%d)\n", res);
    }

    return added;
}

int dict_add(struct dict_t *dict, struct word_t *word) {
    printf("Adding word: |%.*s| of len (%d)\n", word->len, word->text,
           word->len);

    for (size_t i = 0; i < dict->len; i++) {
        if (!strncmp(TEXT_AT(i), word->text, word->len)) {
            printf("found word |%.*s| at (%ld)\n", word->len, word->text, i);

            COUNT_AT(i)++;
            word->methods->word_free(word);

            return 0;
        }
    }

    DICT_AT(dict->len) = *word;
    dict->len++;

    if (dict->len >= dict->cap - 1) {
        printf("resizing from cap = (%ld) to cap = (%ld)\n", dict->cap, dict->cap * 2);

        void *tmp = realloc(dict->arr, dict->cap * 2 * sizeof(struct word_t));
        if (tmp == NULL) {
            fprintf(stderr,
                    "ERROR: Could not resize dictionary to (%ld) bytes.\n",
                    dict->cap * 2 * sizeof(struct word_t));
            return -1;
        }
        dict->arr = tmp;
        dict->cap *= 2;
    }

    return 0;
}

void dict_print(struct dict_t *dict) {
    for (size_t i = 0; i < dict->len; i++) {
        printf("dict[%ld] = |%.*s| seen (%d) times\n", i, dict->arr[i].len,
               TEXT_AT(i), COUNT_AT(i));
    }

    return;
}

void dict_free(struct dict_t *dict) {
    for (size_t i = 0; i < dict->len; i++) {
        fprintf(stderr, "freeing arr[%ld]\n", i);
        DICT_AT(i).methods->word_free(&dict->arr[i]);
    }

    free(dict->arr);
}
