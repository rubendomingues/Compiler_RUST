
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
    E_STRING,
    E_OPERATION
  } kind;
  union {
    int valueInt; // for integer values
    char* valueString;
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr {
  enum {
    BOOL_BOOL,
    EXP_BOOLEANO,
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
    struct {
      int operator;
      struct _Expr* left;
      int value;
    } exp_b;
    struct {
      int operator; // PLUS, MINUS, etc
      struct _BoolExpr* left;
      struct _BoolExpr* right;
    } boolen;
  } attr;
};

struct _cmd {
  enum{
    E_ATRIB,
    E_IF,
    E_IF_ELSE,
    E_WHILE,
    E_PRINT,
    E_PSTR,
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
    struct {
      char* string;
      char* var;
    } string_var;
    char* str;
  } attr;
};

Cmd_list* newCmdList(Cmd* head, Cmd_list* tail);
// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_variable(char* s);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_bool_bool(int operator, BoolExpr* left, BoolExpr* right);
BoolExpr* ast_booleano(int v);
BoolExpr* ast_exp(int operator, Expr* left, Expr* right);
BoolExpr* ast_exp_bool(int operator, Expr* left, int v);
Cmd* ast_ATRIB(char* var, Expr* v);
Cmd* ast_IF(BoolExpr* cond, Cmd_list* comando);
Cmd* ast_IF_ELSE(BoolExpr* cond, Cmd_list* comando_if, Cmd_list* comando_else);
Cmd* ast_WHILE(BoolExpr* cond, Cmd_list* comando);
Cmd* ast_PRINT(char* str);
Cmd* ast_READ(char* var);
Cmd* ast_PRINT_STRING(char* string, char* var);
#endif
