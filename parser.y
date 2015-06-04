%{
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
%}

%token NUMBER
%left '(' ')'
%left '/' '*'
%left '+' '-'

%%

list:	|expr {printf("Thread id : %ld ... Ans : %d \n",pthread_self(),$1);}
	;
	
expr:	'(' expr ')' { $$ = $2; }
	|
	expr '/' expr { $$ = $1 / $3; }
	|
	expr '*' expr { $$ = $1 * $3; }
	|
	expr '+' expr { $$ = $1 + $3; }
	|
	expr '-' expr { $$ = $1 - $3; }
	|
	NUMBER
	;

%%

void *parse(void *arguments)
{
	yyparse();
	pthread_exit(NULL);
	return 0;
}

int main(void)
{
	pthread_t threads[20];
	int i;
	for(i=0;i<20;i++)
	{
		pthread_create(&threads[i],NULL,&parse,NULL);
		sleep(2);
	}
	for(i=0;i<20;i++)
	{
		pthread_join(threads[i],NULL);
	}
	return 0;	
}

int yyerror(char *c)
{
	return 0;
}
