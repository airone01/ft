#!/usr/bin/env bash

# This function finds files with identical names to libft functions and
# symlinks them to their libft counterpart.
# Example usage:
# find -type d -name 'ex*' -exec bash -c "source ~/ft/.worktree/malloc/transform.sh; cd {}; transform" \;

transform() {
  for file in *; do
    target="$HOME/ft/.worktree/malloc/milestone-0/libft/src/$file"
    if [ -f "$file" ]; then
      if [ -f "$target" ]; then
        ln -rsf "$target" "$file"
        echo "Linked: $file"
      else
        echo "Target '$target' is not a file"
      fi
    else
      echo "File '$file' is not a file"
    fi
  done
}
