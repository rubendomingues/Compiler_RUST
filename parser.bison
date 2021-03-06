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
  FUNC
  COM
  VIRG
  STRING
  AND
  MAIN
  OR


// Operator associativity and precedence
%left FALSE TRUE
%left AND OR GT LT GTE LTE EQ NOT_EQ
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
%type <charValue> STRING
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
  #include "hashMips.h"

  extern int yylex();
  extern int yyline;
  extern char* yytext;
  extern FILE* yyin;
  extern void yyerror(const char* msg);
  Cmd_list* root;
}
%%
program: FUNC MAIN OPENPAR CLOSEPAR KEY1 cmdlist KEY2 { root = $6; }
//program: cmdlist { root = $1; }
expr:
  VAR {
    $$ = ast_variable($1);
    if(!lookup($1)){
      yyerror("variavel not defined");
      return 1;
    }
  }
  |
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
  expr EQ TRUE{
    $$ = ast_exp_bool(EQ, $1, 1);
  }
  |
  expr EQ FALSE{
    $$ = ast_exp_bool(EQ, $1, 0);
  }
  |
  expr NOT_EQ TRUE{
    $$ = ast_exp_bool(NOT_EQ, $1, 1);
  }
  |
  expr NOT_EQ FALSE{
    $$ = ast_exp_bool(NOT_EQ, $1, 0);
  }
  |
  bool_expr AND bool_expr{
    $$ = ast_bool_bool(AND,$1,$3);
  }
  |
  bool_expr OR bool_expr{
    $$ = ast_bool_bool(OR,$1,$3);
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
    if(!lookup($2)){
      insert($2,"var");
    }
  }
  |
  IF bool_expr KEY1 cmdlist KEY2 {
    $$ = ast_IF($2,$4);
  }
  |
  IF bool_expr KEY1 cmdlist KEY2 ELSE KEY1 cmdlist KEY2 {
    $$ = ast_IF_ELSE($2,$4,$8);
  }
  |
  WHILE bool_expr KEY1 cmdlist KEY2 {
    $$ = ast_WHILE($2,$4);
  }
  |
  READ OPENPAR COM VAR CLOSEPAR SM{
    $$ = ast_READ($4);
    if(!lookup($4))
      insert($4,"var");
  }
  |
  PRINT OPENPAR STRING CLOSEPAR SM{
    $$ = ast_PRINT($3);
    if(!lookup($3))
      insert($3,"text");
  }
  |
  PRINT OPENPAR STRING VIRG VAR CLOSEPAR SM{
    $$ = ast_PRINT_STRING($3,$5);
    if(!lookup($5)){
      yyerror("variavel not defined");
      return 1;
    }
    if(!lookup($3))
      insert($3,"text");
  }
  ;

cmdlist:
  cmd {
    $$ = newCmdList($1, NULL);
  }
  |
  cmd cmdlist {
    $$ = newCmdList($1,$2);
  }
  ;
  %%
//said where is the error
void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}
