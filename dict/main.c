#include "dict.h"
#include "word_eng.h"
#include <stdio.h>

int main(int argc, const char **argv) {
    (void)argc;
    (void)argv;

    struct dict_t dict;
    struct word_methods meth = {"english", word_eng_parse, word_eng_free};

    int dict_err = dict_init(&dict);
    if (dict_err) {
        fprintf(stderr, "ERROR: could not init dictionary\n");
        return dict_err;
    }

    dict_read(&dict, "JOJO JOJO JOJO DIO DIO JOJO DIO a b e a b r t e d o", &meth);
    dict_print(&dict);

    dict_free(&dict);

    return 0;
}
