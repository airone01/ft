
#include "philo.h"

bool launch_monitor(t_ctx *ctx, pthread_t *big_brother) {
  if (pthread_create(big_brother, NULL, routine_monitor, ctx) != 0) {
    ctx->stop = true;
    return (true);
  }
  ctx->monitor_launched = true;
  return (false);
}
