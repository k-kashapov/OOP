#include "word_eng.h"
#include <string.h>
#include <ctype.h>

int word_eng_parse(char *str, struct word_t *dest)
{
    char *str_p = str;

    while(isalpha(*str_p++)) ;
    if (str_p <= str) return -1;

    char *text = (char *)malloc(str_p - str);
    if (text == NULL) 
    {
        return -1;
    }
    
    dest->len  = str_p - str;
    
    strncpy(text, str, dest->len);
    dest->text = text;

    return dest->len;
}

void word_eng_free(struct word_t *word)
{
    word_std_free(word);
}
