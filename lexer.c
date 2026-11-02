#include "lexer.h" 

int iskeyword(char word[]) {
    int size = sizeof(keywords_data) / sizeof(keywords_data[0]);
    for(int i = 0; i < size; i++) {
        if(strcmp(keywords_data[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_nondatakeyword(char word[]) {
    int size = sizeof(keywords_non_data) / sizeof(keywords_non_data[0]);
    for(int i = 0; i < size; i++) {
        if(strcmp(keywords_non_data[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int isoperator(char ch) {
    int size = sizeof(operators) / sizeof(operators[0]);
    for(int i = 0; i < size; i++) {
        if(operators[i] == ch) {
            return 1;
        }
    }
    return 0;
}

int issymbol(char ch) {
    int size = sizeof(symbols) / sizeof(symbols[0]);
    for(int i = 0; i < size; i++) {
        if(symbols[i] == ch) {
            return 1;
        }
    }
    return 0;
}