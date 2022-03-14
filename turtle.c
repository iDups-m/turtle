#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

double constant(const char *name) {
    if (strcmp(name, "PI") == 0) {
        return 3.14159265358979323846;
    }
    if (strcmp(name, "SQRT2") == 0) {
        return 1.41421356237309504880;
    }
    if (strcmp(name, "SQRT3") == 0) {
        return 1.7320508075688772935;
    }

    fprintf(stderr, "Unknown constant: '%s'\n", name);
    return 0.0;
}

int main() {
  srand(time(NULL));

  struct ast root;
  int ret = yyparse(&root);

  if (ret != 0) {
    return ret;
  }

  yylex_destroy();

  assert(root.unit);

  struct context ctx;
  context_create(&ctx);

  //ast_eval(&root, &ctx);
  ast_print(&root);

  ast_destroy(&root);

  return ret;
}
