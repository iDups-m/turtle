#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

/**
 * intern function to duplicate a string
 * @param src the string to duplicate
 * @return the copy of the string
 */
char *str_dup(char *src) {
    char *str;
    char *p;
    int len = 0;

    while (src[len]) {
        len++;
    }

    str = malloc(len + 1);
    p = str;

    while (*src) {
        *p++ = *src++;
    }

    *p = '\0';
    return str;
}


/**
 * we have multiple constructor for all the
 * different commands, functions, values and names
 * So, we allocate a node with calloc of type struct ast_node
 * and we define the kind and the 'value' of the node
 * such as a value, a name an operand, a function or a command
 */


/**
 * constructor for a value
 * @param value the value to give to the node
 * @return the node created
 */
struct ast_node *make_expr_value(double value) {
   struct ast_node *node = calloc(1, sizeof(struct ast_node));
   node->kind = KIND_EXPR_VALUE;
   node->u.value = value;
   return node;
}
/**
 * constructor for a name
 * @param name the name to give to the node
 * @return the node created
 */
struct ast_node *make_expr_name(char* name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = name;
  return node;
}
/**
 * constructor for a binary operand
 * @param expr1 the left part of the operation
 * @param operand the operand
 * @param expr2 the right part of the operation
 * @return the node created
 */
struct ast_node *make_binary_operand(struct ast_node *expr1, char operand, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_BINOP;
    node->u.op = operand;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
/**
 * constructor for a unary operand
 * @param operand the operand
 * @param expr the right part of the operation
 * @return the node created
 */
struct ast_node *make_unary_operand(char operand, struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_UNOP;
    node->u.op = operand;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the command forward
 * @param expr the expr node
 * @return the node created
 */
struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the command backward
 * @param expr the expr node
 * @return the node created
 */
struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the command position
 * @param expr1 the x-axis value
 * @param expr2 the y-axis value
 * @return the node created
 */
struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
/**
 * constructor for the command right
 * @param expr the expr node
 * @return the node created
 */
struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the left command
 * @param expr the expr value
 * @return the node created
 */
struct ast_node *make_cmd_left(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the heading command
 * @param expr the expr value
 * @return the node created
 */
struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the up command
 * @return the node created
 */
struct ast_node *make_cmd_up() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    return node;
}
/**
 * constructor for the down command
 * @return the node created
 */
struct ast_node *make_cmd_down() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    return node;
}
/**
 * constructor for the print command
 * @param expr the expr to display
 * @return the node created
 */
struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the color with values command
 * @param expr1 the red value of the color
 * @param expr2 the green value of the color
 * @param expr3 the blue value of the color
 * @return the node created
 */
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
/**
 * constructor for the color with name command
 * @param val1 the red value fo the color
 * @param val2 the green value of the color
 * @param val3 the blue value of the color
 * @return the node created
 */
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
/**
 * constructor for the home command
 * @return the node created
 */
struct ast_node *make_cmd_home() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    return node;
}
/**
 * constructor for the repeat command
 * @param expr1 the value of the repeat
 * @param expr2 the command block to repeat
 * @return the node created
 */
struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_REPEAT;
    node->u.value = expr1->u.value;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
/**
 * constructor for the set command
 * @param expr1 the variable name to define
 * @param expr2 the value to affect to the variable
 * @return the node created
 */
struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SET;
    node->u.name = expr1->u.name;
    node->u.value = expr1->u.value;
    return node;
}
/**
 * constructor for the proc command
 * @param expr1 the name
 * @param expr2 the command
 * @return the node created
 */
struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_PROC;
    node->u.name = expr1->u.name;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
/**
 * constructor for the call command
 * @param expr the name of the procedure to call
 * @return the node created
 */
