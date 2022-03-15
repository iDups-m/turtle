#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}
struct ast_node *make_expr_name(char* name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = name;
  return node;
}
struct ast_node *make_binary_operand(struct ast_node *expr1, char operand, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_BINOP;
    node->u.op = operand;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
struct ast_node *make_unary_operand(char operand, struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_UNOP;
    node->u.op = operand;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_left(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_up() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    return node;
}
struct ast_node *make_cmd_down() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    return node;
}
struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
struct ast_node *make_cmd_color(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 3;
    node->children[0] = expr1;
    node->children[1] = expr2;
    node->children[2] = expr3;
    return node;
}
struct ast_node *make_cmd_color_yy(double val1, double val2, double val3) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 3;
    node->children[0] = make_expr_value(val1);
    node->children[1] = make_expr_value(val2);
    node->children[2] = make_expr_value(val3);
    return node;
}
struct ast_node *make_cmd_home() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    return node;
}
struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_REPEAT;
    node->u.value = expr1->u.value;
    return node;
}
struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SET;
    node->u.name = expr1->u.name;
    node->u.value = expr1->u.value;
    return node;
}
struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_PROC;
    node->u.name = expr1->u.name;
    //node->children_count = 1;
    //node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_call(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_CALL;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_func_sin(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_func_cos(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_func_tan(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_func_random(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_RANDOM;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}

struct ast_node *make_func_sqrt(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

void ast_destroy(struct ast *self) {
    ast_node_destroy(self->unit);
}

void ast_node_destroy(struct ast_node *self) {
    if(self->next){
        ast_node_destroy(self->next);
    }
    for(int i=0; i<self->children_count; ++i){
        ast_node_destroy(self->children[i]);
    }
    free(self);
}

/*
 * context
 */
void context_create(struct context *self) {

}

/*
 * eval
 */
void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */
void ast_print(const struct ast *self) {
    if (!self) {
        return;
    }

    ast_node_print(self->unit);
}

void ast_node_print(const struct ast_node *self) {
    if (!self) {
        return;
    }

    switch (self->kind) {
        case KIND_CMD_SIMPLE:
        case KIND_CMD_REPEAT:
            print_cmd_repeat(self);
            break;
        case KIND_CMD_BLOCK:
        case KIND_CMD_PROC:
            print_cmd_proc(self);
            break;
        case KIND_CMD_CALL:
            print_cmd_call(self);
            break;
        case KIND_CMD_SET:
            print_cmd_set(self);
            break;
        case KIND_EXPR_FUNC:
            switch (self->u.func) {
                case FUNC_COS:
                    print_func_cos(self);
                    break;
                case FUNC_RANDOM:
                    print_func_random(self);
                    break;
                case FUNC_SIN:
                    print_func_sin(self);
                    break;
                case FUNC_SQRT:
                    print_func_sqrt(self);
                    break;
                case FUNC_TAN:
                    print_func_tan(self);
                    break;
            }
        case KIND_EXPR_VALUE:
            fprintf(stderr, "%f", self->u.value);
            break;
        case KIND_EXPR_UNOP:
        case KIND_EXPR_BINOP:
            fprintf(stderr, "%c", self->u.op);
            break;
        case KIND_EXPR_BLOCK:
        case KIND_EXPR_NAME:
            fprintf(stderr, "%s", self->u.name);
            break;
    }

    fprintf(stderr, "\n");

    ast_node_print(self->next);
}

void print_cmd_forward(const struct ast_node *self) {
    for(int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }
}
void print_cmd_backward(const struct ast_node *self) {

}
void print_cmd_position(const struct ast_node *self) {

}
void print_cmd_right(const struct ast_node *self) {

}
void print_cmd_left(const struct ast_node *self) {

}
void print_cmd_heading(const struct ast_node *self) {

}
void print_cmd_up(const struct ast_node *self) {

}
void print_cmd_down(const struct ast_node *self) {

}
void print_cmd_print(const struct ast_node *self) {

}
void print_cmd_color(const struct ast_node *self) {

}
void print_cmd_color_yy(const struct ast_node *self) {

}
void print_cmd_home(const struct ast_node *self) {

}
void print_cmd_repeat(const struct ast_node *self) {

}
void print_cmd_set(const struct ast_node *self) {

}
void print_cmd_proc(const struct ast_node *self) {

}
void print_cmd_call(const struct ast_node *self) {

}
void print_func_sin(const struct ast_node *self) {

}
void print_func_cos(const struct ast_node *self) {

}
void print_func_tan(const struct ast_node *self) {

}
void print_func_random(const struct ast_node *self) {

}
void print_func_sqrt(const struct ast_node *self) {

}