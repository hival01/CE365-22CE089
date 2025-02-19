#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 100

const char *keywords[] = {
    "int", "float", "double", "char", "void", "if", "else", "while", "for", "return", "switch", "case", "default", "break", "continue"
};

typedef enum { 
    KEYWORD, IDENTIFIER, CONSTANT, STRING, PUNCTUATION, OPERATOR, ERROR 
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_LEN];
} Token;

void remove_comments(char *code);
int is_keyword(char *word);
int is_operator(char ch);
int is_punctuation(char ch);
int is_identifier(char *word);
int is_constant(char *word);
int is_valid_number(const char *word);
int is_string(char *word);
void print_token(Token token);
void analyze_code(char *code);

int main() {
    char code[MAX_LEN];
    printf("Enter C code (type 'exit' to end):\n");

    while (1) {
        fgets(code, sizeof(code), stdin);
        if (strcmp(code, "exit\n") == 0) break;

        remove_comments(code);
        analyze_code(code);
    }

    return 0;
}

void remove_comments(char *code) {
    char temp[MAX_LEN];
    int i = 0, j = 0;
    int inside_comment = 0;

    while (code[i] != '\0') {
        if (code[i] == '/' && code[i + 1] == '*') {
            inside_comment = 1;
            i += 2; 
            continue;
        }
        if (code[i] == '*' && code[i + 1] == '/') {
            inside_comment = 0;
            i += 2; 
            continue;
        }

        if (!inside_comment) {
            temp[j++] = code[i];
        }
        i++;
    }
    temp[j] = '\0';
    strcpy(code, temp); 
}

int is_keyword(char *word) {
    for (int i = 0; i < 15; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1; 
    }
    return 0;
}

int is_operator(char ch) {
    char operators[] = "+-*/%=<>!&|^";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i])
            return 1; 
    }
    return 0;
}

int is_punctuation(char ch) {
    char punctuations[] = ".,;()[]{}";
    for (int i = 0; i < strlen(punctuations); i++) {
        if (ch == punctuations[i])
            return 1; 
    }
    return 0;
}

int is_identifier(char *word) {
    if (!isalpha(word[0]) && word[0] != '_') return 0; 
    for (int i = 1; i < strlen(word); i++) {
        if (!isalnum(word[i]) && word[i] != '_') return 0; 
    }
    return 1; 
}

int is_constant(char *word) {
    if (is_valid_number(word)) {
        return 1;
    }
    return 0;
}

int is_valid_number(const char *word) {
    int i = 0;
    int dot_count = 0;
    
    if (word[i] == '+' || word[i] == '-') {
        i++;
    }
    
    while (isdigit(word[i])) {
        i++;
    }
    
    if (word[i] == '.') {
        dot_count++;
        i++;
        while (isdigit(word[i])) {
            i++;
        }
    }

    if (word[i] == '\0' && dot_count <= 1) {
        return 1;
    }

    return 0;
}

int is_string(char *word) {
    if (word[0] == '"' && word[strlen(word) - 1] == '"')
        return 1;
    return 0;
}

void print_token(Token token) {
    switch (token.type) {
        case KEYWORD:
            printf("KEYWORD: %s\n", token.value);
            break;
        case IDENTIFIER:
            printf("IDENTIFIER: %s\n", token.value);
            break;
        case CONSTANT:
            printf("CONSTANT: %s\n", token.value);
            break;
        case STRING:
            printf("STRING: %s\n", token.value);
            break;
        case PUNCTUATION:
            printf("PUNCTUATION: %s\n", token.value);
            break;
        case OPERATOR:
            printf("OPERATOR: %s\n", token.value);
            break;
        case ERROR:
            printf("ERROR: %s\n", token.value);
            break;
    }
}

void analyze_code(char *code) {
    char temp[MAX_LEN];
    int i = 0, j = 0;
    Token token;

    while (code[i] != '\0') {
        if (isspace(code[i])) {
            i++; 
            continue;
        }

        if (is_operator(code[i])) {
            token.type = OPERATOR;
            token.value[0] = code[i++];
            token.value[1] = '\0';
            print_token(token);
            continue;
        }

        if (is_punctuation(code[i])) {
            token.type = PUNCTUATION;
            token.value[0] = code[i++];
            token.value[1] = '\0';
            print_token(token);
            continue;
        }

        if (isalpha(code[i]) || code[i] == '_') {
            j = 0;
            while (isalnum(code[i]) || code[i] == '_') {
                temp[j++] = code[i++];
            }
            temp[j] = '\0';

            if (is_keyword(temp)) {
                token.type = KEYWORD;
            } else if (is_identifier(temp)) {
                token.type = IDENTIFIER;
            } else {
                token.type = ERROR;
            }
            strcpy(token.value, temp);
            print_token(token);
            continue;
        }

        if (isdigit(code[i])) {
            j = 0;
            while (isdigit(code[i])) {
                temp[j++] = code[i++];
            }
            temp[j] = '\0';

            if (is_constant(temp)) {
                token.type = CONSTANT;
                strcpy(token.value, temp);
                print_token(token);
            } else {
                token.type = ERROR;
                strcpy(token.value, "Invalid constant");
                print_token(token);
            }
            continue;
        }

        if (code[i] == '"') {
            j = 0;
            temp[j++] = code[i++];
            while (code[i] != '"' && code[i] != '\0') {
                temp[j++] = code[i++];
            }
            if (code[i] == '"') {
                temp[j++] = code[i++];
                temp[j] = '\0';
                token.type = STRING;
                strcpy(token.value, temp);
                print_token(token);
            } else {
                token.type = ERROR;
                strcpy(token.value, "Unterminated string literal");
                print_token(token);
                break;
            }
            continue;
        }

        token.type = ERROR;
        token.value[0] = code[i++];
        token.value[1] = '\0';
        print_token(token);
    }
}