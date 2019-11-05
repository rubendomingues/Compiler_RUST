// #include <stdio.h>
// #include "parser.h"
//
// void eval(Cmd_list* list) {
//   if (list == NULL) {
//     yyerror("Null expression!!");
//   }
//   else {
//     while(list != NULL){
//       switch (list->elem->kind) {
//         case E_ATRIB:
//           break;
//         case E_IF:
//           break;
//         case E_IF_ELSE:
//           break;
//         case E_WHILE:
//           break;
//         case E_PRINT:
//           break;
//         case E_READ:
//           break;
//         // TODO Other cases here ...
//         default: yyerror("Unknown operator!");
//       }
//       list = list->next;
//     }
//   }
// }
// int main(int argc, char** argv) {
//   --argc; ++argv;
//   if (argc != 0) {
//     yyin = fopen(*argv, "r");
//     if (!yyin) {
//       printf("'%s': could not open file\n", *argv);
//       return 1;
//     }
//   } //  yyin = stdin
//   if (yyparse() == 0) {
//   }
//   return 0;
//
//
// }
#include <stdio.h>
#include "parser.h"

int eval(BoolExpr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == BOOLEANO) {
    result = expr->attr.value;
  }
  else if (expr->kind == EXP) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case GT:
        if(vLeft > vRight)
          result = 1;
        else
          result = 0;
        break;
      case LT:
        if(vLeft < vRight)
          result = 1;
        else
          result = 0;
        break;
      case GTE:
        if(vLeft >= vRight)
          result = 1;
        else
          result = 0;
        break;
      case LTE:
        if(vLeft <= vRight)
          result = 1;
        else
          result = 0;
        break;
      case EQ:
        if(vLeft == vRight)
          result = 1;
        else
          result = 0;
        break;
      case NOT_EQ:
        if(vLeft != vRight)
          result = 1;
        else
          result = 0;
        break;
      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
  }
  return result;
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
      printf("Result = %d\n", eval(root));
  }
  return 0;


}
