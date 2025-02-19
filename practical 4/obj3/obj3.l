%option noyywrap
%{
    #include <stdio.h>
    int l=0,c=0,w=0;
%}

%%
[\n] {l++;}
[ \t] {c+=yyleng;}
[\^ \t\n]+ {w++; c+=yyleng;} 
%%

int main() {
    printf("Enter string: ");
    yylex();                           
    return 0;
}
