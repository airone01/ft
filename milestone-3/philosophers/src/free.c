
/*
** Finite resource cleaning
*/

#include "philo.h"
#include <stdio.h>
#include <stdlib.h> // free()

void destroy_fork_mutexes(t_ctx *ctx) {
  int i;

  i = 0;
  while (i < ctx->fork_mtx_created) {
    pthread_mutex_destroy(&ctx->forks[i].mtx);
    i++;
  }
}

static void destroy_all_mutexes(t_ctx *ctx) {
  if (ctx->fork_mtx_created > 0)
    destroy_fork_mutexes(ctx);
  if (ctx->print_mtx_created)
    pthread_mutex_destroy(&ctx->print_mtx);
  if (ctx->ctx_mtx_created)
    pthread_mutex_destroy(&ctx->ctx_mtx);
}

void free_ctx(t_ctx *ctx) {
  if (!ctx)
    return;
  destroy_all_mutexes(ctx);
  if (ctx->philos) {
    free(ctx->philos);
    ctx->philos = NULL;
  }
  if (ctx->forks) {
    free(ctx->forks);
    ctx->forks = NULL;
  }
  free(ctx);
}
