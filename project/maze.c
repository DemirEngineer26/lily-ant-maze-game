#include <sdtio.h>
#include <stdlib.h> 
#include "maze.h"

int maze_load(Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    //read maze file into maze grid row by row using malloc
    //locate initial positions, points, walls, etc
    int num_rows;
    scanf("%d", n);
    char **grid = malloc(sizeof(char *) * num_rows);//interchangeable with char **grid = malloc(sizeof(*grid) * num_rows);
    if (grid == NULL) {
        return NULL;
    }
    int rows = 0;
    int cols = 0;
    int max_cols = 0;
    int ch;
    while ((ch == fgetc(file)) != EOF) {
        if (ch == '\n') {
            rows++;
        }
        if (cols > max_cols) max_cols = cols;
        cols = 0;
    } else {
        cols++;
    }
    if (cols > 0) {
        rows++;
        if (cols > max_cols) max_cols = cols;
    }
    maze->rows = rows;
    maze->cols = max_cols;
    //free(grid);

    fclose(file);
    fopen(filename, "r");
    return 1;
}

void maze_print(const Name *maze) {
    //loop through maze grid and print each character to stdout
    for (int i = 0; i < (*maze.rows); i++) {
        for (int j = 0; j < (*maze.cols); j++) {
            printf("%c", (*maze.grid[i][j]));
        }
    }
}

int maze_can_move(const Maze *maze, int row, int col) {
    //check if (row, col) is within bounds rather than a wall '#'
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (*maze.grid[i][j] == '#') {
                printf("Error! Out of bounds!");
                return 0;
            } else {          
                printf("within bounds");
                return 1;
            }
        }
    }
    //return 0;
}

int maze_move_lily(Maze *maze, char direction) {
    //update maze, meaning lily's position depends on W/A/S/D. 
    //W is for up, A is for left, S is for down, D is for right

    int target_row = maze->lily_pos.row;
    int target_col = maze->lily_pos.col
    if (direction == 'W' || direction == 'w') {
        target_row--;
    } else if (direction == 'A' || direction == 'a') {
        target_col--;
    } else if (direction == 'S' || direction == 's') {
        target_row++;
    } else if (direction == 'D' || direction == 'd') {
        target_col++;
    } else {
        return 0;
    }

    if (maze_can_move(maze, target_row, target_col)) {
        //clear lily's old position on the grid
        maze->grid[maze->lily_pos.row][maze->lily_pos.col] = ' ';

        //update lily's stored position
        maze->lily_pos.row = target_row;
        maze->lily_pos.col = target_col;

        //draw lily at her new spot on the grid
        maze->grid[target_row][target_col] = 'L';

        return 1;
    }
    
    return 0;
}

int maze_collect_point(Maze *maze) {
    //check if Lily is on a point tile, increment maze score, and clear
    int target_row = maze->lily_pos.row;
    int target_col = maze->lily_pos.col;
    if (maze->grid[target_row][target_col] == '*') {
        maze->score += 1;
        maze->grid[target_row][target_col] = ' ';//check if correct 
        return 1;
    }
    return 0;
}

