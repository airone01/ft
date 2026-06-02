
#include "fdf.h"

int key_hook_int(int keycode, t_ctx *ctx) {
  key_hook(keycode, ctx);
  return (0);
}

int ctx_clear_0_int(t_ctx *ctx) {
  ctx_clear_0(ctx);
  return (0);
}

/**
 * @brief	Attach mlx hooks to the window
 *
 * @param	ctx	Context
 */
void register_hooks(t_ctx *ctx) {
  mlx_loop_hook(ctx->mlx, render_next_frame, ctx);
  mlx_hook(ctx->win, 2, 1L << 0, key_hook_int, ctx);
  mlx_hook(ctx->win, 17, 0, ctx_clear_0_int, ctx);
}
