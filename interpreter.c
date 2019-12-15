#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"
#include "hashMips.h"
#include "code.h"

int main(int argc, char** argv) {
  init_table();
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  }
  if (yyparse() == 0) {
    // printf("fn main()\n");
    // cmdListPrint(root, 0);
    Instr_list* list = compileCmdList(root);
    printInstrList(list);
    remove("mips.txt");
    FILE *fp = fopen("mips.txt","ab+");
    printMipsData(fp);
    printMips(list,fp);
    fclose(fp);
  }

  return 0;


}
