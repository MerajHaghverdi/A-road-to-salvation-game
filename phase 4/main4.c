#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 17
#define MAX_COLUMNS 17
#define MAX_KINGDOMS 4
#define MAX_VILLAGES 20

char map[MAX_ROWS + 1][MAX_COLUMNS + 1];
char hardnes_backup[MAX_COLUMNS+1][MAX_COLUMNS+1];
int rows, columns, numVillages, numKingdom, turn, new_road_x,new_road_y;
char Kingdoms_name[4]={'A','B','C','D'};
char Kingdoms_road_name[4]={'a','b','c','d'};
int village_goldRates[MAX_VILLAGES];
int village_foodRates[MAX_VILLAGES];
int village_coordinates[MAX_VILLAGES][2];
int conquered_village[MAX_KINGDOMS][MAX_VILLAGES][2];
int counter_conquered_village[MAX_KINGDOMS];
int kingdom_gold_rate[MAX_KINGDOMS];
int kingdom_food_rate[MAX_KINGDOMS];
int kingdom_workers[MAX_KINGDOMS];
int kingdom_soldiers[MAX_KINGDOMS];
int kingdom_coordinates[MAX_KINGDOMS][2];
int kingdom_gold[MAX_KINGDOMS];
int kingdom_food[MAX_KINGDOMS];
int current_location[MAX_KINGDOMS][2];

void generate_map() {
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

void genrate_hardness(){
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            if (map[i][j]=='O'){
                int num = generate_number();
                map[i][j] = num + '0'; 
                hardnes_backup[i][j] = num + '0';
            }
        }
    }
}

