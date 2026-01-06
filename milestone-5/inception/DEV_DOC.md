# Developer Documentation

## Environment setup

- Prerequisites: Docker and Docker Compose must be installed.
- Secrets: Create the `srcs/secrets/` directory if it does not exist. Add the required password files (txt) inside.
- Domain: Add this to `/etc/hosts` on your host machine: `127.0.0.1 elagouch.42.fr`

## Build and launch

The project uses a Makefile to automate Docker Compose commands.
- Build & Run: `make up`
  This command creates the data directories (`~/data/mariadb`, ``~/data/wordpress``) and builds the images locally.

## Container management

- Enter a container: `docker exec -it <container_name> /bin/sh`
- View Logs: `make log`

## Data persistence

Data is stored on the host machine using Docker bind mounts to ensure persistence across restarts.

- Database data: `$HOME/data/mariadb/`
- Wordpress data: `$HOME/data/wordpress/`

To wipe all data and start fresh, run:
```sh
$ make down
$ sudo rm -rfv "$HOME/data/*/*"
```

