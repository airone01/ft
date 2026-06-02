
#include "globals.h"

// int	g_signal_status = 0;

/*
Because of an obscure bug with `ld`, we need this file as well as the
associated header `globals.h`. Otherwise having functions defined not in the
same exact file can break minishell signals (???), which is obviously not
possible because of the norm.
*/
