# FDF Map Converter

> A heightmap image to FDF map file converter.

This program takes heightmap images and converts them to text files to be used
with [FDF](../../milestone-2/fdf/README.md). The program reads the image in
grayscale mode, uncaring any color.

## Usage

```
usage: fdfMapConverter [options] <file [...file(s)]>
Converts an heightmap image to a FDF-compatible file.

-h, --help
     display this help screen
-H, --desired-height <height>
     set the desired map height
-i, --infile <file>
     read input file
     if set to '-', and by default, read from standard input
-o, --outfile <file>
     write result to file
     if set to '-', and by default, write to standard output
```

## Supported image types

This program uses
[`stb_image.h`](https://github.com/nothings/stb/blob/master/stb_image.h), which
supports a wide variety of images and color formats. Refer to the file's
documentation for more details. Images that are not a square are supported, even
with the `-H` option.
