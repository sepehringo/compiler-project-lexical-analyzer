# Lexical Analyzer

## Project Overview

This is a **Lexical Analyzer** (Scanner) designed for a subset of a programming language, developed as part of a Compiler Project for **Dr. Hokmi's** course.

---

## Language Specification

### Reserved Keywords
The language supports the following reserved keywords:
- `if`
- `for`
- `int`
- `float`
- `void`

**Note:** Keywords must be written in lowercase. If written with uppercase letters, they will be treated as identifiers.

---

### Operators
The language supports the following operators:
- `=` (Assignment)
- `+` (Addition)
- `<` (Less than)
- `>` (Greater than)
- `++` (Increment)

---

### Identifiers
Identifiers follow these rules:
- Maximum length: **5 characters**
- Must start with a **lowercase English letter** (a-z)
- Subsequent characters can be uppercase or lowercase letters
- If a digit is used in the identifier, it **must be preceded by an underscore** `_`

**Valid Examples:**
- `q`
- `aBcD`
- `b_2GH`
- `g_3_4`

**Invalid Examples:**
- `Q` (starts with uppercase)
- `b45` (digit not preceded by underscore)
- `aNBcfd` (too long - more than 5 characters)

---

### Separators
The language supports the following separators:
- `(` `)` (Parentheses)
- `{` `}` (Braces)
- `;` (Semicolon)
- `,` (Comma)

---

### Constants

#### 1. **Character Constants**
- Format: `'a'` (single character enclosed in single quotes)

#### 2. **String Constants**
- Format: `"abcd"` (sequence of characters enclosed in double quotes)

#### 3. **Numeric Constants**
   - **Integers:** Whole numbers with or without a sign (e.g., `42`, `-10`, `+5`)
   - **Floating-point numbers:** Decimal numbers with at least one digit before and after the decimal point (e.g., `3.14`, `-2.5`, `+0.1`)

---

## Features

### Input
The lexical analyzer reads a **text file** containing source code.

### Output
1. **Tokens File:** Each token (lexeme) and its type are saved to an output file.
2. **Errors File:** Lexical errors are logged with their line numbers.

### Error Handling
At the end of execution, a list of all errors with their corresponding line numbers is displayed to the user.

---

## Project Structure

```
lexical_analyzer/
├── character.c          # Handles character constant recognition
├── delimeter.c          # Handles delimiter recognition
├── floating.c           # Handles floating-point number recognition
├── helper.c             # Helper functions
├── identifier.c         # Handles identifier recognition
├── integer.c            # Handles integer recognition
├── keyword.c            # Handles keyword recognition
├── lexeme_finder.c      # Main lexeme finder logic
├── lexical_analyser.h   # Header file with definitions
├── main.c               # Main entry point
├── matcher.c            # Pattern matching logic
├── operator.c           # Handles operator recognition
├── punctuation.c        # Handles punctuation recognition
├── string.c             # Handles string constant recognition
└── makefile             # Build configuration

parser/
├── func.c               # Parser helper functions
├── grammar.c            # Grammar rules implementation
├── parser.c             # Main parser logic
└── parser.h             # Parser header file
```

---

## How to Build and Run

### Prerequisites
- GCC compiler
- macOS, Linux, or Windows with GCC support

### Build Lexical Analyzer
```sh
cd lexical_analyzer
make
```

### Run Lexical Analyzer
```sh
./program input.txt
```

This will:
- Read tokens from `input.txt`
- Generate `lexicons.txt` with all tokens
- Generate `errors.txt` with any lexical errors (if found)

### Build Parser
```sh
cd parser
gcc -g parser.c grammar.c func.c -o parser
```

### Run Parser
```sh
./parser lexicons.txt
```

---

## Debugging in VS Code

### 1. **Set Up Build Task**
The project includes [`.vscode/tasks.json`](.vscode/tasks.json) with build tasks configured.

### 2. **Set Up Debug Configuration**
The project includes [`.vscode/launch.json`](.vscode/launch.json) with debug configurations:
- **Debug parser:** Debugs the parser with `lexicon.txt` as input

### 3. **Debug Steps**
1. Place your input file in the appropriate folder
2. Open the Run and Debug sidebar in VS Code (`Cmd+Shift+D`)
3. Select the appropriate debug configuration
4. Set breakpoints in any `.c` file
5. Press **F5** to start debugging

---

## Original Project Requirements (Translated from Persian)

### Part One (Lexical Analyzer) - Compiler Project

We want to design a compiler for a small subset of a programming language. In this example, the language vocabulary includes only:

**Reserved Keywords:** `void`, `int`, `float`, `for`, `if`

**Operators:** `=` (assignment), `+`, `<`, `>`, and `++`

**Identifiers:** Their names are at most 5 characters and must start with a lowercase English letter (the rest of the letters can be uppercase or lowercase). If a digit is used in naming an identifier, an underscore `_` must appear before each digit.

**Valid Examples:** `q`, `aBcD`, `b_2GH`, `g_3_4`

**Invalid Examples:** `Q`, `b45`, `aNBcfd`

**Symbols:** `(`, `)`, `{`, `}`, `;`, `,`

**Constants:**
- Character constant: `'a'`
- String constant: `"abcd"`
- Numeric constant: integer and floating-point numbers (at least one digit must exist before and after the decimal point)

The language is case-sensitive and reserved keywords must be written in lowercase; otherwise, they are recognized as identifiers.

The lexical analyzer receives a text file as input, stores each word and its type in another file. Errors are also stored in another file, and at the end, a list of errors along with the line numbers where errors occurred is displayed to the user.

---

## Author
Developed by **Sepehr** for Dr. Hokmi's Compiler Course

---

## License
This project is for educational purposes only.
