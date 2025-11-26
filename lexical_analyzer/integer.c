#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define T -1

#define NSTATES 4
#define NEVENTS 2

// Terminals (sigma) Check Function
bool int_term_check(char* c)
{
    return is_digit(*c) || *c == '+' || *c == '-';
}
// Event function (Transitions)
int int_event_mapper(char* c)
{
    if (is_digit(*c))
        return 0;
    if (*c == '+' || *c == '-')
        return 1;
    return -1;
}

int int_table[] = {
   Q1, Q2,
   Q1, T,
   Q1, T,
   T, T
};

// Final States
int int_finals[] = {Q1};

machine int_machine = {
    .machine_type = integer,
    .starting = Q0,
    .terminal_function = int_term_check,
    .event_mapper = int_event_mapper,
    .finals = int_finals,
    .finals_count = sizeof(int_finals)/sizeof(int_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = int_table
};