%{
#include "y.tab.h"
#include <stdlib.h>

int yycolumn = 1;

/* Track cols for pretty compiler error output */
#define YY_USER_ACTION                                                         \
  do {                                                                         \
    yylloc.first_line = yylineno;                                              \
    yylloc.first_column = yycolumn;                                            \
    for (int i = 0; yytext[i]; i++) {                                          \
      if (yytext[i] == '\n')                                                   \
        yycolumn = 1;                                                          \
      else if (yytext[i] == '\t')                                              \
        yycolumn += 8 - (yycolumn - 1) % 8;                                    \
      else                                                                     \
        yycolumn++;                                                            \
    }                                                                          \
    yylloc.last_line = yylineno;                                               \
    yylloc.last_column = yycolumn - 1;                                         \
  } while (0);
%}

/* The below 'option' call voids some unused functions.
 * Older versions of lex might not recognize this line.
 * Although I trust flex in showing me warns when something is not
 * POSIX-compliant. */
%option nounput noinput yylineno

%%

[ \t\n]+                   /* skip (horizontal) whitespace */
"/*"([^*]|\*+[^*/])*\*+"/" /* skip comment */

"auto"                     { return TOK_AUTO; }
"extrn"                    { return TOK_EXTERN; }
"while"                    { return TOK_WHILE; }
"if"                       { return TOK_IF; }
"else"                     { return TOK_ELSE; }
"goto"                     { return TOK_GOTO; }
"return"                   { return TOK_RETURN; }
"switch"                   { return TOK_SWITCH; }
"case"                     { return TOK_CASE; }
"default"                  { return TOK_DEFAULT; }
"break"                    { return TOK_BREAK; }

[a-zA-Z_][a-zA-Z0-9_]*     { // Identifiers
                             yylval.str = strdup(yytext);
                             return TOK_IDENT; 
                           }
[0-9]+                     { // Plain integers
                             yylval.num = atoi(yytext); 
                             return TOK_NUM; 
                           }
[0-9]+\.[0-9]+             { // Floating-points
                             // Convert into raw IEEE-754 bits
                             float f = atof(yytext);
                             unsigned int bits;
                             memcpy(&bits, &f, sizeof(bits));
                             yylval.num = bits;
                             return TOK_NUM;
                           }
'(\\.|[^\\'])'             { // Plain characters
                             if (yytext[1] == '\\') {
                               if (yytext[2] == 'n') yylval.num = '\n';
                               else if (yytext[2] == 't') yylval.num = '\t';
                               else if (yytext[2] == '0') yylval.num = '\0';
                               else yylval.num = yytext[2];
                             } else {
                               yylval.num = (unsigned char)yytext[1];
                             }
                             return TOK_NUM;
                           }
\"([^\"\\]|\\.)*\"         { // Strings
                             yylval.str = strdup(yytext);
                             return TOK_STR;
                           }

";"                        { return TOK_SEMI; }
":"                        { return TOK_COL; }
","                        { return TOK_COMMA; }
"="                        { return TOK_ASSIGN; }

"("                        { return TOK_LPAREN; }
")"                        { return TOK_RPAREN; }
"{"                        { return TOK_LBRACE; }
"}"                        { return TOK_RBRACE; }
"["                        { return TOK_LBRACKET; }
"]"                        { return TOK_RBRACKET; }
"<"                        { return TOK_LANGLE; }
">"                        { return TOK_RANGLE; }
"<<"                       { return TOK_LSHIFT; }
">>"                       { return TOK_RSHIFT; }

"=="                       { return TOK_EQ; }
"!="                       { return TOK_NEQ; }
"<="                       { return TOK_LTE; }
">="                       { return TOK_GTE; }
"!"                        { return TOK_EXCL; }
"~"                        { return TOK_TILDE; }
"&&"                       { return TOK_DBL_AMPER; }
"&"                        { return TOK_AMPER; }
"||"                       { return TOK_DBL_PIPE; }
"|"                        { return TOK_PIPE; }
"^"                        { return TOK_CARRET; }

"#+"                       { return TOK_FPLUS; }
"#-"                       { return TOK_FMINUS; }
"#*"                       { return TOK_FMULT; }
"#/"                       { return TOK_FDIV; }
"#<"                       { return TOK_FLT; }
"#>"                       { return TOK_FGT; }

"#=="                      { return TOK_FEQ; }
"#!="                      { return TOK_FNEQ; }
"#<="                      { return TOK_FLTE; }
"#>="                      { return TOK_FGTE; }
"##"                       { return TOK_HASH_HASH; }
"#"                        { return TOK_HASH; }

"++"                       { return TOK_INCREMENT; }
"--"                       { return TOK_DECREMENT; }
"+"                        { return TOK_PLUS; }
"-"                        { return TOK_MINUS; }
"*"                        { return TOK_STAR; }
"/"                        { return TOK_DIV; }
"%"                        { return TOK_MOD; }

.                          {
                             fprintf(stderr, "Unknown character '%c`.\nThis should not have happened in the first place, as such characters should be considered as identifiers I believe. Please report to author.\n", yytext[0]);
                             return 1;
                             return TOK_UNKNOWN;
                           }

%%

int yywrap() {
    return 1;
}
