#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4
#define Q5 5
#define Q6 6
#define Q7 7
#define Q8 8
#define T -1

#define NSTATES 10
#define NEVENTS 4

// Terminals (sigma) Check Function
bool id_term_check(char* c)
{
    return is_alphanumeric(*c) || *c == '_';
}
// Event function (Transitions)
int id_event_mapper(char* c)
{
    if (is_lowerCase(*c))
        return 0;
    if (is_upperCase(*c))
        return 1;
    if (is_digit(*c))
        return 2;
    if (*c == '_')
        return 3;
    return -1;
}

int id_table[] = {
    Q1, T, T, T,
    Q2, Q2, T, Q6,
    Q3, Q3, T, Q7,
    Q4, Q4, T, Q8,
    Q5, Q5, T, T,
    T, T, T, T,
    T, T, Q3, T,
    T, T, Q4, T,
    T, T, Q5, T,
    T, T, T, T,
};

// Final States
int id_finals[] = {Q1, Q2, Q3, Q4, Q5};

machine id_machine = {
    .machine_type = identifier,
    .starting = Q0,
    .terminal_function = id_term_check,
    .event_mapper = id_event_mapper,
    .finals = id_finals,
    .finals_count = sizeof(id_finals)/sizeof(id_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = id_table
};