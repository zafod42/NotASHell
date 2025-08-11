#include <stdio.h>

void read_loop()
{
    int c;
    while ((c = fgets(stdin)) != EOF)
    {

    }
}

int main(void)
{
    char c;
    int result;
    printf("> ");
    result = scanf("%c", &c);
    if (result == -1) {
        fprintf(stderr, "Got EOF\n");
        return 1;
    }
    if (result != 1) {
        fprintf(stderr, "Problem with read the character\n");
        return 1;
    }
    return 0;
}
