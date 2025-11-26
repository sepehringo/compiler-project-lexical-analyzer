#include "lexical_analyser.h"

bool is_delimeter(int deli_code, char c)
{
    int t;
    // Short circuit
    if ((deli_code & dm_digits) && is_digit(c))
        return true;
    if ((deli_code & dm_double_qoutation) && c == '\"')
        return true;
    if ((deli_code & dm_new_lines) && c == '\n')
        return true;
    if ((deli_code & dm_operators) && is_operator(c))
        return true;
    if ((deli_code & dm_punctuations) && is_punctuation(c))
        return true;
    if ((deli_code & dm_single_qoutation) && c == '\'')
        return true;
    if ((t = ((deli_code & dm_white_spaces))) && is_white_space(c))
        return true;
    if ((deli_code & dm_alpha) && is_alpha(c))
        return true;
    if ((deli_code & dm_dot) && c == '.')
        return true;
    return false;
}

