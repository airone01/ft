#!/usr/bin/env sh
# shellcheck disable=SC2012
ls -l | awk 'NR % 2 == 1'
