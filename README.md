# C Lexical Analyzer

A lightweight lexical analyzer (tokenizer) for C source files, written in C.
It reads a C file, breaks it into tokens, and prints each token with its
category and line number. It also detects unbalanced braces and unterminated
string literals.

**Repository:** [github.com/sanushk42-a11/Lexical_Analyzer-C](https://github.com/sanushk42-a11/Lexical_Analyzer-C)

## Features

- Token classification:
  - Keywords (data-type/storage keywords like `int`, `char`, `static`)
  - Non-data keywords (control-flow like `if`, `while`, `return`)
  - Identifiers
  - Numeric constants
  - String and character literals
  - Operators
  - Symbols (`;`, `,`, `[`, `]`, `:` etc.)
  - Round and curly braces (tracked separately)
  - Preprocessor directives (`#include`, `#define`, ...)
- Skips single-line (`//`) and multi-line (`/* */`) comments
- Line number reported for every token
- Error detection for unbalanced `()` / `{}` and unterminated string literals
- Colored terminal output

## Project Structure

| File        | Description                                         |
|-------------|-----------------------------------------------------|
| `main.c`    | Main scanning loop and token printing               |
| `lexer.c`   | Helper functions (keyword/operator/symbol checks)   |
| `lexer.h`   | Declarations, keyword tables, color macros          |
| `sample.c`  | Sample C file to test the analyzer                  |

## Getting Started

### Clone the repository

```bash
git clone https://github.com/sanushk42-a11/Lexical_Analyzer-C.git
cd Lexical_Analyzer-C
```

### Build

Requires `gcc` (or any C compiler).

```bash
gcc main.c lexer.c -o lexer
```

### Usage

```bash
./lexer <path-to-c-file>
```

Example:

```bash
./lexer sample.c
```

## Sample Output
## Sample Output

Line 1 : Preprocessor directive : #include <stdio.h>
Line 4 : Keyword : int
Line 4 : identifier : main
Line 4 : round braces opening : (
Line 4 : round braces closing : )
Line 4 : curly braces opening : {
Line 7 : Keyword : int
Line 7 : identifier : x
Line 7 : operator : =
Line 7 : numeric constant : 42
Line 7 : symbol : ;
...
Successfully parsed


## Error Handling

- Missing argument or unreadable file → error message
- Unbalanced `(`, `)`, `{`, `}` → reports which brace is unbalanced
- Unterminated string literal → reports the line number

## Known Limitations

- Floating-point numbers (e.g. `3.14`) are split into two numeric tokens
- Multi-character operators (`==`, `++`, `&&`, `<=`) are reported as separate single-character operators
- Character literals like `'A'` are labeled "String literals"
- Hex/octal/suffixed numbers (`0xFF`, `10L`) are not fully supported
- Tokens longer than 99 characters may overflow the internal buffer

## Possible Improvements

- Support floats, hex and multi-character operators
- Separate token type for character literals
- Output tokens to a file / JSON
- Bounds checking on the token buffer

## Concepts Covered

Lexical analysis, finite-state style scanning, tokenization, compiler design (phase 1).

## Author

**Sanush K Santhosh**

- GitHub: [@sanushk42-a11](https://github.com/sanushk42-a11)
- LinkedIn: [Sanush K Santhosh](https://www.linkedin.com/in/sanush-k-santhosh-498432376)

Feedback and suggestions are welcome. Feel free to open an issue or connect on LinkedIn.

## License

MIT
