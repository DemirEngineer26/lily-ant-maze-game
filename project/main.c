#include <stdio.h>
#include <ctype.h>
#include "maze.h"
#include "stack.h"
#include "queue.h"

int main (int argc, char *argv[]) {
    Maze maze; 
    Stack undo_stack;
    int running = 1;
    char choice;

    // Initialize stack
    stack_init(&undo_stack);

    // Select a maze file from a menu
    const char *filename = "maze_normal.txt"; // Default
    int menu_choice;
    //extra credit: multiple files
    printf("--- SELECT A MAZE ---\n");
    printf("1. Normal Maze (maze_normal.txt)\n");
    printf("2. Blocked Maze (maze_blocked.txt)\n");
    printf("3. Large Maze (maze_10x20.txt)\n");
    printf("Select option (1-3): ");
    
    if (scanf("%d", &menu_choice) == 1) {
        if (menu_choice == 2) {
            filename = "maze_blocked.txt";
        } else if (menu_choice == 3) {
            filename = "maze_10x20.txt";
        }
    }
    if (!maze_load(&maze, filename)) {
        printf("Error: Could not load maze file '%s'.\n", filename);
        return 1;
    }

    printf("Welcome to Lily the Ant Maze Game!\n");
    //main game loop
    while (running) {
        printf("\n--- CURRENT MAZE ---\n");
        maze_print(&maze);
        printf("Score: %d\n", maze.score);
        printf("Controls: [W/A/S/D] Move | [U] Undo | [H] Hint | [Q] Quit\n");
        printf("Enter command: ");
        scanf(" %c", &choice);

        switch (toupper(choice)) {
            case 'W':
            case 'A':
            case 'S':
            case 'D': {
                //save old position before moving
                Position old_pos = maze.lily_pos;

                if (maze_move_lily(&maze, choice)) {
                    //move succedded; save old position to stack
                    stack_push(&undo_stack, old_pos);
                } else {
                    printf("Blocked! You cannot move there.\n");
                }
                break;
            }
            case 'U': {
                Position prev_pos;
                if (stack_pop(&undo_stack, &prev_pos)) {
                    //restore lilys position
                    maze.grid[maze.lily_pos.row][maze.lily_pos.col] = '.';
                    maze.lily_pos = prev_pos;
                    maze.grid[prev_pos.row][prev_pos.col] = 'L';
                    printf("Undid last move!\n");
                } else {
                    printf("Nothing to undo!\n");
                }
                break;
            }
            case 'H':
                printf("Hint feature requested (BFS search)\n");
                //call BFS queue hint logic here
                char hint;
                if (maze_bfs_hint(&maze, & hint)) {
                    printf("Hint: try moving '%c'\n", hint);
                } else {
                    printf("No reachable points left to collect.\n");
                }
                break;
            case 'Q':
                running = 0;
                break;
            
            default:
                printf("Invalid option! Try W, A, S, D, U, H, or Q.\n");
                break;
        }
    }

    printf("\nGame Over! Final Score: %d\n", maze.score);
    // --- EXTRA CREDIT: HIGH SCORE SAVE/LOAD ---
    int high_score = 0;
    
    // 1. Try to load the existing high score
    FILE *f_read = fopen("highscore.txt", "r");
    if (f_read != NULL) {
        fscanf(f_read, "%d", &high_score);
        fclose(f_read);
    }

    // 2. Compare and save if the player beat it
    if (maze.score > high_score) {
        high_score = maze.score;
        FILE *f_write = fopen("highscore.txt", "w");
        if (f_write != NULL) {
            fprintf(f_write, "%d", high_score);
            fclose(f_write);
        }
        printf("🏆 NEW HIGH SCORE: %d! 🏆\n", high_score);
    } else {
        printf("Highest Score to beat: %d\n", high_score);
    }
    //clean up dynamically allocated memory
    maze_free(&maze);

    return 0;
}