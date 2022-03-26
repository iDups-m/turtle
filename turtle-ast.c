#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define PI 3.141592653589793
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

/* Useful functions */

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
 * function to convert degree to radian angle
 * @param angle the angle to convert
 * @return the value of the angle in radian
 */
double degree_to_radian(double angle) {
    return angle * (PI/180);
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
    //node->u.value = expr1->u.value;
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
struct ast_node *make_cmd_set(char *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SET;
    node->u.name = expr1;
    node->children_count = 1;
    node->children[0] = expr2;
    return node;
}
/**
 * constructor for the proc command
 * @param expr1 the name
 * @param expr2 the command
 * @return the node created
 */
struct ast_node *make_cmd_proc(char *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_PROC;
    node->u.name = expr1;
    node->children_count = 1;
    node->children[0] = expr2;
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
 * constructor for the expression block
 * @param expr the block
 * @return the node result created
 */
struct ast_node *make_expr_block(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_BLOCK;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

/**
 * recursive function to destroy the tree and all these nodes
 */

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

    if(self->kind == KIND_EXPR_NAME) {
        free(self->u.name);
    }

    if(self->next) {
        ast_node_destroy(self->next);
    }
    for(int i=0; i<self->children_count; ++i) {
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
    self->stopProgram = false;

    self->x = 0.0;
    self->y = 0.0;
    self->angle = 0.0;
    self->up = false;
    self->color.r = 0.0;
    self->color.g = 0.0;
    self->color.b = 0.0;

    self->handlerForProc = calloc(1, sizeof(struct proc_handling));
    self->handlerForProc->first = NULL;

    self->handlerForVar = calloc(1, sizeof(struct var_handling));
    self->handlerForVar->first = NULL;

    //create the different default variable
    add_default_var("PI", PI, self);
    add_default_var("SQRT2", SQRT2, self);
    add_default_var("SQRT3", SQRT3, self);
}

/**
 * function to handle the creation of the different default variable
 * of the turtle program : PI, SQRT2 and SQRT3
 * @param name is the name of the variable
 * @param value is the value to affect to the variable
 * @param ctx is the current context to modify
 */
void add_default_var(char *name, double value, struct context *ctx) {
    struct var_handling_node *node = calloc(1, sizeof(struct var_handling_node));
    if(node == NULL) {
        fprintf(stderr, "Error : allocation\n");
        return;
    }
    node->name = str_dup(name);
    node->value = value;

    if(ctx->handlerForVar->first == NULL) {
        ctx->handlerForVar->first = node;
        node->next = NULL;
        return;
    }
    node->next = ctx->handlerForVar->first;
    ctx->handlerForVar->first = node;
}

/**
 * function to add a procedure to the linked list of procedures
 * in the context
 * @param ctx the current context
 * @param name the name of the procedure
 * @param astNode the node of the procedure with the different commands
 */
void handler_proc_push(struct context *ctx, const struct ast_node *self, struct ast_node *astNode) {
    assert(self);
    assert(astNode);
    assert(ctx->handlerForProc);

    //handle the situation where the procedure name is already used
    struct proc_handling_node *currProc = ctx->handlerForProc->first;
    while(currProc) {
        if (strcmp(currProc->name, self->u.name) == 0) {
            fprintf(stderr, "Error : procedure %s is already created\n", self->u.name);
            ctx->stopProgram = true;
            return;
        }
        currProc = currProc->next;
    }

    printf("here with %s\n", self->u.name);

    struct proc_handling_node *node = calloc(1, sizeof(struct proc_handling_node));
    if(node == NULL) {
        fprintf(stderr, "Error : allocation\n");
        ctx->stopProgram = true;
        return;
    }
    node->name = self->u.name;
    node->astNode = astNode;

    if(ctx->handlerForProc->first == NULL) {
        ctx->handlerForProc->first = node;
        node->next = NULL;
        return;
    }
    node->next = ctx->handlerForProc->first;
    ctx->handlerForProc->first = node;
}

/**
 * function to add a variable to the linked list of variables
 * @param ctx the current context
 * @param name the name of the variable
 * @param value the value of the variable
 */
void handler_var_push(struct context *ctx, const struct ast_node *self, double value) {
    assert(ctx->handlerForVar);
    assert(self);

    struct var_handling_node *node = calloc(1, sizeof(struct var_handling_node));
    if(node == NULL) {
        fprintf(stderr, "Error : allocation\n");
        return;
    }
    node->name = self->u.name;
    node->value = value;

    if(ctx->handlerForVar->first == NULL) {
        ctx->handlerForVar->first = node;
        node->next = NULL;
        return;
    }
    node->next = ctx->handlerForVar->first;
    ctx->handlerForVar->first = node;
}

/**
 * function to destroy both linked list of the context
 * @param ctx the current context
 */
void ctx_handler_destroy(struct context *ctx) {
    assert(ctx->handlerForProc);
    struct proc_handling_node *currProc = ctx->handlerForProc->first;
    struct var_handling_node *currVar = ctx->handlerForVar->first;

    while(currProc) {
        struct proc_handling_node *tmp = currProc;
        currProc = currProc->next;
        free(tmp->name);
        free(tmp);
        tmp = NULL;
    }
    ctx->handlerForProc->first = NULL;
    free(ctx->handlerForProc);

    while(currVar) {
        struct var_handling_node *tmp = currVar;
        currVar = currVar->next;
        free(tmp->name);
        free(tmp);
        tmp = NULL;
    }
    ctx->handlerForVar->first = NULL;
    free(ctx->handlerForVar);
}


/**
 * we have multiple function for all the eval for the
 * different commands, functions, values and names
 * So, we display LineTo, MoveTo or color and calculate
 * the different values in the functions
 */


/**
 * evaluate a turtle tree
 * @param self the tree to evaluate
 * @param ctx the context to evaluate
 */
void ast_eval(const struct ast *self, struct context *ctx) {
    if (!self) {
        return;
    }

    ast_node_eval(self->unit, ctx);
}

/**
 * evaluate a node of the turtle tree
 * @param self the node to evaluate
 * @param ctx the context to evaluate
 * @return the value if it's a value expression, otherwise return 0.0
 * as the default value
 */
double ast_node_eval(const struct ast_node *self, struct context *ctx) {
    if (!self) {
        return -1;
    }
    if(ctx->stopProgram){
        printf("stop!\n");
        return -1;
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
                    return eval_func_cos(self, ctx);
                case FUNC_RANDOM:
                    return eval_func_random(self, ctx);
                case FUNC_SIN:
                    return eval_func_sin(self, ctx);
                case FUNC_SQRT:
                    return eval_func_sqrt(self, ctx);
                case FUNC_TAN:
                    return eval_func_tan(self, ctx);
            }
            break;
        case KIND_EXPR_VALUE:
            return self->u.value;
        case KIND_EXPR_UNOP:
            return eval_unary_operand(self, ctx);
        case KIND_EXPR_BINOP:
            return eval_binary_operand(self, ctx);
        case KIND_EXPR_BLOCK:
            return eval_expr_block(self, ctx);
            break;
        case KIND_EXPR_NAME:
            return eval_set_value(self, ctx);
            break;
    }

    if (self->next) {
        return ast_node_eval(self->next, ctx);
    }

    return 0.0;
}

/**
 * all the different eval function for the turtle program
 * display for the turtle program only : LineTo, MoveTo and color
 */

void eval_cmd_forward(const struct ast_node *self, struct context *ctx) {
    double angle_radian = degree_to_radian(ctx->angle);
    double value = ast_node_eval(self->children[0], ctx);
    ctx->x -= sin(angle_radian) * value;
    ctx->y -= cos(angle_radian) * value;

    if (ctx->up) {
        fprintf(stdout, "MoveTo %f %f", ctx->x, ctx->y);
    } else {
        fprintf(stdout, "LineTo %f %f", ctx->x, ctx->y);
    }

    fprintf(stdout, "\n");
}
void eval_cmd_backward(const struct ast_node *self, struct context *ctx) {
    double angle_radian = degree_to_radian(ctx->angle);
    double value = ast_node_eval(self->children[0], ctx);
    ctx->x += sin(angle_radian) * value;
    ctx->y += cos(angle_radian) * value;

    if (ctx->up) {
        fprintf(stdout, "MoveTo %f %f", ctx->x, ctx->y);
    } else {
        fprintf(stdout, "LineTo %f %f", ctx->x, ctx->y);
    }

    fprintf(stdout, "\n");
}
void eval_cmd_position(const struct ast_node *self, struct context *ctx) {
    ctx->x = ast_node_eval(self->children[0], ctx);
    ctx->y = ast_node_eval(self->children[1], ctx);

    fprintf(stdout, "MoveTo %f %1.f\n", ctx->x, ctx->y);
}
void eval_cmd_right(const struct ast_node *self, struct context *ctx) {
    ctx->angle -= ast_node_eval(self->children[0], ctx);
    if (ctx->angle > 360) {
        ctx->angle -= 360;
    }

    if (ctx->angle < 0) {
        ctx->angle += 360;
    }
}
void eval_cmd_left(const struct ast_node *self, struct context *ctx) {
    ctx->angle += ast_node_eval(self->children[0], ctx);
    if (ctx->angle > 360) {
        ctx->angle -= 360;
    }

    if (ctx->angle < 0) {
        ctx->angle += 360;
    }
}
void eval_cmd_heading(const struct ast_node *self, struct context *ctx) {
    ctx->angle = 0;
}
void eval_cmd_print(const struct ast_node *self, struct context *ctx) {
    fprintf(stderr, "%f\n", self->u.value);
}
void eval_cmd_color(const struct ast_node *self, struct context *ctx) {
    ctx->color.r = ast_node_eval(self->children[0], ctx);
    ctx->color.g = ast_node_eval(self->children[1], ctx);
    ctx->color.b = ast_node_eval(self->children[2], ctx);

    if(ctx->color.r < 0 || ctx->color.r > 1 || ctx->color.g < 0 || ctx->color.g > 1 || ctx->color.b < 0 || ctx->color.b > 1){
        //not in interval [0 - 1]
        fprintf(stderr, "Error : color values must be in [0 - 1] interval\n");
        ctx->stopProgram = true;
    }
}
void eval_cmd_home(const struct ast_node *self, struct context *ctx) {
    ctx->x = 0.0;
    ctx->y = 0.0;
    ctx->angle = 0.0;
    ctx->up = false;
    ctx->color.r = 0.0;
    ctx->color.g = 0.0;
    ctx->color.b = 0.0;
}
void eval_cmd_repeat(const struct ast_node *self, struct context *ctx) {
    double iter = floor(ast_node_eval(self->children[0], ctx));
    for(int i = 0; i < iter; ++i) {
        ast_node_eval(self->children[1], ctx);
    }
}
void eval_cmd_set(const struct ast_node *self, struct context *ctx) {
    double value = ast_node_eval(self->children[0], ctx);
    handler_var_push(ctx, self, value);
}
void eval_cmd_proc(const struct ast_node *self, struct context *ctx) {
    handler_proc_push(ctx, self, self->children[0]);
    printf("stopProgramm=%i\n", ctx->stopProgram);
}
void eval_cmd_call(const struct ast_node *self, struct context *ctx) {
    char* name = self->children[0]->u.name;

    struct proc_handling_node *curr = ctx->handlerForProc->first;

    while(curr) {
        if (strcmp(name, curr->name)==0) {
            ast_node_eval(curr->astNode, ctx);
            return;
        }
        curr = curr->next;
    }

    fprintf(stderr, "Error : no procedure with this name !\n");
}
void eval_cmd_block(const struct ast_node *self, struct context *ctx) {
    ast_node_eval(self->children[0], ctx);
}
double eval_func_sin(const struct ast_node *self, struct context *ctx) {
    double value = ast_node_eval(self->children[0], ctx);
    double res = sin(value);
    return res;
}
double eval_func_cos(const struct ast_node *self, struct context *ctx) {
    double value = ast_node_eval(self->children[0], ctx);
    double res = cos(value);
    return res;
}
double eval_func_tan(const struct ast_node *self, struct context *ctx) {
    double value = ast_node_eval(self->children[0], ctx);
    double res = tan(value);
    return res;
}
double eval_func_random(const struct ast_node *self, struct context *ctx) {
    double lower = ast_node_eval(self->children[0], ctx);
    double upper = ast_node_eval(self->children[1], ctx);

    if(upper < lower) {
        // invalid intervals
        fprintf(stderr, "Error : the lower limit must be lesser than the upper limit\n");
        ctx->stopProgram = true;
        return -1;
    }

    double f = (double) rand() / RAND_MAX;
    return lower + f * (upper - lower);
}
double eval_func_sqrt(const struct ast_node *self, struct context *ctx) {
    double value = ast_node_eval(self->children[0], ctx);

    if(value < 0) {
        // sqrt of a negative number
        fprintf(stderr, "Error : the value to put in the square root in negative\n");
        ctx->stopProgram = true;
        return -1;
    }

    double res = sqrt(value);
    return res;
}
double eval_binary_operand(const struct ast_node *self, struct context *ctx) {
    double value = 0.0;
    switch (self->u.op) {
        case '+':
            value = ast_node_eval(self->children[0],ctx) + ast_node_eval(self->children[1],ctx);
            break;
        case '-':
            value = ast_node_eval(self->children[0],ctx) - ast_node_eval(self->children[1],ctx);
            break;
        case '*':
            value = ast_node_eval(self->children[0],ctx) * ast_node_eval(self->children[1],ctx);
            break;
        case '/':
            value = ast_node_eval(self->children[0],ctx) / ast_node_eval(self->children[1],ctx);
            break;
        case '^':
            if(ast_node_eval(self->children[1],ctx) >= 32) {
                // power of the current value is out of bounds
                fprintf(stderr, "Error : pow arguments too big\n");
                ctx->stopProgram = true;
                return -1;
            }
            value = pow(ast_node_eval(self->children[0],ctx), ast_node_eval(self->children[1],ctx));
            break;
    }

    return value;
}
double eval_unary_operand(const struct ast_node *self, struct context *ctx) {
    double value = 0;
    switch (self->u.op) {
        case '-':
            value = -ast_node_eval(self->children[0],ctx);
            break;
        case '+':
            value = ast_node_eval(self->children[0],ctx);
            break;
    }
    return value;
}
double eval_set_value(const struct ast_node *self, struct context *ctx) {
    struct var_handling_node *curr = ctx->handlerForVar->first;

    while(curr) {
        if (strcmp(self->u.name, curr->name)==0) {
            return curr->value;
        }
        curr = curr->next;
    }

    fprintf(stderr, "Error : no variables with this name !\n");
    return -1;
}
double eval_expr_block(const struct ast_node *self, struct context *ctx) {
    return ast_node_eval(self->children[0], ctx);
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
            print_expr_block(self);
            break;
        case KIND_EXPR_NAME:
            fprintf(stderr, "%s", self->u.name);
            break;
    }

    ast_node_print(self->next);
}


/**
 * we have multiple function for all the print for the
 * different commands, functions, values and names
 * So, we display the node and all of these children
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
    fprintf(stderr, "set %s ", self->u.name);

    ast_node_print(self->children[0]);

    fprintf(stderr, "\n");
}
void print_cmd_proc(const struct ast_node *self) {
    fprintf(stderr, "proc %s", self->u.name);

    fprintf(stderr, " {\n");

    ast_node_print(self->children[0]);

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
void print_expr_block(const struct ast_node *self) {
    fprintf(stderr, "(");

    ast_node_print(self->children[0]);

    fprintf(stderr, ")");
}