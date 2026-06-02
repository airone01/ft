
#include <unistd.h>

/**
 * Displays "Error\n" to the standard error output
 */
void std_error(void) { (void)!write(2, "Error\n", 6); }
