# snow-crash

This project is an introduction to vulnerability analysis, reverse engineering,
and

## Levels

### Level 00

Use `find` to locate all files owned by user. One of them is the flag.

### Level 01

Run John The Ripper (or any password cracking utility) against `/etc/passwd`.
The file of the previous level was named "john", a clue for this level.

### Level 02

Study PCAP trace of a Telnet session with WireShark. One must understand the way
backspaces work in Telnet , and piece the password together.

### Level 03

Change PATH to spoof a call to `echo`.

### Level 04

Basic Perl string injection.

### Level 05

Weird cron script (`openarenaserver`) that reads all files from a dir and
executes them. The difficulty in this level is more of understanding how cron
works.

### Level 06

PHP string injection where the entry argument is then edited by some RegEx.

### Level 07

Basic Shell injection payload and exiting using `;`.

### Level 08

Dynamically linking to a target file, with a different enough name to not
trigger the defense mechanism of the program.

### Level 09

Figure out that the program shifts the bytes of chars by their index as a hint.
Then make a function to shift the same way the other way around and feed it the
token.

### Level 10

Race against the program. The program uses (shadows) the same fd var for both
the net socket and the file to read.

### Level 11

Input string is not sanitized before being passed to popen. Exploit that and
avoid the rest of the script by opening a comment (`#`).

### Level 12

Perl string escape while working around constraints, which in this case are that
the path to our file must not contain lowercase letters. So we use the niche `?`
character.

### Level 13

Memory manipulation (using gdb in my case) to fool the program.

### Level 14

Memory manipulation (using gdb in my case) and avoidance of ptrace detection to
fool the program.

## Notes

```sh
qemu-system-x86_64 -display gtk -enable-kvm -m 2G -cdrom SnowCrash.iso -boot d -nic user,model=virtio-net-pci,hostfwd=tcp::4242-:4242
```
