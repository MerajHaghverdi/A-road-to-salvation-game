#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

int rows,columns,numVillages;
// function to genrating empty map
void generate_map(char map[rows + 1][columns + 1]) {
    for (int i=0; i<=rows; i++){
        for (int j=0; j<=columns; j++){
            if(i == 0 || j == 0)
            {
                map[i][j] = ' ';
            }
            else
            {
                map[i][j] = 'O';
            }
        }
    }
}
// Function to print the map
void print_map(char map[rows + 1][columns + 1]) {
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            if (i == 0 && j > 0) {
                printf("%2d ", j);
            } else if (j == 0 && i > 0) {
                printf("%2d ", i);
            }
            else if(i ==0 && j == 0)
            {
                printf("%2d ", 0);
            }
             else {
                printf("%2c ", map[i][j]);
            }
        }
        printf("\n");
    }
}
//get blocked
void get_blocked (char map[rows + 1][columns + 1]) {
    int numBlocked;
    printf("How many blocked cells: ");
    scanf("%d", &numBlocked);

    for (int i = 0; i < numBlocked; i++) {
        int x, y;
        printf("Enter the coordinates of blocked cell  %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (map[x][y] == 'O') {
            map[x][y] = 'X';
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}
void get_kingdom(char map[rows + 1][columns + 1]) {
    int num_kings;
    printf("Enter the number of kingdoms: \n");
    scanf("%d", &num_kings);

    for (int i = 0; i < num_kings; i++) {
        int x, y;
        printf("Enter the coordinates of kingdoms %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (map[x][y] == 'O') {
            map[x][y] = 'C';
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void get_villages(char map[rows + 1][columns + 1],int numVillages, int goldRates[], int foodRates[]) {

    for (int i = 0; i < numVillages; i++) {
        int x, y, goldRate, foodRate;
        printf("Enter the coordinates of village %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);

        if (map[x][y] == 'O') {
            map[x][y] = 'V';
            printf("Enter gold production rate for this village: ");
            scanf("%d", &goldRate);
            printf("Enter food production rate for this village: ");
            scanf("%d", &foodRate);

            goldRates[i] = goldRate;
            foodRates[i] = foodRate;
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}
void VillageInfo(int numVillages, int goldRates[], int foodRates[]) {
    printf("\nVillage Information:\n");
    for (int i = 0; i < numVillages; i++) {
        printf("Village %d -> Gold Rate: %d, Food Rate: %d\n", i + 1, goldRates[i], foodRates[i]);
    }
}
int main()
{

    int action;
        printf("welcome to A road to salvation game\n1.Enter to game\n2.Exit\nenter your acyion:");
        scanf("%d",&action);
        if (action==1) {
            printf("enter rows =");
            scanf("%d", &rows);
            printf("enter columns =");
            scanf("%d", &columns);
            char map[rows][columns];
            generate_map(map);
            get_blocked(map);
            get_kingdom(map);
            printf("Enter the number of villages: ");
            scanf("%d", &numVillages);
            int goldRates[numVillages];
            int foodRates[numVillages];
            get_villages(map,numVillages,goldRates,foodRates);
            print_map(map);
            VillageInfo(numVillages, goldRates,foodRates);
        }

    return 0;
}

