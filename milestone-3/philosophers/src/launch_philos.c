
#include "philo.h"

bool launch_philos(t_ctx *ctx) {
  int i;

  i = -1;
  while (++i < ctx->philos_count) {
    if (pthread_create(&ctx->philos[i].thread, NULL, routine,
                       &ctx->philos[i]) != 0)
      return (true);
    ctx->philos_launched++;
  }
  return (false);
}
