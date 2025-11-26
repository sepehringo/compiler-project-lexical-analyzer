#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define T -1

#define NSTATES 3
#define NEVENTS 1

// Terminals (sigma)
char *keyword_terminals[] = {
    "if",
    "for",
    "int",
    "float",
    "void"};

bool keyword_term_check(char* w)
{
    char* q = w;
    int i = sizeof(keyword_terminals) / sizeof(keyword_terminals[0]);
    while (i--)
        if (strcmp(q, keyword_terminals[i]) == 0)
            return true;
    return false;
}

// int keyword_event_mapper(char *w)
// {
//     char* q = w;
//     if (keyword_term_check(q))
//         return 0;
//     return -1;
// }

// int keyword_table[] = {
//     Q1, T, T};

// int keyword_finals[] = {Q1};

// machine keyword_machine = {
//     .machine_type = character,
//     .starting = Q0,
//     .terminal_function = keyword_term_check,
//     .event_mapper = keyword_event_mapper,
//     .finals = keyword_finals,
//     .finals_count = sizeof(keyword_finals) / sizeof(keyword_finals[0]),
//     .events_count = NEVENTS,
//     .states_count = NSTATES,
//     .transition_table = keyword_table,
// };
