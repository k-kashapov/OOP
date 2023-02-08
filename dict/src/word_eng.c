#include "word_eng.h"
#include <ctype.h>
#include <string.h>

int word_eng_parse(char *str, struct word_t *dest) {
    char *str_init = str;
    while (*str == ' ')
        str++;

    char *str_p = str;

    while (isalpha(*str_p))
        str_p++;
    if (str_p <= str)
        return -1;

    char *text = (char *)malloc(str_p - str);
    if (text == NULL) {
        return -1;
    }

    dest->len = str_p - str;

    strncpy(text, str, dest->len);
    dest->text = text;

    return str_p - str_init;
}

void word_eng_free(struct word_t *word) { word_std_free(word); }