struct ast_node *make_cmd_call(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_CALL;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the block command
 * @param expr the block or commands
 * @return the node created
 */
struct ast_node *make_cmd_block(struct ast_node *expr){
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_BLOCK;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

/**
 * constructor for the sin function
 * @param expr the value to calculate
 * @return the node result created
 */
struct ast_node *make_func_sin(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the cos function
 * @param expr the value to calculate
 * @return the node result created
 */
struct ast_node *make_func_cos(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the tan function
 * @param expr the value to calculate
 * @return the node result created
 */
struct ast_node *make_func_tan(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}
/**
 * constructor for the random function
 * @param expr1 the lower limit
 * @param expr2 the upper limit
 * @return the node result created
 */
struct ast_node *make_func_random(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_RANDOM;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}
/**
 * constructor for the sqrt
 * @param expr the value to calculate
 * @return the node result created
 */
struct ast_node *make_func_sqrt(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

/**
 * free the allocated space for the tree and all his nodes
 * @param self the whole tree
 */
void ast_destroy(struct ast *self) {
    if (!self) {
        return;
    }

    ast_node_destroy(self->unit);
}

/**
 * recursive function to free the current node
 * @param self the current node to free
 */
void ast_node_destroy(struct ast_node *self) {
    if (!self) {
        return;
    }

    //TODO : free (str_dup)

    if(self->next){
        ast_node_destroy(self->next);
    }
    for(int i=0; i<self->children_count; ++i){
        ast_node_destroy(self->children[i]);
    }
    free(self);
}

/**
 * create the initial context
 * set initials values for attributes of the context
 * @param self the context of the execution
 */
void context_create(struct context *self) {
    self->x = 0.0;
    self->y = 0.0;
    self->angle = 0.0;
    self->up = false;
    self->color.r = 0.0;
    self->color.g = 0.0;
    self->color.b = 0.0;
}

/**
 * eval a turtle tree
 * @param self the three to eval
 * @param ctx the context
 */
void ast_eval(const struct ast *self, struct context *ctx) {
    if (!self) {
        return;
    }

    ast_node_eval(self->unit, ctx);
}

void ast_node_eval(const struct ast_node *self, struct context *ctx) {
    if (!self) {
        return;
    }

    switch (self->kind) {
        case KIND_CMD_SIMPLE:
            switch (self->u.cmd){
                case CMD_UP:
                    ctx->up = true;
                    break;
                case CMD_DOWN:
                    ctx->up = false;
                    break;
                case CMD_RIGHT:
                    eval_cmd_right(self, ctx);
                    break;
                case CMD_LEFT:
                    eval_cmd_left(self, ctx);
                    break;
                case CMD_HEADING:
                    eval_cmd_heading(self, ctx);
                    break;
                case CMD_FORWARD:
                    eval_cmd_forward(self, ctx);
                    break;
                case CMD_BACKWARD:
                    eval_cmd_backward(self, ctx);
                    break;
                case CMD_POSITION:
                    eval_cmd_position(self, ctx);
                    break;
                case CMD_HOME:
                    eval_cmd_home(self, ctx);
                    break;
                case CMD_COLOR:
                    eval_cmd_color(self, ctx);
                    break;
                case CMD_PRINT:
                    eval_cmd_print(self, ctx);
                    break;
            }
            break;
        case KIND_CMD_REPEAT:
            eval_cmd_repeat(self, ctx);
            break;
        case KIND_CMD_BLOCK:
            eval_cmd_block(self, ctx);
            break;
        case KIND_CMD_PROC:
            eval_cmd_proc(self, ctx);
            break;
        case KIND_CMD_CALL:
            eval_cmd_call(self, ctx);
            break;
        case KIND_CMD_SET:
            eval_cmd_set(self, ctx);
            break;
        case KIND_EXPR_FUNC:
            switch (self->u.func) {
                case FUNC_COS:
                    eval_func_cos(self, ctx);
                    break;
                case FUNC_RANDOM:
                    eval_func_random(self, ctx);
                    break;
                case FUNC_SIN:
                    eval_func_sin(self, ctx);
                    break;
                case FUNC_SQRT:
                    eval_func_sqrt(self, ctx);
                    break;
                case FUNC_TAN:
                    eval_func_tan(self, ctx);
                    break;
            }
            break;
        case KIND_EXPR_VALUE:
            //fprintf(stdout, "%.1f ", self->u.value);
            break;
        case KIND_EXPR_UNOP:
            eval_unary_operand(self, ctx);
            break;
        case KIND_EXPR_BINOP:
            eval_binary_operand(self, ctx);
            break;
        case KIND_EXPR_BLOCK:
            //TODO
        case KIND_EXPR_NAME:
            fprintf(stdout, "%s ", self->u.name);
            break;
    }

    ast_node_eval(self->next, ctx);
}

void eval_cmd_forward(const struct ast_node *self, struct context *ctx) {

    ctx->y -= self->children[0]->u.value;

    fprintf(stdout, "LineTo %1.f %1.f", ctx->x, ctx->y);

    fprintf(stdout, "\n");
}
void eval_cmd_backward(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_position(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_right(const struct ast_node *self, struct context *ctx) {
    ctx->angle += self->children[0]->u.value;

    if (ctx->angle > 360) {
        ctx->angle -= 360;
    }

    if (ctx->angle < 360) {
        ctx->angle += 360;
    }
}
void eval_cmd_left(const struct ast_node *self, struct context *ctx) {
    ctx->angle -= self->children[0]->u.value;

    if (ctx->angle > 360) {
        ctx->angle -= 360;
    }

    if (ctx->angle < 360) {
        ctx->angle += 360;
    }
}
void eval_cmd_heading(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_print(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_color(const struct ast_node *self, struct context *ctx) {
    ctx->color.r = self->children[0]->u.value;
    ctx->color.g = self->children[1]->u.value;
    ctx->color.b = self->children[2]->u.value;

    fprintf(stdout, "Color %1.f %1.f %1.f", ctx->color.r, ctx->color.g, ctx->color.b);

    fprintf(stdout, "\n");
}
void eval_cmd_home(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_repeat(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_set(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_proc(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_call(const struct ast_node *self, struct context *ctx) {

}
void eval_cmd_block(const struct ast_node *self, struct context *ctx) {

}
void eval_func_sin(const struct ast_node *self, struct context *ctx) {

}
void eval_func_cos(const struct ast_node *self, struct context *ctx) {

}
void eval_func_tan(const struct ast_node *self, struct context *ctx) {

}
void eval_func_random(const struct ast_node *self, struct context *ctx) {

}
void eval_func_sqrt(const struct ast_node *self, struct context *ctx) {

}
void eval_binary_operand(const struct ast_node *self, struct context *ctx) {

}
void eval_unary_operand(const struct ast_node *self, struct context *ctx) {

}

/**
 * print the commands and all his children
 * @param self the whole tree to display
 */
void ast_print(const struct ast *self) {
    if (!self) {
        return;
    }

    ast_node_print(self->unit);
}

/**
 * function for debug the turtle program
 * it depends on the kind of the node we want
 * to display
 * @param self the node to display
 */
void ast_node_print(const struct ast_node *self) {
    if (!self) {
        return;
    }

    switch (self->kind) {
        case KIND_CMD_SIMPLE:
            switch (self->u.cmd){
                case CMD_UP:
                    print_cmd_up(self);
                    break;
                case CMD_DOWN:
                    print_cmd_down(self);
                    break;
                case CMD_RIGHT:
                    print_cmd_right(self);
                    break;
                case CMD_LEFT:
                    print_cmd_left(self);
                    break;
                case CMD_HEADING:
                    print_cmd_heading(self);
                    break;
                case CMD_FORWARD:
                    print_cmd_forward(self);
                    break;
                case CMD_BACKWARD:
                    print_cmd_backward(self);
                    break;
                case CMD_POSITION:
                    print_cmd_position(self);
                    break;
                case CMD_HOME:
                    print_cmd_home(self);
                    break;
                case CMD_COLOR:
                    print_cmd_color(self);
                    break;
                case CMD_PRINT:
                    print_cmd_print(self);
                    break;
            }
            break;
        case KIND_CMD_REPEAT:
            print_cmd_repeat(self);
            break;
        case KIND_CMD_BLOCK:
            print_cmd_block(self);
            break;
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
            break;
        case KIND_EXPR_VALUE:
            fprintf(stderr, "%.1f", self->u.value);
            break;
        case KIND_EXPR_UNOP:
            print_unary_operand(self);
            break;
        case KIND_EXPR_BINOP:
            print_binary_operand(self);
            break;
        case KIND_EXPR_BLOCK:
        case KIND_EXPR_NAME:
            fprintf(stderr, "%s", self->u.name);
            break;
    }

    ast_node_print(self->next);
}


/**
 * we have multiple function for all the print for the
 * different commands, functions, values and names
 * So, we display the node and all of his children
 */


void print_cmd_forward(const struct ast_node *self) {
    fprintf(stderr, "fw ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
        if (i != self->children_count-1) {
            fprintf(stderr, ", ");
        }
    }

    fprintf(stderr, "\n");
}
void print_cmd_backward(const struct ast_node *self) {
    fprintf(stderr, "bw ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_position(const struct ast_node *self) {
    fprintf(stderr, "pos ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
        if (i != self->children_count-1) {
            fprintf(stderr, ", ");
        }
    }

    fprintf(stderr, "\n");
}
void print_cmd_right(const struct ast_node *self) {
    fprintf(stderr, "rt ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_left(const struct ast_node *self) {
    fprintf(stderr, "lt ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_heading(const struct ast_node *self) {
    fprintf(stderr, "hd ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_up(const struct ast_node *self) {
    fprintf(stderr, "up");
    fprintf(stderr, "\n");
}
void print_cmd_down(const struct ast_node *self) {
    fprintf(stderr, "down");
    fprintf(stderr, "\n");
}
void print_cmd_print(const struct ast_node *self) {
    fprintf(stderr, "print ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_color(const struct ast_node *self) {
    fprintf(stderr, "color ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
        if (i != self->children_count-1) {
            fprintf(stderr, ", ");
        }
    }

    fprintf(stderr, "\n");
}
void print_cmd_home(const struct ast_node *self) {
    fprintf(stderr, "home ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_repeat(const struct ast_node *self) {
    fprintf(stderr, "repeat ");

    ast_node_print(self->children[0]);

    fprintf(stderr, " {\n");

    ast_node_print(self->children[1]);

    fprintf(stderr, "}");

    fprintf(stderr, "\n");
}
void print_cmd_set(const struct ast_node *self) {
    fprintf(stderr, "set ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
        if (i != self->children_count-1) {
            fprintf(stderr, ", ");
        }
    }

    fprintf(stderr, "\n");
}
void print_cmd_proc(const struct ast_node *self) {
    fprintf(stderr, "proc ");

    ast_node_print(self->children[0]);

    fprintf(stderr, " {\n");

    ast_node_print(self->children[1]);

    fprintf(stderr, "}");

    fprintf(stderr, "\n");
}
void print_cmd_call(const struct ast_node *self) {
    fprintf(stderr, "call ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_cmd_block(const struct ast_node *self) {
    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }
}
void print_func_sin(const struct ast_node *self) {
    fprintf(stderr, "sin ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_func_cos(const struct ast_node *self) {
    fprintf(stderr, "cos ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_func_tan(const struct ast_node *self) {
    fprintf(stderr, "tan ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}
void print_func_random(const struct ast_node *self) {
    fprintf(stderr, "random ");

    fprintf(stderr, "(");
    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
        if (i < self->children_count-1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ")");

    fprintf(stderr, "\n");
}
void print_func_sqrt(const struct ast_node *self) {
    fprintf(stderr, "sqrt ");

    for (int i = 0; i < self->children_count; ++i) {
        ast_node_print(self->children[i]);
    }

    fprintf(stderr, "\n");
}

void print_binary_operand(const struct ast_node *self) {
    ast_node_print(self->children[0]);

    fprintf(stderr, " %c ", self->u.op);

    ast_node_print(self->children[1]);
}

void print_unary_operand(const struct ast_node *self) {
    fprintf(stderr, "%c", self->u.op);

    ast_node_print(self->children[0]);
}