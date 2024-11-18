find . -type f -printf "%f\n"|sed '/.*.sh/!d'|sed 's/\.sh//g'
