
#include "fdf.h"

/**
 * @brief Toggle a specific debug mode flag
 *
 * @param ctx Context
 * @param flag The debug flag to toggle
 */
void toggle_debug_mode(t_ctx *ctx, int flag) {
  if (ctx->debug_mode & flag)
    ctx->debug_mode &= ~flag;
  else
    ctx->debug_mode |= flag;
  ctx->needs_render = true;
}
