// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.valueInt = v;
  return node;
}

Expr* ast_float(float v){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_FLOAT;
  node->attr.valueFloat = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr* ast_booleano(int v){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = BOOLEANO;
  node->attr.value = v;
  return node;
}

BoolExpr* ast_exp(int operator, Expr* left, Expr* right){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = EXP;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Cmd* ast_ATRIB(char* var, int v){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_ATRIB;
  node->attr.let.var = var;
  node->attr.let.value = v;
  return node;
}

Cmd* ast_IF(BoolExpr* cond, Cmd* comando){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_IF;
  node->attr.op.cond = cond;
  node->attr.op.comando = comando;
  return node;
}

Cmd* ast_IF_ELSE(BoolExpr* cond, Cmd* comando_if, Cmd* comando_else){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_IF_ELSE;
  node->attr.if_else.cond = cond;
  node->attr.if_else.comando_if = comando_if;
  node->attr.if_else.comando_else = comando_else;
  return node;

}

Cmd* ast_WHILE(BoolExpr* cond, Cmd* comando){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_WHILE;
  node->attr.op.cond = cond;
  node->attr.op.comando = comando;
  return node;
}

Cmd* ast_PRINT(char* str){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_PRINT;
  node->attr.str = str;
  return node;
}

Cmd* ast_READ(char* var){
  Cmd* node = (Cmd*)malloc(sizeof(Cmd));
  node->kind = E_READ;
  node->attr.str = var;
  return node;
}
