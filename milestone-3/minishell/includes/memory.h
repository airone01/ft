
#ifndef MEMORY_H
#define MEMORY_H

#include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// memory.c
char *safe_strdup(t_ctx *ctx, const char *str, const char *module);
char *safe_strjoin(t_ctx *ctx, const char *s1, const char *s2,
                   const char *module);
void *safe_malloc(t_ctx *ctx, size_t size, const char *module);
void *safe_calloc(t_ctx *ctx, size_t nmemb, size_t size, const char *module);

// cleanup_utils.c
void safe_free_str(char **str);

#endif
