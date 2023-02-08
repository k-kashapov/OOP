#include <stdio.h>
#include "list.h"

#define INIT_CAP 10
#define LIST_AT(idx)  (list->arr[i])
#define COUNT_AT(idx) (DICT_AT(idx).count)
#define TEXT_AT(idx)  (DICT_AT(idx).text)

int list_init(struct list_t *list) {
    list->len = 0;
    list->cap = INIT_CAP;
    list->arr = (struct word_t *)calloc(INIT_CAP, sizeof(struct word_t));

    return list->arr == NULL;
}

int list_add(struct list_t *list, struct word_t *word) {
    printf("Adding word: |%.*s| of len (%d)\n", word->len, word->text,
           word->len);

    for (size_t i = 0; i < list->len; i++) {
        if (!strncmp(TEXT_AT(i), word->text, word->len)) {
            printf("found word |%.*s| at (%ld)\n", word->len, word->text, i);

            COUNT_AT(i)++;
            word->methods->word_free(word);

            return 0;
        }
    }

    LIST_AT(list->len) = *word;
    list->len++;

    if (list->len >= list->cap - 1) {
        printf("resizing from cap = (%ld) to cap = (%ld)\n", list->cap, list->cap * 2);

        void *tmp = realloc(list->arr, list->cap * 2 * sizeof(struct word_t));
        if (tmp == NULL) {
            fprintf(stderr,
                    "ERROR: Could not resize listionary to (%ld) bytes.\n",
                    list->cap * 2 * sizeof(struct word_t));
            return -1;
        }
        list->arr = tmp;
        list->cap *= 2;
    }

    return 0;
}

void list_print(struct list_t *list) {
    for (size_t i = 0; i < list->len; i++) {
        printf("list[%ld] = |%.*s| seen (%d) times\n", i, list->arr[i].len,
               TEXT_AT(i), COUNT_AT(i));
    }

    return;
}

void list_free(struct list_t *list) {
    for (size_t i = 0; i < list->len; i++) {
        fprintf(stderr, "freeing list[%ld]\n", i);
        LIST_AT(i).methods->word_free(&list->arr[i]);
    }

    free(list->arr);
}
