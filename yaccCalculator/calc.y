%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sym.h"
%}

%union {
    double dval;
    struct sym * symptr;
}

%token <symptr> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression
%%
statement_list
    : statement '\n'
    | statement_list statement '\n'
    ;

statement
    : NAME '=' expression {
        if((strcmp($1->name, "PI") == 0) || (strcmp($1->name, "PHI") == 0))
            printf("assign to const\n");
        else
            $1->value = $3;
        }
    | expression { printf("= %g\n", $1); }
    ;

expression
    : expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
        if($3 != 0) // Check for division by zero
            $$ = $1 / $3;
        else {
                printf("divide by zero\n"); 
                $$ = $1;
            }   
        }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER
    | NAME {
        if(strcmp($1->name, "PI") == 0)
            $$ = 3.14159;
        else if (strcmp($1->name, "PHI") == 0)
            $$ = 1.61803;
        else
            $$ = $1->value;
        }
    | '?' {printList();}
    ;

%%
struct sym * head = NULL;


struct sym * sym_lookup(char * s)
{
    struct sym * p = head;

    while(p != NULL)
    {
        if(strcmp(p->name, s) == 0){
            return p;
        }
        else
           p = p->next;
    }
    struct sym * sp = malloc(sizeof(struct sym));

    sp->name = strdup(s);
    sp->next = head;
    head = sp;
    return sp;
}

/* void sym_Add(char * s, double n)
{
    struct sym * p = head;

    while(p != NULL)
    {
        if(strcmp(p->name, s) == 0){
            return;
        }
        else
           p = p->next;
    }
    struct sym * sp = malloc(sizeof(struct sym));

    sp->name = strdup(s);
    sp->value = n;
    sp->next = head;
    head = sp;
    return;
} */

void printList() {
    struct sym * p = head;
    printf("Printing list:\n");
    while(p != NULL)
    {
        printf("\t%s = %d\n", p->name, p->value);
        p = p->next;
    }
}