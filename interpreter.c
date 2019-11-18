#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"
#include "hash.h"

int main(int argc, char** argv) {
  init_table();
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    printf("fn main()\n");
    cmdListPrint(root, 0);
  }
  return 0;


}
