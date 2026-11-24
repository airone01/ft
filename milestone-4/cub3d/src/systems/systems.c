#include "systems.h"
#include "game.h"
#include <stdarg.h>
#include <string.h>

// Eventually, there needs to be a dependency system between the systems. Also
// the current priority system is very naive.

void game_add_system(game_system sys) {
  gamed.systems[gamed.systems_count] = sys;
}

void game_add_systems(int argc, ...) {
  va_list args;
  va_start(args, argc);
  for (int i = 0; i < argc; i++)
    game_add_system(va_arg(args, game_system));
  va_end(args);
}

game_system *get_sys(const char *sys_name) {
  for (unsigned int i = 0; i < gamed.systems_count; i++)
    if (!strcmp(sys_name, gamed.systems[i].name))
      return &(gamed.systems[i]);
  return NULL;
}

void game_init(void) {
  for (unsigned int i = 0; i < gamed.systems_count; i++)
    if (gamed.systems[i].init)
      gamed.systems[i].init(gamed);
}

void game_loop(void) {
  for (;;) {
    // Loop begin
    for (unsigned int i = 0; i < gamed.systems_count; i++)
      if (gamed.systems[i].loop_begin)
        gamed.systems[i].loop_begin(gamed);
    // Loop middle
    for (unsigned int i = 0; i < gamed.systems_count; i++)
      if (gamed.systems[i].loop_middle)
        gamed.systems[i].loop_middle(gamed);
    // Loop end
    for (unsigned int i = 0; i < gamed.systems_count; i++)
      if (gamed.systems[i].loop_end)
        gamed.systems[i].loop_end(gamed);
  }
}