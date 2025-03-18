
%{
    #include<stdio.h>
%}
%%
[ ] {}
"//".* {printf("%s is single line comment\n",yytext);}
"/*"([^*]|\*+[^*/])*\*+"/" {printf("%s is multiple line comment\n",yytext);}
"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {printf("%s is a keyword\n",yytext);}
[a-zA-Z_][a-zA-Z0-9_]*  {printf("%s is an identifier\n",yytext);}
"++"|"--"|"=="|"!="|">="|"<="|"<<"|">>"|"&&"|"%="|"||"|"+"|"-"|"*"|"/"|"="|"%"|"^"|"\&"|"\|"|"<"|">"|"!" {printf("%s is an operator\n",yytext);}
[0-9]+"\."[0-9]+ {printf("%s is a float constant\n",yytext);}
[0-9]+ {printf("%s is an int constant\n",yytext);}
\"\" {printf("%s is a string constant\n",yytext);}
\'.\' {printf("%s is a character constant\n",yytext);}
[{}(),\[\];] {printf("%s is a special symbol\n",yytext);}
. ;
%%
int yywrap()
{
    return 1;
}
int main()
{
    yyin=fopen("temp.c","r");
    yylex();
    return 0;
}
