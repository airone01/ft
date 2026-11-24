#ifndef SRC_GAME_H
#define SRC_GAME_H

#ifndef MAX_GAME_SYSTEMS
#define MAX_GAME_SYSTEMS 100
#endif /* MAX_GAME_SYSTEMS */

#if !defined(WIN_H) && !defined(WIN_W)
#if defined(__3DS__)
#define WIN_H 240
#define WIN_W 400

#elif defined(__VALGRIND__)
#define WIN_H 480
#define WIN_W 640

#else
#define WIN_H 720
#define WIN_W 1280
#endif /* __3DS__ __VALGRIND__ */

#endif /* WIN_H WIN_W */

typedef struct sgame game; // forward declare for circular dep

typedef struct {
  const char *name;

  void *resources;
  void (*init)(game);
  void (*free)(game);

  // Using three functions for priority is naive and can break easily. The
  // cleanest would be compile-time resolution of dependencies.
  void (*loop_begin)(game);
  void (*loop_middle)(game);
  void (*loop_end)(game);
} game_system;

typedef struct sgame {
  int argc;
  char **argv;

  unsigned short win_height;
  unsigned short win_width;

  unsigned int systems_count;
  game_system systems[MAX_GAME_SYSTEMS];
} game;

extern game gamed;

#endif /* SRC_GAME_H */