<div align="center">
    <h1>ft</h1>
</div>

<div align="center">
  <p>
    <a href="https://github.com/airone01/ft/pulse"><img alt="Last commit" src="https://img.shields.io/github/last-commit/airone01/ft?style=flat-square&logo=starship&color=8bd5ca&logoColor=D9E0EE&labelColor=302D41"/></a>
    <a href="https://github.com/airone01/ft/blob/main/LICENSE"><img alt="License" src="https://img.shields.io/github/license/airone01/ft?style=flat-square&logo=unlicense&color=ee999f&logoColor=D9E0EE&labelColor=302D41" /></a>
    <a href="https://github.com/airone01/ft/stargazers"><img alt="Stars" src="https://img.shields.io/github/stars/airone01/ft?style=flat-square&logo=githubsponsors&color=c69ff5&logoColor=D9E0EE&labelColor=302D41" /></a>
    <a href="https://github.com/airone01/ft/issues"><img alt="Issues" src="https://img.shields.io/github/issues/airone01/ft?style=flat-square&logo=bilibili&color=F5E0DC&logoColor=D9E0EE&labelColor=302D41" /></a>
    <a href="https://github.com/airone01/ft"><img alt="Repo Size" src="https://img.shields.io/github/repo-size/airone01/ft?color=%23DDB6F2&label=SIZE&logo=codesandbox&style=flat-square&logoColor=D9E0EE&labelColor=302D41" /></a><br />
    <a href="https://github.com/airone01/ft/actions/workflows/make.yml"><img alt="Bazel workflow status" src="https://img.shields.io/github/actions/workflow/status/airone01/ft/bazel.yml?style=flat-square&logo=bazel&logoColor=D9E0EE&labelColor=302D41" /></a>
    <a href="https://github.com/airone01/ft/actions/workflows/norminette.yml"><img alt="Norminette workflow status" src="https://img.shields.io/github/actions/workflow/status/airone01/ft/norminette.yml?style=flat-square&logo=42&logoColor=D9E0EE&labelColor=302D41&label=norm" /></a>
  </p>
</div>

<div align="center">
  <code>ft</code> is a monorepo of all my projects related to <a href="https://42.fr/en/homepage/">42</a>. It's mainly meant for personal archiving, but I also share some cool stuff.
</div>

---

<div align="center"><p>

[Foreword]: #foreword
[Projects]: #projects
[Extra tools/projects]: #extra-toolsprojects
[Additional notes]: #additional-notes

**[<kbd><br/> Foreword <br/>​</kbd>][Foreword]**
**[<kbd><br/> Projects <br/>​</kbd>][Projects]**
**[<kbd><br/> Extra tools/projects <br/>​</kbd>][Extra tools/projects]**
**[<kbd><br/> Additional notes <br/>​</kbd>][Additional notes]**

</p></div>

---

## Foreword

