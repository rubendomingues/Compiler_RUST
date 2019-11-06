#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "interpreter.h"
void exprPrint(Expr* expr, int tab){
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    // result = expr->attr.value;
    printf("integer\n");
  }
  else if (expr->kind == E_OPERATION) {
    switch (expr->attr.op.operator) {
      case PLUS:
        printf("Plus\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MINUS:
        printf("Minus\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MOD:
        printf("Mod\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case DIV:
        printf("Div\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      // TODO Other cases here ...
      default:
        yyerror("Unknown operator!");
        break;
    }
  }
}
void boolPrint(BoolExpr* expr, int tab) {
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == BOOLEANO) {
    // result = expr->attr.value;
    printf("booleano\n");
  }
  else if (expr->kind == EXP) {
    switch (expr->attr.op.operator) {
      case GT:
        printf("Greater\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LT:
        printf("Lower\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case GTE:
        printf("GreaterEqual\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LTE:
        printf("LowerEqual\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case EQ:
        printf("Equal\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case NOT_EQ:
        printf("NotEqual\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      // TODO Other cases here ...
      default:
        yyerror("Unknown operator!");
        break;
    }
  }
}

void cmdPrint(Cmd* comand, int tab){
  switch(comand->kind){
    case E_READ:
      printf("read\n");
      break;
    case E_MAIN:
      printf("main\n");
      cmdListPrint(comand->attr.funcT.list, tab+1);
      break;
    case E_FUNC:
      printf("func\n");
      cmdListPrint(comand->attr.funcT.list, tab+1);
      break;
    case E_ATRIB:
      printf("atrib\n");
      break;
    case E_IF:
      printf("if\n");
      boolPrint(comand->attr.ifT.cond, tab+1);
      cmdListPrint(comand->attr.ifT.list, tab+1);
      break;
    case E_IF_ELSE:
      printf("if_else\n");
      boolPrint(comand->attr.if_else.cond, tab+1);
      cmdListPrint(comand->attr.if_else.comando_if, tab+1);
      cmdListPrint(comand->attr.if_else.comando_else, tab+1);
      break;
    case E_WHILE:
      printf("while\n");
      boolPrint(comand->attr.whileT.cond, tab+1);
      cmdListPrint(comand->attr.whileT.list, tab+1);
      break;
    case E_PRINT:
      printf("print\n");
      break;
    default:
     yyerror("Unknown operator!");
     break;
  }
}

void cmdListPrint(Cmd_list* cmdList, int tab){
  while(cmdList != NULL){
    cmdPrint(cmdList->elem, tab+1);
    cmdList = cmdList->next;
  }
}
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
  //    printf("Result = %d\n", eval(root));
  cmdListPrint(root, 0);
  }
  return 0;


}
