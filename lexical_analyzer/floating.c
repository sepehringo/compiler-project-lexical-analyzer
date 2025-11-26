#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4
#define T -1

#define NSTATES 5
#define NEVENTS 3

// Terminals (sigma) Check Function
bool floating_term_check(char* c)
{
    return is_digit(*c) || *c == '+' || *c == '-' || *c == '.';
}
// Event function (Transitions)
int floating_event_mapper(char* c)
{
    if (is_digit(*c))
        return 0;
    if (*c == '.')
        return 1;
    if (*c == '+' || *c == '-')
        return 2;
    return -1;
}

int floating_table[] = {
   Q1, T, Q4,
   Q1, Q2, T,
   Q3, T, T,
   Q3, T, T,
   Q1, T, T,
   T, T, T
};

// Final States
int floating_finals[] = {Q3};

machine floating_machine = {
    .machine_type = floating,
    .starting = Q0,
    .terminal_function = floating_term_check,
    .event_mapper = floating_event_mapper,
    .finals = floating_finals,
    .finals_count = sizeof(floating_finals)/sizeof(floating_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = floating_table
};