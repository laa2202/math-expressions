# Math Expressions

This project solves the math expression assignment in C++.

The program starts with the number `1` and tries to reach the number entered on
the command line. The only operations allowed are:

- integer division by 3
- multiplication by 2

The program tries division first and multiplication second, like the assignment
asks.

## How To Compile

Run:

```bash
make
```

This creates the executable named `mathexpr`.

## How To Run

Example:

```bash
./mathexpr 10
```

Output:

```text
1 x 2 x 2 x 2 x 2 / 3 x 2
```

To remove the compiled file:

```bash
make clean
```

## Algorithm

The program uses breadth-first search, or BFS.

I used BFS because it checks shorter expressions before longer expressions. That
means when the program reaches the target number for the first time, it has found
the shortest expression.

Each number is treated like a state. From each state, the program tries:

```text
current / 3
current * 2
```

The program stores the previous number and the move used to get there. At the
end, it walks backward from the target to `1` and then prints the expression in
the correct order.

## Limitations

The BFS search has a max limit so the program does not use too much memory.
Right now that limit is `20000000`.

If the input is bigger than that limit, the program usually prints:

```text
No solution found.
```

There is one exception: if the number is a power of two, the program can still
solve it because it only needs repeated multiplication by 2.

This limit is there because BFS stores arrays for the numbers it visits. Without
a limit, a very large input could make the program use too much memory.

## Runtime

The runtime is `O(n)`, where `n` is the search limit. BFS visits each number at
most once, and for each number it tries two operations.

The memory usage is also `O(n)` because the program stores arrays to remember the
previous number and the operation used.

## Files

- `mathexpr.cpp` - source code
- `Makefile` - compiles the program
- `input1.txt` to `input10.txt` - test inputs
- `output1.txt` to `output10.txt` - expected outputs
