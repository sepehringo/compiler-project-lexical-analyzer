#include "parser.h"

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        printf("Usage: %s LexFile\n", argv[0]);
        return 2;
    }
    // Read lexical tokens from the input
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    Token tokens[100];
    char c[20];
    int token_count = 0;
    while (fscanf(inptr, "%s %s", tokens[token_count].value, c) == 2)
    {
        tokens[token_count].type = get_token_type(c);
        printf("Token: %s, Type: %d\n", tokens[token_count].value, tokens[token_count].type);
        token_count++;
        if (token_count >= 100)
        {
            printf("Error: Too many tokens\n");
            break;
        }
    }
    strcpy(tokens[token_count].value, "$");
    tokens[token_count].type = unknown;
    token_count++;
    // Parse the tokens
    Token *lookahead = tokens;
    parse(lookahead, token_count);

    // Close the file
    fclose(inptr);
    return 0;
}
