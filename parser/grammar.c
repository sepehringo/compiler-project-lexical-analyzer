#include "parser.h"
void S(Token *tokens, int *i, int token_count);
void E(Token *tokens, int *i, int token_count);


// Match a specific terminal character
void match_term(Token *tokens, char c, int *i, int token_count)
{
    if (*i >= token_count || tokens[*i].value[0] != c)
    {
        printf("Error: Expected '%c', found '%s' at token %d\n", c, tokens[*i].value, *i);
        exit(EXIT_FAILURE);
    }
    printf("Matched terminal '%c' at token %d\n", c, *i);
    (*i)++;
}

// Match a specific token type
void match_type(Token *tokens, int *i, Token_Type type, int token_count)
{
    if (*i >= token_count || tokens[*i].type != type)
    {
        printf("Error: Expected type %d, found type %d at token %d\n", type, tokens[*i].type, *i);
        exit(EXIT_FAILURE);
    }
    printf("Matched type %d at token %d\n", type, *i);
    (*i)++;
}

// Numeric expressions      N-> integer | floating
void N(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && (tokens[*i].type == integer || tokens[*i].type == floating))
    {
        match_type(tokens, i, tokens[*i].type, token_count);
    }
}

// Identifier expressions I-> identifier
void I(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == identifier)
    {
        match_type(tokens, i, identifier, token_count);
    }
}

// Value expressions    V-> I | N
void V(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == identifier)
    {
        I(tokens, i, token_count);
    }
    else if (*i < token_count && (tokens[*i].type == integer || tokens[*i].type == floating))
    {
        N(tokens, i, token_count);
    }
}

// Unary operators      U->  ++ | --
void U(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == operator)
    {
        if (strcmp(tokens[*i].value, "++") == 0 || strcmp(tokens[*i].value, "--") == 0)
        {
            match_type(tokens, i, operator, token_count);
        }
    }
}

// Binary operators B-> + | - | < | > | = | ==
void B(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == operator)
    {
        if (strcmp(tokens[*i].value, "+") == 0 || strcmp(tokens[*i].value, "-") == 0 ||
            strcmp(tokens[*i].value, "<") == 0 || strcmp(tokens[*i].value, ">") == 0 ||
            strcmp(tokens[*i].value, "=") == 0 || strcmp(tokens[*i].value, "==") == 0)
        {
            match_type(tokens, i, operator, token_count);
        }
    }
}

// Binary operation expression  X->  V B V
void X(Token *tokens, int *i, int token_count)
{
    V(tokens, i, token_count);
    B(tokens, i, token_count);
    V(tokens, i, token_count);
}

// Unary operation expression   W->  U V | V U
void W(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == operator)
    {
        if (strcmp(tokens[*i].value, "++") == 0 || strcmp(tokens[*i].value, "--") == 0)
        {
            U(tokens, i, token_count);
            V(tokens, i, token_count);
        }
        else
        {
            V(tokens, i, token_count);
            U(tokens, i, token_count);
        }
    }
}

// Operation expression O->  W | X
void O(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == operator)
    {
        if (strcmp(tokens[*i].value, "++") == 0 || strcmp(tokens[*i].value, "--") == 0)
        {
            W(tokens, i, token_count); // Handle unary operation
        }
        else
        {
            X(tokens, i, token_count); // Handle binary operation
        }
    }
}

// Data type expressions    T->  int | float | void
void T(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == keyword)
    {
        if (strcmp(tokens[*i].value, "int") == 0 || strcmp(tokens[*i].value, "float") == 0 || strcmp(tokens[*i].value, "void") == 0)
        {
            match_type(tokens, i, keyword, token_count);
        }
        else
        {
            printf("Error: Invalid data type '%s' at token %d\n", tokens[*i].value, *i);
            exit(EXIT_FAILURE);
        }
    }
}

// Declaration expressions  D->  T I
void D(Token *tokens, int *i, int token_count)
{
    T(tokens, i, token_count);
    I(tokens, i, token_count);
}

// Assignment expressions   A->  T I = E | I = E
void A(Token *tokens, int *i, int token_count)
{
    if (*i < token_count && tokens[*i].type == keyword &&
        (strcmp(tokens[*i].value, "int") == 0 || strcmp(tokens[*i].value, "float") == 0 || strcmp(tokens[*i].value, "void") == 0))
    {
        T(tokens, i, token_count); 
        I(tokens, i, token_count); 
        match_term(tokens, '=', i, token_count); 
        E(tokens, i, token_count);              
    }
    else
    {
        I(tokens, i, token_count); 
        match_term(tokens, '=', i, token_count); 
        E(tokens, i, token_count);              
    }
}

// Expressions  E->  A | O | V
void E(Token *tokens, int *i, int token_count)
{
    if (*i >= token_count)
    {
        printf("E: Out of bounds access at token %d\n", *i);
        return;
    }
// Handle assignment E-> A
    if (tokens[*i].type == identifier && *i + 1 < token_count && tokens[*i + 1].value[0] == '=') /*  Short circuit: *i + 1 checks if we do not run out of bound*/
    {
        A(tokens, i, token_count); 
        // return;
    }
    // Handle operation E-> O
    else if (tokens[*i].type == operator)
    {
        O(tokens, i, token_count); 
        // return;
    } 
    // Handle Value E-> V
    else if (tokens[*i].type == identifier || tokens[*i].type == integer || tokens[*i].type == floating)
    {
        V(tokens, i, token_count); 
        
        if (*i < token_count && tokens[*i].type == operator)
        {
            if (strcmp(tokens[*i].value, "++") == 0 || strcmp(tokens[*i].value, "--") == 0)
            {
                U(tokens, i, token_count); 
            }
            else
            {
                B(tokens, i, token_count); 
                V(tokens, i, token_count); 
            }
        }

    }
}

