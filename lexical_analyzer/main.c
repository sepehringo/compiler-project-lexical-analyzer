#include "lexical_analyser.h"

int main(int argc, char *argv[])
{
    // Make all the necessary machines

    // Check for correct number of arguments
    if (argc != 2)
    {
        printf("Usage: %s TESTFILE\n", argv[0]);
        return 2;
    }
    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    FILE *lexicons = fopen("lexicons.txt", "w");
    FILE *errors = fopen("errors.txt", "w");
    allocation_check(inptr);

    // //    Read the file
    char c;
    int line = 1;
    int col = 1;

    int id_delimiters = dm_double_qoutation + dm_new_lines + dm_operators + dm_punctuations + dm_single_qoutation + dm_white_spaces;
    int num_delimiters = dm_alpha + dm_double_qoutation + dm_new_lines + dm_punctuations + dm_single_qoutation + dm_white_spaces + dm_operators;
    int punct_delimiters = dm_white_spaces + dm_new_lines + dm_operators + dm_digits + dm_double_qoutation + dm_single_qoutation + dm_alpha + dm_dot;
    int op_delimiters = num_delimiters - dm_operators + dm_digits + dm_dot;
    // Read in all the Text
    while ((c = fgetc(inptr)) != EOF)
    {
        char *word;
        lex_type type;
        // Strip white spaces
        if (is_white_space(c))
        {
            col++;
            continue;
        }
        if (c == '\n')
        {
            line++;
            col = 0;
            continue;
        }
        col++;
        // try for id/key
        switch (c)
        {
        case 'a' ... 'z':
            word = find_token(inptr, c, id_delimiters, &line, &col);
            if (keyword_term_check(word))
                type = keyword;
            else
                type = match_type(&id_machine, word);
            break;
        case '0' ... '9':
        case '.':
        case '-':
        case '+':
        case '=':
        case '<':
        case '>':
            word = find_token(inptr, c, num_delimiters, &line, &col);
            if (match_type(&floating_machine, word) != illigal)
                type = floating;
            else if (match_type(&int_machine, word) != illigal)
                type = integer;
            else
            {   // get back to check if it was an operator that break the machine
                fseek(inptr, -sizeof(char) * strlen(word) + 1, SEEK_CUR);
                word = find_token(inptr, c, op_delimiters, &line, &col);
                type = match_type(&op_machine, word);
            }
            break;
        case ')':
        case '(':
        case '{':
        case '}':
        case ';':
        case ',':
            word = find_token(inptr, c, punct_delimiters, &line, &col);
            type = match_type(&punct_machine, word);
            break;
        case '\"':
            word = find_token(inptr, c, dm_double_qoutation, &line, &col);
            type = match_type(&str_machine, word);
            break;
        case '\'':
            word = find_token(inptr, c, dm_single_qoutation, &line, &col);
            type = match_type(&char_machine, word);
            break;
        default:
            // To ignore unknown terminals
            word = find_token(inptr, c, dm_white_spaces + dm_new_lines, &line, &col);
            type = unkown;
            break;
        }
        if (type != illigal && type != unkown)
            fprintf(lexicons, "%-20s\t%-10s\n", word, enum_to_string(type));
        else
            fprintf(errors, "%-20s\t%-10s\tLine:%3d\tCol:%3d\n", word, enum_to_string(type), line, col);
        free(word);
    }
}