#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define T -1

#define NSTATES 3
#define NEVENTS 1

// Terminals (sigma)
char punctuation_terminals[] = {
    '(',
    ')',
    '{',
    '}',
    ';',
    ','};

// Terminal Check Function
bool punct_term_check(char* c)
{
    int size = sizeof(punctuation_terminals) / sizeof(punctuation_terminals[0]);
    while (size--)
    {
        if (*c == punctuation_terminals[size])
            return true;
    }
    return false;
}

// Event function (Transitions)
int punct_event_mapper(char* c)
{
    if (punct_term_check(c))
        return 0;
    return -1;
}


int punct_table[] = { Q1, T};
// Final states
int punct_finals[] = {Q1};

// Machine definition
machine punct_machine = {
    .machine_type = punctuation,
    .starting = Q0,
    .terminal_function = punct_term_check,
    .event_mapper = punct_event_mapper,
    .finals = punct_finals,
    .finals_count = sizeof(punct_finals)/sizeof(punct_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = punct_table,
};
