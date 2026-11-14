<div align="center">
    <h1>ft</h1>
</div>

<div align="center">
  <p>
    <a href="https://github.com/airone01/ft/pulse"><img
        alt="When was the last commit"
        src="https://img.shields.io/github/last-commit/airone01/ft?style=flat-square&logo=git&color=8bd5ca&logoColor=D9E0EE&labelColor=302D41"
      /></a>
    <a href="https://github.com/airone01/ft/blob/main/LICENSE"><img
        alt="This repo is licensed under MIT"
        src="https://img.shields.io/github/license/airone01/ft?style=flat-square&logo=unlicense&color=ee999f&logoColor=D9E0EE&labelColor=302D41"
      /></a>
    <a href="https://github.com/airone01/ft?tab=readme-ov-file#number-of-projects"><img
        alt="How many projects are in this repo"
        src="https://img.shields.io/badge/project_count-42_(yes,_really)-_?style=flat-square&logo=42&color=F5E0DC&logoColor=D9E0EE&labelColor=302D41"
      /></a>
    <a href="https://github.com/airone01/ft"><img
        alt="Repo size in bytes"
        src="https://img.shields.io/github/repo-size/airone01/ft?color=%23DDB6F2&label=repo%20size&logo=codesandbox&style=flat-square&logoColor=D9E0EE&labelColor=302D41"
      /></a>
    <a href="https://github.com/airone01/ft/actions/workflows/zig-build.yml"><img
        alt="Zig workflow status"
        src="https://img.shields.io/github/actions/workflow/status/airone01/ft/zig-build.yml?style=flat-square&logo=zig&logoColor=D9E0EE&labelColor=302D41"
      /></a>
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
[Building and packaging]: #building-and-packaging
[Additional notes]: #additional-notes

**[<kbd><br/> Foreword <br/>​</kbd>][Foreword]**
**[<kbd><br/> Projects <br/>​</kbd>][Projects]**
**[<kbd><br/> Extra tools/projects <br/>​</kbd>][Extra tools/projects]**
**[<kbd><br/> Building and packaging <br/>​</kbd>][Building and packaging]**
**[<kbd><br/> Additional notes <br/>​</kbd>][Additional notes]**

</p></div>

---

## Foreword

