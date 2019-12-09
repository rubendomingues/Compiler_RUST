#ifndef __code_h__
#define __code_h__
#include "ast.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum {I_LABEL, I_GOTO, I_ATRIB, I_PLUS, I_MINUS, I_MULT, I_DIV, I_IFG, I_IFL, I_IFGE, I_IFLE, I_IFEQ, I_IFNEQ} I_Kind;

typedef enum {A_STRING, A_INT, A_EMPTY} AtomKind;

typedef struct{
  AtomKind kind;
  union{
    int val;
    char* name;
  } elem;
}Atom;

typedef struct{
  I_Kind ikind;
  union{
    struct{
      int operator;
      Atom* a1;
      Atom* a2;
      char* label1;
      char* label2;
    } i_if;
    struct{
      char* label1;
    } label;
    struct{
      Atom* a1; // variavel
      Atom* a2; // valor
    } atrib;
    struct{
      char* label1;
    } i_goto;
    struct{
      int operator;
      Atom* a1;
      Atom* a2;
      Atom* a3;
    } op;
  } attr;
} Instr;

typedef struct ilist{
  Instr* instr;
  struct ilist* next;
} Instr_list;

char* newTemp();

Atom* makeVar(char* var);
Atom* makeInt(int val);
Atom* makeEmpty();
void printAtom(Atom* a);

Instr* makeIf(int op, Atom* a1, Atom* a2, char* label1, char* label2);
Instr* makelabel(char* label);
Instr* makeAtrib(Atom* a1, Atom* a2);
Instr* makeGoto(char* label);
Instr* makeOperation(int operator, Atom* a1, Atom* a2, Atom* a3);

Instr_list* mkInstrList(Instr* i, Instr_list* l);
Instr_list* appendInstrList(Instr_list* l1, Instr_list* l2);
Instr_list* getFirstInstrList(Instr_list* l);
Instr_list* nextInstr(Instr_list* l);
int length(Instr_list* l);

Instr_list* compileCmd(Cmd* command);
Instr_list* compileBool(BoolExpr* e, char* label1, char* label2);
Instr_list* compileExpr(Expr* e, char* r);
void compileCmdList(Cmd_list* cmdList);
void printInstrList(Instr_list* listExpr);

#endif
