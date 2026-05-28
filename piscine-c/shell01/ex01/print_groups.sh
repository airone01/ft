#!/usr/bin/env sh
id -znG "$FT_USER" | sed 's/\x0/,/g' | sed 's/.$//'