This is a [monorepo](https://en.wikipedia.org/wiki/Monorepo), meaning these
projects are tightly coupled and share dependencies to work properly.

**Why Bazel instead of Make?** The 42 curriculum relies heavily on GNU Make to
teach students the fundamentals of compilation. However, maintaining 30+ nearly
identical Makefiles in a monorepo quickly becomes tedious. Because I enjoy
DevOps and reproducibility, I migrated this repository to Bazel. I now only
generate a standard Makefile and clean the repo right before pushing a project
for grading.

> [!CAUTION]
> A natural side effect of this Bazel setup is that it makes it harder to
> blindly copy-paste my projects and submit them as your own. While deterring
> cheating wasn't my primary technical goal, I fully support the result. Copying
> defeats the core principles of 42 and goes against what I personally believe
> in. This repository is meant to serve as an example of what you can build at
> this school, not as a shortcut. It's called a school for a reason. _Learn;
> Write your own tests; and "By Odin! By Thor! Use your brain!"._

## Projects

<details>
  <summary>Projects statuses</summary>
  <table border="1" align="center">
    <thead>
      <tr>
        <th><strong>Milestone</strong></th>
        <th><strong>Project</strong></th>
        <th><strong>Finished</strong></th>
        <th><strong>Grade</strong></th>
      </tr>
    </thead>
    <tbody>
      <tr align="center">
        <td>0</td>
        <td><a href="/milestone-0/libft/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/libftm.png" alt="libft logo"></a></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td rowspan="3">1</td>
        <td><a href="/milestone-1/born2beroot/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/born2berootm.png" alt="born2beroot logo"></a></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><a href="/milestone-1/ft_printf/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/ft_printfe.png" alt="ft_printf logo"></a></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td><a href="/milestone-1/get_next_line/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/get_next_linee.png" alt="get_next_line logo"></a></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan="3">2</td>
        <td><a href="/milestone-2/pipex/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/pipexm.png" alt="pipex logo"></a></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><a href="/milestone-2/push_swap/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/push_swape.png" alt="push_swap logo"></a></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td><a href="/milestone-2/fdf/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/fdfm.png" alt="fdf logo"></a></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td rowspan=2>3</td>
        <td>
            <a href="/milestone-3/minishell/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/minishelle.png" alt="minishell logo"></a><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a></sub>
        </td>
        <td>✅</td>
        <td>101</td>
      </tr>
      <tr align="center">
        <td><a href="/milestone-3/philosophers/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/philosopherse.png" alt="philosophers logo"></a></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan=3>4</td>
        <td>
            <a href="/milestone-4/cub3d/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/cub3dm.png" alt="cub3d logo"></a><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a></sub>
        </td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td>
            <a href="/milestone-4/cpp00/"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/cppe.png" alt="CPP logo"></a><br/>
            <sub>CPP 00-04</sub>
        </td>
        <td>✅</td>
        <td><sub>(various grades)</sub></td>
      </tr>
      <tr align="center">
        <td>
            <img src="https://github.com/ayogun/42-project-badges/raw/main/badges/netpracticee.png" alt="NetPractice logo"><br/>
        </td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan="3">5</td>
        <td>
            <a href="/milestone-5/ft_irc/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/ft_irce.png" alt="ft_irc logo"></a><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a> & <a href="https://github.com/Sunny-444">@nahamida</a></sub>
        </td>
        <td>✅</td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td>
            <a href="/milestone-5/inception/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/inceptione.png" alt="inception logo"><br/>
        </td>
        <td>✅</td>
        <td>90</td>
      </tr>
      <tr align="center">
        <td>
            <a href="/milestone-5/cpp05/"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/cppe.png" alt="CPP logo"></a><br/>
            <sub>CPP 05-09</sub>
        </td>
        <td>✅
        </td>
        <td><sub>(various grades)</sub></td>
      </tr>
      <tr align="center">
        <td rowspan="1">6</td>
        <td>
            <a href="/milestone-6/ft_transcendence/README.md"><img src="https://github.com/ayogun/42-project-badges/raw/main/badges/ft_transcendencem.png" alt="ft_transcendence logo"></a><br/>
            <sub>with <a href="https://github.com/v-blanc">@vblanc</a>, <a href="https://github.com/EnzoPasselegue1">@enpassel</a> & <a href="https://github.com/SimonCottenet">@scottene</a></sub>
        </td>
        <td>✅</td>
        <td>125</td>
      </tr>
    </tbody>
  </table>
</details>

### Notable projects

| [fdf](/milestone-2/fdf/README.md)<br /><img src="/.github/assets/banners/fdf.avif" width=400 height=300 /> | [cub3d](/milestone-4/cub3d/README.md) (and its [3DS port](/milestone-4/cub3d/3DS_README.md))<br /><img src="/.github/assets/banners/cub3d.avif" width=400 height=300 /> |
| ---------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- |

## Extra tools/projects

### [`3DS port of cub3d`](/milestone-4/cub3d/3DS_README.md)

During a boring weekend, I set up a Bazel target to cross-compile a 3DS homebrew
app. If you have a modded 3DS on hand, you can compile it and try yourself. It's
very limited, laggy, and crashes on quit though. You have been warned.

### [`Minecraft push_swap visualizer`](./tools/push-swap-visualizer-minecraft/README.md)

A program to flex on your friends by visualizing your push_swap algorithm in
Minecraft. It uses [Valence](https://valence.rs/) to control the game packets
and visualize the sorting algorithm on your `1.20.1` client.

<details>
  <summary>In-game screenshot</summary>
  <img alt="Minecraft push_swap visualizer in-game screenshot" src="./.github/assets/screenshot_1.webp" />
</details>

### [`FDF generator`](./external-tools/fdf-bmp-converter/README.md)

A simple script to convert a BMP image into a fdf file. It currently only works
for bitmap images smaller than 255 \* 255, because I don't really know how to
reliably get the width of the image in the header.

You can convert PNG images to BMP using `convert` using
[ImageMagick](https://imagemagick.org/), or online with
[EzGIF](https://ezgif.com/png-to-bmp).

## Additional notes

### Bazel

> [!NOTE]
> Did you read the foreword?

You can build all of the projects in this monorepo using
[Bazel](https://bazel.build/).

- Run `bazel query ...` to list all projects.
- Run `bazel build //milestone-2/fdf:fdf` to make `fdf` (or `bazel build fdf`,
  [there are aliases](./BUILD.bazel)).
- Most importantly, run `bazel build //...` to make all projects at once (as
  well as the required external libs).

As per Bazel fashion, building the entirety of the repo at once is pretty fast.

### LSPs and `compile_commands.json`

If you use an IDE or LSP server and the constant `clangd` type errors appearing
when browsing this repo hurt your eyes, I might have a solution for you. The
`compile_commands.json` file! It instructs your LSP server on where to locate
the headers, and in which order, and how your compiling system (Bazel in this
case) manages your compilation.

To compile this file for the whole project using Bazel:

```sh
bazel run //:refresh_compile_commands
```

> [!NOTE]
> The `compile_commands.json` is gitignore'd for your inconvenience :-)

### nix-direnv

This project's dev dependencies are managed using
[`nix-direnv`](https://github.com/nix-community/nix-direnv). There is a central
[`flake.nix`](./flake.nix) file whose main purpose is exposing `devShell`s.

I might eventually package the projects of this repo into this flake when I find
the time.

## License

This project is licensed under the [MIT License](/LICENSE). See the
[LICENSE](/LICENSE) file for details.
