# High-Performance Sudoku Solver in C

A fast, efficient command-line Sudoku solver written in C. This project implements a recursive backtracking algorithm optimized with **bitwise operations** for constant-time $O(1)$ constraint checking.

## 🚀 Features

* **Bitwise Optimization:** Uses integer bitmasks to track used numbers in rows, columns, and 3x3 boxes. This eliminates the need for slow iterative loops to check if a move is valid.
* **Recursive Backtracking:** Efficiently explores the search space to find solutions.
* **Flexible Input:** Accepts puzzles via file arguments or Standard Input (stdin), allowing for piping and batch processing.
* **Minimal Memory Footprint:** Utilizes a flattened 1D array structure and global static memory for maximum cache efficiency.
* **Solvability Check:** Warns users if a puzzle contains fewer than 17 clues (implying potential non-uniqueness).

## 🛠️ Compilation

You can compile the solver using `gcc` or any standard C compiler.

```bash
gcc sudoku.c -o sudoku_solver

