# Algorithm-and-data-structures-Project-Polimi - A.Y. 2022-2023

Final project for Algorithms and Principles of Computer Science for the academic year 2022-2023.

### Goal:
design and development of an efficient solution to a complex problem using algorithms and structures taught in the course.

Instructor: Martineghi Davide

**Grade**: 30/30

## Project Objective

Develop a C program to find the optimal path between gas stations on a highway.

The program must not only produce the correct output but also meet memory and CPU time constraints, as shown in the table below:

| Grade | Memory  | Time  |       Result       |
|-------|--------:|------:|:------------------:|
| 18    | 128 MiB | < 19 s  | :white_check_mark: |
| 21    | 118 MiB | < 15 s  | :white_check_mark: |
| 24    | 108 MiB | < 10 s  | :white_check_mark: |
| 27    |  98 MiB | < 6 s  | :white_check_mark: |
| 30    |  88 MiB | < 4 s  | :white_check_mark: |

By using the verifier's data, my project has the following memory and execution time usage:

These results may vary depending on the computing power of the machine.

## Principal implementative Choices
### Linked List: 
Used to manage highway stations (stazione), maintaining an ordered sequence with prev and next pointers.
### Hash Table: 
Enables fast station lookup, implemented with separate chaining to handle collisions.
### Heap Sort: 
Ensures cars at each station are stored in sorted order, using a max heap for efficient sorting.

## Other stuff
The complete project specification is available [here](project_specifications.pdf).

The test cases are available [here](Test).

## Tools Used

| Description        | Tool                                       |
|-------------------|-------------------------------------------|  
| Compiler         | [gcc](https://gcc.gnu.org/)               |
| Memory profiling | [Valgrind - Massif](https://valgrind.org/)|
| Operating system | Mac OS |


