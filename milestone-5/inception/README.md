*This project has been created as part of the 42 curriculum by elagouch.*

## Description

*Inception* is an introductory project for Docker and Docker Compose.

## Instructions

The goals are to build a Docker Compose setup and its custom images (base image allowed are `debian` or `alpine` or similar, but not i.e.  `mariadb`), as well as to connect them, in order to have a working production-like server setup.

The containers and images required are:
- `mariadb` (set up for wordpress, secured)
- `nginx` (set up for wordpress, secured)
- `wordpress` (configured to connect to nginx)
  - CGI acchieved in NGINX, not with i.e. `lighttpd`.

A `Makefile` must be provided, which allows running the correct `docker compose` commands.

## Resources

- EndeavourOS ISO (a mirror):
  - ISO: [https://mirror.rznet.fr/endeavouros/iso/EndeavourOS_Ganymede-2025.11.24.iso](https://mirror.rznet.fr/endeavouros/iso/EndeavourOS_Ganymede-2025.11.24.iso)
  - Sha512: [https://mirror.rznet.fr/endeavouros/iso/EndeavourOS_Ganymede-2025.11.24.iso.sha512sum](https://mirror.rznet.fr/endeavouros/iso/EndeavourOS_Ganymede-2025.11.24.iso.sha512sum)
- [https://hub.docker.com/_/alpine](https://hub.docker.com/_/alpine)
- [https://docs.docker.com/compose/](https://docs.docker.com/compose/)

## Usage

> [!NOTE]
> This project requires write rights to `/etc/hosts`, and permissions to bind to TCP port `443`, both of which usually require superuser.
> What this means is in order to correct the project in 42's cluster, you will need to run this through a VM.
> I am purposely not including indications on how the VM is set up. Ask me during correction, or look up the scripts I made for my `LFS` on [my GitHub](https://github.com/airone01/lfs).

