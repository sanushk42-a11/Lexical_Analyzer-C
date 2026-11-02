#include <stdio.h>

// This is a single-line comment
int main() {
    /* This is a 
       multi-line comment */
    int x = 42;
    float y = 3.14;
    char ch = 'A';
    char str[] = "Hello Lexer";

    if (x < y) {
        return 1;
    } else {
        return 0;
    }
}