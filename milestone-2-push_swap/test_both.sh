#!/usr/bin/env bash
PS_ARGS="78 91 1 2 6 7 13 65 58 22 98 24 85 54 4 32 20 31 64 16 49 92 48 19 99 90 8 11 82 41 25 26 68 77 80 40 53 73 95 55 30 28 36 34 45 76 79 33 75 84 83 35 88 87 47 61 70 96 3 63 39 81 60 9 44 42 56 69 66 23 74 52 43 15 67 27 10 97 86 50 71 94 29 57 37 14 18 12 72 38 21 51 46 62 17 59 93 5 89 100"

~/goinfre/push_swap/push_swap "${PS_ARGS}"|tee ~/goinfre/result_original.txt
~/ft/milestone-2-push_swap/push_swap "${PS_ARGS}"|tee ~/goinfre/result_mine.txt
git diff --no-index ~/goinfre/result_original.txt ~/goinfre/result_mine.txt|tee ~/goinfre/results_diff.txt
