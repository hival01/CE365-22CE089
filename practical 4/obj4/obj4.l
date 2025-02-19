
%{
    #include <stdio.h>
    int length=0,lc=0,uc=0, digit=0, symbol=0, ec=0;
%}

%%
[a-z] {lc++; length+=yyleng;}
[A-Z] {uc++; length+=yyleng;}
[0-9] {digit++; length+=yyleng;}
[*,;#$@] {symbol++; length+=yyleng;}
[\n] {  
        if(length>=9 && length<=15 && lc>0 && uc>0 && digit>0 && symbol>0 && ec==0){
            printf("password is valid\n");
        }else{
            printf("password is invalid \n");
        }
        length=0; lc=0; uc=0; digit=0; symbol=0,ec=0;
    } 
. {ec++;length+=yyleng;}

%%

int yywrap() {return 1;} // to get infinite
int main() {
    printf("Enter string: ");
    yylex();
    return 0;
}
