# lily-ant-maze-game
ESE 124 Final Project - C Maze Exploration Game with Stack &amp; Queue ADTs
This project is meant to be a console based maze game in C where Lily the Ant explores a maze, collects points, and tries to achieve the highest score before the time runs out. 
This project includes an Abstract Data Type (ADT), a stack-based Undo feature, and a queue-based shortest path search. 

The ADT has a clear public interface and private implementation details. Stacks are used to store and move history, as well as to undo the most recent move. The queue is used to explore maze positions in FIFO (first-in, first-out) behavior. This project utilizes loops, arrays, strings, file I/O, functions, pointers, structures, and modular design. 

Walls are represented by the '#' character while spaces lily can move are represented by ' ' and points lily can obtain are represented by '*'

Normal and edge cases:
A valid maze file opens a valid maze.txt and the maze loads and displays correctly
If the file is missing,  the program is run without maze.txt and print error and exit safely
If the maze is blocked, 
If Lily tries to go out of bounds, her move is blocked and an out of bounds message prints
