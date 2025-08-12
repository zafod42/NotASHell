#include "word_list.h"

#include <stdlib.h>

static int word_list_init(word_item_ptr *list, char *word)
{
    *list = (word_item_ptr)malloc(sizeof(word_item_t));
    if (!*list)
        return 0;
    (*list)->word = word; 
    (*list)->next = NULL;
    return 1;
}

word_item_ptr word_list_add_item(word_item_ptr *list, char *word)
{
    word_item_ptr tmp = NULL;
    word_list_init(&tmp, word);
    if (!*list) {
        *list = tmp;
    } else {
        (*list)->next = tmp;
    }
    return tmp;
}

void word_list_free(word_item_ptr *ptr) 
{
    while (*ptr) {
        word_item_ptr tmp = *ptr;
        *ptr = (*ptr)->next;
        free(tmp->word);
        free(tmp);
    }
}

