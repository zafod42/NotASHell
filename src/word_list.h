#ifndef WORD_LIST_H_PROTECT
#define WORD_LIST_H_PROTECT

struct word_item_s {
    char *word;
    struct word_item_s *next;
};
typedef struct word_item_s word_item_t;
typedef word_item_t *word_item_ptr;

int word_list_add_item(word_item_ptr *list, char *word);
void word_list_free(word_item_ptr *ptr);


#endif /* WORD_LIST_H_PROTECT */
