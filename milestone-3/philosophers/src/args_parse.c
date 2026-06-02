
/*
** The goal of this file is to parse the cli arguments.
*/

#include "philo.h"
#include "std.h"

void args_parse(t_ctx *ctx, int argc, char **argv) {
  ctx->philos_count = (long)ft_atoul(argv[1]);
  ctx->death_time = (long)ft_atoul(argv[2]);
  ctx->meal_time = (long)ft_atoul(argv[3]);
  ctx->sleep_time = (long)ft_atoul(argv[4]);
  if (argc == 6)
    ctx->max_meal_count = (long)ft_atoul(argv[5]);
  else
    ctx->max_meal_count = -1;
  ctx->epoch = get_time(TIMEE_US);
}
