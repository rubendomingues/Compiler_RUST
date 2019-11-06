#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "interpreter.h"

void tabPrint(int tab){
  for(int i=0; i<tab; i++){
    printf("  ");
  }
}

void exprPrint(Expr* expr, int tab){
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_STRING) {
    tabPrint(tab);
    printf("%s\n", expr->attr.valueString);
  }
  else if (expr->kind == E_INTEGER) {
    // result = expr->attr.value;
    tabPrint(tab);
    printf("%d\n", expr->attr.valueInt);
  }
  else if (expr->kind == E_OPERATION) {
    switch (expr->attr.op.operator) {
      case PLUS:
        tabPrint(tab);
        printf("PLUS\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MINUS:
        tabPrint(tab);
        printf("MINUS\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MOD:
        tabPrint(tab);
        printf("MOD\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case DIV:
        tabPrint(tab);
        printf("DIV\n");
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
    tabPrint(tab);
    printf("BOOL\n");
  }
  else if (expr->kind == EXP) {
    switch (expr->attr.op.operator) {
      case GT:
        tabPrint(tab);
        printf("GREATER\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LT:
        tabPrint(tab);
        printf("LOWER\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case GTE:
        tabPrint(tab);
        printf("GREATER OR EQUAL\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LTE:
        tabPrint(tab);
        printf("LOWER OR EQUAL\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case EQ:
        tabPrint(tab);
        printf("EQUAL\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case NOT_EQ:
        tabPrint(tab);
        printf("NOT EQUAL\n");
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
      tabPrint(tab);
      printf("READ\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.str);
      break;
    case E_MAIN:
      tabPrint(tab);
      printf("MAIN\n");
      cmdListPrint(comand->attr.funcT.list, tab);
      break;
    case E_FUNC:
      tabPrint(tab);
      printf("FUNC\n");
      cmdListPrint(comand->attr.funcT.list, tab);
      break;
    case E_ATRIB:
      tabPrint(tab);
      printf("ATRIB\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.let.var);
      exprPrint(comand->attr.let.value,tab+1);
      break;
    case E_IF:
      tabPrint(tab);
      printf("IF\n");
      boolPrint(comand->attr.ifT.cond, tab+1);
      cmdListPrint(comand->attr.ifT.list, tab);
      break;
    case E_IF_ELSE:
      tabPrint(tab);
      printf("IF THEN ELSE\n");
      boolPrint(comand->attr.if_else.cond, tab+1);
      cmdListPrint(comand->attr.if_else.comando_if, tab);
      cmdListPrint(comand->attr.if_else.comando_else, tab);
      break;
    case E_WHILE:
      tabPrint(tab);
      printf("WHILE\n");
      boolPrint(comand->attr.whileT.cond, tab+1);
      cmdListPrint(comand->attr.whileT.list, tab);
      break;
    case E_PRINT:
      tabPrint(tab);
      printf("PRINT\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.str);
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
  cmdListPrint(root, -1);
  }
  return 0;


}
