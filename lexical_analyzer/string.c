#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define T -1

#define NSTATES 4
#define NEVENTS 2

// Terminals (sigma)
char string_terminals[] = {
    '\"', /* Anything Else */
};

// Terminal Check Function
bool str_term_check(char* c)
{
    return true;
}

// Event function (Transitions)
int str_event_mapper(char* c)
{
    if (*c == '\"')
        return 0;
    return 1;
    // There is not any wrong terminal either is ' or anything else shown as * in documentation
}

int str_table[] = {
    Q1, T,
    Q2, Q1, 
    T, T,
    T, T};
// Final states
int str_finals[] = {Q2};

// Machine definition
machine str_machine = {
    .machine_type = string,
    .starting = Q0,
    .terminal_function = str_term_check,
    .event_mapper = str_event_mapper,
    .finals = str_finals,
    .finals_count = sizeof(str_finals) / sizeof(str_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = str_table,
};
