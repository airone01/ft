
#ifndef SIGNALS_H
#define SIGNALS_H

#include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// signals.c
void setup_interactive_signals(void);
void setup_child_signals(void);
void setup_parent_signals(void);
void setup_heredoc_signals(void);

// signals_update.c
void update_signal_status(t_ctx *ctx);

#endif
