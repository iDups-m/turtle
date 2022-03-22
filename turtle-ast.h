#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_RANDOM,
  FUNC_SIN,
  FUNC_SQRT,
  FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};

char *str_dup(char *src);

//constructors

/*
 * expression and operand
 */
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_name(char* name);
struct ast_node *make_binary_operand(struct ast_node *expr1, char operand, struct ast_node *expr2);
struct ast_node *make_unary_operand(char operand, struct ast_node *expr);

/*
 * commands and math functions
 */
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_up();
struct ast_node *make_cmd_down();
struct ast_node *make_cmd_print(struct ast_node *expr);
struct ast_node *make_cmd_color(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3);
struct ast_node *make_cmd_color_yy();
struct ast_node *make_cmd_home();
struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_call(struct ast_node *expr);
struct ast_node *make_cmd_block(struct ast_node *expr);
struct ast_node *make_func_sin(struct ast_node *expr);
struct ast_node *make_func_cos(struct ast_node *expr);
struct ast_node *make_func_tan(struct ast_node *expr);
struct ast_node *make_func_random(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_func_sqrt(struct ast_node *expr);
struct ast_node *make_expr_block(struct ast_node *expr);


// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);
void ast_node_destroy(struct ast_node *self);

// handling of proc for the context
struct proc_handling {
    char* name;
    struct ast_node *self;
    struct proc_handling *next;
};
// the execution context
struct context {
    double x;
    double y;
    double angle;
    bool up;

    struct {
        double r;
        double g;
        double b;
    } color;

    struct proc_handling* handler;
};

// create an initial context
void context_create(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);
void ast_node_print(const struct ast_node *node);

// print elements
void print_cmd_forward(const struct ast_node *self);
void print_cmd_backward(const struct ast_node *self);
void print_cmd_position(const struct ast_node *self);
void print_cmd_right(const struct ast_node *self);
void print_cmd_left(const struct ast_node *self);
void print_cmd_heading(const struct ast_node *self);
void print_cmd_up(const struct ast_node *self);
void print_cmd_down(const struct ast_node *self);
void print_cmd_print(const struct ast_node *self);
void print_cmd_color(const struct ast_node *self);
void print_cmd_home(const struct ast_node *self);
void print_cmd_repeat(const struct ast_node *self);
void print_cmd_set(const struct ast_node *self);
void print_cmd_proc(const struct ast_node *self);
void print_cmd_call(const struct ast_node *self);
void print_cmd_block(const struct ast_node *self);
void print_func_sin(const struct ast_node *self);
void print_func_cos(const struct ast_node *self);
void print_func_tan(const struct ast_node *self);
void print_func_random(const struct ast_node *self);
void print_func_sqrt(const struct ast_node *self);
void print_binary_operand(const struct ast_node *self);
void print_unary_operand(const struct ast_node *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);
double ast_node_eval(const struct ast_node *self, struct context *ctx);

//eval elements
void eval_cmd_forward(const struct ast_node *self, struct context *ctx);
void eval_cmd_backward(const struct ast_node *self, struct context *ctx);
void eval_cmd_position(const struct ast_node *self, struct context *ctx);
void eval_cmd_right(const struct ast_node *self, struct context *ctx);
void eval_cmd_left(const struct ast_node *self, struct context *ctx);
void eval_cmd_heading(const struct ast_node *self, struct context *ctx);
void eval_cmd_print(const struct ast_node *self, struct context *ctx);
void eval_cmd_color(const struct ast_node *self, struct context *ctx);
void eval_cmd_home(const struct ast_node *self, struct context *ctx);
void eval_cmd_repeat(const struct ast_node *self, struct context *ctx);
void eval_cmd_set(const struct ast_node *self, struct context *ctx);
void eval_cmd_proc(const struct ast_node *self, struct context *ctx);
void eval_cmd_call(const struct ast_node *self, struct context *ctx);
void eval_cmd_block(const struct ast_node *self, struct context *ctx);
double eval_func_sin(const struct ast_node *self, struct context *ctx);
double eval_func_cos(const struct ast_node *self, struct context *ctx);
double eval_func_tan(const struct ast_node *self, struct context *ctx);
double eval_func_random(const struct ast_node *self, struct context *ctx);
double eval_func_sqrt(const struct ast_node *self, struct context *ctx);
double eval_binary_operand(const struct ast_node *self, struct context *ctx);
double eval_unary_operand(const struct ast_node *self, struct context *ctx);

//useful function
double degre_to_radian(double angle);

#endif /* TURTLE_AST_H */
