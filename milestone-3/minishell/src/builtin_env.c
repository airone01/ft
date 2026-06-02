
#include "minishell.h"

/**
 * @brief Executes the env built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status (0 for success, non-zero for error)
 */
int builtin_env(t_ctx *ctx, t_command *cmd) {
  t_env *env;

  (void)cmd;
  env = ctx->env_list;
  while (env) {
    if (env->value)
      ft_printf("%s=%s\n", env->key, env->value);
    env = env->next;
  }
  return (0);
}
