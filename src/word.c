#include "word.h"

#include <stdlib.h>

static enum { scale_factor = 2 };
static enum { initial_capacity = 10 };

int word_init(word_ptr word)
{
    word->size = 0;
    word->capacity = initial_capacity;
    /* definitly have to check errno */
    word->data = (char *)malloc(initial_capacity);
    if (!word->data)
        return 0;
    return 1;
}

static int string_copy(char *dest, const char *src) 
{
    int i;
    for(i = 0; src[i]; i++)
        dest[i] = src[i];
    return i;
}

static char *word_resize(word_ptr word)
{
    word_ptr new_word;
    new_word->size = word->size;
    new_word->capacity = word->capacity * scale_factor;
    new_word->data = (char *)malloc(new_word->capacity);
    string_copy(new_word->data, word->data);
    free(word->data);
}

/**
 *  Add a character to a word
 *
 *  Returns 0 if failed, and 1 on success
 */
int word_add_char(word_ptr word, int c)
{
    if (word->size >= word->capacity) {
        char *ptr = word_resize(word);
        if (!ptr)
            return 0;
    }
    word->data[word->size] = (char) c;
    word->size++;
}

void word_free(word_ptr *ptr)
{
    free((*ptr)->data);
}

