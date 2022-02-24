%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

/*internal functions
%token 		  SIN      "sin"
%token		  COS      "cos"
%token 		  TAN      "tan"
%token		  RANDOM   "random"*/

//keywords
%token 		  KW_PRINT    "print"
%token		  KW_UP	      "up"
%token		  KW_DOWN     "down"
%token            KW_FORWARD  "forward"
%token 		  KW_BACKWARD "backward"
%token		  KW_POSITION "position"
%token 		  KW_RIGHT    "right"
%token		  KW_LEFT     "left"
%token		  KW_HEADING  "heading"
%token		  KW_COLOR    "color"
%token		  KW_HOME     "home"
%token 		  KW_REPEAT   "repeat"
%token		  KW_SET      "set"
%token 		  KW_PROC     "proc"
%token		  KW_CALL     "call"

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr   { /* TODO */ }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
