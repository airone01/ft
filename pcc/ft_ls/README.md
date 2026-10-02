# ft_ls

A simple clone of GNU BinUtils' `ls`.

```txt
$ ./zig-out/bin/ft_ls [options] [file(s)...]
List information about the FILEs (the current directory by default).
  -a, --all
         do not ignore entries starting with .
  -d, --directory
         list directories themselves, not their contents
  -g
         like -l, but do not list owner
  -f
         same as -a -U
  -l
         use a long listing format
  -o
         like -l, but do not list group information
  -r, --reverse
         reverse order while sorting
  -R, --recursive
         list subdirectories recursively
  -S
         sort by file size, largest first
  -t
         sort by time, newest first
  -u
         with -lt: sort by, and show, access time;
         with -l: show access time and sort by name;
         otherwise: sort by access time, newest first
  -U
         do not sort directory entries
      --zero
         end each output line with NUL, not newline
  -1
         list one file per line
      --help
         display this help and exit
```

## Testing

### Extended Attributes

```sh
touch /tmp/test_xattr
setfattr -n user.comment -v 'test' /tmp/test_xattr
ft_ls -l /tmp/test_xattr
# Extected: -rw-r--r--@ 1 ...
```

## ACL

```sh
touch /tmp/test_acl
setfacl -m u:nobody:r /tmp/test_acl
ft_ls -l /tmp/test_acl
# Extected: -rw-r--r--+ 1 ...
```

## Symbolic Links

```sh
ln -s /usr/bin/sh /tmp/test_lnk
ft_ls -l /tmp/test_acl
# Extected: lrwxrwxrwx 1 ... /tmp/test_acl -> /usr/bin/sh
```
