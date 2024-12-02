#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

// Function to create and print the map
void get_map(int rows, int columns) {
    char map[rows][columns];

    // Fill the map with 'x'
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            map[i][j] = 'x';
        }
    }

    // Print the map
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, columns;
    printf("Please enter the number of rows and columns: \n");
    scanf("%d %d", &rows, &columns);

    if (rows <= 0 || columns <= 0) {
        printf("Rows and columns must be positive integers.\n");
        return 1;
    }

    get_map(rows, columns);
    return 0;
}

