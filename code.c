#include "code.h"
int k=0;
int labelnum=1;
// int countString = 1;
//Atom constructor
Atom* makeVar(char* var){
  Atom* a = malloc(sizeof(Atom));
  a->kind = A_STRING;
  a->elem.name = strdup(var);
  return a;
}

Atom* makeInt(int val){
  Atom* a = malloc(sizeof(Atom));
  a->kind = A_INT;
  a->elem.val = val;
  return a;
}

Atom* makeRegister(char* reg){
  Atom* a = malloc(sizeof(Atom));
  a->kind = A_REGISTER;
  a->elem.name = strdup(reg);
  return a;
}

Atom* makeEmpty(){
  Atom* a = malloc(sizeof(Atom));
  a->kind = A_EMPTY;
  return a;
}

void printAtom(Atom* a){
  switch (a->kind){
    case A_INT:
      printf("%d", a->elem.val);
      break;
    case A_STRING:
      printf("%s", a->elem.name);
      break;
    case A_EMPTY:
      printf("VAZIO");
      break;
    case A_REGISTER:
      printf("%s", a->elem.name);
      break;
    default:
      printf("ATOM ERROR!\n");
      break;
  }
}
//Instr constructor
Instr* makeIf(int op, Atom* a1, Atom* a2, char* label1, char* label2){
  Instr* instr = malloc(sizeof(Instr));
  switch (op) {
    case GT:
      instr->ikind = I_IFG;
      break;
    case LT:
      instr->ikind = I_IFL;
      break;
    case GTE:
      instr->ikind = I_IFGE;
      break;
    case LTE:
      instr->ikind = I_IFLE;
      break;
    case EQ:
      instr->ikind = I_IFEQ;
      break;
    case NOT_EQ:
      instr->ikind = I_IFNEQ;
      break;
  }
  instr->attr.i_if.operator = op;
  instr->attr.i_if.a1 = a1;
  instr->attr.i_if.a2 = a2;
  instr->attr.i_if.label1 = strdup(label1);
  instr->attr.i_if.label2 = strdup(label2);
  return instr;
}

Instr* makePrint(Atom* a1, Atom* a2){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_PRINT;
  instr->attr.print.a1 = a1;
  instr->attr.print.a2 = a2;
}

Instr* makeRead(Atom * a1, Atom* a2){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_READ;
  instr->attr.read.a1 = a1;
  instr->attr.read.a2 = a2;
  return instr;
}

Instr* makelabel(char* label){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_LABEL;
  instr->attr.label.label1 = strdup(label);
  return instr;
}

Instr* makeAtrib(Atom* a1, Atom* a2){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_ATRIB;
  instr->attr.atrib.a1 = a1;
  instr->attr.atrib.a2 = a2;
  return instr;
}

Instr* makeGoto(char* label){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_GOTO;
  instr->attr.i_goto.label1 = strdup(label);
  return instr;
}

Instr* makePrintString(Atom* a1, Atom* a2, Atom* a3, Atom* a4){
  Instr* instr = malloc(sizeof(Instr));
  instr->ikind = I_PRINTS;
  instr->attr.print2.a1 = a1;
  instr->attr.print2.a2 = a2;
  instr->attr.print2.a3 = a3;
  instr->attr.print2.a4 = a4;
  return instr;
}

Instr* makeOperation(int operator, Atom* a1, Atom* a2, Atom* a3){
  Instr* instr = malloc(sizeof(Instr));
  switch (operator) {
    case PLUS:
      instr->ikind = I_PLUS;
      break;
    case MINUS:
      instr->ikind = I_MINUS;
      break;
    case DIV:
      instr->ikind = I_DIV;
      break;
    case TIMES:
      instr->ikind = I_MULT;
      break;
  }
  instr->attr.op.operator = operator;
  instr->attr.op.a1 = a1;
  instr->attr.op.a2 = a2;
  instr->attr.op.a3 = a3;
  return instr;
}
//Other functions
char* newTemp(){
  char* temp = malloc(1024*sizeof(char));
  sprintf(temp,"t%d",k);
  k++;
  if(k==8)
    k=0;
  // printf("%s\n",temp);
  return temp;
}

