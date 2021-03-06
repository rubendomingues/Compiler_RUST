%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}
"true" { return TRUE; }
"false" {return FALSE; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"%" { return MOD; }
">" { return GT; }
"<" { return LT; }
">=" { return GTE; }
"&&" { return AND; }
"||" { return OR; }
"<=" { return LTE; }
"==" { return EQ; }
"!=" { return NOT_EQ; }
"," { return VIRG; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"println!" { return PRINT; }
"read_line" { return READ; }
"let" { return ATRIB; }
"fn" { return FUNC; }
"main" { return MAIN; }
"&" { return COM; }
"(" { return OPENPAR; }
")" { return CLOSEPAR; }
"{" { return KEY1; }
"}" { return KEY2; }
";" { return SM; }
"=" { return TOKEN_EQ; }

\".*\" {
  yylval.charValue = strdup(yytext);
  return STRING;
}

[a-z][a-zA-Z]* {
	yylval.charValue = strdup(yytext);
	return VAR;
}
.  { yyerror("unexpected character"); }
%%
