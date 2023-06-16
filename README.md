# Brainfuck Interpreter

Author:
```brainfuck
+[----->+++<]>.++.+++++++++++.------------.[--->+<]>---.+[->+++<

]>.[-->+<]>---.--[--->+<]>-.++++++++++++.--.+++[->+++++<]>-.+.[-

---->+<]>--.++++++.+.
```

06/16/2023

---

## Background

*Adapted from the [Wikipedia article on Brainfuck][brainfuck-wiki].*

Brainfuck is an esoteric programming language created in 1993 by Urban Müller.
The language contains only eight simple commands and an instruction pointer.
While it is fully Turing-complete, it is not intended for practical use, but to
challenge and amuse programmers.

The language's name is a reference to the slang term brainfuck, which refers to
things so complicated or unusual that they exceed the limits of one's
understanding.

## Overview

Brainfuck is a turing-complete language modelled after the theoretical model of a
[turing machine][turing-machine]. As such, when programming in brainfuck, it is
good to keep a mental model of a brainfuck turing machine in mind.

The brainfuck turning machine:
```
----------------------||---||----------------------
  | 0 | 0 | 0 | 0 | 0 || 0 || 0 | 0 | 0 | 0 | 0 |
----------------------||---||----------------------
  tape ---^     ^        ^
    cell --------        |
       head (pointer) ----
```

The "tape" shown above is the memory of the computer. The "cells" in the tape
contain values. The currently selected cell is at the "head" and is sometimes
called the "pointer".

Instructions to manipulate the tape are fed into the machine. They are not
stored in the tape itself. The instructions specify how the machine should move
the tape. The cell under the head can change and the value of that cell can be
updated, replaced or outputted. The full instruction set is described in detail
in the [Instructions](#instructions) section.

## Instructions

Brainfuck has 8 basic instructions:

* `>` - move the pointer right
* `<` - move the pointer left
* `+` - increment the current cell
* `-` - decrement the current cell
* `.` - output the value of the current cell
* `,` - **replace** the value of the current cell with input
* `[` - jump to the **matching** `]` instruction if the current value is zero
* `]` - jump to the **matching** `[` instruction if the current value is **not** zero
* `?` - **Debug:** prints the value in current cell in number form


## Memory Layout

The brainfuck tape is made of an "infinite" collection of 1 byte cells. Each
cell represents a single, unsigned 8-bit number. Cells start initialized at
zero.

Since the numbers are unsigned, there is no need for any complex integer
implementation. If the upper limit of the cell is reached, it wraps back to
zero. If zero is decremented, it must wrap back to 11111111. Normal binary
number arithmetic rules applies.

## Hello World Example

*Adapted from the [Wikipedia article on Brainfuck][brainfuck-wiki].*

The following program prints "Hello World!" and a newline to the screen:

```brainfuck
[ This program prints "Hello World!" and a newline to the screen, its
  length is 106 active command characters. [It is not the shortest.]

  This loop is an "initial comment loop", a simple way of adding a comment
  to a BF program such that you don't have to worry about any command
  characters. Any ".", ",", "+", "-", "<" and ">" characters are simply
  ignored, the "[" and "]" characters just have to be balanced. This
  loop and the commands it contains are ignored because the current cell
  defaults to a value of 0; the 0 value causes this loop to be skipped.
]
++++++++               Set Cell #0 to 8
[
    >++++               Add 4 to Cell #1; this will always set Cell #1 to 4
    [                   as the cell will be cleared by the loop
        >++             Add 2 to Cell #2
        >+++            Add 3 to Cell #3
        >+++            Add 3 to Cell #4
        >+              Add 1 to Cell #5
        <<<<-           Decrement the loop counter in Cell #1
    ]                   Loop till Cell #1 is zero; number of iterations is 4
    >+                  Add 1 to Cell #2
    >+                  Add 1 to Cell #3
    >-                  Subtract 1 from Cell #4
    >>+                 Add 1 to Cell #6
    [<]                 Move back to the first zero cell you find; this will
                        be Cell #1 which was cleared by the previous loop
    <-                  Decrement the loop Counter in Cell #0
]                       Loop till Cell #0 is zero; number of iterations is 8

The result of this is:
Cell No :   0   1   2   3   4   5   6
Contents:   0   0  72 104  88  32   8
Pointer :   ^

>>.                     Cell #2 has value 72 which is 'H'
>---.                   Subtract 3 from Cell #3 to get 101 which is 'e'
+++++++..+++.           Likewise for 'llo' from Cell #3
>>.                     Cell #5 is 32 for the space
<-.                     Subtract 1 from Cell #4 for 87 to give a 'W'
<.                      Cell #3 was set to 'o' from the end of 'Hello'
+++.------.--------.    Cell #3 for 'rl' and 'd'
>>+.                    Add 1 to Cell #5 gives us an exclamation point
>++.                    And finally a newline from Cell #6
```

For "readability", this code has been spread across many lines and blanks and
comments have been added. Brainfuck ignores all characters except the eight
commands `+-<>[],.` so no special syntax for comments is needed (as long as the
comments don't contain the command characters). The code could just as well have
been written as:

```brainfuck
++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.
```

---

## Additional Notes


+ Using any register outside of 1-50000 can result in undefined behavior

+ Unclosed brackets can result in undefined behavior

+ Might not fully conform to the official bf standard bc im lazy



\\/ (Most of) **README.md** taken from \\/


+ https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md

^ **hello_world.bf** is also taken from here ^

---
```brainfuck
+[------->++<]>-.------------.+++.+.--[--->+<]>-.--[->++++<]>-.+[->+++<]>+
.+++++++++++.------------.--[--->+<]>--.++[->+++<]>.++++++++++++.+++.--.+.
--.+++[->+++<]>++.--[--->+<]>-.-----------.++++++.-.>++++++++++..-[->+++++
<]>.[--->++<]>++.[-->+++++<]>-.--[--->+<]>-.++++++.+.-[---->+<]>+++.--[->
++<]>.---------.
```
Licensed under [GPL-v3][gplv3]

[brainfuck-wiki]: https://en.wikipedia.org/wiki/Brainfuck
[turing-machine]: https://en.wikipedia.org/wiki/Turing_machine
[gplv3]: https://www.gnu.org/licenses/gpl-3.0.en.html