char* newLabel(){
  char* temp = malloc(1024*sizeof(char));
  sprintf(temp,"label%d",labelnum);
  labelnum++;
  return temp;
}
//List of instructions
Instr_list* mkInstrList(Instr* i, Instr_list* l){
  Instr_list* list = malloc(sizeof(struct ilist));
  list->instr = i;
  list->next = l;
  return list;
}

Instr_list* appendInstrList(Instr_list* l1, Instr_list* l2){
  Instr_list* lf = l1;
  if(l1 == NULL) return l2;
  else{
    while(l1->next != NULL){
      l1=l1->next;
    }
    l1->next=l2;
  }
  return lf;
}

Instr* getFirstInstr(Instr_list* l){
  if(l == NULL){
    printf("ERROR");
  }
  else{
    return (l->instr);
  }
}

Instr_list* nextInstr(Instr_list* l){
  if(l == NULL){
    printf("ERROR");
  }
  else if(l->next == NULL)
    printf("ERROR");
  else{
    return l->next;
  }
}

int length(Instr_list* l){
  int i=0;
  while(l != NULL){
    l=l->next;
    i++;
  }
  return i;
}

Instr_list* compileExpr(Expr* e, char* r){
  char* r1 = malloc(1024*sizeof(char));
  char* r2 = malloc(1024*sizeof(char));
  Instr_list* code1 = malloc(sizeof(struct ilist));
  Instr_list* code2 = malloc(sizeof(struct ilist));
  Instr_list* code3 = malloc(sizeof(struct ilist));
  Instr_list* code4 = malloc(sizeof(struct ilist));
  Instr_list* codeOp = malloc(sizeof(struct ilist));
  Instr* instrOp = malloc(sizeof(Instr));
  int op;
  int finalReg=0;
  switch(e->kind){
    case E_OPERATION:
      finalReg = k;
      r1 = newTemp();
      r2 = newTemp();
      code1 = compileExpr(e->attr.op.left, r1);
      code2 = compileExpr(e->attr.op.right, r2);
      op = e->attr.op.operator;
      code3 = appendInstrList(code1,code2);
      Atom* a1 = makeRegister(r);
      Atom* a2 = makeRegister(r1);
      Atom* a3 = makeRegister(r2);
      codeOp = mkInstrList(makeOperation(op,a1,a2,a3),NULL);
      code4 = appendInstrList(code3,codeOp);
      k = finalReg;
      return code4;
      break;
    case E_INTEGER:
      r1 = r;
      code1 = mkInstrList(makeAtrib(makeRegister(r1),makeInt(e->attr.valueInt)),NULL);
      return code1;
      break;
    case E_STRING:
      r1 = r;
      code1 = mkInstrList(makeAtrib(makeRegister(r1),makeVar(e->attr.valueString)),NULL);
      return code1;
      break;
    default:
      printf("ERROR");
      break;

  }
}

Instr_list* compileBool(BoolExpr* e, char* label1, char* label2){ // recebe 2 labels (true e false)
  char* r1 = malloc(1024*sizeof(char));
  char* r2 = malloc(1024*sizeof(char));
  Instr_list* code1 = malloc(sizeof(struct ilist));
  Instr_list* code2 = malloc(sizeof(struct ilist));
  Instr_list* code3 = malloc(sizeof(struct ilist));
  Instr_list* code4 = malloc(sizeof(struct ilist));
  Instr_list* codeOp = malloc(sizeof(struct ilist));
  Instr* instrOp = malloc(sizeof(Instr));
  int op;
  int finalReg = 0;
  switch(e->kind){
    case EXP:
      finalReg = k;
      r1 = newTemp();
      r2 = newTemp();
      code1 = compileExpr(e->attr.op.left, r1);
      code2 = compileExpr(e->attr.op.right, r2);
      op = e->attr.op.operator;
      code3 = appendInstrList(code1,code2);
      Atom* a1 = makeRegister(r1);
      Atom* a2 = makeRegister(r2);
      codeOp = mkInstrList(makeIf(op,a1,a2,label1,label2),NULL);
      code4 = appendInstrList(code3,codeOp);
      k = finalReg;
      return code4;
      break;
    case BOOLEANO:
      r1 = newTemp();
      code1 = mkInstrList(makeAtrib(makeRegister(r1),makeInt(e->attr.value)),NULL);
      return code1;
      break;

    default:
      printf("ERROR");
      break;

  }
}

