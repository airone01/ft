#include "game.h"

void game_init(int argc, char *argv[]) {
  gamed = (game){
      .systems = {0},
      .systems_count = 0,
      .win_height = WIN_H,
      .win_width = WIN_W,
      .argc = argc,
      .argv = argv,
  };
}