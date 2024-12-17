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

void get_kingdom(char map[MAX_ROWS + 1][MAX_COLUMNS + 1],int kingdom_coordinates[][2], int numKingdom,int kingdom_gold_rate[],int kingdom_food_rate[],int kingdom_workers[],int kingdom_soldiers[]) {

    for (int i = 0; i < numKingdom; i++) {
        int x, y;
        printf("Enter the coordinates of kingdom %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'C';
             printf("enter the gold production rate of kingdom %d : ",i+1);
             scanf("%d",&kingdom_gold_rate[i]);
             printf("enter the food production rate of kingdom %d : ",i+1);
             scanf("%d",&kingdom_food_rate[i]);
             printf("enter the number of workers for kingdom %d : ",i+1);
             scanf("%d",&kingdom_workers[i]);
             printf("enter the number of soldier for kingdom %d : ",i+1);
             scanf("%d",&kingdom_soldiers[i]);
             kingdom_coordinates[i][0] = x;
             kingdom_coordinates[i][1] = y;
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void get_villages(char map[MAX_ROWS + 1][MAX_COLUMNS + 1], int village_goldRates[], int village_foodRates[], int vilage_coordinates[][2]) {
    for (int i = 0; i < numVillages; i++) {
        int x, y, goldRate, foodRate;
        printf("Enter the coordinates of village %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);

        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'V';
            printf("Enter gold production rate for village %d: ",i+1);
            scanf("%d", &goldRate);
            printf("Enter food production rate for this village %d: ",i+1);
            scanf("%d", &foodRate);
            vilage_coordinates[i][0]= x;
            vilage_coordinates[i][1]= y;
            village_goldRates[i] = goldRate;
            village_foodRates[i] = foodRate;
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void VillageInfo(int numVillages, int village_goldRates[], int village_foodRates[], int vilaage_coordinates[][2]) {
    printf("\nVillages Information:\n");
    for (int i = 0; i < numVillages; i++) {
        printf("Village %d -> Gold Rate: %d, Food Rate: %d ,coordinates;(%d,%d)\n", i + 1, village_goldRates[i], village_foodRates[i],vilaage_coordinates[i][0],vilaage_coordinates[i][1]);
    }
}
void kingdominfo(int numkingdom,int kingdom_gold_rate[],int kingdom_food_rate[],int kingdom_gold[],int kingdom_food[],int kingdom_coordinates[][2]){
     printf("\nkingdoms Information:\n");
    for(int i = 0;i < numkingdom;++i)
    {
        printf("kingdom %d -> gold rate : %d,food rate : %d ,current gold : %d ,current food : %d ,coordinates : (%d,%d)\n",i+1,kingdom_gold_rate[i],kingdom_food_rate[i],kingdom_gold[i],kingdom_food[i],kingdom_coordinates[i][0],kingdom_coordinates[i][1]);                                     
    }
}
void kingdom_properties(int numKingdom,int kingdom_workers[],int kingdom_soldiers[])
{
    printf("\nkingdoms property:\n");
    for(int i = 0;i < numKingdom;i++)
    {
        printf("the kingdome %d -> have %d workers and %d soldiers \n",i+1,kingdom_workers[i],kingdom_soldiers[i]);
        printf("\n");
    }
}

void acting_kingdoms(int kingdom_gold[],int kingdom_food[],int numKingdom,int kingdom_workers[],int kingdom_soldiers[])
{
    int act;
    for(int i = 0;i < numKingdom;i++)
    {
    printf("what do you want to act ? : \n");
    printf("enter 1 for buying 1 food with spending 1 gold : \n");
    printf("enter 2 for hiring a worker for your kingdom with spending 3 food : \n");
    printf("enter 3 for hiring a soldier for your kingdom with spending 2 gold : \n");
    printf("enter 4 for creating a road in map with the consider cooardination : \n");
    printf("enter 0 for act nothing and continue : \n");
    scanf("%d",&act);
        switch (act) {
        case 1:
            if (kingdom_gold[i] > 0) {
                kingdom_food[i]++;
                kingdom_gold[i]--;
                printf("Bought 1 food. Remaining gold: %d\n", kingdom_gold[i]);
            } else {
                printf("Not enough gold!\n");
            }
            break;
        case 2:
            if (kingdom_food[i] >= 3) {
                kingdom_workers[i]++;
                kingdom_food[i] -= 3;
                printf("Hired 1 worker. Remaining food: %d\n", kingdom_food[i]);
            } else {
                printf("Not enough food!\n");
            }
            break;
        case 3:
            if (kingdom_gold[i] >= 2) {
                kingdom_soldiers[i]++;
                kingdom_gold[i] -= 2;
                printf("Hired 1 soldier. Remaining gold: %d\n", kingdom_gold[i]);
            } else {
                printf("Not enough gold!\n");
            }
            break;
        case 4:
            printf("not define yet!\n");
            break;
        case 0:
            printf("No action taken.\n");
            break;
        default:
            printf("Invalid action! Try again.\n");
        }
    }
}
void collect_resources(int numKingdom, int numVillages, 
                       int kingdom_gold_rate[], int kingdom_food_rate[], 
                       int kingdom_gold[], int kingdom_food[], 
                       int village_goldRates[], int village_foodRates[], 
                       int village_coordinates[][2], int kingdom_coordinates[][2], 
                       int village_status[]) {
    for (int i = 0; i < numKingdom; i++) {
            kingdom_gold[i] += kingdom_gold_rate[i];
            kingdom_food[i] += kingdom_food_rate[i];
        for (int j = 0; j < numVillages; j++) {
            int vx = village_coordinates[j][0];
            int vy = village_coordinates[j][1];
            int kx = kingdom_coordinates[i][0];
            int ky = kingdom_coordinates[i][1];

            
            if (abs(vx - kx) + abs(vy - ky) <= 2) {
                if (village_status[j] == 0) {
                    printf("Village at (%d, %d) is within range of Kingdom %d. Do you want to conquer it? (1 = Yes, 0 = No): ", 
                           vx, vy, i + 1);
                    int choice;
                    scanf("%d", &choice);

                    if (choice == 1) {
                        village_status[j] = 1; //the village conquered!
                        printf("Village at (%d, %d) is now conquered by Kingdom %d.\n", vx, vy, i + 1);
                    } else {
                        printf("Village at (%d, %d) remains unconquered.\n", vx, vy);
                    }
                    if (village_status[j] == 1) {
                    kingdom_gold_rate[i] += village_goldRates[j];
                    kingdom_food_rate[i] += village_foodRates[j];
                }
                }

            }
        }
    }
}
void distance_maker()
{
    printf("________________________________________________________________________________________________________________________________");
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

        int kingdom_gold_rate[numKingdom];
        int kingdom_food_rate[numKingdom];
        int kingdom_workers[numKingdom];
        int kingdom_soldiers[numKingdom];
        int kingdom_coordinates[numKingdom][2];
        int kingdom_gold[numKingdom];
        int kingdom_food[numKingdom];
        get_kingdom(map, kingdom_coordinates,numKingdom,kingdom_gold_rate,kingdom_food_rate,kingdom_workers,kingdom_soldiers);
        for(int i = 0; i < numKingdom; i++)
        {
            kingdom_gold[i] = 0;
            kingdom_food[i] = 0;
        }

        printf("Enter the number of villages: ");
        scanf("%d", &numVillages);

        int village_goldRates[numVillages];
        int village_foodRates[numVillages];
        int village_coordinates[numVillages][2];

        get_villages(map, village_goldRates, village_foodRates, village_coordinates);
        genrate_hardness(map);
        print_map(map);
        VillageInfo(numVillages, village_goldRates, village_foodRates, village_coordinates);
        kingdominfo(numKingdom,kingdom_gold_rate,kingdom_food_rate,kingdom_gold,kingdom_food,kingdom_coordinates);
        int village_status[numVillages];
        for (int i = 0; i < numVillages; i++) {
        village_status[i] = 0;
        }
        distance_maker();
        //GAME IS STARTING 🗡️
        printf("\n--- Game Turn ---\n");
        for(int i = 0;i < numKingdom;i++) {
        printf("its turn kingdom %d\n", i + 1);
        collect_resources(numKingdom, numVillages, 
                          kingdom_gold_rate, kingdom_food_rate, 
                          kingdom_gold, kingdom_food, 
                          village_goldRates, village_foodRates, 
                          village_coordinates, kingdom_coordinates, 
                          village_status);
        kingdominfo(numKingdom,kingdom_gold_rate,kingdom_food_rate,kingdom_gold,kingdom_food,kingdom_coordinates);
        kingdom_properties(numKingdom,kingdom_workers,kingdom_soldiers);
        acting_kingdoms(kingdom_gold,kingdom_food,numKingdom,kingdom_workers,kingdom_soldiers);
        printf("\nDo you want to continue? (1 = Yes, 0 = No): ");
        if(i == numKingdom - 1) i = -1;
        int continueGame;
        scanf("%d", &continueGame);
        if (!continueGame) break;
        distance_maker();
    }
 }
    return 0;
}
