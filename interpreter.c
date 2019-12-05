#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"
#include "hash.h"
#include "label.h"
#include "code.h"

int main(int argc, char** argv) {
  init_table();
  init_tableLabel();
  // --argc; ++argv;
  // if (argc != 0) {
  //   yyin = fopen(*argv, "r");
  //   if (!yyin) {
  //     printf("'%s': could not open file\n", *argv);
  //     return 1;
  //   }
  // } //  yyin = stdin
  // if (yyparse() == 0) {
  //   printf("fn main()\n");
  //   // cmdListPrint(root, 0);
  // }
  // 2 + 3
  /*
  T1 = T2 + T3
  T2 = 2
  T3 = 3
  */
  // Expr* e1 = ast_integer(1);
  Expr* e3 = ast_integer(4);
  Expr* e5 = ast_integer(5);
  BoolExpr* e6 = ast_exp(GT,e3,e5);
  // Expr* e4 = ast_operation(PLUS,e1,e6);
  execExpr(compileBool(e6,"t0"));
  return 0;


}
