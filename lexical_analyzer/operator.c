#include "lexical_analyser.h"

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define T -1

#define NSTATES 5
#define NEVENTS 2

// Terminals (sigma)
char operator_terminals[] = {
    '+',
    '<',
    '>',
    '=',
};

// Terminal Check Function
bool op_term_check(char* c)
{
    int size = sizeof(operator_terminals) / sizeof(operator_terminals[0]);
    while (size--)
    {
        if (*c == operator_terminals[size])
            return true;
    }
    return false;
}

// Event function (Transitions)
int op_event_mapper(char* c)
{
    switch (*c)
    {
    case '+':
        return 1;
    case '>':
    case '<':
    case '=':
        return 0;
    default:
        break;
    }
    return -1;
}


int op_table[] = { 
    Q1, Q2,
    T, T,
    T, Q3,
    T, T,
    T, T,
};
// Final states
int op_finals[] = {Q1, Q2, Q3};

// Machine definition
machine op_machine = {
    .machine_type = operator,
    .starting = Q0,
    .terminal_function = op_term_check,
    .event_mapper = op_event_mapper,
    .finals = op_finals,
    .finals_count = sizeof(op_finals)/sizeof(op_finals[0]),
    .events_count = NEVENTS,
    .states_count = NSTATES,
    .transition_table = op_table,
};
