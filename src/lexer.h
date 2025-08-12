#ifndef NASH_LEXER_H_PROTECT
#define NASH_LEXER_H_PROTECT

#include "word.h"
#include "word_list.h"

#define error_status int

typedef struct analyser_s {
    int           quotation_mode;
    int           escaping;
    int           ready;
    word_item_ptr first;
    word_item_ptr last;
    word_t        word;
    error_status  error;
    int c;
} analyser_t;
typedef analyser_t *analyser_ptr;

void analyser_init(analyser_ptr ptr);
void analyser_prepare_next_line(analyser_ptr ptr);
void analyser_process_char(analyser_ptr ptr, int c);
void analyser_free(analyser_ptr ptr);

int analyser_line_ready(analyser_ptr ptr);
int analyser_has_error(analyser_ptr ptr);

void analyser_print_error(analyser_ptr ptr);

#endif /* NASH_LEXER_H_PROTECT */
