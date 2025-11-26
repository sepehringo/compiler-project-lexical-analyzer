#include "lexical_analyser.h"

bool is_lowerCase(char c)
{
    return c >= 'a' && c <= 'z';
}
bool is_upperCase(char c)
{
    return c >= 'A' && c <= 'Z';
}
bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}
bool is_alpha(char c)
{
    return is_lowerCase(c) || is_upperCase(c);
}
bool is_alphanumeric(char c)
{
    return is_alpha(c) || is_digit(c);
}
bool is_punctuation(char c)
{
    switch (c)
    {
    case '(':
    case ')':
    case '{':
    case '}':
    case ';':
    case ',':
        return true;
    default:
        return false;
    }
}
bool is_operator(char c)
{
    switch (c)
    {
    case '+':
    case '>':
    case '<':
    case '=':
        return true;
    default:
        return false;
}
}
bool is_white_space(char c)
{
    return c == ' ' || c == '\t' ||  c == '\r' || c == '\f' || c == '\v';
}
void allocation_check(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

bool is_in_char_set(char c,char* word)
{
    while (*word)
        if(*word++ == c)    
            return true;
    return false;
}