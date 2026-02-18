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
```

## 💻 Usage

### 1. Using a File
Create a text file (e.g., `puzzle.txt`) containing the Sudoku grid. You can use numbers `1-9`, and `0` or `.` for empty spaces.

**Command:**
```bash
./sudoku_solver puzzle.txt
```

### 2. Using Standard Input (Terminal)
You can type the puzzle directly or pipe it from another command.

**Command:**
```bash
./sudoku_solver
```
*(Then type your puzzle and press **Ctrl+D** (Linux/Mac) or **Ctrl+Z** (Windows) to end input)*

**Piping Example:**
```bash
cat puzzle.txt | ./sudoku_solver
```

## 📄 Input Format
The solver is robust and ignores whitespace and newlines. It expects 81 valid characters.
* **Empty cells:** Represented by `0` or `.`
* **Filled cells:** Digits `1` through `9`

**Example Input:**
```text
5 3 . . 7 . . . .
6 . . 1 9 5 . . .
. 9 8 . . . . 6 .
8 . . . 6 . . . 3
4 . . 8 . 3 . . 1
7 . . . 2 . . . 6
. 6 . . . . 2 8 .
. . . 4 1 9 . . 5
. . . . 8 . . 7 9
```

## 🧠 How It Works (The Bitwise Logic)

Instead of looping through rows and columns to check if a number is valid (which takes $O(9)$ time), this solver uses **Bitmasks**.

Each row, column, and box is represented by an integer flag. When a number $N$ is placed, the $N$-th bit is flipped to `1`.

* **Number 1:** `...000000010` (shifted `1 << 1`)
* **Number 5:** `...000100000` (shifted `1 << 5`)

Checking if a number is safe is a simple bitwise AND operation that happens in **constant time** $O(1)$:

```c
// Check if the bit for 'num' is already set in Row, Col, or Box
if ((row_flags[r] & mask) || (col_flags[c] & mask) || (box_flags[b] & mask)) {
    return 0; // Unsafe
}
```

This significantly speeds up the solver compared to naive implementations.