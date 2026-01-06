# User Documentation

## Overview

This stack runs a complete WordPress website infrastructure:
- NGINX: Secure web server (entry point).
- WordPress: Content management system.
- MariaDB: Database storing your site's data.

## Project management

Run these commands from the root of the repository:

- Start: `make up` (builds and starts the server)
- Stop: `make down` (stops containers and removes network)
- Restart: `make re` (rebuilds and restarts everything)
- See logs: `make log` (in real time)

## Accessing the Website

1. Ensure `elagouch.42.fr` points to `127.0.0.1` in your `/etc/hosts` file.
2. Open your browser:
   - Website: `https://elagouch.42.fr`
   - Admin Panel: `https://elagouch.42.fr/wp-admin`

**Note: You __will__ see a security warning because the TLS certificate is self-signed. You must accept the risk to proceed.**

## Credentials

Credentials are stored in local secret files.

* Location: `srcs/secrets/` directory.
* Files:
  * `db_password.txt`
  * `db_root_password.txt`
  * `wordpress_admin_password.txt`

## Status Check

To verify services are running correctly run `docker compose -f srcs/docker-compose.yml ps`.
You should see nginx, mariadb, and wordpress with a status of `Up`.

