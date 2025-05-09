#!/usr/bin/env bash

print_help() {
  echo -e "\033[1;36mGradient Generator (OKLab)\033[0m"
  echo -e "\n\033[1mUsage:\033[0m"
  echo -e "  ./gradient.sh [options] <color1> <color2> <steps>"
  echo -e "\n\033[1mOptions:\033[0m"
  echo -e "  -c, --char <char>   Set display character (default: EN SPACE ' ')"
  echo -e "  -v, --vertical      Show colors vertically with RGB + ANSI info"
  echo -e "  -h, --help          Show this help message"
  echo -e "\n\033[1mColor formats:\033[0m"
  echo -e "  Accepts hex codes (e.g. #ff00aa, ff00aa) or R G B triplets."
  echo -e "\n\033[1mExamples:\033[0m"
  echo -e "  ./gradient.sh '#40C9FF' '#E81CFF' 30"
  echo -e "  ./gradient.sh -v -c █ 64 201 255 232 28 255 10"
  exit 0
}

# Default values
CHAR=" "
VERTICAL=0
POSITIONAL=()

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
  -h | --help) print_help ;;
  -v | --vertical)
    VERTICAL=1
    shift
    ;;
  -c | --char)
    if [[ -n "$2" ]]; then
      CHAR="$2"
      shift 2
    else
      echo "Error: --char requires a character"
      exit 1
    fi
    ;;
  -*)
    echo "Unknown option: $1"
    exit 1
    ;;
  *)
    POSITIONAL+=("$1")
    shift
    ;;
  esac
done

set -- "${POSITIONAL[@]}"

# Validate argument count
if [[ ${#POSITIONAL[@]} -lt 3 ]]; then
  echo "Error: Not enough arguments"
  print_help
fi

# Hex or RGB parser
parse_color() {
  local input="$1"
  if [[ "$input" =~ ^#?[0-9a-fA-F]{6}$ ]]; then
    input="${input/#\#/}"
    echo "$((16#${input:0:2})) $((16#${input:2:2})) $((16#${input:4:2}))"
  else
    echo "$input"
  fi
}

read R1 G1 B1 <<<$(parse_color "${POSITIONAL[0]}")
read R2 G2 B2 <<<$(parse_color "${POSITIONAL[1]}")
STEPS=${POSITIONAL[2]}

# Gradient generation
awk -v R1=$R1 -v G1=$G1 -v B1=$B1 -v R2=$R2 -v G2=$G2 -v B2=$B2 \
  -v steps=$STEPS -v vertical=$VERTICAL -v char="$CHAR" '
function srgb_to_linear(c) {
  c = c / 255
  return (c <= 0.04045) ? c / 12.92 : ((c + 0.055)/1.055)^2.4
}
function linear_to_srgb(c) {
  return (c <= 0.0031308) ? 12.92 * c : 1.055 * (c^(1/2.4)) - 0.055
}
function rgb_to_oklab(r, g, b,   rl, gl, bl, l, m, s, l_, m_, s_, L, A, B) {
  rl = srgb_to_linear(r); gl = srgb_to_linear(g); bl = srgb_to_linear(b)
  l = 0.4122214708*rl + 0.5363325363*gl + 0.0514459929*bl
  m = 0.2119034982*rl + 0.6806995451*gl + 0.1073969566*bl
  s = 0.0883024619*rl + 0.2817188376*gl + 0.6299787005*bl
  l_ = l^(1/3); m_ = m^(1/3); s_ = s^(1/3)
  L = 0.2104542553*l_ + 0.7936177850*m_ - 0.0040720468*s_
  A = 1.9779984951*l_ - 2.4285922050*m_ + 0.4505937099*s_
  B = 0.0259040371*l_ + 0.7827717662*m_ - 0.8086757660*s_
  return L " " A " " B
}
function oklab_to_rgb(L, A, B,   l_, m_, s_, l, m, s, r, g, b) {
  l_ = L + 0.3963377774*A + 0.2158037573*B
  m_ = L - 0.1055613458*A - 0.0638541728*B
  s_ = L - 0.0894841775*A - 1.2914855480*B
  l = l_^3; m = m_^3; s = s_^3
  r = 4.0767416621*l - 3.3077115913*m + 0.2309699292*s
  g = -1.2684380046*l + 2.6097574011*m - 0.3413193965*s
  b = -0.0041960863*l - 0.7034186147*m + 1.7076147010*s
  r = int(linear_to_srgb(r)*255 + 0.5)
  g = int(linear_to_srgb(g)*255 + 0.5)
  b = int(linear_to_srgb(b)*255 + 0.5)
  r = (r < 0) ? 0 : ((r > 255) ? 255 : r)
  g = (g < 0) ? 0 : ((g > 255) ? 255 : g)
  b = (b < 0) ? 0 : ((b > 255) ? 255 : b)
  return r " " g " " b
}
BEGIN {
  split(rgb_to_oklab(R1, G1, B1), c1, " ")
  split(rgb_to_oklab(R2, G2, B2), c2, " ")

  for (i = 0; i < steps; i++) {
    t = i / (steps - 1)
    L = c1[1]*(1 - t) + c2[1]*t
    A = c1[2]*(1 - t) + c2[2]*t
    B = c1[3]*(1 - t) + c2[3]*t
    split(oklab_to_rgb(L, A, B), rgb, " ")
    r = rgb[1]; g = rgb[2]; b = rgb[3]
    code = sprintf("38;2;%d;%d;%d", r, g, b)
    if (vertical) {
      printf("\033[%sm%s\033[0m  RGB(%3d,%3d,%3d) ANSI:%s\n", code, char, r, g, b, code)
    } else {
      printf("\033[48;2;%d;%d;%dm%s\033[0m", r, g, b, char)
    }
  }
  if (!vertical) print ""
}
'
