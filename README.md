# Expression Calculator

This project is a console-based infix expression calculator written in C++. It converts an input expression to postfix form and then evaluates the result using custom stack and queue implementations.

It is also designed as a DSA learning project, with the stack and queue written manually instead of using STL containers.

The project is built around these source files:

- [main.cpp](main.cpp) for the user interface and program flow
- [evaluation.hpp](evaluation.hpp) for validation, postfix conversion, and evaluation logic
- [stack.hpp](stack.hpp) for the linked-list stack used by the algorithm
- [queue.hpp](queue.hpp) for the linked-list queue used to collect multi-digit numbers


## Project Overview

The calculator accepts a single infix expression at a time, converts it into postfix notation, and evaluates the postfix expression. The program runs continuously until the user types `exit`.

Supported operators:

- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Power: `^`

Supported brackets:

- Round brackets: `()`
- Curly brackets: `{}`
- Square brackets: `[]`

## How It Works

1. The program reads an expression from the console in [main.cpp](main.cpp).
2. The expression is checked for validity in [evaluation.hpp](evaluation.hpp).
3. The valid infix expression is converted to postfix notation.
4. The postfix expression is evaluated using a stack of numeric values.
5. The result is printed on the screen.

The calculator also prints the postfix form before showing the final answer.

## File Description

### [main.cpp](main.cpp)

This file handles the console interface.

- Displays the title and operator list
- Accepts user input
- Prints postfix output
- Prints the final calculated result
- Displays error messages for invalid expressions or runtime errors

It also uses Windows console functions to color the output.

### [evaluation.hpp](evaluation.hpp)

This file contains the core logic of the calculator.

- `isValid()` checks bracket matching and expression balance
- `precedence()` returns operator precedence
- `postfix()` converts infix to postfix notation
- `calculate()` applies one operator to two operands
- `evaluate()` computes the final numeric result

### [stack.hpp](stack.hpp)

This file provides a generic linked-list stack implementation.

Main operations:

- `push()` inserts an element on top
- `pop()` removes and returns the top element
- `top()` reads the top element without removing it
- `is_empty()` checks whether the stack is empty
- `display()` prints all elements from top to bottom

### [queue.hpp](queue.hpp)

This file provides a generic linked-list queue implementation.

Main operations:

- `equeue()` inserts an element at the rear
- `dequeue()` removes and returns the front element

The queue is used while building and evaluating multi-digit numbers.

## DSA Learning Focus

This project highlights two core data structures used in algorithm design:

- The custom stack supports operator handling and postfix evaluation.
- The custom queue helps process multi-digit numbers during conversion and evaluation.
- Both structures are implemented with linked lists to make the internal logic easier to study.
- The code is useful for understanding LIFO and FIFO behavior in a real calculator workflow.

## Input Format

To get correct output, enter the expression without spaces.

Examples:

```text
12+3
(5+7)*2
10/[2+3]
2^3^2
```

## Limitations

- Expressions must not contain spaces
- Only integer digits are handled by the current implementation
- Unary operators such as `-5` are not supported directly
- Invalid bracket order or invalid symbols will trigger an error
- Division by zero is detected and reported

## Example Run

```text
>>> (2+3)*4
Postfix: 2 3 + 4 *
Result: 20.000000
```

## Build and Run

This project is intended for Windows because `main.cpp` uses `windows.h` and `AllocConsole()`.

In Visual Studio, open the project and build it normally.

If you are compiling with MinGW on Windows, use a command similar to:

```bash
g++ main.cpp -o calculator
```

Then run the program and enter an expression when prompted.

## Notes

- The calculator uses a custom stack and a custom queue instead of STL containers.
- The postfix conversion and evaluation logic are implemented manually for learning purposes.
- The program is suitable for data structures and algorithm evaluation work.
