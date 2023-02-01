#include <stdlib.h>

struct word_t {
    char *text;
    int len;
};

struct word_methods {
	char *parser_name;
	
	struct word_t* (*word_alloc)(size_t len);
	struct word_t* (*parse_str)(char *str);
	void           (*word_free) (size_t len);
}
