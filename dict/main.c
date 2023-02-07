#include <stdio.h>
#include "dict.h"
#include "word_eng.h"

int main(int argc, const char **argv) {
    (void) argc;
    (void) argv;

    struct dict_t dict;
    struct word_methods meth = 
        {
            "english",
            word_eng_alloc,
            word_eng_parse,
            word_eng_free
        };

    

    return 0;
}
