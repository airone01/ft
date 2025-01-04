<img src="https://skillicons.dev/icons?i=c,cpp,rust" align="right" />

# `airone01/ft`

Collection of all my repos related to 42. Mostly for personal archiving.

![Repobeats analytics image](https://repobeats.axiom.co/api/embed/698d4445b8026dcf271a98d57f9360c137016740.svg "Repobeats analytics image")

## GPM

> [!WARNING]
> GPM was never meant to be used by anyone other than me. It is a personal tool that I use to manage my projects in this monorepo. It is not meant to be a general-purpose tool. It could break your stuff, consider yourself warned.

Git Project Manager (GPM) is a bash script that helps me manage my 42 projects in this monorepo. It provides two main functions:

-   `gpm.sh add <repo-url> <project-name>`: Adds a project from a separate repository to this central repo while preserving its commit history in the commit message (to a certain extent)
-   `gpm.sh submit <project-name> <target-repo-url>`: Submits a project from this repo and force pushes it to a target repository (usually the 42 intra)

## Direnv

This project's dev dependencies are managed using `nix-direnv`. If you don't know what NixOS is, you probably don't have to care about that though.
