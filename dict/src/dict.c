#include "dict.h"
#include <stdio.h>

int dict_add(struct dict_t *dict, struct word_t *word)
{
	printf("Adding word: |%.*s| of len (%d)\n",
			word->len, word->text, word->len);
	return 0;
}

void dict_print(struct dict_t *dict)
{
	printf(__FILE__ " (%d) - Print Not implemented!\n", __LINE__);
	return;
}
