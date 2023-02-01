#include <stdio.h>
#include "dict.h"
#include "parser.h"

struct word_t *test_parser(char *str)
{
	struct word_t *res = (struct word_t *)malloc(sizeof(struct word_t));
	
	res->text = str;
	res->len  = 4;
	
	return res;
}

int main(int argc, const char **argv) {
    struct dict_t dict;
    struct word_t word = {"JOJO", 4};
    struct word_t *word_p;

    struct parser_t parser = {};

    word_p = parser.parse_str("JOJO");

    dict_add(&dict, word_p);
    dict_print(&dict);

    return 0;
}
