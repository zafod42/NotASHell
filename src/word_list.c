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

int word_list_add_item(word_item_ptr *list, char *word)
{
    int result;
    word_item_ptr tmp = NULL;
    result = word_list_init(&tmp, word);
    if (!*list) {
        *list = tmp;
        return result;
    }
    while ((*list)->next)
        list = &(*list)->next;
    (*list)->next = tmp;
    return result;
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

