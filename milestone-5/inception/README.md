*This project has been created as part of the 42 curriculum by elagouch.*

## Description

*Inception* is an introductory project for Docker and Docker Compose.
This implementation is centered around simplicity and availability of the build, thanks to static alpine versions.
Below are the responses to the dumb questions asked by the subject:

### Difference between Docker (containers) and VMs

Firstly, emulation softwares use a variety of complex computing techniques destined to mimick a computer CPU, RAM, screen, storage, etc.
This effectively "emulates" (hence the name) how real motherboard circuits would run code, albeit simplifying some parts for speed's sake.
Emulators can then feed runnable data to the emulated CPU to have it interpret the byte code, and represent its result through the emulator's screen, cli, etc. The best emulators can run general-purpose operating systems like the Linux kernel or Windows.
A Virtual Machine (VM), is loosely described as an instance of such an emulator (the different technical concepts and implementations vary depending on the emulation sofware/suite). Its data and everything that composes it are fundamentaly separated from the hosts it runs in (depends on the implementation).

Contenerization's role is that of a way to run a computer program on a system or system kernel while avoiding the program's access to the rest of the system as much as possible. Meaning, a program that cannot (or is limited of) mess with the rest of the system.
What people are usually talking about when they say Docker's contenerization is actually Linux kernel's namespaces, which allow running programs separated from each other to begin with. Docker is based on namespaces, and brings predictable-(ish) builds, community images, and easy configuration of bindmount volumes and network interfaces, as well as Docker Compose, which is an orchestration software.
This is particularly useful for server and enterprise running environments, where separation of programs' data is necessary to ensure security, but where enulation may be too heavy at a large scale.

Does it show that I'm sick of people confusing VMs and containers?

See the Wikipédia articles for [Linux namespaces](https://en.wikipedia.org/wiki/Linux_namespaces) and [emulation](https://en.wikipedia.org/wiki/Emulator).

### Secrets and environment variables

Both are techniques used to pass runtime information to an application.
If, say, a web server must present users with a password prompt, it needs to know what the password is before it can check users' against.
The app has multiple solutions to be passed sensitive information like that. There are env variables, which are flags set in the login shell used to launch the server program (like bash), but those are shared accross programs, so an attacker could extract them easily.
There are also secret files, in which we write the secret, and then pass the file path for the program to read them itself. Those are more secure because a secret file can be set to provide read permissions exclusively to the user running the server, assuring that other users on the system cannot read it. "Env files" (.env, .env.local) are types of secret files.

### Docker Network vs Host Network

As explained sooner, Docker provides advanced networking configuration with simple defaults for containers.
This allows users to quickly forward a port (`ports: ["80:80"]`), or set up more complex networks. See the docs.
Also, in order to achieve this flexibility, Docker passes traffic through a custom network card (usually `docker0`), which is one of the many reasons Doker needs a background service to be able to run (and advanced perms).

The host network is the host computer's implementation of networking. You cannot really compare them so I don't really understand the point of this question because Linux networking is very maleable. Usually this would be a simple enp0s card loaded with the correct kernel module, on which softwares would connect to access the network.

They really are the same thing really, it's just that Docker makes a its own with easy config so users have it easy, but you can reproduce all of "Docker Network's" behaviour with enough patience.

### Docker Volumes vs Bind Mounts

Docker volumes are controlled by Docker and allow for more configuration and easy configuration, whereas bind mounts are handled by the host system.
Bind mounts require much configuration to be used sometimes, and sometimes they need more sofware to configure them than juat the system tools. Docker mounts sometimes use bind mounts.
In short, bind mount were too annoying so Docker made their own system for simple and portative configuraion, much like they did for networking.

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

