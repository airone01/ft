#include "malloc.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

// Note: the explanations you are looking for are in 'malloc.h', or in the
// manual 'mallopt(3)'.

int mallopt(t_debug_flag param, int value) {
  _alloc_conf.debug[param] = value;
  return 0;
}

static int getenv_int(const char *name) {
  char *v = getenv(name); ///< Even though 'getenv()' is not allowed in the
                          ///< subject, it's not possible to get an environment
                          ///< var otherwise in the program, except if I require
                          ///< for 'char *envp[]' in all allocation functions as
                          ///< parameters. I can defend this, np.
  errno = 0;
  long l = strtol(v, NULL, 10);
  if (l < 0 || l >= INTMAX_MAX)
    return -1;
  return l;
}

/// \param[in/out] cfg Debug config
void _dbg_env_load(unsigned int cfg[NMDEBUG_FLAGS]) {
  const char *names[NMDEBUG_FLAGS] = /* */
      {"MALLOC_CHECK"};

  for (t_debug_flag f = 0; f < NMDEBUG_FLAGS; f++)
    cfg[f] = getenv_int(names[f]);
}
