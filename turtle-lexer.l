%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
ID    [A-Z][A-Z0-9]*
BIG-LETTER  [A-Z]
LETTER      [A-Za-z]
HEX         [0-9A-Fa-f]
INT         0|[1-9][0-9]*

%%

"print"               { return KW_PRINT; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"forward"|"fw"        { return KW_FORWARD; }
"backward"|"bw"       { return KW_BACKWARD; }
"position"|"pos"      { return KW_POSITION; }
"right"|"rt"          { return KW_RIGHT; }
"left"|"lt"           { return KW_LEFT; }
"heading"|"hd"        { return KW_HEADING; }
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

"red"                 { yylval.color.r = 1.0; yylval.color.g = 0.0; yylval.color.b = 0.0; return COLOR; }
"green"               { yylval.color.r = 0.0; yylval.color.g = 1.0; yylval.color.b = 0.0; return COLOR; }
"blue"                { yylval.color.r = 0.0; yylval.color.g = 0.0; yylval.color.b = 1.0; return COLOR; }
"cyan"                { yylval.color.r = 0.0; yylval.color.g = 1.0; yylval.color.b = 1.0; return COLOR; }
"magenta"             { yylval.color.r = 1.0; yylval.color.g = 0.0; yylval.color.b = 1.0; return COLOR; }
"yellow"              { yylval.color.r = 1.0; yylval.color.g = 1.0; yylval.color.b = 1.0; return COLOR; }
"black"               { yylval.color.r = 0.0; yylval.color.g = 0.0; yylval.color.b = 0.0; return COLOR; }
"gray"                { yylval.color.r = 0.5; yylval.color.g = 0.5; yylval.color.b = 0.5; return COLOR; }
"white"               { yylval.color.r = 1.0; yylval.color.g = 1.0; yylval.color.b = 1.0; return COLOR; }

","           { return ','; }
"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"("           { return '('; }
")"           { return ')'; }
"{"           { return '{'; }
"}"           { return '}'; }
"#"           { return '#'; }
QUIT          { return 'q'; }

true                                                                        { printf("true found\n"); }
{DIGIT}+                                                                    { yylval.value = strtod(yytext, NULL); return VALUE; }
{ID}                                                                        { yylval.name = strdup(yytext); return NAME; }
0|[1-9]{DIGIT}*                                                             { printf("Number: %s\n", yytext); }
0x{HEX}+                                                                    { printf("Hex number: %s\n", yytext); }
{INT}(\.{DIGIT}+)?([eE][-+]?{DIGIT}+)?|\.{DIGIT}+([eE][-+]?{DIGIT}+)?       { printf("Floating number: %s\n", yytext); }
{BIG-LETTER}[A-Z0-9]*                                                       { printf("Variable or proc: %s\n", yytext); }
(_{LETTER}|_{DIGIT}|{LETTER})([0-9a-zA-Z_])*                                { printf("C identifier: %s\n", yytext); }
#[A-Za-z0-9 -_]*                                                            /* nothing */
[\n\t ]*                                                                    /* whitespace */
.                                                                           { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
