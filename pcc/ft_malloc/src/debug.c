#define _GNU_SOURCE /* extern char *program_invocation_name */

#include "malloc.h"
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *program_invocation_name;

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
  if (!v || !*v)
    return -1;
  int old_errno = errno; ///< Need to preserve errno and restore it
  errno = 0;             ///< But still need to reset errno for 'strtol'
  long l = strtol(v, NULL, 10);
  if (l < 0 || l >= INTMAX_MAX)
    return -1;
  errno = old_errno;
  return l;
}

/// \param[in/out] cfg Debug config
void _dbg_env_load(unsigned int cfg[NMDEBUG_FLAGS]) {
  const char *names[NMDEBUG_FLAGS] = /* */
      {"MALLOC_CHECK", "MALLOC_PERTURB"};

  for (t_debug_flag f = 0; f < NMDEBUG_FLAGS; f++) {
    int r = getenv_int(names[f]);
    if (r >= 0)
      cfg[f] = r;
  }
}

void _err(t_err error, void *ptr, const char *fname) {
  if (_alloc_conf.debug[M_CHECK_ACTION] & M_CA_EMSG) {
    char *msg = NULL;

    switch (error) {
    case NotFound:
      msg = "invalid memory address";
      break;
    case DoubleFree:
      msg = "double free or corruption";
      break;
    }

    fprintf(stderr, "*** ft_malloc detected *** %s: %s",
            program_invocation_name, msg);
    if (!(_alloc_conf.debug[M_CHECK_ACTION] & M_CA_SMPL))
      fprintf(stderr, " (in %s)", fname);
    fprintf(stderr, ": 0x%" PRIXPTR " ***\n", ptr);
  }

  if (_alloc_conf.debug[M_CHECK_ACTION] & M_CA_ABRT)
    abort();
}
