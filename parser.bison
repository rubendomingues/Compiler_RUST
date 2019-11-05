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
  OPENPAR
  CLOSEPAR
  KEY1
  KEY2
  SM
  TOKEN_EQ
  VAR
  MAIN

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
  Cmd_list* cmdSequence;
}

%type <intValue> INT
%type <charValue> VAR
%type <exprValue> expr
%type <boolValue> bool_expr
%type <cmdValue> cmd
%type <cmdSequence> cmdlist

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
  Cmd_list* root;
}
%%
// program: MAIN OPENPAR CLOSEPAR KEY1 cmdlist KEY2 { root = $5; }
program: cmdlist { root = $1; }
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

cmd:
  ATRIB VAR TOKEN_EQ expr SM {
    $$ = ast_ATRIB($2,$4);
  }
  |
  IF OPENPAR bool_expr KEY1 cmdlist KEY2 CLOSEPAR ELSE KEY1 cmdlist KEY2 SM {
    $$ = ast_IF_ELSE($3,$5,$10);
  }
  |
  IF OPENPAR bool_expr KEY1 cmdlist CLOSEPAR KEY2 SM {
    $$ = ast_IF($3,$5);
  }
  |
  WHILE OPENPAR bool_expr CLOSEPAR KEY1 cmdlist KEY2 SM {
    $$ = ast_WHILE($3,$6);
  }
  |
  READ OPENPAR VAR CLOSEPAR SM{
    $$ = ast_READ($3);
  }
  |
  PRINT OPENPAR VAR CLOSEPAR SM{
    $$ = ast_PRINT($3);
  }
  ;

cmdlist:
  cmd {
    $$ = newCmdList($1, NULL);
  }
  |
  cmd SM cmdlist {
    $$ = newCmdList($1,$3);
  }
  ;
  %%

//said where is the error
void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}
