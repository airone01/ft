<div align="center">
	<img src="https://github.com/ayogun/42-project-badges/raw/main/covers/cover-philosophers.png" />
</div>

## Build

```sh
make
```

## Allowed functions

> memset, printf, malloc, free, write,
> usleep, gettimeofday, pthread_create,
> pthread_detach, pthread_join, pthread_mutex_init,
> pthread_mutex_destroy, pthread_mutex_lock,
> pthread_mutex_unlock

## Rules

The specific rules for the mandatory part are:

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.
