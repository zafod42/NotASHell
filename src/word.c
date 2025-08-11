#include "word.h"

#include <stdlib.h>

static enum { scale_factor = 2 };
static enum { initial_capacity = 10 };

int word_init(word_ptr word)
{
    word->data = (char *)malloc(initial_capacity);
    if (!word->data)
        return 0;
    word->size = 0;
    word->capacity = initial_capacity;
    /* definitly have to check errno */
    return 1;
}

static int string_n_copy(char *dest, const char *src, int n) 
{
    int i;
    for (i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
    return i;
}

static char *word_resize(word_ptr word)
{
    char *new_data;
    word->capacity *= scale_factor;
    new_data = (char *)malloc(word->capacity);
    string_n_copy(new_data, word->data, word->size);
    free(word->data);
    word->data = new_data;
    return new_data;
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
    return 1;
}

void word_free(word_ptr ptr)
{
    free(ptr->data);
}

