libasm
======

A library of basic functions, written in assembly.

Assembly specifications
-----------------------

This project is programmed for baseline x86_64 with the System V AMD64 convention, for the GNU/Linux ABI.
The Intel syntax is the one used, as required by the subject.
This is not programmed for any AVX extension.

Provided functions
------------------

The functions provided by this project are the following:

- ft_strlen (man 3 strlen)
- ft_strcpy (man 3 strcpy)
- ft_strcmp (man 3 strcmp)
- ft_write (man 2 write)
- ft_read (man 2 read)
- ft_strdup (man 3 strdup, call to malloc allowed)

