#include <stdio.h>
#include <stdlib.h> 
#include "maze.h"
#include "queue.h"
int maze_load(Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return 0;
    }

    //read maze file into maze grid row by row using malloc
    //locate initial positions, points, walls, etc
    if (fscanf(file, "%d %d", &maze->rows, &maze->cols) != 2) {
        fclose(file);
        return 0;
    }

    maze->grid = malloc(maze->rows * sizeof(char *));
    if (maze->grid == NULL) {
        fclose(file);
        return 0;
    }
    for (int i = 0; i < maze->rows; i++) {
        maze->grid = malloc((maze->cols + 1) * sizeof(char));
        for (int j = 0; j < maze->cols; j++) {
            fscanf(file, " %c", &maze->grid[i][j]);

            if (maze->grid[i][j] == 'L') {
                maze->lily_pos.row = i;
                maze->lily_pos.col = j;
            }
        }
    }
    maze->score = 0;
    fclose(file);
    return 1;
}

void maze_print(const Maze *maze) {
    //loop through maze grid and print each character to stdout
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c ", maze->grid[i][j]);
        }
        printf("\n");
    }
}

int maze_can_move(const Maze *maze, int row, int col) {
    //check if (row, col) is within bounds rather than a wall '#'
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (maze->grid[i][j] == '#') {
                printf("Error! Out of bounds!");
                return 0;
            } else {          
                printf("within bounds");
                return 1;
            }
        }
    }
    return 0;
}

int maze_move_lily(Maze *maze, char direction) {
    //update maze, meaning lily's position depends on W/A/S/D. 
    //W is for up, A is for left, S is for down, D is for right

    int target_row = maze->lily_pos.row;
    int target_col = maze->lily_pos.col;
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
        maze->grid[maze->lily_pos.row][maze->lily_pos.col] = '.';

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
        maze->grid[target_row][target_col] = '.';//check if correct 
        return 1;
    }
    return 0;
}

int maze_bfs_hint(const Maze *maze, char *out_direction) {
    if (maze == NULL || out_direction == NULL) return 0;
    int rows = maze->rows;
    int cols = maze->cols;
    int visited[50][50] = {0};
    char first_move[50][50];

    Queue q;
    queue_init(&q); //use queue ADT
    //run BFS algorithm using queue_enqueue and queue_dequeue
    //use maze->rows and maze->cols
    Position start = maze->lily_pos;
    visited[start.row][start.col] = 1;
    queue_enqueue(&q, start);

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, -1, 0, 1};
    char dch[4] = {'W', 'A', 'S', 'D'};

    Position found;
    int foundFlag = 0;
    
    while (!queue_is_empty(&q)) {
        Position cur;
        queue_dequeue(&q, &cur);

        if(maze->grid[cur.row][cur.col] == '*' && 
        !(cur.row == start.row && cur.col == start.col)) {
            found = cur;
            foundFlag = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];

            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                continue;
            }
            if (visited[nr][nc]) {
                continue;
            }
            if (maze->grid[nr][nc] == '#') {
                continue;
            }
            visited[nr][nc] = 1;
            //start neighbors define the first move
            if (cur.row == start.row && cur.col == start.col) {
                first_move[nr][nc] = dch[i];
            } else {
                first_move[nr][nc] = first_move[cur.row][cur.col];
            }
            Position next = {nr, nc};
            queue_enqueue(&q, next);
        }      
    }
       //return the minimum steps to 'E' or -1 if blocked
    if(!foundFlag) return 0;
    *out_direction = first_move[found.row][found.col];
    return 1; 
}

void maze_free(Maze *maze) {
    if (maze->grid == NULL) {
        return;
    }

    for (int i = 0; i < maze->rows; i++) {
        free(maze->grid[i]);
    }

    free(maze->grid);
    maze->grid = NULL;
}
