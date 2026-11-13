# Lexical Analyzer in C

## Overview

This project implements a basic lexical analyzer using C. It reads source code from an input file (`input.txt`), identifies different types of tokens and classifies them into categories.

It also detects invalid identifiers, invalid tokens and unterminated string or character constants.

## Features

- Identifies keywords such as `int`, `float`, `char`, `if`, `else`, `while` and `return`
- Recognizes identifiers
- Detects integer and floating-point constants
- Identifies character and string constants
- Recognizes operators
- Identifies braces and separators
- Detects invalid identifiers and invalid characters
- Reports unterminated string and character constants
- Reads input directly from a file

## Token Categories

| Token | Example |
|---|---|
| Keywords | `int`, `float`, `return` |
| Identifiers | `count`, `total` |
| Integer Constants | `10`, `25` |
| Floating Constants | `3.14`, `5.6` |
| Character Constants | `'A'` |
| String Constants | `"Hello"` |
| Operators | `+`, `-`, `=`, `*` |
| Braces | `()`, `{}`, `[]` |
| Separators | `;`, `,` |

## Technologies Used

- Language: C
- Concepts: File Handling, String Handling, Character Classification
- Libraries: `stdio.h`, `string.h`, `ctype.h`

## How to Run

1. Compile the program:

   ```bash
   gcc main.c -o lexer
   ```

2. Create an input file named `input.txt` in the same directory.

3. Add sample source code to `input.txt`.

4. Run the executable:

   ```bash
   ./lexer
   ```

## Example Input

```c
int main()
{
    int num = 10;
    float value = 3.14;
    char letter = 'A';

    return 0;
}
```

## Example Output

```text
int --> Keyword
main --> Identifier
( --> Brace
) --> Brace
{ --> Brace
int --> Keyword
num --> Identifier
= --> Operator
10 --> Integer Constant
; --> Separator
float --> Keyword
value --> Identifier
= --> Operator
3.14 --> Floating Constant
; --> Separator
char --> Keyword
letter --> Identifier
= --> Operator
'A' --> Character Constant
; --> Separator
return --> Keyword
0 --> Integer Constant
; --> Separator
} --> Brace
```

## Concepts Learned

- Lexical analysis fundamentals
- Token identification and classification
- C file handling
- String processing
- Character classification using `ctype.h`
- Input validation and error detection

## Author

Sneha B.
