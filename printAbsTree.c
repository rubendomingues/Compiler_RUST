#include "printAbsTree.h"

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
        printf("+\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MINUS:
        tabPrint(tab);
        printf("-\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case MOD:
        tabPrint(tab);
        printf("%c\n",'%');
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case DIV:
        tabPrint(tab);
        printf("/\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case TIMES:
        tabPrint(tab);
        printf("*\n");
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
    switch(expr->attr.value){
      case 1:
        printf("true\n");
        break;
      case 0:
        printf("false\n");
        break;
      default:
        yyerror("Unknown operator!");
        break;
    }
  }
  else if (expr->kind == BOOL_BOOL){
    switch(expr->attr.boolen.operator){
      case AND:
        tabPrint(tab);
        printf("&&\n");
        boolPrint(expr->attr.boolen.left, tab+1);
        boolPrint(expr->attr.boolen.right, tab+1);
        break;
      case OR:
        tabPrint(tab);
        printf("||\n");
        boolPrint(expr->attr.boolen.left, tab+1);
        boolPrint(expr->attr.boolen.right, tab+1);
        break;
      // TODO Other cases here ...
      default:
        yyerror("Unknown operator!");
        break;
    }
  }
  else if (expr->kind == EXP_BOOLEANO){
    switch(expr->attr.exp_b.operator){
      case EQ:
        tabPrint(tab);
        printf("==\n");
        exprPrint(expr->attr.exp_b.left, tab+1);
        break;
      case NOT_EQ:
        tabPrint(tab);
        printf("!=\n");
        exprPrint(expr->attr.exp_b.left, tab+1);
        break;
      default:
        yyerror("Unknown operator!");
        break;
    }
    if(expr->attr.exp_b.value == 0){
      tabPrint(tab+1);
      printf("false\n");
    }
    else{
      tabPrint(tab+1);
      printf("true\n");
    }
  }
  else if (expr->kind == EXP) {
    switch (expr->attr.op.operator) {
      case GT:
        tabPrint(tab);
        printf(">\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LT:
        tabPrint(tab);
        printf("<\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case GTE:
        tabPrint(tab);
        printf(">=\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case LTE:
        tabPrint(tab);
        printf("<=\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case EQ:
        tabPrint(tab);
        printf("==\n");
        exprPrint(expr->attr.op.left, tab+1);
        exprPrint(expr->attr.op.right, tab+1);
        break;
      case NOT_EQ:
        tabPrint(tab);
        printf("!=\n");
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
      printf("read_line()\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.str);
      break;
    case E_ATRIB:
      tabPrint(tab);
      printf("let\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.let.var);
      exprPrint(comand->attr.let.value,tab+1);
      break;
    case E_IF:
      tabPrint(tab);
      printf("if\n");
      boolPrint(comand->attr.ifT.cond, tab+1);
      cmdListPrint(comand->attr.ifT.list, tab);
      break;
    case E_IF_ELSE:
      tabPrint(tab);
      printf("if\n");
      boolPrint(comand->attr.if_else.cond, tab+1);
      cmdListPrint(comand->attr.if_else.comando_if, tab);
      tabPrint(tab);
      printf("else\n");
      cmdListPrint(comand->attr.if_else.comando_else, tab);
      break;
    case E_WHILE:
      tabPrint(tab);
      printf("while\n");
      boolPrint(comand->attr.whileT.cond, tab+1);
      cmdListPrint(comand->attr.whileT.list, tab);
      break;
    case E_PRINT:
      tabPrint(tab);
      printf("print_line!()\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.str);
      break;
    case E_PSTR:
      tabPrint(tab);
      printf("print_line!()\n");
      tabPrint(tab+1);
      printf("%s\n", comand->attr.string_var.string);
      tabPrint(tab+1);
      printf("%s\n", comand->attr.string_var.var);
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
