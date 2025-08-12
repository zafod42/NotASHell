#include "lexer.h"
#include "word_list.h"
#include "word.h"

#include <stdio.h>

void report_word(word_item_ptr item)
{
    printf("[%s]\n", item->word); 
}

int process_line(const word_item_ptr *list)
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
    analyser_t analyser;
    analyser_init(&analyser);

    printf("> ");
    while ((c = fgetc(stdin)) != EOF) 
    {
        analyser_process_char(&analyser, c);
        if (analyser_has_error(&analyser)) {
            while (c != '\n' && c != EOF) 
                c = fgetc(stdin);
            analyser_print_error(&analyser);
            analyser_prepare_next_line(&analyser);
            printf("> ");
        }
        else if (analyser_line_ready(&analyser)) {
            process_line(&analyser.first);
            analyser_prepare_next_line(&analyser);
            printf("> ");
        }
    }
    printf("\nexit\n");
}

int main(void)
{
    read_loop();
    return 0;
}