Instr_list* compileCmdList(Cmd_list* cmdList){
  if(cmdList == NULL)
    return NULL;

  Instr_list* instrList = malloc(sizeof(Instr_list)); //Lista dos comandos convertida em instruções
  instrList = compileCmd(cmdList->elem);
  cmdList=cmdList->next;

  while(cmdList!=NULL){
    instrList = appendInstrList(instrList,compileCmd(cmdList->elem));
    cmdList = cmdList->next;
  }

  return instrList;
}

Instr_list* compileCmd(Cmd* command){
  Instr_list* instrlist = malloc(sizeof(Instr_list));
  char* registo = malloc(1024*(sizeof(char)));
  char* registo2 = malloc(1024*(sizeof(char)));
  char* label1 = malloc(1024*(sizeof(char)));
  char* label2 = malloc(1024*(sizeof(char)));
  char* label3 = malloc(1024*(sizeof(char)));
  switch (command->kind) {
    case E_ATRIB:
      registo = newTemp();
      instrlist = mkInstrList(makeAtrib(makeVar(command->attr.let.var),makeRegister(registo)),NULL);
      instrlist = appendInstrList(compileExpr(command->attr.let.value,registo),instrlist);
      return instrlist;
      break;

    case E_IF:
      label1 = newLabel();
      label2 = newLabel();
      instrlist = compileBool(command->attr.ifT.cond,label1,label2);
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label1),NULL));
      instrlist = appendInstrList(instrlist,compileCmdList(command->attr.ifT.list));
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label2),NULL));
      return instrlist;
      break;

    case E_IF_ELSE:
      label1 = newLabel();
      label2 = newLabel();
      label3 = newLabel();
      instrlist = compileBool(command->attr.if_else.cond,label1,label2);
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label1),NULL));
      instrlist = appendInstrList(instrlist,compileCmdList(command->attr.if_else.comando_if));
      instrlist = appendInstrList(instrlist,mkInstrList(makeGoto(label3),NULL));
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label2),NULL));
      instrlist = appendInstrList(instrlist,compileCmdList(command->attr.if_else.comando_else));
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label3),NULL));
      return instrlist;
      break;

    case E_WHILE:
      label1 = newLabel();
      label2 = newLabel();
      label3 = newLabel();
      instrlist = mkInstrList(makelabel(label1),NULL);
      instrlist = appendInstrList(instrlist,compileBool(command->attr.whileT.cond,label2,label3));
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label2),NULL));
      instrlist = appendInstrList(instrlist,compileCmdList(command->attr.whileT.list));
      instrlist = appendInstrList(instrlist,mkInstrList(makeGoto(label1),NULL));
      instrlist = appendInstrList(instrlist,mkInstrList(makelabel(label3),NULL));
      return instrlist;
      break;

    case E_PRINT:
      // registo = newTemp();
      instrlist = mkInstrList(makePrint(makeVar(command->attr.str),makeRegister(registo)),NULL);
      return instrlist;
      break;

    case E_PSTR:
      // registo = newTemp();
      // registo2 = newTemp();
      instrlist = mkInstrList(makePrintString(makeVar(command->attr.string_var.var),makeRegister(registo),makeVar(command->attr.string_var.string),makeRegister(registo2)),NULL);
      return instrlist;
      break;

    case E_READ:
      // registo = newTemp();
      instrlist = mkInstrList(makeRead(makeVar(command->attr.str),makeRegister(registo)),NULL);
      return instrlist;
      break;
  }
}

