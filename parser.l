%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[0-9]+		{sscanf(yytext,"%d",&yylval);
		return(NUMBER);}
[\n]		{return -1;}
[^0-9]		{return yytext[0];}

%%

int yywrap(void){
	return 1;
}
