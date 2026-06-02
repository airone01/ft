
#include "error.h"
#include "free.h"

/**
 * @brief Frees context, displays an error and quits with the corresponding
 * exit code
 *
 * @param ctx Context
 * @param proof (optional) Proof that the error occured
 * @param module (optional) Module where the error occured
 * @param err Error code
 */
void ctx_error_exit(t_ctx *ctx, const char *proof, const char *module,
                    t_error_type err) {
  if (ctx)
    ctx_clear(ctx);
  exit(error(proof, module, err));
}
