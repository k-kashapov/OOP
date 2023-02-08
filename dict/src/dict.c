#include <stdio.h>
#include <string.h>
#include "dict.h"
#include "list.h"

#define DICT_CAP 20

#define DICT_AT(idx) (dict->arr[idx])
#define LEN_AT(idx) (DICT_AT(idx).len)

int dict_init(struct dict_t *dict) {
    dict->cap = INIT_CAP;
    dict->arr = (struct list_t *)calloc(INIT_CAP, sizeof(struct list_t));

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

int dict_add(struct dict_t *dict, struct word_t *word)
{
    

    return 0;
}

void dict_print(struct dict_t *dict) {
    return;
}

void dict_free(struct dict_t *dict) {
    for(size_t list = 0; list < dict->len)
    {
        list_free(dict->arr[list]);
    }

    free(dict->arr);
}
