#include "word.h"

struct dict_t
{
	struct word *arr;
	size_t       len;
};

int dict_add(struct dict_t *dict, struct word_t *word);

void dict_print(struct dict_t *dict);
