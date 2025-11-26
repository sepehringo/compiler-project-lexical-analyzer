# Lexical Analyzer Project

This project contains a set of C programs designed to perform lexical analysis on a given input file. It identifies tokens such as keywords, operators, identifiers, floating-point numbers, integers, punctuations, strings, and characters. Each program serves a specific function, as detailed below.

## File Descriptions

*   **character.c:** Defines the state machine for recognizing character literals.
*   **delimeter.c:** Contains functions to identify delimiters in the input stream.
*   **floating.c:** Defines the state machine for recognizing floating-point numbers.
*   **helper.c:** Provides helper functions for character classification (e.g., is\_digit, is\_alpha).
*   **identifier.c:** Defines the state machine for recognizing identifiers.
*   **integer.c:** Defines the state machine for recognizing integer literals.
*   **keyword.c:** Contains functions and data structures for identifying keywords.
*   **lexeme\_finder.c:** Implements the `find_token` function, which extracts tokens from the input stream based on defined delimiters. Also includes `enum_to_string` to convert token types to string representations.
*   **lexical\_analyser.h:** Header file containing definitions for data structures, enums, and function prototypes used throughout the project.
*   **matcher.c:** Implements the `match_type` function, which determines the type of a given token based on the defined state machines.
*   **operator.c:** Defines the state machine for recognizing operators.
*   **punctuation.c:** Defines the state machine for recognizing punctuation symbols.
*   **string.c:** Defines the state machine for recognizing string literals.

## Compilation and Usage

To compile the programs, use a C compiler such as GCC. It's recommended to compile all `.c` files together to resolve dependencies. For example:

```bash
gcc *.c -o lexer
```

To run the compiled program, provide an input file as an argument:

```bash
./lexer <input_file>
```

The program will then output the tokens found in the input file along with their types, line numbers, and column numbers.

## Dependencies

*   Standard C library (libc)
*   No external libraries are required.

## Notes

*   The project uses finite state machines to recognize different token types.
*   The `lexical_analyser.h` header file contains important definitions and should be included in all source files.
*   The `find_token` function in `lexeme_finder.c` is responsible for extracting tokens from the input stream.
*   The `match_type` function in `matcher.c` determines the type of each token.
*   Error handling is minimal; the program may not handle all possible error conditions gracefully.
*   The project can be extended to support more token types and error handling.
