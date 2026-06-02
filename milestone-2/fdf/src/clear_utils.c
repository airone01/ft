
#include "fdf.h"

/**
 * @brief Clears the context and exits normally
 *
 * @param ctx Context
 */
void ctx_clear_0(t_ctx *ctx) {
  ctx_clear(ctx);
  exit(EXIT_SUCCESS);
}
