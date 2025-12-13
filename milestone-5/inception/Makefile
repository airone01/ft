up:
	@mkdir -p $(HOME)/data/mariadb
	@mkdir -p $(HOME)/data/wordpress
	cd srcs; docker compose up --remove-orphans --detach --build

down:
	cd srcs; docker compose down --remove-orphans --volumes

re: down up

log:
	cd srcs; docker compose logs --follow
