
// AST definitions
#ifndef __ast_h__
#define __ast_h__
typedef struct _BoolExpr BoolExpr;
typedef struct _Expr Expr; // Convenience typedef
typedef struct _cmd Cmd;
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
      char* var;
      int value;
    } let;
    struct {
      BoolExpr* cond;
      Cmd* comando;
    } op;
    struct {
      BoolExpr* cond;
      Cmd* comando_if;
      Cmd* comando_else;
    } if_else;
    char* str;
  } attr;
};

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_float(float v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_booleano(int v);
BoolExpr* ast_exp(int operator, Expr* left, Expr* right);
Cmd* ast_ATRIB(char* var, int v);
Cmd* ast_IF(BoolExpr* cond, Cmd* comando);
Cmd* ast_IF_ELSE(BoolExpr* cond, Cmd* comando_if, Cmd* comando_else);
Cmd* ast_WHILE(BoolExpr* cond, Cmd* comando);
Cmd* ast_PRINT(char* str);
Cmd* ast_READ(char* var);

#endif
