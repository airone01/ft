#define STB_IMAGE_IMPLEMENTATION
#define _GNU_SOURCE

#include "stb_image.h"
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note: stb_image allows replacing assert, malloc, realloc, and free by
// defining them before including 'stb_image.h'. See the top of the file for
// details.
// TODO: use ft_malloc

// Supported image formats are detailed near the top of 'stb_image.h'.

static void print_help(FILE *f, const char *pname) {
  fprintf(f, "usage: %s [options] <file [...file(s)]>\n", pname);
  fprintf(f, "Converts an heightmap image to a FDF-compatible file.\n\n");

  fprintf(f, "-h, -?, --help\n");
  fprintf(f, "     display this help screen\n");
  fprintf(f, "-H, --desired-height <height>\n");
  fprintf(f, "     set the desired map height\n");
  fprintf(f, "-i, --infile <file>\n");
  fprintf(f, "     read input file\n");
  fprintf(f, "     if set to '-', and by default, read from standard input\n");
  fprintf(f, "-o, --outfile <file>\n");
  fprintf(f, "     write result to file\n");
  fprintf(f, "     if set to '-', and by default, write to standard output\n");
}

/// \param[out] out_height
/// \param[out] out_width
/// \return A pointer that can be freed using this file's 'free()'
static unsigned char *load_heightmap(FILE *file, int desired_height,
                                     int *out_height, int *out_width) {
  int h, w, channels;
  stbi_uc *pixels = stbi_load_from_file(file, &w, &h, &channels, STBI_grey);
  if (!pixels)
    return NULL;

  if (desired_height <= 0) {
    // No conversion necessary
    *out_width = w;
    *out_height = h;
    return pixels; ///< \note This is fine because 'stbi_image_free()' is just a
                   ///< 'free()'
  }

  int nw = (int)lroundf((float)w * desired_height / (float)h);
  if (nw < 1)
    nw = 1;
  int nh = desired_height;

  unsigned char *dst = malloc((size_t)nw * nh * sizeof(unsigned char));
  if (!dst) {
    stbi_image_free(pixels);
    return NULL;
  }

  // Bilinear resample
  const float x_ratio = (float)w / (float)nw;
  const float y_ratio = (float)h / (float)nh;
  for (int y = 0; y < nh; y++) {
    float gy = (y + 0.5f) * y_ratio - 0.5f;
    gy = gy < 0 ? 0 : (gy > h - 1 ? h - 1 : gy);
    int y0 = (int)gy;
    int y1 = y0 + 1 < h ? y0 + 1 : y0;
    float fy = gy - y0;

    for (int x = 0; x < nw; x++) {
      float gx = (x + 0.5f) * x_ratio - 0.5f;
      gx = gx < 0 ? 0 : (gx > w - 1 ? w - 1 : gx);
      int x0 = (int)gx;
      int x1 = x0 + 1 < w ? x0 + 1 : x0;
      float fx = gx - x0;

      float top = pixels[y0 * w + x0] * (1 - fx) + pixels[y0 * w + x1] * fx;
      float bottom = pixels[y1 * w + x0] * (1 - fx) + pixels[y1 * w + x1] * fx;

      float value = top * (1 - fy) + bottom * fy;
      value = value < 0 ? 0 : (value > 255 ? 255 : value);
      dst[y * nw + x] = (unsigned char)(value + 0.5f);
    }
  }
  stbi_image_free(pixels);

  *out_width = nw;
  *out_height = nh;
  return dst;
}

int main(int argc, char *const argv[]) {
  int c;
  static struct option long_opts[] = {
      {"help", no_argument, 0, 'h'},
      {"outfile", required_argument, 0, 'o'},
      {"infile", required_argument, 0, 'i'},
      {"desired-height", required_argument, 0, 'H'},
      {0, 0, 0, 0}};
  FILE *ofile = stdout;
  FILE *ifile = stdin;
  int desired_height = -1;

  for (;;) {
    int opt_i = 0;
    c = getopt_long(argc, argv, "h?o:i:H:", long_opts, &opt_i);
    if (c == -1)
      break;

    switch (c) {
    case '?':
    case 'h': {
      print_help(stdout, *argv);
      return EXIT_SUCCESS;
    }
    case 'o': {
      if (ofile != stdout)
        fclose(ofile);
      if (strcmp(optarg, "-") == 0) {
        ofile = stdout;
        break;
      }
      ofile = fopen(optarg, "w");
      if (!ofile) {
        fprintf(stderr, "warn: could not open file for writing '%s'\n", optarg);
        ofile = stdout;
      }
      break;
    }
    case 'i': {
      if (ifile != stdin)
        fclose(ifile);
      if (strcmp(optarg, "-") == 0) {
        ifile = stdin;
        break;
      }
      ifile = fopen(optarg, "r");
      if (!ifile) {
        fprintf(stderr, "warn: could not open file for reading '%s'\n", optarg);
        ifile = stdin;
      }
      break;
    }
    case 'H': {
      errno = 0;
      long r = strtol(optarg, NULL, 10);
      if (errno == ERANGE || (unsigned long)r >= UINTMAX_MAX) {
        fprintf(stderr, "Invalid height.");
        return EXIT_FAILURE;
      }
      desired_height = (int)r;
      break;
    }
    default: {
      fprintf(stderr, "?? getopt returned character code 0%o ??\n", c);
      break;
    }
    }
  }

  int h = -1, w = -1;
  unsigned char *map = load_heightmap(ifile, desired_height, &h, &w);
  fclose(ifile);

  if (!map) {
    fprintf(stderr, "error: failed to convert image.\n");
    return EXIT_FAILURE;
  }

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      fprintf(ofile, "%d", map[(y * w) + x]);
      if (x != w - 1)
        fprintf(ofile, " ");
    }
    fprintf(ofile, "\n");
  }

  fclose(ofile);
  free(map);

  /* */
}
