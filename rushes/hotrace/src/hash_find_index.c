
#include "hotrace.h"

/**
 * @brief	Find the index of the key in the table.
 *
 * @param	key		Key to find.
 * @return	uint	Index of the key.
 */
int hash_find_index(char *key) {
  uint32_t hash;
  size_t len;

  if (!key)
    return (-1);
  len = ft_strlen(key);
  if (len == 0)
    return (-1);
  hash = fnv1a_hash(key, len);
  return (hash % TBL_SIZE);
}
