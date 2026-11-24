#ifndef SRC_SYSTEMS_H
#define SRC_SYSTEMS_H

#include "game.h"

void game_add_system(game_system sys);

void game_add_systems(int argc, ...);

game_system *get_sys(const char *sys_name);

void game_init(void);

void game_loop(void);

#endif /* SRC_SYSTEM_H */