#include "code.h"
int k=1;
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
  // printf("%s\n",temp);
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
  switch(e->kind){
    case E_OPERATION:
      r1 = newTemp();
      r2 = newTemp();
      code1 = compileExpr(e->attr.op.left, r1);
      code2 = compileExpr(e->attr.op.right, r2);
      op = e->attr.op.operator;
      code3 = appendInstrList(code1,code2);
      Atom* a1 = makeVar(r);
      Atom* a2 = makeVar(r1);
      Atom* a3 = makeVar(r2);
      codeOp = mkInstrList(makeOperation(op,a1,a2,a3),NULL);
      code4 = appendInstrList(code3,codeOp);
      return code4;
      break;
    case E_INTEGER:
      r1 = r;
      code1 = mkInstrList(makeAtrib(makeVar(r1),makeInt(e->attr.valueInt)),NULL);
      return code1;
      break;
    case E_STRING:
      r1 = r;
      code1 = mkInstrList(makeAtrib(makeVar(r1),makeVar(e->attr.valueString)),NULL);
      return code1;
      break;
    default:
      printf("ERROR");
      break;

  }
}

// //NOT FINISHED
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
  switch(e->kind){
    case EXP:
      r1 = newTemp();
      r2 = newTemp();
      code1 = compileExpr(e->attr.op.left, r1);
      code2 = compileExpr(e->attr.op.right, r2);
      op = e->attr.op.operator;
      code3 = appendInstrList(code1,code2);
      Atom* a1 = makeVar(r1);
      Atom* a2 = makeVar(r2);
      codeOp = mkInstrList(makeIf(op,a1,a2,label1,label2),NULL);
      code4 = appendInstrList(code3,codeOp);
      return code4;
      break;
    case BOOLEANO:
      r1 = newTemp();
      code1 = mkInstrList(makeAtrib(makeVar(r1),makeInt(e->attr.value)),NULL);
      return code1;
      break;
    default:
      printf("ERROR");
      break;

  }
}

void printInstrList(Instr_list* listExpr){
  //CONVERSAO MIPS PARA OUTRO FICHEIRO
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
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" > ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;
      case I_IFL:
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" < ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;
      case I_IFGE:
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" >= ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;

      case I_IFLE:
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" <= ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;

      case I_IFEQ:
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" == ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;

      case I_IFNEQ:
        printAtom(listExpr->instr->attr.i_if.a1);
        printf(" != ");
        printAtom(listExpr->instr->attr.i_if.a2);
        printf(" { %s", listExpr->instr->attr.i_if.label1);
        printf(" } %s", listExpr->instr->attr.i_if.label1);
        printf("\n");
        break;

      default:
        printf("execExpr ERROR\n");
        break;
    }
    listExpr = listExpr->next;
  }
}

void compileCmdList(Cmd_list* cmdList){
  Instr_list* instrList = malloc(sizeof(Instr_list)); //Lista dos comandos convertida em instruções
  instrList = compileCmd(cmdList->elem);
  cmdList=cmdList->next;
  while(cmdList!=NULL){
    instrList = appendInstrList(instrList,compileCmd(cmdList->elem));
    cmdList = cmdList->next;
  }
}

Instr_list* compileCmd(Cmd* command){
  Instr_list* instrlist = malloc(sizeof(Instr_list));
  char* registo;
  switch (command->kind) {
    case E_ATRIB:
      registo = newTemp();
      instrlist = mkInstrList(makeAtrib(makeVar(command->attr.let.var),makeVar(registo)),NULL);
      instrlist = appendInstrList(instrlist,compileExpr(command->attr.let.value,registo));
      return instrlist;
      break;

    case E_IF:
      break;

    case E_IF_ELSE:
      break;

    case E_WHILE:
      break;

    case E_PRINT:
      break;

    case E_PSTR:
      break;

    case E_READ:
      break;
  }
}
