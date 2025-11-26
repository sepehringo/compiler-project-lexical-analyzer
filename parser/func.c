#include "parser.h"
void get_token(char *buffer, Token *token)
{
    char type_str[20];
    sscanf(buffer, "%s %s", token->value, type_str);
    token->type = get_token_type(type_str);
}
Token_Type get_token_type(char *str)
{
        char trimmed_str[20];
    sscanf(str, "%s", trimmed_str);

    if (strcmp(trimmed_str, "keyword") == 0)
        return keyword;
    if (strcmp(trimmed_str, "identifier") == 0)
        return identifier;
    if (strcmp(trimmed_str, "integer") == 0)
        return integer;
    if (strcmp(trimmed_str, "floating") == 0)
        return floating;
    if (strcmp(trimmed_str, "operator") == 0)
        return operator;
    if (strcmp(trimmed_str, "punctuation") == 0)
        return punctuation;
    if (strcmp(trimmed_str, "string") == 0)
        return string;
    if (strcmp(trimmed_str, "character") == 0)
        return character;
    return unknown;  
}