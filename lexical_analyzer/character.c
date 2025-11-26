#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define T -1

#define NSTATES 5
#define NEVENTS 2

// Terminals (sigma)
char character_terminals[] = {
    '\'', /* Anything Else */
};

// Terminal Check Function
bool char_term_check(char* c)
{
    return true;
}

// Event function (Transitions)
int char_event_mapper(char* c)
{
    if (*c == '\'')
        return 0;
    return 1;
    // There is not any wrong terminal either is ' or anything else shown as * in documentation
}

int char_table[] = {
    Q1, T,
    T, Q2, 
    Q3, T,
    T, T,
    T, T};
// Final states
int char_finals[] = {Q3};

// Machine definition
machine char_machine = {
    .machine_type = character,
    .starting = Q0,
    .terminal_function = char_term_check,
    .event_mapper = char_event_mapper,
    .finals = char_finals,
    .finals_count = sizeof(char_finals) / sizeof(char_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = char_table,
};
