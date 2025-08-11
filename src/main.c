#include "word_list.h"
#include "word.h"

#include <stdio.h>

int is_word_end(int c) 
{
    switch(c) {
        case ' ':
        case '\n':
        case '\t':
            return 1;
    }
    return 0;
}

int is_space(int c) 
{
    switch(c) {
        case ' ':
        case '\t':
            return 1;
    }
    return 0;
}

void string_repr(int c, char *value)
{
    switch (c) {
        case '\n':
            value[0] = '\\';
            value[1] = 'n';
            value[2] = '\0';
            break;
        case '\t':
            value[0] = '\\';
            value[1] = 't';
            value[2] = '\0';
            break;
        case '\r':
            value[0] = '\\';
            value[1] = 'r';
            value[2] = '\0';
            break;
        default:
            value[0] = (char) c;
            value[1] = '\0';
            break;
    }
}

void report_word(word_item_ptr item)
{
    printf("[%s]\n", item->word); 
}

int process_line(word_item_ptr *list)
{
    while (*list)
    {
        report_word(*list);
        list = &(*list)->next;
    }
    return 1;
}

void read_loop(void)
{
    int c;
    int in_word = 0;
    int quotation_mode = 0;
    int escaping = 0;
    word_t word;
    word_item_t *first = NULL;
    word_init(&word);
    printf("> ");
    while ((c = fgetc(stdin)) != EOF)
    {
        if ('"' == c && !escaping) {
            in_word = 1;
            quotation_mode = !quotation_mode;
            continue;
        }
        else if ('\\' == c && !escaping) {
            in_word = 1;
            escaping = 1;
            continue;
        }

        if (escaping) {
            escaping = 0;
            if ('"' == c || '\\' == c) {
                word_add_char(&word, c);
            } else {
                char repr[3];
                string_repr(c, repr);
                fprintf(stderr, "Error: escaping \"%s\" unsupported\n", repr);

                if(first) {
                    word_list_free(&first);
                }
                while(c != '\n' && c != EOF) {
                    c = fgetc(stdin);
                }
                word_free(&word);
                word_init(&word); /* NOTE: it is not just clear */
            }
        }
        else if (quotation_mode) {
            word_add_char(&word, c);
        } else {
            if (!is_word_end(c)) {      /* word start or center */
                in_word = 1;
                word_add_char(&word, c);
            } else if (is_word_end(c) && in_word) {   /* word end */
                word_add_char(&word, '\0');
                word_list_add_item(&first, word.data);
                in_word = 0;
                word_init(&word);
            }
        }

        if ('\n' == c) {                /* end of string */
            if (quotation_mode) {
                quotation_mode = 0;
                fprintf(stderr, "Error: unmached quotes\n");
            } else {
                process_line(&first);
            }
            word_list_free(&first);
            fprintf(stdout, "> ");
        }
    }
    word_free(&word);
    fprintf(stdout, "\nexit\n");
}

int main(void)
{
    read_loop();
    return 0;
}
