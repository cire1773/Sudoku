#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int grid[81];
int row_flags[9]; //stores which numbers are used in each row
int col_flags[9]; //stores which numbers are used in each column
int box_flags[9]; //stores which numbers are used in each box


//function to get 3x3 box index from the cell index
int get_box_index(int index){
    int r = index / 9;
    int c = index % 9;
    return (r / 3) * 3 + (c / 3);
}

//checks if a number is safe using bitwise AND
int is_safe(int index, int num){
    int r = index / 9;
    int c = index % 9;
    int b = get_box_index(index);
    int mask = 1 << num; //create a binary mask for the number

    //return 0 if bit is set in any of the three flags
    if ((row_flags[r] & mask) || (col_flags[c] & mask) || (box_flags[b] & mask)){
        return 0;
    }
    return 1;
}

//function that "toggles" a number (bit on or off)
void toggle_number(int index, int num){
    int r = index / 9;
    int c = index % 9;
    int b = get_box_index(index);
    int mask = 1 << num;
    //using XOR to flip the bit
    row_flags[r] ^= mask;
    col_flags[c] ^= mask;
    box_flags[b] ^= mask;
}

void readGrid(FILE *fp){
    int i = 0, num;
    char c;
    while(i < 81){
        c = fgetc(fp);
        if(isdigit(c)){
            num = c - '0';
            grid[i] = num;
            if (num){
                toggle_number(i, num);
            }
            i++;
        }
        else if(c == '.'){
            grid[i] = 0;
            i++;
        }
    }
}

int solve(int index){
    if (index == 81){
        return 1; //success
    }

    //if the cell is already filled, skip to the next one
    if (grid[index]){
        return solve(index + 1);
    }

    for (int num = 1; num <= 9; num++){
        //check if safe
        if (is_safe(index, num)){
            //place the number
            grid[index] = num;
            toggle_number(index, num); //mark the bits as used
            //recurse
            if (solve(index + 1)){
                return 1;
            }
            //backtrack
            grid[index] = 0;
            toggle_number(index, num); //unmarks the bits
        }
    }
    return 0;//trigger the backtracking
}

void printGrid(){
    for (int i = 0; i < 81; i++){
        printf("%d", grid[i]);
        if (i % 9 == 8){
            printf("\n");
        }
        else printf(" ");
    }
}

int main(int argc, char *argv[]){
    FILE *fp;
    if (argc == 2)
        fp = fopen(argv[1], "r");
    else
        fp = stdin;
    
    if (fp == NULL) {
        perror("Error opening file\n");
        return 1;
    }

    int counter = 0;
    readGrid(fp);    

    for (int i = 0; i < 81; i++){
        if(grid[i])
            counter++;
    }

    if (counter < 17){
        printf("Warning: This Sudoku may have multiple solutions\n");
    }

    if (solve(0)){
        printf("Solved:\n");
        printGrid();
    }
    else printf("No solution found.\n");

    return 0;
}