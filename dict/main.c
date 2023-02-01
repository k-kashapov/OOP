#include <stdio.h>
#include "dict.h"

int main(int argc, const char **argv)
{
	struct dict_t dict;
	struct word_t word = { "JOJO", 4, 0 };

	dict_add(&dict, &word);
	dict_print(&dict);

	return 0;
}
