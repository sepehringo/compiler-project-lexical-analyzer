#include "lexical_analyser.h"

lex_type match_type(machine *m, char *word)
{
    char *q = word;
    int current_state = 0;
    while (*q)
    {
        int e = (m->event_mapper)(q);
        // undefined terminal in the string or falling in trap, can lead to an early exit
        if (e == -1 || current_state == -1 || (m->terminal_function)(q) == false)
            return illigal;
        current_state = ((m->transition_table))[(current_state)*m->events_count + e]; // Treating 1d array like a 2d array : i * col
        q++;
    }
    int i = m->finals_count;
    while (i--)
    {
        if ((m->finals)[i] == current_state)
            return m->machine_type;
    }
    return illigal;
}
