%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"

	
%}

%%

"read"						{return READ;}
"write"						{return WRITE;}
"argc"						{return ARGC;}
"if"						{return IF;}
"else"						{return ELSE;}
"do"						{return DO;}
"while"						{return WHILE;}
"return"					{return RET;}
"FUN"						{return FUN;}
[0-9]+						{yylval.i = atoi(yytext); return NUM;}
[a-zA-Z][a-zA-Z0-9]* 		{yylval.s = malloc(sizeof(char)*20); strcpy(yylval.s, yytext); return VAR;}
[ \t\n]						{}
[()*+-=!<>;{}]				{return *yytext;}
.							{yyerror("unknown character\n");exit(1);}

%%

int yywrap(void) {
	return 1;
}
