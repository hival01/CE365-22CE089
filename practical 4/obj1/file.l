%option noyywrap
%{
    #include <stdio.h>
    int v = 0, c = 0;
%}

%%
[aeiouAEIOU]    {v++;}                
[a-zA-Z]        {c++;}                
[ \t\n]          ;                     
.               ;   
%%

int main() {
    printf("Enter string: ");
    yylex();                           
    printf("Number of vowels: %d\n", v);
    return 0;
}
