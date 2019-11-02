// Tokens
%token
  INT
  TRUE
  FALSE
  PLUS
  MINUS
  TIMES
  DIV
  MOD
  GT
  LT
  GTE
  LTE
  EQ
  IF
  ELSE
  WHILE
  READ
  PRINT
  NOT_EQ
  ATRIB
  KEY1
  KEY2
  SM
  TOKEN_EQ
  VAR

// Operator associativity and precedence
%left FALSE TRUE
%left GT LT GTE LTE EQ NOT_EQ
%left PLUS MINUS
%left TIMES DIV
%left MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* charValue;
  Expr* exprValue;
  BoolExpr* boolValue;
  Cmd* cmdValue;
}

%type <intValue> INT
%type <charValue> VAR
%type <exprValue> expr
%type <boolValue> bool_expr
%type <cmdValue> cmd_expr

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"

  extern int yylex();
  extern int yyline;
  extern char* yytext;
  extern FILE* yyin;
  extern void yyerror(const char* msg);
  Expr* root;
}
%%
program: expr { root = $1; }

program: expr { root = $1; }
expr:
  INT {
    $$ = ast_integer($1);
  }
  |
  expr PLUS expr {
    $$ = ast_operation(PLUS, $1, $3);
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr TIMES expr {
    $$ = ast_operation(TIMES, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_operation(MOD, $1, $3);
  }
;

bool_expr:
  expr GT expr{
    $$ = ast_exp(GT, $1, $3);
  }
  |
  expr LT expr{
    $$ = ast_exp(LT, $1, $3);
  }
  |
  expr GTE expr{
    $$ = ast_exp(GTE, $1, $3);
  }
  |
  expr LTE expr{
    $$ = ast_exp(LTE, $1, $3);
  }
  |
  expr EQ expr{
    $$ = ast_exp(EQ, $1, $3);
  }
  |
  expr NOT_EQ expr{
    $$ = ast_exp(NOT_EQ, $1, $3);
  }
  |
  FALSE {
    $$ = ast_booleano(0);
  }
  |
  TRUE {
    $$ = ast_booleano(1);
  }
  ;

cmd_expr:
  ATRIB VAR TOKEN_EQ expr SM {
    $$ = ast_ATRIB($2,$4);
  }
  |
  IF bool_expr KEY1 cmd_expr KEY2 ELSE KEY1 cmd_expr KEY2 SM {
    $$ = ast_IF_ELSE($2,$4,$8);
  }
  |
  IF bool_expr KEY1 cmd_expr KEY2 SM {
    $$ = ast_IF($2,$4);
  }
  |
  WHILE bool_expr KEY1 cmd_expr KEY2 SM {
    $$ = ast_WHILE($2,$4);
  }
  |
  READ VAR {
    $$ = ast_READ($2);
  }
  ;
  %%

//said where is the error
void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}
