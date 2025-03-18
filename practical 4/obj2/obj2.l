%option noyywrap
%{
    #include <stdio.h>
%}

%%
charusat     {printf("university");}
Charusat     {printf("University");}
.            {printf("%c", yytext[0]);}  
%%

int main() {
    printf("Enter string: ");
    yylex();                           
    return 0;
}