This is a [monorepository](https://en.wikipedia.org/wiki/Monorepo), meaning
these projects are tightly coupled and share dependencies to work properly.

**Why CMake?** The 42 curriculum relies heavily on GNU Make to teach students
the fundamentals of compilation. However, maintaining 30+ nearly identical
makefiles in a monorepo quickly becomes tedious. Because I enjoy DevOps and
reproducibility, I migrated this repository to the CMake build system[^1]. I now
only make a standard makefile and clean the repo right before pushing a project
for grading.

> [!NOTE]
> There are no subject PDFs here, hit the road, traveler!

> [!CAUTION]
> A natural side effect of this monorepo setup is that it makes it harder to
> blindly copy-paste my projects and submit them as your own, as some projects
> are heavily tied together. While deterring cheating wasn't my primary
> technical goal, I support the result. Copying defeats the core principles of
> 42 and goes against what I personally believe in. This repository is meant to
> serve as an example of what you can build at this school, not as a shortcut.
> It's called a school for a reason. _Learn; Write your own tests; and "By Odin!
> By Thor! Use your brain!"_.

## Projects

To see my grades, unwrap the following table.

<details>
  <summary>Common Core project grades</summary>
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
        <td><strong>Libft</strong></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td rowspan="3">1</td>
        <td><strong>Born2beroot</strong></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><strong>ft_printf</strong></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td><strong>get_next_line</strong></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan="3">2</td>
        <td><strong>pipex</strong></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><strong>push_swap</strong></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td><strong>FdF</strong></td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td rowspan=2>3</td>
        <td>
            <strong>minishell</strong><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a></sub>
        </td>
        <td>✅</td>
        <td>101</td>
      </tr>
      <tr align="center">
        <td><strong>Philosophers</strong></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan=3>4</td>
        <td>
            <strong>cub3d</strong><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a></sub>
        </td>
        <td>
          ✅<br/>
          <sub>(with bonuses)</sub>
        </td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><strong>CPP 00-04</strong></td>
        <td>✅</td>
        <td><sub>(various grades)</sub></td>
      </tr>
      <tr align="center">
        <td><strong>NetPractice</strong></td>
        <td>✅</td>
        <td>100</td>
      </tr>
      <tr align="center">
        <td rowspan="3">5</td>
        <td>
            <strong>ft_irc</strong><br/>
            <sub>with <a href="https://github.com/Manomania/">@maximart</a> & <a href="https://github.com/Sunny-444">@nahamida</a></sub>
        </td>
        <td>✅</td>
        <td>125</td>
      </tr>
      <tr align="center">
        <td><strong>Inception</strong></td>
        <td>✅</td>
        <td>90</td>
      </tr>
      <tr align="center">
        <td><strong>CPP 05-09</strong></td>
        <td>✅
        </td>
        <td><sub>(various grades)</sub></td>
      </tr>
      <tr align="center">
        <td rowspan="1">6</td>
        <td>
            <strong>ft_transcendence</strong><br/>
            <sub>with <a href="https://github.com/v-blanc">@vblanc</a>, <a href="https://github.com/EnzoPasselegue1">@enpassel</a> & <a href="https://github.com/SimonCottenet">@scottene</a></sub>
        </td>
        <td>✅</td>
        <td>125</td>
      </tr>
    </tbody>
  </table>
</details>

To see all the projects in this repo and the skills learned, unwrap the
following table. Head to the end of the section for the best projects.

<details>
  <summary>All projects</summary>
  <table border="1">
    <tr>
      <th>Name</th>
      <th>Description</th>
      <th>Note</th>
      <th>I learned</th>
    </tr>
    <tr>
      <td>libft</td>
      <td>Standard library</td>
      <td>Used for many other 42 projects.</td>
      <td>Library packaging, low-level good practices</td>
    </tr>
    <tr>
      <td>Born2beroot</td>
      <td>Basic Linux VM</td>
      <td>I had a background in VMs before 42, so this project wasn't hard.</td>
      <td>Linux and VM usage</td>
    </tr>
    <tr>
      <td>ft_printf</td>
      <td><code>printf(3)</code> implementation<a/td>
      <td></td>
      <td>String manipulation, some ABI features</td>
    </tr>
    <tr>
      <td>get_next_line</td>
      <td><code>readline(3)</code> implementation</td>
      <td></td>
      <td>String manipulation, memory</td>
    </tr>
    <tr>
      <td>fdf</td>
      <td>Heightmap visualizer</td>
      <td></td>
      <td>Some math calculations, optimization, GUI UX</td>
    </tr>
    <tr>
      <td>pipex</td>
      <td>Output redirection/pipes exercise</td>
      <td></td>
      <td>UNIX pipes, UNIX usage</td>
    </tr>
    <tr>
      <td>push_swap</td>
      <td>Sorting algorithm, its checker, and visualizer</td>
      <td></td>
      <td>FIFO/stacks, multi-target build systems, Rust programming and ECS</td>
    </tr>
    <tr>
      <td>philosophers</td>
      <td>The classic <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">dining philosophers problem</a></td>
      <td></td>
      <td>Concurrent algorithms, deadlocks, and racing prevention</td>
    </tr>
    <tr>
      <td>minishell</td>
      <td>A POSIX-compliant shell</td>
      <td></td>
      <td>More piping, processes and threads, lexers and parsers, team organization</td>
    </tr>
    <tr>
      <td>CPP 00 to 09</td>
      <td>C++ exercises</td>
      <td></td>
      <td>C++, OOP, more standards</td>
    </tr>
    <tr>
      <td>cub3d</td>
      <td>A <a href="https://en.wikipedia.org/wiki/Wolfenstein_3D">Wolfenstein 3D</a>-style game in 2.5D</td>
      <td></td>
      <td>2.5D, ray casting, more math, project management, assets and textures, optimization, conditional and multi-platform building and bundling</td>
    </tr>
    <tr>
      <td>net_practice</td>
      <td>Basic networking exercises in a Cisco Packet Tracer-like interface</td>
      <td></td>
      <td>Basic networking</td>
    </tr>
    <tr>
      <td>Inception</td>
      <td>(More) advanced VM and Docker (Compose) usage</td>
      <td>see Born2beroot</td>
      <td>Docker, Docker Compose, kernel features</td>
    </tr>
    <tr>
      <td>ft_transcendence</td>
      <td>Full-stack webapp social media and game</td>
      <td></td>
      <td>Project organization and management, Typescript, Bun, Svelte, ORMs (Drizzle), DBs (Postgres), crunches, Agile mindset</td>
    </tr>
    <tr>
      <td>B</td>
      <td>An assembly compiler for the B language</td>
      <td></td>
      <td>Advanced lexers and parsers, Bison, Flex, terminology and inner workings of compilers, assembly, i386 processors</td>
    </tr>
    <tr>
      <td>ft_linux</td>
      <td>A <a href="https://www.linuxfromscratch.org/lfs/">Linux From Scratch</a> (and <a href="https://www.linuxfromscratch.org/blfs/">BLFS</a>) system</td>
      <td></td>
      <td>Distro maintainer skills, package compilation, bootstrapping, SystemD, Init, many build systems like CMake, Ninja, ...</td>
    </tr>
    <tr>
      <td>ft_ls</td>
      <td>A clone of GNU BinUtils' <code>ls(1)</code></td>
      <td></td>
      <td>C project architecture, FS operations, some kernel ABI and features</td>
    </tr>
    <tr>
      <td>libasm</td>
      <td>Standard library in assembly</td>
      <td></td>
      <td>x86_64, assembly</td>
    </tr>
    <tr>
      <td>malloc</td>
      <td><code>malloc(3)</code> implementation</td>
      <td>(with <code>mmap(2)</code> only, without <code>brk(2)</code>)</td>
      <td>Linux ABI, memory allocation, defragmentation algorithms</td>
    </tr>
    <tr>
      <td>nm</td>
      <td>A clone of GNU BinUtils' <code>nm(1)</code></td>
      <td></td>
      <td>ELFs, Linux ABI, packaging and sectors, C project organization</td>
    </tr>
    <tr>
      <td>snow-crash</td>
      <td>A <a href="https://en.wikipedia.org/wiki/Capture_the_flag_(cybersecurity)">CTF</a></td>
      <td></td>
      <td>ELFs, cybersecurity, Linux protection and exploitation, permission systems</td>
    </tr>
  </table>
</details>

### Notable projects

|      [fdf](/milestone-2/fdf/README.md)<br /><img src="/.github/assets/banners/fdf.avif" g width=400 />       | [cub3d](/milestone-4/cub3d/README.md) (and its [3DS port](/milestone-4/cub3d/3DS_README.md))<br /><img src="/.github/assets/banners/cub3d.avif" width=400 /> |
| :----------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------: |
| **[ft_linux](/pcc/ft_linux/README.md)**<br /><img src="/.github/assets/banners/ft_linux.avif" g width=400 /> |          **[ft_transcendence](/milestone-6/ft_transcendence/README.md)**<br /><img src="/.github/assets/banners/ft_transcendence.avif" width=400 />          |

## Extra tools/projects

### [`3DS port of cub3d`](/milestone-4/cub3d/3DS_README.md)

During a boring weekend, I set up a Bazel[^1] target to cross-compile a 3DS
home-brew app. If you have a modded 3DS on hand, you can compile it and try
yourself. It's very limited, laggy, and crashes on quit though. You have been
warned. The level packaged is also very basic.

### [`Minecraft push_swap visualizer`](./tools/ps-viz-mc/README.md)

A program to flex on your friends by visualizing your push_swap algorithm in
Minecraft. It uses [Valence](https://valence.rs/) to control the game packets
and visualize the sorting algorithm on your `1.20.1` client.

<details>
  <summary>In-game screenshot</summary>
  <img alt="Minecraft push_swap visualizer in-game screenshot" src="./.github/assets/screenshot_1.webp" />
</details>

### [`FDF generator`](./external-tools/fdf-bmp-converter/README.md)

A simple script to convert a BMP[^2] image into a fdf file. It currently only
works for bitmap images smaller than 255 \* 255, because I don't really know how
to reliably get the width of the image in the header.

## Building and packaging

### CMake

You can build all[^3] the projects in this monorepo using
[CMake](https://cmake.org/).

```bash
# Example usage
cmake -B build -G Ninja
ninja -C build
```

### 3DS

The build instructions for the 3DS port of cub3d are detailed in a
[dedicated file](milestone-4/cub3d/3DS_README.md);

## Nix

This project's dev dependencies are packaged using [Nix](https://nixos.org/) in
a `devShell` that I personally use with
[`nix-direnv`](https://github.com/nix-community/nix-direnv). There is a central
[`flake.nix`](./flake.nix) that loads all nix files using `import-tree`.

I might eventually package the projects of this repo into this flake when I find
the time.

## Additional notes

### LSPs and `compile_commands.json`

If you use an IDE or LSP server and the constant `clangd` type errors appearing
when browsing this repo hurt your eyes, I might have a solution for you. The
`compile_commands.json` file! It instructs your LSP server on where to locate
the headers, and in which order, and how your build system (CMake in this case)
manages your compilation.

To generate this file, just generate the CMake project once. CMake should make
sure the file exists, and your LSP should be smart enough to find it. If not the
latter, it'll be in `BUILD_DIR/compile_commands.json`, where "BUILD_DIR" is the
directory you instructed CMake to build to with the `-B` argument.

Bear[^4] is not necessary anymore.

### Number of projects

To get the number of projects in this repo, you can run a quick
[`jq`](https://jqlang.org/) command.

```sh
jq '.packages | keys | map(select(startswith("tools") | not)) | length' -- release-please-config.json
```

## License

This project is licensed under the [MIT License](/LICENSE). See the
[LICENSE](/LICENSE) file for details.

[^1]: I used to use Bazel to build my projects, but it's somewhat incompatible
    with Nix[^5], so I moved to the Zig build system. The I moved away from Zig
    to CMake, because Zig wasn't really adapted to a monorepo architecture. Or
    more accurately, I didn't have the skills or time to make it suit my needs.
    CMake comes built-in with a bunch of features (like `compile_commands`[^4],
    or automatic target discovery) that are a plus for this repo.

[^2]: You can convert PNG images to BMP using `convert` from
    [ImageMagick](https://imagemagick.org/), or online with
    [EzGIF](https://ezgif.com/png-to-bmp).

[^3]: I haven't bothered to make _everything_ compile using CMake. At the time
    of writing, ft_transcendence (Typescript/NodeJS) and the Minecraft push_swap
    visualizer (Rust) must be compiled with their respective toolings (pnpm and
    cargo). I don't update the README as often as I update projects though, so
    take a look around and see for yourself!

[^4]: From [https://github.com/rizsotto/Bear](https://github.com/rizsotto/Bear):
    "Bear generates a compilation database for Clang tooling". Bear is not
    needed anymore, now that I've moved the build system to CMake.

[^5]: Here are good talks that detail the issues I came across:
    https://www.youtube.com/watch?v=6qOoOsjmyZ0
    https://www.youtube.com/watch?v=s801fgQOGnw
    https://www.youtube.com/watch?v=HI7LwgyOQO4
