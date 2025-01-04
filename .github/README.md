<div align="center">
    <h1>ft</h1>
</div>

<div align="center">
  <p>
    <a href="https://github.com/airone01/ft/pulse"><img alt="Last commit" src="https://img.shields.io/github/last-commit/airone01/ft?style=for-the-badge&logo=starship&color=8bd5ca&logoColor=D9E0EE&labelColor=302D41"/></a> 
	<a href="https://github.com/airone01/ft/blob/main/LICENSE"><img alt="License" src="https://img.shields.io/github/license/airone01/ft?style=for-the-badge&logo=unlicense&color=ee999f&logoColor=D9E0EE&labelColor=302D41" /></a> 
    <a href="https://github.com/airone01/ft/stargazers"><img alt="Stars" src="https://img.shields.io/github/stars/airone01/ft?style=for-the-badge&logo=githubsponsors&color=c69ff5&logoColor=D9E0EE&labelColor=302D41" /></a> 
    <a href="https://github.com/airone01/ft/issues"><img alt="Issues" src="https://img.shields.io/github/issues/airone01/ft?style=for-the-badge&logo=bilibili&color=F5E0DC&logoColor=D9E0EE&labelColor=302D41" /></a> 
    <a href="https://github.com/airone01/ft"><img alt="Repo Size" src="https://img.shields.io/github/repo-size/airone01/ft?color=%23DDB6F2&label=SIZE&logo=codesandbox&style=for-the-badge&logoColor=D9E0EE&labelColor=302D41" /></a>
  </p>
</div>

<div align="center">
  <a>
    ft is a monorepo of all my projects related to 42. It's mainly meant for personal archiving, but I share some cool projects that you can check out. For example, the Minecraft push_swap visualizer.
  </a>
</div>

---

<div align="center"><p>

[Projects]: #projects
[Extra tools/projects]: #extra-toolsprojects
[Additional stuff/notes]: #additional-stuffnotes

**[<kbd> <br>Projects<br> </kbd>][Projects]**
**[<kbd> <br>Extra tools/projects<br> </kbd>][Extra tools/projects]**
**[<kbd> <br>Additional stuff/notes<br> </kbd>][Additional stuff/notes]**

</p></div>

---

## Projects

| **Milestone** |                                                                  **Project**                                                                  |     **Finished**      | **Grade** |
| :-----------: | :-------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------: | :-------: |
|       0       |             [![libft logo](https://github.com/ayogun/42-project-badges/raw/main/badges/libftm.png)](/milestone-0-libft/README.md)             | ✅ <br> (with bonuses) |    125    |
|       1       |    [![born2beroot logo](https://github.com/ayogun/42-project-badges/raw/main/badges/born2berootm.png)](/milestone-1-born2beroot/README.md)    | ✅ <br> (with bonuses) |    125    |
|       1       |       [![ft_printf logo](https://github.com/ayogun/42-project-badges/raw/main/badges/ft_printfe.png)](/milestone-1-ft_printf/README.md)       |           ✅           |    100    |
|       1       | [![get_next_line logo](https://github.com/ayogun/42-project-badges/raw/main/badges/get_next_linee.png)](/milestone-1-get_next_line/README.md) |           ✅           |    100    |
|       2       |       [![push_swap logo](https://github.com/ayogun/42-project-badges/raw/main/badges/push_swapn.png)](/milestone-1-push_swap/README.md)       |          ...          |           |

## Extra tools/projects

<img src="https://skillicons.dev/icons?i=rust" align="right" />

### [`Minecraft push_swap visualizer`](https://github.com/airone01/ft/tree/main/extra-push-swap-visualizer-minecraft)

A program to flex on your friends by visualizing your push_swap algorithm in Minecraft. It uses [Valence](https://valence.rs/) to control the game packets and visualize the sorting algorithm on your `1.20.1` client.

![In-game screenshot](/.github/assets/screenshot_1.webp)

<img src="https://skillicons.dev/icons?i=rust" align="right" />

### [`Arthur`](/extra-arthur/README.md)

Arthur is a test runner for 42 projects. It is a program that runs tests on your project and displays the results in a nice and readable format. Currently, it supports `libft`.

<img src="https://skillicons.dev/icons?i=bash" align="right" />

### [`GPM`](/gpm.sh)

> [!WARNING]
> GPM was never meant to be used by anyone other than me. It is a personal tool that I use to manage my projects in this monorepo. It is not meant to be a general-purpose tool. It could break your stuff, consider yourself warned.

Git Project Manager (GPM) is a bash script that helps me manage my 42 projects in this monorepo. It provides two main functions:

-   `gpm.sh add <repo-url> <project-name>`: Adds a project from a separate repository to this central repo while preserving its commit history in the commit message (to a certain extent)
-   `gpm.sh submit <project-name> <target-repo-url>`: Submits a project from this repo and force pushes it to a target repository (usually the 42 intra)

## Additional stuff/notes

### Direnv

This project's dev dependencies are managed using `nix-direnv`. If you don't know what NixOS is, you probably don't have to care about that though.

### Ford

`ford` was a quick and dirty test runner I made for my projects during the pool. I's now deprecated in favor of [arthur](/extra-arthur/README.md).
