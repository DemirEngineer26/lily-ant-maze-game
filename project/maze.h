#ifndef MAZE_H
#define MAZE_H

//Header guards prevent double inclusion errors

typedef struct {
    int row;
    int col;
} Position;

//Maze struture, featuring a 50x50 grid 
typedef struct {
    char grid[50][50];
    int rows; 
    int cols;
    Position lily_pos;
    int score;
} Maze;

//function prototypes
int maze_load(Maze, *maze, const char *filename);
void maze_print(const Maze *maze);
int maze_can_move(const Maze *maze, int row, int col);
int maze_move_lily(Maze *maze, char direction);
int maze_college_point(Maze *maze);

#endif //MAZE_H
