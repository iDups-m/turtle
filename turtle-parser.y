%{
#include <stdio.h>
#include <stdlib.h>

#include "turtle-ast.h"
#include "turtle.h"

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

//internal functions
%token 		  MATH_SIN      "sin"
%token		  MATH_COS      "cos"
%token 		  MATH_TAN      "tan"
%token		  MATH_RANDOM   "random"
%token		  MATH_SQRT   	"sqrt"

//color
%token            CL_RED        "red"
%token            CL_GREEN      "green"
%token            CL_BLUE       "blue"
%token            CL_CYAN       "cyan"
%token            CL_MAGENTA    "magenta"
%token            CL_YELLOW     "yellow"
%token            CL_BLACK      "black"
%token            CL_GREY       "grey"
%token            CL_WHITE      "white"

%left '+' '-'
%left '*' '/'
%precedence NEG

%type <node> unit cmds cmd expr
%type <value> value

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP	   		{ $$ = make_cmd_up(); }
  |  KW_DOWN			{ $$ = make_cmd_down(); }
  |  KW_FORWARD expr   		{ $$ = make_cmd_forward($2); }
  |  KW_BACKWARD expr		{ $$ = make_cmd_backward($2); }
  |  KW_POSITION expr expr	{ $$ = make_cmd_position($2, $3); }
  |  KW_RIGHT expr		{ $$ = make_cmd_right($2); }
  |  KW_LEFT expr		{ $$ = make_cmd_left($2); }
  |  KW_HEADING expr		{ $$ = make_cmd_heading($2); }
  |  KW_PRINT expr		{ $$ = make_cmd_print($2); }
  |  KW_COLOR expr		{ $$ = make_cmd_color($2); }
  |  KW_HOME			{ $$ = make_cmd_home(); }
  |  KW_REPEAT expr cmd		{ $$ = make_cmd_repeat($2, $3); }
  |  KW_SET expr expr		{ $$ = make_cmd_set($2, $3);}
  |  KW_PROC expr cmd		{ $$ = make_cmd_proc($2, $3); }
  |  KW_CALL expr		{ $$ = make_cmd_call($2); }
  |  MATH_SIN expr		{ $$ = make_func_sin($2); }
  |  MATH_COS expr		{ $$ = make_func_cos($2); }
  |  MATH_TAN expr		{ $$ = make_func_tan($2); }
  |  MATH_RANDOM expr expr	{ $$ = make_func_random($2, $3); }
  |  MATH_SQRT expr		{ $$ = make_func_sqrt($2); }
;

expr:
    VALUE             		{ $$ = make_expr_value($1); }

value:
  'q'                 	  	{ exit(0); }
  | NAME                  	{ $$ = constant($1); }
  | value '+' value       	{ $$ = $1 + $3; }
  | value '-' value       	{ $$ = $1 - $3; }
  | value '*' value       	{ $$ = $1 * $3; }
  | value '/' value       	{ $$ = $1 / $3; }
  | '-' value %prec NEG   	{ $$ = -$2; }
  | '(' value ')'         	{ $$ = $2; }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
