#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    illigal,
    unkown
} lex_type;

typedef struct 
{
    char* word;
    lex_type type;
} token;
// Set out for bitwise operations
typedef enum
{
    dm_white_spaces = 1,
    dm_new_lines = 2,
    dm_operators = 4,
    dm_punctuations = 8,
    dm_digits = 16,
    dm_double_qoutation = 32,
    dm_single_qoutation = 64,
    dm_alpha = 128,
    dm_dot = 256,
} delimiter;

typedef struct
{
    lex_type machine_type;
    int starting;
    bool (*terminal_function)(char*);
    int (*event_mapper)(char*);
    int* finals;
    int finals_count;
    int states_count;
    int events_count;
    int* transition_table;
} machine;


machine punct_machine;
machine id_machine;
machine char_machine;
machine str_machine;
machine int_machine;
machine floating_machine;
machine op_machine;

bool keyword_term_check(char* w);
// Function Definitions
lex_type match_type(machine *m, char *word);
bool is_delimeter(int deli_code, char c);
char* find_token(FILE *inptr, char c, int delimeter, int* line, int* col);
char *enum_to_string(lex_type e);
// Helper functions
void allocation_check(void *ptr);

bool is_lowerCase(char c);

bool is_upperCase(char c);

bool is_digit(char c);

bool is_alpha(char c);

bool is_alphanumeric(char c);

bool is_white_space(char c);

bool is_operator(char c);

bool is_punctuation(char c);