void printInstrList(Instr_list* listExpr){
  while(listExpr!= NULL){
    switch (listExpr->instr->ikind){
      case I_ATRIB:
        printAtom(listExpr->instr->attr.atrib.a1);
        printf(" = ");
        printAtom(listExpr->instr->attr.atrib.a2);
        printf("\n");
        break;

      case I_PLUS:
        printAtom(listExpr->instr->attr.op.a1);
        printf(" = ");
        printAtom(listExpr->instr->attr.op.a2);
        printf(" + ");
        printAtom(listExpr->instr->attr.op.a3);
        printf("\n");
        break;

      case I_MINUS:
        printAtom(listExpr->instr->attr.op.a1);
        printf(" = ");
        printAtom(listExpr->instr->attr.op.a2);
        printf(" - ");
        printAtom(listExpr->instr->attr.op.a3);
        printf("\n");
        break;

      case I_DIV:
        printAtom(listExpr->instr->attr.op.a1);
        printf(" = ");
        printAtom(listExpr->instr->attr.op.a2);
        printf(" / ");
        printAtom(listExpr->instr->attr.op.a3);
        printf("\n");
        break;

      case I_MULT:
        printAtom(listExpr->instr->attr.op.a1);
        printf(" = ");
        printAtom(listExpr->instr->attr.op.a2);
        printf(" * ");
        printAtom(listExpr->instr->attr.op.a3);
        printf("\n");
        break;

      case I_IFG:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" GT ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;
      case I_IFL:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" LT ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;
      case I_IFGE:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" GTE ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;

      case I_IFLE:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" LTE ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;

      case I_IFEQ:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" EQ ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;

      case I_IFNEQ:
        printf("IF ");
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" NEQ ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" THEN ");
        printf("%s", listExpr->instr->attr.i_if.label1);
        printf(" ELSE ");
        printf("%s", listExpr->instr->attr.i_if.label2);
        printf("\n");
        break;

      case I_LABEL:
        printf("%s \n",listExpr->instr->attr.label.label1);
        break;

      case I_GOTO:
        printf("GOTO %s\n", listExpr->instr->attr.i_goto.label1);
        break;

      case I_READ:
        printf("READ ");
        printAtom(listExpr->instr->attr.read.a1);
        // printf(" ");
        // printAtom(listExpr->instr->attr.read.a2);
        printf("\n");
        break;

      case I_PRINT:
        printf("PRINT ");
        printAtom(listExpr->instr->attr.print.a1);
        // printf(" ");
        // printAtom(listExpr->instr->attr.print.a2);
        printf("\n");
        break;

      case I_PRINTS:
        printf("PRINT ");
        printAtom(listExpr->instr->attr.print2.a1);
        printf(" ");
        // printAtom(listExpr->instr->attr.print2.a2);
        // printf(" ");
        printAtom(listExpr->instr->attr.print2.a3);
        // printf(" ");
        // printAtom(listExpr->instr->attr.print2.a4);
        printf("\n");
        break;
      default:
        printf("execExpr ERROR\n");
        break;
    }
    listExpr = listExpr->next;
  }
}