void print_map() {
    printf("   ");
    for (int j = 1; j <= columns; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= rows; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= columns; j++) {
            switch (map[i][j]) {
                case 'a':
                    printf("🔵 ");
                    break;
                case 'b':
                    printf("🔴 ");
                    break;
                case 'c':
                    printf("⚪ ");
                    break;
                case 'd':
                    printf("🟣 ");
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
                case 'A':
                    printf("🏰 ");
                    break;
                case 'B':
                    printf("🏰 ");
                    break;
                case 'C':
                    printf("🏰 ");
                    break;
                 case 'D':
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

void conquer_villages() {
    for (int i = 0; i < numKingdom; i++) {
        for (int j = 0; j < numVillages; j++) {
            int vx = village_coordinates[j][0];
            int vy = village_coordinates[j][1];
            int cx = current_location[i][0];
            int cy = current_location[i][1];

            if (abs(vx - cx)+abs(vy - cy)==0) {
                    conquered_village[i][counter_conquered_village[i]][0] = cx;
                    conquered_village[i][counter_conquered_village[i]][1] = cy;
                    counter_conquered_village[i]++;

            
                    kingdom_gold_rate[i] += village_goldRates[j];
                    kingdom_food_rate[i] += village_foodRates[j];
                }
            }
        }
    }


void move_kingdom() {
    int new_x, new_y;
    int move, scape;
    int up,down,right,left;

        printf("Choose the arrow keys to move (kingdom %d) or choose Esc to get out:\n", turn + 1);
        scape = 1;

        while (scape) {
            if (_kbhit()) {
                move = _getch(); 
                if (move == 0 || move == 224) {
                    move = _getch();

                    new_x = current_location[turn][0];
                    new_y = current_location[turn][1];
                    up = 0,down = 0,right = 0,left = 0;
                    switch (move) {
                        case (72): 
                            new_x--;
                            up++;
                            break;
                        case (80): 
                            new_x++;
                            down++;
                            break;
                        case (75): 
                            new_y--;
                            left++;
                            break;
                        case (77): 
                            new_y++;
                            right++;
                            break;
                        case (27): 
                            scape = 0;
                            break;
                        default:
                            printf("Invalid move\n");
                            continue;
                    }

                    if (!scape) break;
                    new_road_x=new_x;
                    new_road_y=new_y;
                    if (new_x >= 1 && new_y >= 1 && new_x <= rows && new_y <= columns) {
                        if (map[new_x][new_y] == Kingdoms_road_name[turn]) {
                            printf("Moving on road at (%d, %d).\n", new_x, new_y);
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            continue;
                        }
                        int sw=0;
                        if (map[new_x][new_y] == 'V') {
                             for (int j=0; j<counter_conquered_village[turn]; j++){
                                if (conquered_village[turn][j][0]==new_x && conquered_village[turn][j][1]==new_y){
                                    sw=1;
                                }
                            }
                            if (sw==1){
                            printf("you are now in your village with coordinates of (%d, %d).\n", new_x, new_y);
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            continue;
                            }
                        }
                        if(map[new_x][new_y] == Kingdoms_name[turn])
                        {
                            printf("you are now in your kingdom! \n");
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            continue;
                        }
                        if (map[new_x][new_y] >= '1' && map[new_x][new_y] <= '4') {
                            map[new_x][new_y] -= kingdom_workers[turn];
                            if (map[new_x][new_y] <= '0') {
                                if (turn==0){
                                   map[new_x][new_y] = 'a';
                                } else if (turn==1){
                                    map[new_x][new_y] = 'b';
                                } else if (turn==2){
                                    map[new_x][new_y] = 'c';
                                } else if (turn==3){
                                    map[new_x][new_y] = 'd';
                                }

                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            printf("Built road at (%d, %d).\n", new_x, new_y);
                            break;
                            }
                            else{
                                if(up == 1)new_x++;
                                if(down == 1)new_x--;
                                if(right == 1)new_y--;
                                if(left == 1)new_y++;
                                break;
                            }
                        }
                        if (map[new_x][new_y] == 'V') {
                            
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;

                            if (counter_conquered_village[turn]==0){
                                printf("the vilage with cooardination : (%d, %d) is conquered by kingdom %d .\n", current_location[turn][0], current_location[turn][1],turn + 1);
                                            conquer_villages();
                            } else {
                            for (int j=0; j<counter_conquered_village[turn]; j++){
                                if (conquered_village[turn][j][0]!=new_x || conquered_village[turn][j][1]!=new_y){
                                            printf("the vilage with cooardination : (%d, %d) is conquered by kingdom %d .\n",current_location[turn][0],current_location[turn][1],turn + 1);  
                                            conquer_villages();
                                            break;
                                }
                            }
                            }
                            break; 
                        }
                        if(map[new_x][new_y] == 'X') {
                            printf("Cannot move to this position. Blocked cells. .\n");
                            continue; 
                        }
                        if(map[new_x][new_y] != Kingdoms_road_name[turn]) {
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            if(map[new_x][new_y] != 'A' && map[new_x][new_y] != 'B' && map[new_x][new_y] != 'C' && map[new_x][new_y] != 'D') {
                            map[new_x][new_y] = Kingdoms_road_name[turn];
                            }
                            break;
                        }
                    }
                    else {
                        printf("Out of bounds! Try again.\n");
                    }
                }
            }
        }
}

void remove_roads(int kingdom, int war_x, int war_y) {

    int queue[MAX_ROWS * MAX_COLUMNS][2];
    int front = 0, rear = 0;

    int parent[MAX_ROWS + 1][MAX_COLUMNS + 1][2];
    int visited[MAX_ROWS + 1][MAX_COLUMNS + 1] = {0};

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    // start point
    queue[rear][0] = war_x;
    queue[rear][1] = war_y;
    rear++;
    visited[war_x][war_y] = 1;
    
    //stop point
    int stop_x = -1, stop_y = -1;
    int found_stop = 0;
    
    while (front < rear && !found_stop) {
        int current_x = queue[front][0];
        int current_y = queue[front][1];
        front++;
        
        // if (map[current_x][current_y] == Kingdoms_road_name[kingdom]) {
        //     int connected_roads = 0;
        //     for (int i = 0; i < 4; i++) {
        //         int adj_x = current_x + dx[i];
        //         int adj_y = current_y + dy[i];
        //         if (adj_x >= 1 && adj_x <= rows && adj_y >= 1 && adj_y <= columns) {
        //             if (map[adj_x][adj_y] == Kingdoms_road_name[kingdom] ||
        //                 map[adj_x][adj_y] == Kingdoms_name[kingdom] ||
        //                 (map[adj_x][adj_y] == 'V' && isVillageOwnedByKingdom(kingdom, adj_x, adj_y))) {
        //                 connected_roads++;
        //             }
        //         }
        //     }

        //     if (connected_roads > 2) {
        //         stop_x = current_x;
        //         stop_y = current_y;
        //         found_stop = 1;
        //         continue;
        //     }
        // }
        
        // barasi hamsaye
        for (int i = 0; i < 4; i++) {
            int new_x = current_x + dx[i];
            int new_y = current_y + dy[i];
            
            if (new_x >= 1 && new_x <= rows && new_y >= 1 && new_y <= columns && 
                !visited[new_x][new_y]) {
                
                // rostaye bazande
                if (map[new_x][new_y] == 'V') {
                    if (isVillageOwnedByKingdom(kingdom, new_x, new_y)) {
                        stop_x = new_x;
                        stop_y = new_y;
                        found_stop = 1;
                        parent[new_x][new_y][0] = current_x;
                        parent[new_x][new_y][1] = current_y;
                        break;
                    }
                }
                // maghar bazande
                else if (map[new_x][new_y] == Kingdoms_name[kingdom]) {
                    stop_x = new_x;
                    stop_y = new_y;
                    found_stop = 1;
                    parent[new_x][new_y][0] = current_x;
                    parent[new_x][new_y][1] = current_y;
                    break;
                }
                // age rah bood edame bede
                else if (map[new_x][new_y] == Kingdoms_road_name[kingdom]) {
                    queue[rear][0] = new_x;
                    queue[rear][1] = new_y;
                    rear++;
                    visited[new_x][new_y] = 1;
                    parent[new_x][new_y][0] = current_x;
                    parent[new_x][new_y][1] = current_y;
                }
            }
        }
    }
    
    // delete road
    if (found_stop) {
        int current_x = stop_x;
        int current_y = stop_y;
        
        current_location[kingdom][0] = stop_x;
        current_location[kingdom][1] = stop_y;
        
        while (current_x != war_x || current_y != war_y) {
            if (map[current_x][current_y] == Kingdoms_road_name[kingdom]) {
                map[current_x][current_y] = hardnes_backup[current_x][current_y];
            }
            int temp_x = parent[current_x][current_y][0];
            int temp_y = parent[current_x][current_y][1];
            current_x = temp_x;
            current_y = temp_y;
        }
        
        printf("Kingdom %d has lost! Roads have been removed up to location (%d, %d).\n", 
               kingdom + 1, stop_x, stop_y);
    }
}

int isVillageOwnedByKingdom(int kingdom, int x, int y) {
    for (int i = 0; i < counter_conquered_village[kingdom]; i++) {
        if (conquered_village[kingdom][i][0] == x && 
            conquered_village[kingdom][i][1] == y) {
            return 1;
        }
    }
    return 0;
}

void start_battle(int kingdom1, int kingdom2, int war_x, int war_y) {

    int soldiers_kingdom1 = kingdom_soldiers[kingdom1];
    int soldiers_kingdom2 = kingdom_soldiers[kingdom2];

    if (soldiers_kingdom1 > soldiers_kingdom2) {
        
        int loss_kingdom2 = soldiers_kingdom1 - soldiers_kingdom2;

        if(loss_kingdom2 > kingdom_soldiers[kingdom2]){
            loss_kingdom2 = kingdom_soldiers[kingdom2];
        }
        kingdom_soldiers[kingdom2] -= loss_kingdom2;
        if (kingdom_soldiers[kingdom2] < 0) kingdom_soldiers[kingdom2] = 0;

        printf("Kingdom %d wins the battle!\n", kingdom1 + 1);
        printf("Kingdom %d loses %d soldiers\nKingdom %d loses 0 soldiers.\n",
               kingdom2 + 1, loss_kingdom2, kingdom1 + 1);
        remove_roads(kingdom2, war_x,war_y);
        // map[new_road_x][new_road_y]=Kingdoms_road_name[kingdom1];

    } else if (soldiers_kingdom1 < soldiers_kingdom2) {
        int loss_kingdom1 = soldiers_kingdom2 - soldiers_kingdom1; 

        if(loss_kingdom1 > kingdom_soldiers[kingdom1]){
            loss_kingdom1 = kingdom_soldiers[kingdom1];
        }
        kingdom_soldiers[kingdom1] -= loss_kingdom1;
        if (kingdom_soldiers[kingdom1] < 0) kingdom_soldiers[kingdom1] = 0;

        printf("Kingdom %d wins the battle!\n", kingdom2 + 1);
        printf("Kingdom %d loses %d soldiers\nKingdom %d loses 0 soldiers.\n",
               kingdom1 + 1, loss_kingdom1, kingdom2 + 1);
        remove_roads(kingdom1,war_x,war_y);
    } else {
        // Draw
        printf("The battle ends in a draw! No losses for either kingdom.\n");
        remove_roads(kingdom1,war_x,war_y);
        remove_roads(kingdom2,war_x,war_y);
    }
}

void check_village_war(int current_kingdom) {
    int current_x = current_location[current_kingdom][0];
    int current_y = current_location[current_kingdom][1];

    for (int i = 0; i < numVillages; i++) {
        int village_x = village_coordinates[i][0];
        int village_y = village_coordinates[i][1];
    
        if (abs(current_x - village_x) + abs(current_y - village_y) == 1 && conquered_village[current_kingdom][i][0] != village_x && conquered_village[current_kingdom][i][1] != village_y) {

            int village_owner = -1;

        
            for (int other_kingdom = 0; other_kingdom < numKingdom; other_kingdom++) {
                for (int k = 0; k < counter_conquered_village[other_kingdom]; k++) {
                    if(other_kingdom == current_kingdom)continue;
                    if (conquered_village[other_kingdom][k][0] == village_x &&
                        conquered_village[other_kingdom][k][1] == village_y) {
                        village_owner = other_kingdom; 
                        break;
                    }
                }
                if (village_owner != -1) break; 
            }

            if (village_owner == -1) {
                conquer_villages();
                return; 
            }

            
            printf("Village War! Kingdom %d is fighting with Kingdom %d for the village with the cooardinate (%d %d).😨\n", current_kingdom + 1, village_owner + 1,village_x,village_y);
            start_battle(current_kingdom, village_owner,current_x,current_y);

            
            if (kingdom_soldiers[current_kingdom] > kingdom_soldiers[village_owner]) {
                printf("Kingdom %d wins and conquers the village with the cooardination (%d %d)!🥳\n", current_kingdom + 1,village_x,village_y);

                
                for (int k = 0; k < counter_conquered_village[village_owner]; k++) {
                    if (conquered_village[village_owner][k][0] == village_x &&
                        conquered_village[village_owner][k][1] == village_y) {
                
                        kingdom_gold_rate[village_owner] -= village_goldRates[i];
                        kingdom_food_rate[village_owner] -= village_foodRates[i];
                        kingdom_gold_rate[current_kingdom] += village_goldRates[i];
                        kingdom_food_rate[current_kingdom] += village_foodRates[i];

                        for (int m = k; m < counter_conquered_village[village_owner] - 1; m++) {
                            conquered_village[village_owner][m][0] = conquered_village[village_owner][m + 1][0];
                            conquered_village[village_owner][m][1] = conquered_village[village_owner][m + 1][1];
                        }
                        counter_conquered_village[village_owner]--;
                        break;
                    }
                }

                conquered_village[current_kingdom][counter_conquered_village[current_kingdom]][0] = village_x;
                conquered_village[current_kingdom][counter_conquered_village[current_kingdom]][1] = village_y;
                counter_conquered_village[current_kingdom]++;
                
            }
            else{
                printf("kingdom %d lose the battle and the village with cooardination (%d,%d) is still belong to kingdom %d\n",current_kingdom+1,village_x,village_y,village_owner+1);
            }
            return; 
        }
    }
}


void check_war(int current_kingdom) {
    int current_x = current_location[current_kingdom][0];
    int current_y = current_location[current_kingdom][1];


    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {

    
            for (int other_kingdom = 0; other_kingdom < numKingdom; other_kingdom++) {
                if (current_kingdom == other_kingdom) continue;

                if (map[i][j] == Kingdoms_name[other_kingdom] && 
                    abs(current_x - i) + abs(current_y - j) == 1) {
                    printf("All-Out War! Kingdom %d and Kingdom %d are fighting near a kingdom.\n", current_kingdom + 1, other_kingdom + 1);
                    start_battle(current_kingdom, other_kingdom, current_x, current_y);
                    return;
                }
            if(map[i][j] == 'V' && abs(current_x - i) + abs(current_y - j) == 1){
            check_village_war(current_kingdom);
            return;
            }
                if (current_kingdom == other_kingdom) continue;

                if (map[i][j] == Kingdoms_road_name[other_kingdom] && 
                    abs(current_x - i) + abs(current_y - j) == 1) {
                    printf("Road War! Kingdom %d and Kingdom %d are fighting near a road.\n", current_kingdom + 1, other_kingdom + 1);
                    start_battle(current_kingdom, other_kingdom, current_x, current_y);
                    return; 
                }
            }

        }

    }
}

void get_blocked() {
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

void get_kingdom() {

    for (int i = 0; i < numKingdom; i++) {
        int x, y;
        
        printf("Enter the coordinates of kingdom %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);
        if (x>rows || y>columns){
            printf("out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
             map[x][y] = Kingdoms_name[i];
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

void get_villages() {
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
            village_coordinates[i][0]= x;
            village_coordinates[i][1]= y;
            village_goldRates[i] = goldRate;
            village_foodRates[i] = foodRate;
        } else {
            printf("Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void VillageInfo() {
    printf("\nVillages Information:\n");
    for (int i = 0; i < numVillages; i++) {
        printf("Village %d -> Gold Rate: %d, Food Rate: %d ,coordinates;(%d,%d)\n", i + 1, village_goldRates[i], village_foodRates[i],village_coordinates[i][0],village_coordinates[i][1]);
    }
}
void kingdominfo(){
     printf("\nkingdoms Information:\n");
    for(int i = 0;i < numKingdom;i++)
    {
        printf("kingdom %d -> gold rate : %d,food rate : %d ,current gold : %d ,current food : %d ,coordinates : (%d,%d)\n",i+1,kingdom_gold_rate[i],kingdom_food_rate[i],kingdom_gold[i],kingdom_food[i],kingdom_coordinates[i][0],kingdom_coordinates[i][1]);
        printf("current location of kingdom %d is -> (%d,%d)\n",i+1,current_location[i][0],current_location[i][1]);                                     
    }
}
void kingdom_properties()
{
    printf("\nkingdoms property:\n");
    for(int i = 0;i < numKingdom;i++)
    {
        printf("the kingdome %d -> have %d workers and %d soldiers \n",i+1,kingdom_workers[i],kingdom_soldiers[i]);
        printf("kingdom %d have %d villages in total.\n",i+1,counter_conquered_village[i]);
        for(int j = 0;j < counter_conquered_village[i];j++)
        {
            printf("the kingdom %d have village with cooardination (%d,%d) \n",i+1,conquered_village[i][j][0],conquered_village[i][j][1]);
        }
        printf("\n");
    }
}

void acting_kingdoms()
{
    int act;
        print_map(map);
    printf("what do you want to act ? : \n");
    printf("enter 1 for buying 1 food with spending 1 gold : \n");
    printf("enter 2 for hiring a worker for your kingdom with spending 3 food : \n");
    printf("enter 3 for hiring a soldier for your kingdom with spending 2 gold : \n");
    printf("enter 4 for creating a road in map with the consider cooardination : \n");
    printf("enter 0 for act nothing and continue : \n");
    scanf("%d",&act);
        switch (act) {
        case 1:
            if (kingdom_gold[turn] > 0) {
                kingdom_food[turn]++;
                kingdom_gold[turn]--;
                printf("Bought 1 food. Remaining gold: %d\n", kingdom_gold[turn]);
            } else {
                printf("Not enough gold!\n");
            }
            break;
        case 2:
            if (kingdom_food[turn] >= 3) {
                kingdom_workers[turn]++;
                kingdom_food[turn] -= 3;
                printf("Hired 1 worker. Remaining food: %d\n", kingdom_food[turn]);
            } else {
                printf("Not enough food!\n");
            }
            break;
        case 3:
            if (kingdom_gold[turn] >= 2) {
                kingdom_soldiers[turn]++;
                kingdom_gold[turn] -= 2;
                printf("Hired 1 soldier. Remaining gold: %d\n", kingdom_gold[turn]);
            } else {
                printf("Not enough gold!\n");
            }
            break;
        case 4:
    move_kingdom();
    check_war(turn);
    print_map();
    break;

        case 0:
            printf("No action taken.\n");
            break;
        default:
            printf("Invalid action! Try again.\n");
        }
    
}
void update_resources() {
    for (int i = 0; i < numKingdom; i++) {
        kingdom_gold[i] += kingdom_gold_rate[i];
        kingdom_food[i] += kingdom_food_rate[i];
    }
}


void distance_maker()
{
    printf("___________________________________________________________________________________________________________");
}
void clrscr()
{
    system("cls");
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

        generate_map();
        get_blocked();
        int players;
        printf("How do you want to play the game:\n1-with AI\n2-two players\n3-three players\n4-four players\n");
        scanf("%d",&players);
        if (players==1 || players==2){
            numKingdom=2;
        } else {
            numKingdom=players;
        }
        
        get_kingdom();
        for(int i = 0; i < numKingdom; i++)
        {
            kingdom_gold[i] = 0;
            kingdom_food[i] = 0;
        }


        printf("Enter the number of villages: ");
        scanf("%d", &numVillages);

        for(int i = 0;i < numKingdom;i++) {
        counter_conquered_village[i] = 0;
        }
        get_villages();
        genrate_hardness();
        print_map();
        VillageInfo();
        kingdominfo();

        for (int i = 0; i < numKingdom; i++) {
        current_location[i][0] = kingdom_coordinates[i][0]; // Set starting x
        current_location[i][1] = kingdom_coordinates[i][1]; // Set starting y
        }

        distance_maker();
        //GAME IS STARTING 🗡️
        printf("\n--- Game Turn ---\n");
        for(;turn < numKingdom;turn++) {

        printf("\nits turn kingdom %d\n", turn + 1);
        print_map(map);
        update_resources();
        VillageInfo();
        kingdominfo();

        kingdom_properties();

        acting_kingdoms();
        int continueGame=1;

        if(turn == numKingdom - 1) turn = -1;
        if (!continueGame) break;
        distance_maker();
        // clrscr();
    }
 }
    return 0;
}