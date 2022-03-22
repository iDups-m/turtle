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

/**
 * All types possible.
 * The structure color store red green blue values for each color.
 * A color can be given with doubles and so we put it in the structure, or with a keyword and me know what are values for rgb.
 */
%union {
  double value;
  char *name;
  struct ast_node *node;
  struct {
  	double r;
  	double g;
        double b;
  } color;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"
%token <color> 	  COLOR

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

/**
 * Priority rules :
 * Indicates associativity and priority for arithmetic operations.
 */
%left '+' '-'
%left '*' '/'
%precedence NEG

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

/**
 * Grammar rules for each commands.
 */
cmd:
     '{' cmds '}'			{ $$ = make_cmd_block($2); }
  |  KW_UP	   			{ $$ = make_cmd_up(); }
  |  KW_DOWN				{ $$ = make_cmd_down(); }
  |  KW_FORWARD expr   			{ $$ = make_cmd_forward($2); }
  |  KW_BACKWARD expr			{ $$ = make_cmd_backward($2); }
  |  KW_POSITION expr ',' expr		{ $$ = make_cmd_position($2, $4); }
  |  KW_RIGHT expr			{ $$ = make_cmd_right($2); }
  |  KW_LEFT expr			{ $$ = make_cmd_left($2); }
  |  KW_HEADING expr			{ $$ = make_cmd_heading($2); }
  |  KW_PRINT expr			{ $$ = make_cmd_print($2); }
  |  KW_COLOR expr ',' expr ','	expr	{ $$ = make_cmd_color($2, $4, $6); }						/* color with values of rgb 	*/
  |  KW_COLOR COLOR			{ $$ = make_cmd_color_yy($<color>2.r, $<color>2.g, $<color>2.b); }		/* color with keyword 		*/
  |  KW_HOME				{ $$ = make_cmd_home(); }
  |  KW_REPEAT expr cmd			{ $$ = make_cmd_repeat($2, $3); }
  |  KW_SET expr ',' expr		{ $$ = make_cmd_set($2, $4);}
  |  KW_PROC expr cmd			{ $$ = make_cmd_proc($2, $3); }
  |  KW_CALL expr			{ $$ = make_cmd_call($2); }
;


/**
 * An expression can be a value (double), a name (string) or operation between expressions
 */
expr:
    'q'                 		{ exit(0); }
    | MATH_RANDOM '(' expr ',' expr ')' { $$ = make_func_random($3, $5); }
    | VALUE             		{ $$ = make_expr_value($1); }
    | NAME                  		{ $$ = make_expr_name($1); }
    | expr '+' expr       		{ $$ = make_binary_operand($1, '+', $3); }
    | expr '-' expr       		{ $$ = make_binary_operand($1, '-', $3); }
    | expr '*' expr       		{ $$ = make_binary_operand($1, '*', $3); }
    | expr '/' expr       		{ $$ = make_binary_operand($1, '/', $3); }
    | '-' expr %prec NEG   		{ $$ = make_unary_operand('-', $2); }
    /*| '(' expr ',' expr ')'         	{ $$ = ; }*/
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}

/*
    | MATH_SIN expr			{ $$ = make_func_sin($2); }
    | MATH_COS expr			{ $$ = make_func_cos($2); }
    | MATH_TAN expr			{ $$ = make_func_tan($2); }
    | MATH_SQRT expr			{ $$ = make_func_sqrt($2); }
    */