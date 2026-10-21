# B

This project aims to create a simple B to i386 assembly compiler, using the
`lex` and `yacc` programs and their syntax.

## Requirements

This project requires **GNU Make**,
[**GNU Bison**](https://en.wikipedia.org/wiki/GNU_Bison) and
[**Flex**](https://en.wikipedia.org/wiki/Flex_(lexical_analyzer_generator)) as
drop-in more modern replacements).

## Implementation Details

- The program compiles to i386 assembly (for x86 processors with the
  [SSE](https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions)) using the
  Intel syntax.
- There is no AST. Lookahead is
  [LR(1)](https://en.wikipedia.org/wiki/Canonical_LR_parser).
- Hence, this compiler is very simple. Resulting assembly has duplicated and
  unoptimized operations. But as explicitly explained in the subject, the goal
  is to make it work, not make it good.
- It does not support early B-style assignment operators (`=+` instead of `+=`).
- The char/string escape character is the more modern `\`, not `*`.
- It does not support global vector and vars declarations.
- There are some comments on stuff I deem necessary to detail, or on stuff I
  find cool. For example, take a look around for the IEE-754, string, and
  logical `AND` and `OR` implementations to name a few.
- A few things may not be compatible with original Lex and Yacc, but I don't
  care, as those programs are the age of my grandparents and are not widely
  available right now.
- I'm starting to near the limit of what is possible without an AST. Thankfully,
  Ken Thompson is a legend and this language is perfect for making an LR(1)
  compiler, but for more substantial features than what is present here, I would
  probably need a good refactor, and better file organization.

## Implemented Features

- Functions
  - Parameters
  - Declaration
  - Calling
  - `extern`
- Identifiers and variables
  - Declaration (`auto`)
  - Assignment
  - Calling
- Complete conditions
  - `if`
  - `else`
  - Expressions
    - In all other expected places like `while` as well
  - Assignment in expression `if (a = 5 + b) ...`
  - Chaining
    - `&&`
    - `||`
    - `!`
- Semicolons
- Braces
- Switch
  - `switch`
  - `case`
  - `default`
- `break`
  - In Switch
  - In While
  - Error outside of loop or switch
- Inline labels
  - GOTOs as well
- Math
  - `+`
  - `-`
  - `*`
  - `/`
  - `%`
  - `<`, `>`
  - `|`
  - `&`
  - `~`
  - `^`
  - `<<`, `>>`
  - `<=`, `>=`
  - `==`, `!=`
  - Floating-point operations
    - `#+`
    - `#-`
    - `#*`
    - `#/`
    - `#<`, `#>`
    - `#<=`, `#>=`
    - `#==`, `#!=`
  - `++`, `--`
- `#` and `##`
- Chars
- Strings
- `return`
- Address-of and dereference (`&` and `*`)
- Comments (`/* ... */`)
- Global vectors and variables
- ...and probably more I forgot :-)

### Bonus Features

- Switch/cases, labels and internal declarations
- Floating-point operators (Thinkage-style)
- The B standard library (`./libb/`, except the `gtty` and `stty` functions)

The subject also asks for two more any feature I want. I implemented:

- Compiler optimizations through a simple peephole system (in `c2*.c`) on the
  assembly code itself, post-compilation. Inspired by "C2", one of the early
  compiler optimization layers of the C compiler that worked in a similar
  fashion.
- Global vectors and variables
