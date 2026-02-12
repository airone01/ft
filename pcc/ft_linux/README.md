# LFS

This project is a home-made distro made by following [Linux From Scratch](https://www.linuxfromscratch.org/lfs/).
This was made as [42](https://42.fr/en/homepage/)'s `ft_linux` project.

## Subject

The subject provided by 42 asks students to implement LFS, and then make some
changes to the final LFS implementation. I will not be detailing those changes
here, because 42 is awesome and I don't want to leak the subjects.
Come to 42 if you want to find out!

## Implementation details

- This distro was made by following [LFS 12.4](https://www.linuxfromscratch.org/lfs/view/12.4/) ([permalink](https://web.archive.org/web/20250922045138/https://www.linuxfromscratch.org/lfs/view/12.4/)) and some parts of BLFS.
- The "host" distro was actually an Alpine system I set up on another qcow2.
- The kernel version is 6.16

## What I learned

- 24 cores CPU and 16GB RAM is good, but what gives speed is not running the VM on an USB stick. Learned the hard way.
- I dreaded compiling the kernel, but it wasn't nearly as bad as compiling GCC 3 times.
- The more I read documentation, compiled and tested packages, the more I understood why those packages and why they were made this way.
  - So I would like to ask forgiveness for the gods and goddesses of GNU/Linux who have blessed us with this amazing OS for all the times I complained about how anything worked.
- Turns out `autoconf` and `automake` are fucking awesome.
- I now truly understand the need for a deterministic build system, and hence why Nix and Guix exist.
- Why is Python the only package that has its archive name starting with a capital "P"? (except XML-Parser, but I really want to hate on Python, let's just pretend `XML-Parser-2.47.tar.gz` is spelled in snake case like the rest)
- LFS team, thank you for taking the time to make the `wget-list` and `md5sums` files.
  - And thank you for LFS. It rocks.
  - And thank you for all the little notes and comments, saved me hours of rebuilding.
- Saying RTFM is a dick move but turns out you do get better by reading docs.

## Submission

Nothing for this project is submitted through a git repo, all is in the VM, so this repository is pointless, except for the cool utility script.

But I did make the repo anyways as you can see, just to brag that I finished LFS. So here we are.
You can see some screenshots below because of course I took screenshots.

