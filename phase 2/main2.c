#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 17
#define MAX_COLUMNS 17

int rows, columns, numVillages, numKingdom;

void generate_map(char map[MAX_ROWS + 1][MAX_COLUMNS + 1]) {
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            if (i == 0 || j == 0) {
                map[i][j] = ' ';
            } else {
                map[i][j] = 'O';
            }
        }

    }
}

int generate_number() {
    double r = (double)rand() / RAND_MAX;
    if (r < 0.65)
        return 1;
    else if (r < 0.9)
        return 2;
    else if (r < 0.95)
        return 3;
    else
        return 4;
}

void genrate_hardness(char map[MAX_ROWS + 1][MAX_COLUMNS + 1]){
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            if (map[i][j]=='O'){
                int num = generate_number();
                map[i][j] = num + '0'; 

            }
        }
    }
}
void generate_road(char map[MAX_ROWS + 1][MAX_COLUMNS + 1], int vilage_coordinates[][2], int kingdom_coordinates[][2]) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
    int queue[MAX_ROWS * MAX_COLUMNS][2];
    int front, rear;

    for (int k = 0; k < numKingdom; k++) {
        for (int v = 0; v < numVillages; v++) {
            int start_x = kingdom_coordinates[k][0];
            int start_y = kingdom_coordinates[k][1];
            int end_x = vilage_coordinates[v][0];
            int end_y = vilage_coordinates[v][1];

            int visited[MAX_ROWS + 1][MAX_COLUMNS + 1] = {0}; 
            int prev[MAX_ROWS + 1][MAX_COLUMNS + 1][2];      

            front = rear = 0;
            queue[rear][0] = start_x;
            queue[rear][1] = start_y;
            rear++;
            visited[start_x][start_y] = 1;

            int found = 0;
            while (front < rear && !found) {
                int x = queue[front][0];
                int y = queue[front][1];
                front++;

                for (int d = 0; d < 4; d++) {
                    int new_x = x + directions[d][0];
                    int new_y = y + directions[d][1];

                    if (new_x >= 1 && new_x <= rows && new_y >= 1 && new_y <= columns &&
                        !visited[new_x][new_y] && map[new_x][new_y] != 'X') {
                        visited[new_x][new_y] = 1;
                        prev[new_x][new_y][0] = x;
                        prev[new_x][new_y][1] = y;
                        queue[rear][0] = new_x;
                        queue[rear][1] = new_y;
                        rear++;

                        if (new_x == end_x && new_y == end_y) {
                            found = 1;
                            break;
                        }
                    }
                }
            }

            if (found) {
                int x = end_x, y = end_y;
                while (x != start_x || y != start_y) {
                    if (map[x][y] != 'C' && map[x][y] != 'V') {
                        map[x][y] = 'R';
                    }
                    int temp_x = prev[x][y][0];
                    int temp_y = prev[x][y][1];
                    x = temp_x;
                    y = temp_y;
                }
            }
        }
    }
}

void print_map(char map[MAX_ROWS + 1][MAX_COLUMNS + 1]) {
    printf("   ");
    for (int j = 1; j <= columns; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= rows; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= columns; j++) {
            switch (map[i][j]) {
                case 'R':
                    printf("🟫 ");
                    break;
                case '1':
                    printf("🟩 ");
                    break;
                case '2':
                    printf("🟨 ");
                    break;
                case '3':
                    printf("🟧 ");
                    break;
                case '4':
                    printf("🟥 ");
                    break;
                case 'X':
                    printf("❌ ");
                    break;
                case 'C':
                    printf("🏰 ");
                    break;
                case 'V':
                    printf("🏠 ");
                    break;
                default:
                    printf("❓ ");
                    break;
            }
        }
        printf("\n");
    }
}

void get_blocked(char map[MAX_ROWS + 1][MAX_COLUMNS + 1]) {
    int numBlocked;
    printf("How many blocked cells: ");
    scanf("%d", &numBlocked);

    for (int i = 0; i < numBlocked; i++) {
        int x, y;
        printf("Enter the coordinates of blocked cell %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'X';
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void get_kingdom(char map[MAX_ROWS + 1][MAX_COLUMNS + 1],int kingdom_coordinates[][2], int numKingdom) {

    for (int i = 0; i < numKingdom; i++) {
        int x, y;
        printf("Enter the coordinates of kingdom %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'C';
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
        kingdom_coordinates[i][0] = x;
        kingdom_coordinates[i][1] = y;
    }
}

void get_villages(char map[MAX_ROWS + 1][MAX_COLUMNS + 1], int goldRates[], int foodRates[], int vilage_coordinates[][2]) {
    for (int i = 0; i < numVillages; i++) {
        int x, y, goldRate, foodRate;
        printf("Enter the coordinates of village %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);

        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'V';
            printf("Enter gold production rate for this village: ");
            scanf("%d", &goldRate);
            printf("Enter food production rate for this village: ");
            scanf("%d", &foodRate);
            vilage_coordinates[i][0]=x;
            vilage_coordinates[i][1]=y;
            goldRates[i] = goldRate;
            foodRates[i] = foodRate;
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void VillageInfo(int numVillages, int goldRates[], int foodRates[], int vilaage_coordinates[][2]) {
    printf("\nVillage Information:\n");
    for (int i = 0; i < numVillages; i++) {
        printf("Village %d -> Gold Rate: %d, Food Rate: %d ,coordinates;(%d,%d)\n", i + 1, goldRates[i], foodRates[i],vilaage_coordinates[i][0],vilaage_coordinates[i][1]);
    }
}

int main() {
    srand(time(NULL));
    int action;
    printf("welcome to A road to salvation game\n1.Enter to game\n2.Exit\nenter your action: ");
    scanf("%d", &action);

    if (action == 1) {
        printf("Enter rows (max %d): ", MAX_ROWS);
        scanf("%d", &rows);
        if (rows > MAX_ROWS) rows = MAX_ROWS;

        printf("Enter columns (max %d): ", MAX_COLUMNS);
        scanf("%d", &columns);
        if (columns > MAX_COLUMNS) columns = MAX_COLUMNS;

        char map[MAX_ROWS + 1][MAX_COLUMNS + 1];

        generate_map(map);
        get_blocked(map);
        printf("Enter the number of kingdoms: ");
        scanf("%d", &numKingdom);
        int kingdom_coordinates[numKingdom][2];
        get_kingdom(map, kingdom_coordinates, numKingdom);

        printf("Enter the number of villages: ");
        scanf("%d", &numVillages);

        int goldRates[numVillages];
        int foodRates[numVillages];
        int vilage_coordinates[numVillages][2];

        get_villages(map, goldRates, foodRates, vilage_coordinates);
        genrate_hardness(map);
        generate_road(map,vilage_coordinates, kingdom_coordinates);
        print_map(map);
        VillageInfo(numVillages, goldRates, foodRates, vilage_coordinates);
    }

    return 0;
}
