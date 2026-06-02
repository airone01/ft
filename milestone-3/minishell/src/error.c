
#include "error.h"

/**
 * @brief Get numeric error code from error type
 *
 * @param err Error type
 * @return int Integer error code
 */
int error_code(t_error_type err) {
  t_error_info *info;
  t_error_info *error_table;
  int code;

  error_table = get_error_table();
  info = &error_table[err];
  code = info->code;
  free(error_table);
  return (code);
}

/**
 * @brief Get numeric error code and handle special command not found case
 *
 * @param proof Command name or other proof
 * @param module Module name
 * @param err Error type
 * @return int Error code
 */
int error(const char *proof, const char *module, t_error_type err) {
  t_error_info *error_table;
  t_error_info *info;
  int code;

  error_table = get_error_table();
  info = &error_table[err];
  error_print(proof, module, info->message);
  code = info->code;
  free(error_table);
  return (code);
}
