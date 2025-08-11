#ifndef WORD_H_PROTECT
#define WORD_H_PROTECT

struct word_s {
    char *data;
    int size;
    int capacity;
};
typedef struct word_s word_t;
typedef word_t *word_ptr;

int word_init(word_ptr word);
int word_add_char(word_ptr word, int c);
void word_free(word_ptr *ptr);


#endif /* WORD_LIST_H_PROTECT */
