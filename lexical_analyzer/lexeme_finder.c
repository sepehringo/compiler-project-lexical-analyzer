#include "lexical_analyser.h"

char *enum_to_string(lex_type e)
{
    switch (e)
    {
    case keyword:
        return "keyword";
    case identifier:
        return "identifier";
    case operator:
        return "operator";
    case floating:
        return "floating";
    case integer:
        return "integer";
    case punctuation:
        return "punctuation";
    case string:
        return "string";
    case character:
        return "character";
    case illigal:
        return "illigal";
    case unkown:
        return "unkown";
    default:
        return "ERROR!";
        break;
    }
    return NULL;
}
// This function continues to read the file
/// To insert delimeters add using + enums such as : dm_white_space, dm_new_line ...
char *find_token(FILE *inptr, char c, int delimeter, int *line, int *col)
{
    int i = 0;
    char *w = malloc(sizeof(char));
    allocation_check(w);
    w[0] = c;
    while ((c = fgetc(inptr)) != EOF && is_delimeter(delimeter, c) == false)
    {
        ++i;
        w = realloc(w, (sizeof(char) * i) + 1);
        allocation_check(w);
        w[i] = c;
        // Taking care of lines and cols
        if (c == '\n')
        {
            line++;
            col = 0;
        }
        col++;
    }
    // if was string and delimiter cuts at ' or " must be added to the word
    if (c == '\"' || c == '\'')
    {
        ++i;
        w = realloc(w, (sizeof(char) * i) + 1);
        w[i] = c;
    }
    // Close the word
    w = realloc(w, (sizeof(char) * i) + 1);
    w[++i] = '\0';
    // Turn file pointer back to the delimiter character
    if (c != EOF && !(c == '\"' || c == '\''))
        fseek(inptr, -sizeof(char), SEEK_CUR);
    return w;
}