// Blocks   B->  { S }
void L(Token *tokens, int *i, int token_count)
{
    match_term(tokens, '{', i, token_count); 
    // Multiple S ... Grammar not written accurately ...
    while (*i < token_count && tokens[*i].value[0] != '}')
    {
        S(tokens, i, token_count);
    }
    match_term(tokens, '}', i, token_count);
}

// Conditional expressions  C->  if ( E ) S
void C(Token *tokens, int *i, int token_count)
{
    // Problem: match term can't handle "for" or "if" as keywords ..
    match_type(tokens, i, keyword, token_count); 
    match_term(tokens, '(', i, token_count);    
    E(tokens, i, token_count);                  
    match_term(tokens, ')', i, token_count);   
    S(tokens, i, token_count);                 
}

// For expressions  F->  for ( E ; E ; E )
void F(Token *tokens, int *i, int token_count)
{
    // Problem: match term can't handle "for" or "if" as keywords ...
    match_type(tokens, i, keyword, token_count); 
    match_term(tokens, '(', i, token_count);

    // Handle initialization (declaration or assignment)
    if (tokens[*i].type == keyword && 
        (strcmp(tokens[*i].value, "int") == 0 || 
         strcmp(tokens[*i].value, "float") == 0 || 
         strcmp(tokens[*i].value, "void") == 0))
    {
        D(tokens, i, token_count);
        if (*i < token_count && tokens[*i].value[0] == '=')
        {
            match_term(tokens, '=', i, token_count); 
            E(tokens, i, token_count);             
        }
    }
    else
    {
        A(tokens, i, token_count); 
    }
    match_term(tokens, ';', i, token_count);    

    // Handle condition
    E(tokens, i, token_count);
    match_term(tokens, ';', i, token_count);    

    // Handle increment
    E(tokens, i, token_count);
    match_term(tokens, ')', i, token_count);   

    // Process the statement or block
    if (*i < token_count && tokens[*i].value[0] == '{')
    {
        L(tokens, i, token_count); 
    }
    else
    {
        // Handle single statement
        S(tokens, i, token_count); 
    }
}

// Statements   S->  ; | D ; | E ; | if ( E ) S | for ( E ; E ; E ) S | A ;
void S(Token *tokens, int *i, int token_count)
{
    if (*i >= token_count)
    {
        printf("S: Out-of-bounds access at token %d\n", *i);
        return;
    }

    if (tokens[*i].value[0] == '}') {
        // End of block, do not treat as error, just return
        return;
    }

    if (tokens[*i].value[0] == ';')
    {
        match_term(tokens, ';', i, token_count);
    }
    else if (tokens[*i].value[0] == '{')
    {
        L(tokens, i, token_count); 
    }
    else if (tokens[*i].type == keyword && 
             (strcmp(tokens[*i].value, "int") == 0 || 
              strcmp(tokens[*i].value, "float") == 0 || 
              strcmp(tokens[*i].value, "void") == 0))
    {
        if (*i + 2 < token_count && tokens[*i + 2].value[0] == '=')
        {
            A(tokens, i, token_count);
        }
        else
        {
            D(tokens, i, token_count);
        }
        match_term(tokens, ';', i, token_count);
    }
    else if (tokens[*i].type == identifier || tokens[*i].type == integer || tokens[*i].type == floating) /* Problem: not a good condition*/
    {
        E(tokens, i, token_count);
        match_term(tokens, ';', i, token_count);
    }
    else if (tokens[*i].type == keyword && strcmp(tokens[*i].value, "if") == 0)
    {
        C(tokens, i, token_count);
        if (*i < token_count && tokens[*i].value[0] == '{')
        {
            L(tokens, i, token_count);
        }
        else
        {
            S(tokens, i, token_count);
        }
    }
    else if (strcmp(tokens[*i].value, "for") == 0)
    {
        F(tokens, i, token_count);
        if (*i < token_count && tokens[*i].value[0] == '{')
        {
            L(tokens, i, token_count);
        }
        else
        {
            S(tokens, i, token_count);
        }
    }
    else if (tokens[*i].type == identifier)
    {
        A(tokens, i, token_count);
        match_term(tokens, ';', i, token_count);
    }
    else
    {
        printf("Error: Unexpected token '%s' at token %d\n", tokens[*i].value, *i);
        exit(EXIT_FAILURE);
    }
}

// Main function to start parsing
void parse(Token *tokens, int token_count)
{
    int i = 0;

    while (i < token_count)
    {
        printf("parse: Processing token %d: %s, Type: %d\n", i, tokens[i].value, tokens[i].type);

        if (strcmp(tokens[i].value, "$") == 0)
        {
            printf("Parsing Complete! at token:%d\n", i);
            break;
        }

        S(tokens, &i, token_count);
    }
}