#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

static enum {
    no_error = -1,
    no_mem,
    cant_escape,
    unmatched_quotes
};

static const char *errors[] =
{
    "Can't allocate memmory",
    "Can't escape \"%s\"",
    "Unmatched quotes"
};

static void string_repr(int c, char *value)
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

void analyser_print_error(analyser_ptr ptr)
{
    char repr[3];
    const char *err = errors[ptr->error];
    string_repr(ptr->c, repr);
    fprintf(stderr, "Error: ");
    fprintf(stderr, err, repr);
    fprintf(stderr, "\n");
}

static void analyser_clear(analyser_ptr ptr)
{
    ptr->quotation_mode = 0;
    ptr->escaping = 0;
    ptr->ready = 0;
    ptr->first = NULL;
    ptr->last = NULL;
    ptr->error = no_error;
}

int analyser_has_error(analyser_ptr ptr)
{
    return ptr->error != no_error;
}

void analyser_init(analyser_ptr ptr)
{
    analyser_clear(ptr);
    word_init(&ptr->word);
}

static enum { spaces_length = 3 };
static const int spaces[spaces_length] = { ' ', '\n', '\t' };

static int is_space(int c) 
{
    int i;
    for (i = 0; i < spaces_length; ++i) 
        if (c == spaces[i])
            return 1;

    return 0;
}

static void handle_quotation(analyser_ptr ptr, int c)
{
    if ('"' == c) {
        ptr->quotation_mode = 0;
        ptr->in_word = 1;
        return;
    } else if ('\n' == c) {
        ptr->error = unmatched_quotes;
        return;
    }
    word_add_char(&ptr->word, c);
}

static void handle_escaping(analyser_ptr ptr, int c)
{
    if (('"' != c) && ('\\' != c)) {
        ptr->error = cant_escape;
        return;
    }
    word_add_char(&ptr->word, c);
    ptr->escaping = 0;
}

static void handle_non_space(analyser_ptr ptr, int c)
{
    if ('"' == c) {
        ptr->quotation_mode = 1;
        return;
    } else if ('\\' == c) {
        ptr->escaping = 1;
        return;
    }
    ptr->in_word = 1;
    word_add_char(&ptr->word, c);
}

static void handle_space(analyser_ptr ptr, int c)
{
    if (ptr->word.size > 0 || ptr->in_word) {
        int i;
        char *word = (char *)malloc(ptr->word.size + 1);
        for (i = 0; i < ptr->word.size; ++i) {
            word[i] = ptr->word.data[i];
        }
#ifdef DEBUG
        printf("++(handle_space) DEBUG: %d\n", i);
#endif
        word[i] = '\0';
        word_list_add_item(&ptr->last, word);
        if (!ptr->first) {
            ptr->first = ptr->last;
        } else {
            ptr->last = ptr->last->next;
        }

        ptr->word.size = 0;
        ptr->in_word = 0;
    }
    if ('\n' == c) {
        ptr->ready = 1;
    }
}

void analyser_process_char(analyser_ptr ptr, int c)
{
    ptr->c = c;
    if (ptr->escaping) {
        handle_escaping(ptr, c);
    } else if (ptr->quotation_mode) {
        handle_quotation(ptr, c);
    } else if (!is_space(c)) {
        handle_non_space(ptr, c);
    } else if (is_space(c)) {
        handle_space(ptr, c);
    }
}

void analyser_prepare_next_line(analyser_ptr ptr)
{
    word_list_free(&ptr->first);
    analyser_clear(ptr);
    word_clear(&ptr->word);
}

void analyser_free(analyser_ptr ptr)
{
    if (ptr->first)
        word_list_free(&ptr->first);
    word_free(&ptr->word);
}

int analyser_line_ready(analyser_ptr ptr)
{
    return ptr->ready;
}

