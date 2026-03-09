%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
  int num;
  char *str;
}

%token <str> IDENTIFIER
%token <num> NUMBER
%token EQUALS SEMICOLON

%%

program:
  | program statement
  | program function_definition
  ;

statements_list:
  | statements_list statement
  ;

statement:
  IDENTIFIER EQUALS NUMBER SEMICOLON {
    printf("\tmov eax, %d\n", $3);
    printf("\tmov [ebp-4], eax ; store val\n");
  }
  ;

function_definition:
  IDENTIFIER '(' ')' '{' {
    printf("%s:\n", $1);
    printf("\t.long %s + 4\n", $1);
    printf("\tenter 0, 0\n"); 
  }
  statements_list
  '}' {
    printf("\tleave\n");
    printf("\tret\n");
  }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
  return yyparse();
}
