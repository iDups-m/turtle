%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]

%%

"print"               { return KW_PRINT; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"forward" | "fw"      { return KW_FORWARD; }
"backward" | "bw"     { return KW_BACKWARD; }
"position" | "pos"    { return KW_POSITION; }
"right" | "rt"        { return KW_RIGHT; }
"left" | "lt"         { return KW_LEFT; }
"heading" | "hd"      { return KW_HEADING; }
"color"               { return KW_COLOR; }
"home"                { return KW_HOME; }
"repeat"              { return KW_REPEAT; }
"set"                 { return KW_SET; }
"proc"                { return KW_PROC; }
"call"                { return KW_CALL; }
"sin"                 { return MATH_SIN; }
"cos"                 { return MATH_COS; }
"tan"                 { return MATH_TAN; }
"random"              { return MATH_RANDOM; }
"sqrt"                { return MATH_SQRT; }

"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"("           { return '('; }
")"           { return ')'; }
"\n"          { return '\n'; }
"#"           { return '#'; }
QUIT          { return 'q'; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
{ID}                  { yylval.name = strdup(yytext); return NAME; }
#[A-Za-z0-9 -_]*      /* nothing */
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
