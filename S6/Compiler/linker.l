%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	int labels[100];
    int pass = 0;
    int lineNo = 0;
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
%}

label L[0-9]+

%%

{label}:\n                  {if(pass == 0){labels[atoi(yytext+1)] = lineNo++;} }
{label}                     {if(pass == 1){fprintf(fptr3, "%d", 2056 + 2 * (labels[atoi(yytext+1)] - atoi(yytext+1) - 8));}else{fprintf(fptr2, "%s", yytext);}}

\n                          {lineNo++;if(pass == 0){fprintf(fptr2, "%s", yytext);}else{fprintf(fptr3, "%s", yytext);}}
.							{if(pass == 0){fprintf(fptr2, "%s", yytext);}else{fprintf(fptr3, "%s", yytext);}}

%%

int yywrap(void) {
    if(pass == 0){
        pass = 1;
        fclose(fptr1);
        fclose(fptr2);
        fptr2 = fopen("output_ut.txt", "r");
        fptr3 = fopen("B190392CS.xsm", "w");
        yyin = fptr2;
        return 0;
    }
    fclose(fptr2);
    fclose(fptr3);
	return 1;
}

int main(){
	
	fptr1 = fopen("output.txt", "r");
	fptr2 = fopen("output_ut.txt", "w");	

	if(fptr1)
		yyin = fptr1;

	yylex();
	return 0;
}