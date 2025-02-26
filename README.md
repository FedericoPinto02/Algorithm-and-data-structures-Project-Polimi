# Algorithm-and-data-structures-Project-Polimi
[![License: GPL v2](https://img.shields.io/badge/License-GPL_v2-blue.svg)](https://github.com/ale-polimi/progetto-API-2023/blob/master/LICENSE)


Final project for Algorithms and Principles of Computer Science for the academic year 2022-2023.

Instructor: Martineghi Davide

**Grade**: 30/30

## Project Objective

Develop a C program to find the optimal path between gas stations on a highway.

The program must not only produce the correct output but also meet memory and CPU time constraints, as shown in the table below:

| Grade | Memory  | Time  |       Result       |
|-------|--------:|------:|:------------------:|
| 18    | 128 MiB | 19 s  | :white_check_mark: |
| 21    | 118 MiB | 15 s  | :white_check_mark: |
| 24    | 108 MiB | 10 s  | :white_check_mark: |
| 27    |  98 MiB |  6 s  | :white_check_mark: |
| 30    |  88 MiB |  4 s  | :white_check_mark: |

By using the verifier's data, my project has the following memory and execution time usage:

These results may vary depending on the computing power of the machine.

The complete project specification is available [here]().

The test cases are available [here](https://github.com/ale-polimi/progetto-API-2023/blob/master/documents/open_tests).

## Design Choices

The data structure representing the highway is a [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list). This solution was chosen for its implementation simplicity and lower memory usage compared to other data structures.

To meet the time constraints, a cache containing pointers to the most recently modified or accessed stations was implemented. The graph below shows the execution time of the program with input file `open_111.txt` as the cache size varies:

![alt text](https://github.com/ale-polimi/progetto-API-2023/blob/master/mermaid-diagram-2024-02-24-223609.png)

> [!NOTE]
> The execution times are quite high because the program was tested in a virtual machine.

## Tools Used

| Description        | Tool                                       |
|-------------------|-------------------------------------------|
| IDE              | [CLion](https://www.jetbrains.com/clion/)  |
| Compiler         | [gcc](https://gcc.gnu.org/)               |
| Memory profiling | [Valgrind - Massif](https://valgrind.org/) |
| Operating system | Windows 10 and Debian 11                  |

## Copyright and License

The project is distributed under the [GPL v2 license](https://github.com/ale-polimi/progetto-API-2023/blob/master/LICENSE), and the restrictions described in that license apply.
