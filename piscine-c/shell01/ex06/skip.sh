#!/usr/bin/env sh
ls -l | awk 'NR % 2 == 1'
