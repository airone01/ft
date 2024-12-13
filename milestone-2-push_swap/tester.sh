#!/usr/bin/env bash

# Minimal
./complexity 100 100 700 -f ./push_swap ./checker_linux
# Maximal
./complexity 500 100 5500 -f ./push_swap ./checker_linux
# Nazi
./complexity 1000 100 10000 -f ./push_swap ./checker_linux