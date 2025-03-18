%{
#include <stdio.h>

int c = 0;
int w = 0;
int l = 0;
%}

%%

[a-zA-Z0-9]+        { w++; c += yyleng; }
\n                  { l++; c++; }
[ \t\r]             { c++; }
.                   { c++; } 

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);
    printf("\n");
    printf("Characters : %d\n", c);
    printf("Words : %d\n", w);
    printf("Line : %d\n", l);

    return 0;
}

int yywrap() {
    return 1;
}