void printMipsData(FILE* fp){
  fprintf(fp,".data:\n");
  // char* temp = malloc(1024*sizeof(char));
  // int countS = 1;
  for(int i=0; i<1024; i++){
    if(table[i]==NULL)
      continue;
    LIST p = table[i];
    while(p){
      if(strcmp(p->type,"text")==0){
        fprintf(fp, "  ");
        for(int i=1; i<strlen(p->key)-1; i++){
          fprintf(fp, "%c",p->key[i]);
        }
        // sprintf(temp,"string%d",countS);
        // countS++;
        // fprintf(fp,"%s",temp);
        fprintf(fp,": .askii %s\n",p->key);
      }
      else
        fprintf(fp,"  %s: .space 4\n",p->key);
      p = p->next;
    }
  }
  fprintf(fp,"\n.text:\n");
  fprintf(fp,"  main:\n");
}
void printMips(Instr_list* listExpr, FILE* fp){
  // char* stringT = malloc(1024*sizeof(char));
  //CONVERSAO MIPS PARA OUTRO FICHEIRO
  while(listExpr!=NULL){
    switch (listExpr->instr->ikind){
      case I_ATRIB:
        fprintf(fp, "   ");
        if(listExpr->instr->attr.atrib.a1->kind == A_REGISTER){
          if(listExpr->instr->attr.atrib.a2->kind == A_STRING)
            fprintf(fp, "la $%s, %s\n", listExpr->instr->attr.atrib.a1->elem.name,listExpr->instr->attr.atrib.a2->elem.name);
          else if(listExpr->instr->attr.atrib.a2->kind == A_INT)
            fprintf(fp, "li $%s, %d\n", listExpr->instr->attr.atrib.a1->elem.name,listExpr->instr->attr.atrib.a2->elem.val);
        }
        else if(listExpr->instr->attr.atrib.a1->kind == A_STRING)
          fprintf(fp, "sw %s, $%s\n", listExpr->instr->attr.atrib.a1->elem.name, listExpr->instr->attr.atrib.a2->elem.name);
        break;

      case I_PLUS:
        fprintf(fp, "   ");
        fprintf(fp,"add $%s,$%s,$%s\n",listExpr->instr->attr.op.a1->elem.name,listExpr->instr->attr.op.a2->elem.name,listExpr->instr->attr.op.a3->elem.name);
        break;

      case I_MINUS:
        fprintf(fp, "   ");
        fprintf(fp,"sub $%s,$%s,$%s\n",listExpr->instr->attr.op.a1->elem.name,listExpr->instr->attr.op.a2->elem.name,listExpr->instr->attr.op.a3->elem.name);
        break;

      case I_DIV:
        fprintf(fp, "   ");
        fprintf(fp,"div $%s,$%s,$%s\n",listExpr->instr->attr.op.a1->elem.name,listExpr->instr->attr.op.a2->elem.name,listExpr->instr->attr.op.a3->elem.name);
        break;

      case I_MULT:
        fprintf(fp, "   ");
        fprintf(fp,"mul $%s,$%s,$%s\n",listExpr->instr->attr.op.a1->elem.name,listExpr->instr->attr.op.a2->elem.name,listExpr->instr->attr.op.a3->elem.name);
        break;

      case I_IFG:
        fprintf(fp, "   ");
        fprintf(fp, "ble $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;
      case I_IFL:
        fprintf(fp, "   ");
        fprintf(fp, "bge $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;
      case I_IFGE:
        fprintf(fp, "   ");
        fprintf(fp, "blt $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;

      case I_IFLE:
        fprintf(fp, "   ");
        fprintf(fp, "bgt $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;

      case I_IFEQ:
        fprintf(fp, "   ");
        fprintf(fp, "bne $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;

      case I_IFNEQ:
        fprintf(fp, "   ");
        fprintf(fp, "beq $%s,$%s,%s\n", listExpr->instr->attr.i_if.a1->elem.name,listExpr->instr->attr.i_if.a2->elem.name,listExpr->instr->attr.i_if.label2);
        break;

      case I_LABEL:
        fprintf(fp, "   ");
        fprintf(fp, "%s:\n", listExpr->instr->attr.label.label1);
        break;

      case I_GOTO:
        fprintf(fp, "   ");
        fprintf(fp, "j %s\n", listExpr->instr->attr.i_goto.label1);
        break;

      case I_READ:
        fprintf(fp, "   li $v0, 5\n");
        fprintf(fp, "   syscall\n");
        fprintf(fp, "   sw %s, $v0\n", listExpr->instr->attr.read.a1->elem.name);
        break;

      case I_PRINT:
        fprintf(fp, "   li $v0, 4\n");
        fprintf(fp, "   la $a0, ");
        for(int i=1; i<strlen(listExpr->instr->attr.print.a1->elem.name)-1; i++)
          fprintf(fp,"%c",listExpr->instr->attr.print.a1->elem.name[i]);
        // sprintf(stringT, "string%d",countString);
        // countString++;
        // fprintf(fp,"%s",stringT);
        fprintf(fp,"\n");
        fprintf(fp, "   syscall\n");
        break;

      case I_PRINTS:
        fprintf(fp, "   li $v0, 4\n");
        fprintf(fp, "   la $a0, ");
        for(int i=1; i<strlen(listExpr->instr->attr.print2.a3->elem.name)-1; i++)
          fprintf(fp,"%c",listExpr->instr->attr.print2.a3->elem.name[i]);
        // sprintf(stringT, "string%d",countString);
        // countString++;
        // fprintf(fp,"%s",stringT);
        fprintf(fp,"\n");
        fprintf(fp, "   syscall\n");
        fprintf(fp, "   li $v0, 5\n");
        fprintf(fp, "   la $a0, %s\n", listExpr->instr->attr.print2.a1->elem.name);
        fprintf(fp, "   syscall\n");
        break;

      default:
        printf("execExpr ERROR\n");
        break;
    }
    listExpr = listExpr->next;
  }
}
