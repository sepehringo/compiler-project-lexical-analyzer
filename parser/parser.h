#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


typedef enum
{
    keyword,
    operator,
    identifier,
    floating,
    integer,
    punctuation,
    string,
    character,
    illegal,  
    unknown,
} Token_Type;

typedef struct
{
    int i ;
    char value[20];
    Token_Type type;
} Token;

// Function Headers
Token_Type get_token_type(char *str);
void parse(Token *tokens, int token_count);