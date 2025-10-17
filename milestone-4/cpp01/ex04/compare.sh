!#/usr/bin/env bash

make
valgrind --show-leak-kinds=all --track-fds=yes --leak-check=full --trace-children=yes --trace-children-skip=/bin/\*,/usr/bin/\*,/sgoinfre/elagouch/Config/.brew/Cellar/\*/\*/bin/\*,/sgoinfre/elagouch/.brew/bin/\* --track-origins=yes --suppressions=/home/elagouch/readline.supp ./sed luden.txt "en gros " ""
git diff --no-index --word-diff=color --word-diff-regex=. luden.txt luden.txt.replace

