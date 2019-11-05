
// AST definitions
#ifndef __ast_h__
#define __ast_h__
typedef struct _BoolExpr BoolExpr;
typedef struct _Expr Expr; // Convenience typedef
typedef struct _cmd Cmd;

//LISTA DE COMANDOS
typedef struct list{
  Cmd* elem;
  struct list *next;
}Cmd_list;

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int valueInt; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr {
  enum {
    BOOLEANO,
    EXP
  } kind;
  union {
    int value; // for bool values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _cmd {
  enum{
    E_ATRIB,
    E_IF,
    E_IF_ELSE,
    E_WHILE,
    E_PRINT,
    E_READ
  } kind;
  union {
    struct {
      BoolExpr* cond;
      Cmd_list* list;
    } whileT;
    struct {
      BoolExpr* cond;
      Cmd_list* list;
    } ifT;
    struct {
      char* var;
      Expr* value;
    } let;
    struct {
      BoolExpr* cond;
      Cmd* comando;
    } op;
    struct {
      BoolExpr* cond;
      Cmd_list* comando_if;
      Cmd_list* comando_else;
    } if_else;
    char* str;
  } attr;
};


Cmd_list* newCmdList(Cmd* head, Cmd_list* tail);


// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_booleano(int v);
BoolExpr* ast_exp(int operator, Expr* left, Expr* right);
Cmd* ast_ATRIB(char* var, Expr* v);
Cmd* ast_IF(BoolExpr* cond, Cmd_list* comando);
Cmd* ast_IF_ELSE(BoolExpr* cond, Cmd_list* comando_if, Cmd_list* comando_else);
Cmd* ast_WHILE(BoolExpr* cond, Cmd_list* comando);
Cmd* ast_PRINT(char* str);
Cmd* ast_READ(char* var);

#endif
