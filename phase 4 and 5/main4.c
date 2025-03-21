#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROWS 17
#define MAX_COLUMNS 17
#define MAX_KINGDOMS 4
#define MAX_VILLAGES 20

char map[MAX_ROWS + 1][MAX_COLUMNS + 1];
char hardnes_backup[MAX_COLUMNS+1][MAX_COLUMNS+1];
int rows, columns, numVillages, numKingdom, turn,is_computer_game, new_road_x,new_road_y,spell,totalPlayers;
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
int switch_kingdom[MAX_KINGDOMS];
char House_without_icon[4][100];
char House[4][100];
char player_icons[4][100] = {"🤴","🫅","🦹","👻"};

typedef struct {
    char map[MAX_ROWS + 1][MAX_COLUMNS + 1];
    char hardnes_backup[MAX_COLUMNS+1][MAX_COLUMNS+1];
    int rows, columns, numVillages, numKingdom, turn, is_computer_game,spell;
    char Kingdoms_name[4];
    char Kingdoms_road_name[4];
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
    int switch_kingdom[MAX_KINGDOMS];
    char House[4][100];
    char House_without_icon[4][100];
} GameState;

void save_game() {
    GameState state;

    // Copy all game state variables
    memcpy(state.map, map, sizeof(map));
    memcpy(state.hardnes_backup, hardnes_backup, sizeof(hardnes_backup));
    
    state.rows = rows;
    state.columns = columns;
    state.numVillages = numVillages;
    state.numKingdom = numKingdom;
    state.turn = turn;
    state.is_computer_game = is_computer_game;
    state.spell = spell;
    
    memcpy(state.Kingdoms_name, Kingdoms_name, sizeof(Kingdoms_name));
    memcpy(state.Kingdoms_road_name, Kingdoms_road_name, sizeof(Kingdoms_road_name));
    
    memcpy(state.village_goldRates, village_goldRates, sizeof(village_goldRates));
    memcpy(state.village_foodRates, village_foodRates, sizeof(village_foodRates));
    memcpy(state.village_coordinates, village_coordinates, sizeof(village_coordinates));
    memcpy(state.conquered_village, conquered_village, sizeof(conquered_village));
    memcpy(state.counter_conquered_village, counter_conquered_village, sizeof(counter_conquered_village));
    
    memcpy(state.kingdom_gold_rate, kingdom_gold_rate, sizeof(kingdom_gold_rate));
    memcpy(state.kingdom_food_rate, kingdom_food_rate, sizeof(kingdom_food_rate));
    memcpy(state.kingdom_workers, kingdom_workers, sizeof(kingdom_workers));
    memcpy(state.kingdom_soldiers, kingdom_soldiers, sizeof(kingdom_soldiers));
    memcpy(state.kingdom_coordinates, kingdom_coordinates, sizeof(kingdom_coordinates));
    memcpy(state.kingdom_gold, kingdom_gold, sizeof(kingdom_gold));
    memcpy(state.kingdom_food, kingdom_food, sizeof(kingdom_food));
    memcpy(state.current_location, current_location, sizeof(current_location));
    memcpy(state.switch_kingdom, switch_kingdom, sizeof(switch_kingdom));
    memcpy(state.House, House, sizeof(House));
    memcpy(state.House_without_icon, House_without_icon, sizeof(House_without_icon));

    FILE *file = fopen("game_save.bin", "wb");
    if (file == NULL) {
        printf("Error saving game!\n");
        return;
    }

    fwrite(&state, sizeof(GameState), 1, file);
    fclose(file);
    printf("Game saved successfully!\n");
}

int load_game() {
    GameState state;
    FILE *file = fopen("game_save.bin", "rb");
    if (file == NULL) {
        printf("No saved game found!\n");
        return 0;
    }

    fread(&state, sizeof(GameState), 1, file);
    fclose(file);

    // Restore all game state variables
    memcpy(map, state.map, sizeof(map));
    memcpy(hardnes_backup, state.hardnes_backup, sizeof(hardnes_backup));
    
    rows = state.rows;
    columns = state.columns;
    numVillages = state.numVillages;
    numKingdom = state.numKingdom;
    turn = state.turn;
    is_computer_game = state.is_computer_game;
    spell = state.spell;

    memcpy(Kingdoms_name, state.Kingdoms_name, sizeof(Kingdoms_name));
    memcpy(Kingdoms_road_name, state.Kingdoms_road_name, sizeof(Kingdoms_road_name));
    
    memcpy(village_goldRates, state.village_goldRates, sizeof(village_goldRates));
    memcpy(village_foodRates, state.village_foodRates, sizeof(village_foodRates));
    memcpy(village_coordinates, state.village_coordinates, sizeof(village_coordinates));
    memcpy(conquered_village, state.conquered_village, sizeof(conquered_village));
    memcpy(counter_conquered_village, state.counter_conquered_village, sizeof(counter_conquered_village));
    
    memcpy(kingdom_gold_rate, state.kingdom_gold_rate, sizeof(kingdom_gold_rate));
    memcpy(kingdom_food_rate, state.kingdom_food_rate, sizeof(kingdom_food_rate));
    memcpy(kingdom_workers, state.kingdom_workers, sizeof(kingdom_workers));
    memcpy(kingdom_soldiers, state.kingdom_soldiers, sizeof(kingdom_soldiers));
    memcpy(kingdom_coordinates, state.kingdom_coordinates, sizeof(kingdom_coordinates));
    memcpy(kingdom_gold, state.kingdom_gold, sizeof(kingdom_gold));
    memcpy(kingdom_food, state.kingdom_food, sizeof(kingdom_food));
    memcpy(current_location, state.current_location, sizeof(current_location));
    memcpy(switch_kingdom, state.switch_kingdom, sizeof(switch_kingdom));
    memcpy(House, state.House, sizeof(House));
    memcpy(House_without_icon, state.House_without_icon, sizeof(House_without_icon));

    printf("Game loaded successfully!\n");
    return 1;
}

int load_redaymap() {
    GameState state;
    FILE *ready = fopen("ready_map.bin", "rb");
    if (ready == NULL) {
        printf("No saved game found!\n");
        return 0;
    }

    fread(&state, sizeof(GameState), 1, ready);
    fclose(ready);

    // Restore all game state variables
    memcpy(map, state.map, sizeof(map));
    memcpy(hardnes_backup, state.hardnes_backup, sizeof(hardnes_backup));
    
    rows = state.rows;
    columns = state.columns;
    numVillages = state.numVillages;
    numKingdom = state.numKingdom;
    turn = state.turn;
    is_computer_game = state.is_computer_game;
    spell = state.spell;

    memcpy(Kingdoms_name, state.Kingdoms_name, sizeof(Kingdoms_name));
    memcpy(Kingdoms_road_name, state.Kingdoms_road_name, sizeof(Kingdoms_road_name));
    
    memcpy(village_goldRates, state.village_goldRates, sizeof(village_goldRates));
    memcpy(village_foodRates, state.village_foodRates, sizeof(village_foodRates));
    memcpy(village_coordinates, state.village_coordinates, sizeof(village_coordinates));
    memcpy(conquered_village, state.conquered_village, sizeof(conquered_village));
    memcpy(counter_conquered_village, state.counter_conquered_village, sizeof(counter_conquered_village));
    
    memcpy(kingdom_gold_rate, state.kingdom_gold_rate, sizeof(kingdom_gold_rate));
    memcpy(kingdom_food_rate, state.kingdom_food_rate, sizeof(kingdom_food_rate));
    memcpy(kingdom_workers, state.kingdom_workers, sizeof(kingdom_workers));
    memcpy(kingdom_soldiers, state.kingdom_soldiers, sizeof(kingdom_soldiers));
    memcpy(kingdom_coordinates, state.kingdom_coordinates, sizeof(kingdom_coordinates));
    memcpy(kingdom_gold, state.kingdom_gold, sizeof(kingdom_gold));
    memcpy(kingdom_food, state.kingdom_food, sizeof(kingdom_food));
    memcpy(current_location, state.current_location, sizeof(current_location));
    memcpy(switch_kingdom, state.switch_kingdom, sizeof(switch_kingdom));
    memcpy(House, state.House, sizeof(House));
    memcpy(House_without_icon, state.House_without_icon, sizeof(House_without_icon));

    printf("Game loaded successfully!\n");
    return 1;
}

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

int select_random_kingdom() {
    int chosen = -1;
    double probability = 1.0 / numKingdom ;
    int first = 0;
    for (int i = 0; i < numKingdom; i++) {
        double random_chance = (double)rand() / RAND_MAX;
        if (random_chance <= probability && random_chance >= first) {
            chosen = i;
            break;
        }
        first += probability;
        probability += probability;
        if(i == numKingdom - 1) i = -1;
    }

    return chosen;
}

void select_random_spell(){
    int chosen = -1;
    double random_spell = (double)rand() / RAND_MAX;
    int select = select_random_kingdom();
    if(random_spell < 0.25){
        printf("\ngold round🪙 !%s gained 2 gold in this round!\n",House[select]);
        kingdom_gold[select] += 2;
        return;
    }
    if(random_spell < 0.50){
        printf("\nfood round🍖!%s gained 2 food in this round!\n",House[select]);
        kingdom_food[select] += 2;
        return;
    }
    if(random_spell < 0.70){
        printf("\nfreazing❄️!%s lost 1 food!\n",House[select]);
        kingdom_food[select] -= 1;
        if(kingdom_food[select] < 0) kingdom_food[select] = 0;
        return;
    }
    if(random_spell < 0.90){
        printf("\nillness😷!one of %s soldiers is dead!\n",House[select]);
        kingdom_soldiers[select] -= 1;
        if(kingdom_soldiers[select] < 0) kingdom_soldiers[select] = 0;
        return;
    }
    if(random_spell < 1){
        printf("\na group of soldiers are joining you🔥!%s gained 2 soldier\n",House[select]);
        kingdom_soldiers[select] += 2;
        return;
    }
}
void apply_spell(){
    double random_apply = (double)rand() / RAND_MAX;
    if(random_apply < 0.30){
        select_random_spell();
    }
}
int easy_number() {
    double r = (double)rand() / RAND_MAX;
    if (r < 0.9)
        return 1;
    else if (r < 0.95)
        return 2;
    else
        return 3;
}

int normal_number() {
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

int iran_number() {
    double r = (double)rand() / RAND_MAX;
    if (r < 0.10)
        return 1;
    else if (r < 0.20)
        return 2;
    else if (r < 0.30)
        return 3;
    else
        return 4;
}

void genrate_hardness(int hardness){
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            if (map[i][j]=='O'){
                if (hardness==1){
                    int num = easy_number();
                    map[i][j] = num + '0';
                    hardnes_backup[i][j] = num + '0';
                } else if (hardness==2){
                    int num = normal_number();
                    map[i][j] = num + '0';
                    hardnes_backup[i][j] = num + '0';
                } else if (hardness==3){
                    int num = iran_number();
                    map[i][j] = num + '0';
                    hardnes_backup[i][j] = num + '0';
                }
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
                    printf("🟣 ");
                    break;
                case 'd':
                    printf("⚪ ");
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
                    printf("🤴 ");
                    break;
                case 'B':
                    printf("🫅 ");
                    break;
                case 'C':
                    printf("🦹 ");
                    break;
                case 'D':
                    printf("👻 ");
                    break;
                case 'V':
                    printf("🏠 ");
                    break;
                case 'L':
                    printf("💀 ");
                    break;
                default:
                    printf("❓ ");
                    break;
            }
        }
        printf("\n");
    }
}
void get_blocked() {
    int numBlocked;
    printf("How many blocked cells ❌ : ");
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
            printf("⚠️ Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void get_kingdom() {
    int x, y,p = 1,m=1;
    for (int i = 0; i < numKingdom; i++) {
        m=1;
        switch_kingdom[i]=1;
        if(p){printf("Enter your house name(player %d): ",i+1);
        scanf("%s",House[i]);
        strcpy(House_without_icon[i],House[i]);
        }
        for (int j=0; j<i; j++){
            if (strcmp(House[i],House[j])==0){
                printf("⚠️ This name has already been used. Try another name.\n");
                i--;
                m=0;
                break;
            }
        }
        if (m){
        printf("Enter the coordinates of %s (row column): ", House[i]);
        scanf("%d %d", &x, &y);
        if (x>rows || y>columns){
            printf("⚠️ out of the map. try again\n");
            i--;
            p = 0;
        }else if (map[x][y] == 'O') {
            map[x][y] = Kingdoms_name[i];
            printf("🪙  enter the gold production rate of %s : ",House[i]);
            scanf("%d",&kingdom_gold_rate[i]);
            printf("🍖 enter the food production rate of %s : ",House[i]);
            scanf("%d",&kingdom_food_rate[i]);
            printf("👷 enter the number of workers for %s : ",House[i]);
            scanf("%d",&kingdom_workers[i]);
            printf("💂 enter the number of soldier for %s : ",House[i]);
            scanf("%d",&kingdom_soldiers[i]);
            kingdom_coordinates[i][0] = x;
            kingdom_coordinates[i][1] = y;
            p = 1;
        } else {
            printf("⚠️ Cell already occupied. Try again.\n");
            p = 0;
            i--;
        }
    }
    }
    for(int i = 0; i < numKingdom; i++){
        strcat(House[i],player_icons[i]);
        kingdom_gold[i] = 0;
        kingdom_food[i] = 0;
    }
}

void get_villages() {
    printf("🏠 Enter the number of villages: ");
    scanf("%d", &numVillages);
    for(int i = 0;i < numKingdom;i++) {
        counter_conquered_village[i] = 0;
    }
    for (int i = 0; i < numVillages; i++) {
        int x, y, goldRate, foodRate;
        printf("Enter the coordinates of village %d (row column): ", i + 1);
        scanf("%d %d", &x, &y);

        if (x>rows || y>columns){
            printf("⚠️ out of the map. try again\n");
            i--;
        }else if (map[x][y] == 'O') {
            map[x][y] = 'V';
            printf("🪙  Enter gold production rate for village %d: ",i+1);
            scanf("%d", &goldRate);
            printf("🍖 Enter food production rate for this village %d: ",i+1);
            scanf("%d", &foodRate);
            village_coordinates[i][0]= x;
            village_coordinates[i][1]= y;
            village_goldRates[i] = goldRate;
            village_foodRates[i] = foodRate;
        } else {
            printf("⚠️ Cell already occupied. Try again.\n");
            i--;
        }
    }
}

void VillageInfo() {
    printf("\n🏠 Villages Information:\n");
    for (int i = 0; i < numVillages; i++) {
        printf("Village %d -> Gold Rate: %d, Food Rate: %d ,coordinates;(%d,%d)\n", i + 1, village_goldRates[i], village_foodRates[i],village_coordinates[i][0],village_coordinates[i][1]);
    }
}

void kingdominfo(){
    printf("\n🏰 kingdoms Information:\n");
    for(int i = 0;i < numKingdom;i++)
    {
        if(switch_kingdom[i] == 1){
            printf("%s -> gold rate : %d,food rate : %d ,🪙  = %d ,🍖 = %d ,coordinates : (%d,%d)\n",House[i],kingdom_gold_rate[i],kingdom_food_rate[i],kingdom_gold[i],kingdom_food[i],kingdom_coordinates[i][0],kingdom_coordinates[i][1]);
            printf("current location of %s is -> (%d,%d)\n",House[i],current_location[i][0],current_location[i][1]);
        }
        else continue;
    }
}

void kingdom_properties()
{
    printf("\n🏰 kingdoms property:\n");
    for(int i = 0;i < numKingdom;i++)
    {
        if(switch_kingdom[i] == 1){
            printf("%s ---> 👷= %d ,💂= %d \n",House[i],kingdom_workers[i],kingdom_soldiers[i]);
            printf("%s have %d villages in total.\n",House[i],counter_conquered_village[i]);
            for(int j = 0;j < counter_conquered_village[i];j++)
            {
                printf("%s  have village with cooardination (%d,%d) \n",House[i],conquered_village[i][j][0],conquered_village[i][j][1]);
            }
            printf("\n");
        }
        else continue;
    }
}
// Check if village is owned by kingdom
int is_village_owned(int x, int y, int kingdom) {
    for(int i = 0; i < counter_conquered_village[kingdom]; i++) {
        if(conquered_village[kingdom][i][0] == x &&
           conquered_village[kingdom][i][1] == y) {
            return (1);
        }
    }
    return 0;
}

void start_game(){
    int action;
    printf("🕹️ welcome to A road to salvation game 🕹️\n1.Start the game with the map I want 🗺️\n2.load game 🔃\n3.use ready map 📖\n4.Exit ❌\nenter your action: ");
    scanf("%d", &action);
    if (action == 1) {
        printf("Enter rows (max %d): ", MAX_ROWS);
        scanf("%d", &rows);
        if (rows > MAX_ROWS) rows = MAX_ROWS;

        printf("Enter columns (max %d): ", MAX_COLUMNS);
        scanf("%d", &columns);
        if (columns > MAX_COLUMNS) columns = MAX_COLUMNS;

        generate_map();
        get_blocked();
        int players;
        printf("How do you want to play the game:\n1-with computer 🤖\n2-two players 🤴🫅\n3-three players 🤴🫅🦹\n4-four players 🤴🫅🦹👻\n");
        scanf("%d",&players);
        if (players==1 || players==2){
            numKingdom=2;
            if (players==1){
                is_computer_game=1;
            } else {
                is_computer_game=0;
            }
        } else {
            numKingdom=players;
        }
        int hardness;
        printf("select hardness:\n1-easy 💧\n2-normal 💫\n3-Iran 💀\n");
        scanf("%d",&hardness);
        spell = 0;
        printf("✨ do you want to palying in spell mode? (1=✅ / 0=❌)\n");
        scanf("%d",&spell);
        get_kingdom();
        get_villages();
        genrate_hardness(hardness);
        print_map();
        VillageInfo();
        kingdominfo();

        for (int i = 0; i < numKingdom; i++) {
            current_location[i][0] = kingdom_coordinates[i][0]; // Set starting x
            current_location[i][1] = kingdom_coordinates[i][1]; // Set starting y
        }
    }  else if (action == 2) {
        if (!load_game()) {
            start_game();
        } 
    } else if (action == 3){
        if (!load_redaymap()) {
            start_game();
        } 
    } else if (action == 4) {
        exit(0);
    }
}

int get_computer_direction() {
    int direction;
    int new_x = current_location[turn][0];
    int new_y = current_location[turn][1];
    int valid = 0;

    while (!valid) {
        direction = rand() % 4;
        new_x = current_location[turn][0];
        new_y = current_location[turn][1];

        switch(direction) {
            case 0: // Up
                new_x--;
                direction = 72;
                break;
            case 1: // Down
                new_x++;
                direction = 80;
                break;
            case 2: // Left
                new_y--;
                direction = 75;
                break;
            case 3: // Right
                new_y++;
                direction = 77;
                break;
        }
        if (new_x >= 1 && new_y >= 1 && new_x <= rows && new_y <= columns &&
            map[new_x][new_y] != 'X' && map[new_x][new_y] != 'L' && map[new_x][new_y] != Kingdoms_road_name[turn]) {
            valid = 1;
        }
    }

    return direction;
}

void computer_play() {
    int action = rand() % 4 + 1;
    printf("\n🤖 Computer chose action: %d\n", action);

    switch (action) {
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
            int new_x, new_y;
            int move, scape;
            int up,down,right,left;

            printf("Choose the arrow keys to move (%s) or choose Esc to get out:\n", House[turn]);
            scape = 1;

            while (scape) {
                int direction = get_computer_direction();
                move = direction;
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
                new_road_x = new_x;
                new_road_y = new_y;
                if (new_x >= 1 && new_y >= 1 && new_x <= rows && new_y <= columns) {
                    if (map[new_x][new_y] == Kingdoms_road_name[turn]) {
                        printf("Moving on road at (%d, %d).\n", new_x, new_y);
                        current_location[turn][0] = new_x;
                        current_location[turn][1] = new_y;
                        continue;
                    }
                    int sw = 0;
                    if (map[new_x][new_y] == 'V') {
                        for (int j=0; j<counter_conquered_village[turn]; j++){
                            if (conquered_village[turn][j][0] == new_x && conquered_village[turn][j][1] == new_y){
                                sw = 1;
                                break;
                            }
                        }
                        if (sw == 1){
                            printf("you are now in your village with coordinates of (%d, %d).\n", new_x, new_y);
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            check_war(turn);
                            continue;
                        }
                    }
                    if(map[new_x][new_y] == Kingdoms_name[turn])
                    {
                        printf("you are now in %s kingdom! \n",House[turn]);
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
                    if (map[new_x][new_y] == 'V' && !is_village_owned(new_x, new_y, turn)) {

                        current_location[turn][0] = new_x;
                        current_location[turn][1] = new_y;

                        if (counter_conquered_village[turn] == 0){
                            printf("the vilage with cooardination : (%d, %d) is conquered by %s .\n", current_location[turn][0], current_location[turn][1],House[turn]);
                            conquer_villages();
                        } else {
                            for (int j=0; j<counter_conquered_village[turn]; j++){
                                if (conquered_village[turn][j][0] != new_x || conquered_village[turn][j][1] != new_y){
                                    printf("the vilage with cooardination : (%d, %d) is conquered by %s .\n",current_location[turn][0],current_location[turn][1],House[turn]);
                                    conquer_villages();
                                    break;
                                }
                            }
                        }
                        break;
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
            }
            check_war(turn);
            for (int m=0; m<numKingdom; m++){
                check_connectivity(m);
            }
            print_map();
            break;
    }

}

void conquer_villages() {
    for (int j = 0; j < numVillages; j++) {
        int vx = village_coordinates[j][0];
        int vy = village_coordinates[j][1];
        int cx = current_location[turn][0];
        int cy = current_location[turn][1];

        if (abs(vx - cx)+abs(vy - cy)==0) {
            conquered_village[turn][counter_conquered_village[turn]][0] = cx;
            conquered_village[turn][counter_conquered_village[turn]][1] = cy;
            counter_conquered_village[turn]++;


            kingdom_gold_rate[turn] += village_goldRates[j];
            kingdom_food_rate[turn] += village_foodRates[j];
        }
    }
}


void move_kingdom() {
    int new_x, new_y;
    int move, scape;
    int up,down,right,left;

    printf("🕹️ Choose the arrow keys to move %s or choose Esc to get out:\n", House[turn]);
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
                new_road_x = new_x;
                new_road_y = new_y;
                if (new_x >= 1 && new_y >= 1 && new_x <= rows && new_y <= columns) {
                    if (map[new_x][new_y] == Kingdoms_road_name[turn]) {
                        printf("Moving on road at (%d, %d).\n", new_x, new_y);
                        current_location[turn][0] = new_x;
                        current_location[turn][1] = new_y;
                        continue;
                    }
                    int sw = 0;
                    if (map[new_x][new_y] == 'V') {
                        for (int j=0; j<counter_conquered_village[turn]; j++){
                            if (conquered_village[turn][j][0] == new_x && conquered_village[turn][j][1] == new_y){
                                sw = 1;
                                break;
                            }
                        }
                        if (sw == 1){
                            printf("🏠 you are now in your village with coordinates of (%d, %d).\n", new_x, new_y);
                            current_location[turn][0] = new_x;
                            current_location[turn][1] = new_y;
                            check_war(turn);
                            continue;
                        }
                    }
                    if(map[new_x][new_y] == Kingdoms_name[turn])
                    {
                        printf("you are now in %s kingdom! \n",House[turn]);
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
                            printf("👷 Built road at (%d, %d).\n", new_x, new_y);
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
                    if (map[new_x][new_y] == 'V' && !is_village_owned(new_x, new_y, turn)) {

                        current_location[turn][0] = new_x;
                        current_location[turn][1] = new_y;

                        if (counter_conquered_village[turn] == 0){
                            printf("the vilage with cooardination : (%d, %d) is conquered by %s .\n", current_location[turn][0], current_location[turn][1],House[turn]);
                            conquer_villages();
                        } else {
                            for (int j=0; j<counter_conquered_village[turn]; j++){
                                if (conquered_village[turn][j][0] != new_x || conquered_village[turn][j][1] != new_y){
                                    printf("the vilage with cooardination : (%d, %d) is conquered by %s .\n",current_location[turn][0],current_location[turn][1],House[turn]);
                                    conquer_villages();
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    if(map[new_x][new_y] == 'X' || map[new_x][new_y] == 'L') {
                        printf("⚠️ Cannot move to this position. Blocked cell or destroyed kingdom house! .\n");
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
                    printf("⚠️ Out of bounds! Try again.\n");
                }
            }
        }
    }
}

// Find shortest path using BFS
int find_shortest_path(int start_x, int start_y, int kingdom, int path_x[], int path_y[]) {
    int queue_x[MAX_ROWS * MAX_COLUMNS];
    int queue_y[MAX_ROWS * MAX_COLUMNS];
    int parent_x[MAX_ROWS + 1][MAX_COLUMNS + 1];
    int parent_y[MAX_ROWS + 1][MAX_COLUMNS + 1];
    int visited[MAX_ROWS + 1][MAX_COLUMNS + 1] = {0};
    int front = 0, rear = 0;
    int path_length = 0;
    int found = 0;

    // Initialize parent arrays
    for(int i = 0; i <= rows; i++) {
        for(int j = 0; j <= columns; j++) {
            parent_x[i][j] = -1;
            parent_y[i][j] = -1;
        }
    }

    // Start BFS from war location
    queue_x[rear] = start_x;
    queue_y[rear] = start_y;
    rear++;
    visited[start_x][start_y] = 1;

    // BFS to find path
    while(front < rear) {
        int curr_x = queue_x[front];
        int curr_y = queue_y[front];
        front++;

        // Check if we reached kingdom or owned village
        if(map[curr_x][curr_y] == Kingdoms_name[kingdom] ||
           (map[curr_x][curr_y] == 'V' && is_village_owned(curr_x, curr_y, kingdom))) {
            found = 1;

            // Reconstruct path
            int x = curr_x, y = curr_y;
            while(parent_x[x][y] != -1) {
                path_x[path_length] = x;
                path_y[path_length] = y;
                path_length++;
                int temp_x = parent_x[x][y];
                int temp_y = parent_y[x][y];
                x = temp_x;
                y = temp_y;
            }
            path_x[path_length] = start_x;
            path_y[path_length] = start_y;
            path_length++;
            break;
        }

        // Check adjacent cells
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for(int i = 0; i < 4; i++) {
            int new_x = curr_x + dx[i];
            int new_y = curr_y + dy[i];

            if(new_x >= 1 && new_x <= rows && new_y >= 1 && new_y <= columns &&
               !visited[new_x][new_y] &&
               (map[new_x][new_y] == Kingdoms_road_name[kingdom] ||
                map[new_x][new_y] == Kingdoms_name[kingdom] ||
                (map[new_x][new_y] == 'V' && is_village_owned(new_x, new_y, kingdom)))) {
                queue_x[rear] = new_x;
                queue_y[rear] = new_y;
                rear++;
                visited[new_x][new_y] = 1;
                parent_x[new_x][new_y] = curr_x;
                parent_y[new_x][new_y] = curr_y;
            }
        }
    }

    return found ? path_length : 0;
}


// Check connectivity of roads and villages
void check_connectivity(int kingdom) {
    int visited[MAX_ROWS + 1][MAX_COLUMNS + 1] = {0};
    int queue_x[MAX_ROWS * MAX_COLUMNS];
    int queue_y[MAX_ROWS * MAX_COLUMNS];
    int front = 0, rear = 0;

    // Start BFS from kingdom capital
    queue_x[rear] = kingdom_coordinates[kingdom][0];
    queue_y[rear] = kingdom_coordinates[kingdom][1];
    rear++;
    visited[kingdom_coordinates[kingdom][0]][kingdom_coordinates[kingdom][1]] = 1;

    while(front < rear) {
        int curr_x = queue_x[front];
        int curr_y = queue_y[front];
        front++;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for(int i = 0; i < 4; i++) {
            int new_x = curr_x + dx[i];
            int new_y = curr_y + dy[i];

            if(new_x >= 1 && new_x <= rows && new_y >= 1 && new_y <= columns &&
               !visited[new_x][new_y] &&
               (map[new_x][new_y] == Kingdoms_road_name[kingdom] ||
                (map[new_x][new_y] == 'V' && is_village_owned(new_x, new_y, kingdom)))) {
                queue_x[rear] = new_x;
                queue_y[rear] = new_y;
                rear++;
                visited[new_x][new_y] = 1;
            }
        }
    }                                      


    // Remove disconnected roads and villages
    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= columns; j++) {
            if(!visited[i][j]) {
                if(map[i][j] == Kingdoms_road_name[kingdom]) {
                    // Restore original hardness
                    map[i][j] = hardnes_backup[i][j];
                }
                else if(map[i][j] == 'V' && is_village_owned(i, j, kingdom)) {
                    // Find and remove village from kingdom's possessions
                    for(int k = 0; k < counter_conquered_village[kingdom]; k++) {
                        if(conquered_village[kingdom][k][0] == i &&
                           conquered_village[kingdom][k][1] == j) {
                            // Remove village's resources from kingdom
                            for(int v = 0; v < numVillages; v++) {
                                if(village_coordinates[v][0] == i &&
                                   village_coordinates[v][1] == j) {
                                    kingdom_gold_rate[kingdom] -= village_goldRates[v];
                                    kingdom_food_rate[kingdom] -= village_foodRates[v];
                                    break;
                                }
                            }
                            // Remove village from conquered list
                            for(int m = k; m < counter_conquered_village[kingdom] - 1; m++) {
                                conquered_village[kingdom][m][0] = conquered_village[kingdom][m + 1][0];
                                conquered_village[kingdom][m][1] = conquered_village[kingdom][m + 1][1];
                            }
                            counter_conquered_village[kingdom]--;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void remove_roads(int kingdom, int war_x, int war_y) {
    int path_x[MAX_ROWS * MAX_COLUMNS];
    int path_y[MAX_ROWS * MAX_COLUMNS];
    int path_length;

    // Find shortest path
    path_length = find_shortest_path(war_x, war_y, kingdom, path_x, path_y);

    if(path_length > 0) {
        // Remove roads along path until reaching kingdom or owned village
        for(int i = path_length - 1; i >= 0; i--) {
            int x = path_x[i];
            int y = path_y[i];

            if(map[x][y] == Kingdoms_name[kingdom]) {
                // Reached kingdom capital
                current_location[kingdom][0] = x;
                current_location[kingdom][1] = y;
                break;
            }
            else if(map[x][y] == 'V' && is_village_owned(x, y, kingdom)) {
                // Reached owned village
                current_location[kingdom][0] = x;
                current_location[kingdom][1] = y;
                break;
            }
            else if(map[x][y] == Kingdoms_road_name[kingdom]) {
                // Remove road and restore hardness
                map[x][y] = hardnes_backup[x][y];
            }
        }

        // Check and remove disconnected roads and villages
        check_connectivity(kingdom);
    }
    else {
        // No path found, move to kingdom capital
        current_location[kingdom][0] = kingdom_coordinates[kingdom][0];
        current_location[kingdom][1] = kingdom_coordinates[kingdom][1];
    }
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

        printf("%s wins the battle!\n", House[kingdom1]);
        printf("Kingdom %s loses %d soldiers\n%s loses 0 soldiers.\n",
               House[kingdom2], loss_kingdom2, House[kingdom1]);
        remove_roads(kingdom2, war_x,war_y);
        // map[new_road_x][new_road_y]=Kingdoms_road_name[kingdom1];

    } else if (soldiers_kingdom1 < soldiers_kingdom2) {
        int loss_kingdom1 = soldiers_kingdom2 - soldiers_kingdom1;

        if(loss_kingdom1 > kingdom_soldiers[kingdom1]){
            loss_kingdom1 = kingdom_soldiers[kingdom1];
        }
        kingdom_soldiers[kingdom1] -= loss_kingdom1;
        if (kingdom_soldiers[kingdom1] < 0) kingdom_soldiers[kingdom1] = 0;

        printf("%s wins the battle!\n", House[kingdom2]);
        printf("%s loses %d soldiers\n%s loses 0 soldiers.\n",
               House[kingdom1], loss_kingdom1, House[kingdom2]);
        remove_roads(kingdom1,war_x,war_y);
    } else {
        // Draw
        printf("⚔️ The battle ends in a draw! No losses for either kingdom.\n");
        kingdom_soldiers[kingdom1] = kingdom_soldiers[kingdom1]/2;
        kingdom_soldiers[kingdom2] = kingdom_soldiers[kingdom2]/2;
        remove_roads(kingdom1,war_x,war_y);
        remove_roads(kingdom2,war_x,war_y);
    }
}

void village_battle(int kingdom1, int kingdom2, int war_x, int war_y, int village_x
        ,int village_y) {

    int soldiers_kingdom1 = kingdom_soldiers[kingdom1];
    int soldiers_kingdom2 = kingdom_soldiers[kingdom2];


    if (soldiers_kingdom1 > soldiers_kingdom2) {

        int loss_kingdom2 = soldiers_kingdom1 - soldiers_kingdom2;

        if(loss_kingdom2 > kingdom_soldiers[kingdom2]){
            loss_kingdom2 = kingdom_soldiers[kingdom2];
        }
        kingdom_soldiers[kingdom2] -= loss_kingdom2;
        if (kingdom_soldiers[kingdom2] < 0) kingdom_soldiers[kingdom2] = 0;
        printf("Kingdom %s loses %d soldiers\n%s loses 0 soldiers.\n",
               House[kingdom2], loss_kingdom2, House[kingdom1]);

        remove_roads(kingdom2, village_x,village_y);

    } else if (soldiers_kingdom1 < soldiers_kingdom2) {
        int loss_kingdom1 = soldiers_kingdom2 - soldiers_kingdom1;

        if(loss_kingdom1 > kingdom_soldiers[kingdom1]){
            loss_kingdom1 = kingdom_soldiers[kingdom1];
        }
        kingdom_soldiers[kingdom1] -= loss_kingdom1;
        if (kingdom_soldiers[kingdom1] < 0) kingdom_soldiers[kingdom1] = 0;

        printf("%s wins the battle!\n", House[kingdom2]);
        printf("%s loses %d soldiers\n%s loses 0 soldiers.\n",
               House[kingdom1], loss_kingdom1, House[kingdom2]);
        remove_roads(kingdom1,war_x,war_y);
    } else {
        // Draw
        kingdom_soldiers[kingdom2] = kingdom_soldiers[kingdom2]/2;
        kingdom_soldiers[kingdom1] = kingdom_soldiers[kingdom1]/2;
        printf("⚔️ The battle ends in a draw! No losses for either kingdom.\n");
        remove_roads(kingdom1,war_x,war_y);
        remove_roads(kingdom2,village_x,village_y);
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


            printf("⚔️ Village War! %s is fighting with %s for the village with the cooardinate (%d %d).😨\n", House[current_kingdom], House[village_owner],village_x,village_y);


            if (kingdom_soldiers[current_kingdom] > kingdom_soldiers[village_owner]) {
                printf("%s wins and conquers the village with the cooardination (%d %d)!🥳\n", House[current_kingdom],village_x,village_y);
                counter_conquered_village[current_kingdom]++;
                conquered_village[current_kingdom][counter_conquered_village[current_kingdom] - 1][0] = village_x;
                conquered_village[current_kingdom][counter_conquered_village[current_kingdom] - 1][1] = village_y;
                kingdom_gold_rate[current_kingdom] += village_goldRates[i];
                kingdom_food_rate[current_kingdom] += village_foodRates[i];

                for (int k = 0; k < counter_conquered_village[village_owner]; k++) {
                    if (conquered_village[village_owner][k][0] == village_x &&
                        conquered_village[village_owner][k][1] == village_y) {

                        kingdom_gold_rate[village_owner] -= village_goldRates[i];
                        kingdom_food_rate[village_owner] -= village_foodRates[i];

                        for (int m = k; m < counter_conquered_village[village_owner] - 1; m++) {
                            conquered_village[village_owner][m][0] = conquered_village[village_owner][m + 1][0];
                            conquered_village[village_owner][m][1] = conquered_village[village_owner][m + 1][1];
                        }
                        counter_conquered_village[village_owner]--;
                        break;
                    }
                }
                village_battle(current_kingdom, village_owner,current_x,current_y,village_x,village_y);
            } else if (kingdom_soldiers[current_kingdom] == kingdom_soldiers[village_owner]){
                for (int k = 0; k < counter_conquered_village[village_owner]; k++) {
                    if (conquered_village[village_owner][k][0] == village_x &&
                        conquered_village[village_owner][k][1] == village_y) {

                        kingdom_gold_rate[village_owner] -= village_goldRates[i];
                        kingdom_food_rate[village_owner] -= village_foodRates[i];

                        for (int m = k; m < counter_conquered_village[village_owner] - 1; m++) {
                            conquered_village[village_owner][m][0] = conquered_village[village_owner][m + 1][0];
                            conquered_village[village_owner][m][1] = conquered_village[village_owner][m + 1][1];
                        }
                        counter_conquered_village[village_owner]--;
                        break;
                    }
                }
                village_battle(current_kingdom, village_owner,current_x,current_y,village_x,village_y);
                village_battle(village_owner, current_kingdom,village_x,village_y,current_x,current_y);
            }else{
                printf("%s lose the battle and the village with cooardination (%d,%d) is still belong to kingdom %d\n",House[current_kingdom],village_x,village_y,village_owner+1);
                village_battle(village_owner,current_kingdom,current_x,current_y,village_x,village_y);
            }


            return;
        }
    }
}

void delete_kingdom(int kingdom) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            if (map[i][j] == Kingdoms_road_name[kingdom]) {
                map[i][j] = hardnes_backup[i][j];
            }
        }
    }

    for (int i = 0; i < counter_conquered_village[kingdom]; i++) {
        int village_x = conquered_village[kingdom][i][0];
        int village_y = conquered_village[kingdom][i][1];

        for (int j = 0; j < numVillages; j++) {
            if (village_coordinates[j][0] == village_x &&
                village_coordinates[j][1] == village_y) {


                kingdom_gold_rate[kingdom] -= village_goldRates[j];
                kingdom_food_rate[kingdom] -= village_foodRates[j];
                break;
            }
        }
    }

    counter_conquered_village[kingdom] = 0;
    switch_kingdom[kingdom] = 0;
    kingdom_gold[kingdom] = 0;
    kingdom_food[kingdom] = 0;
    kingdom_workers[kingdom] = 0;
    kingdom_soldiers[kingdom] = 0;
    map[kingdom_coordinates[kingdom][0]][kingdom_coordinates[kingdom][1]] = 'L';

    printf("%s eliminated 🤣🤣🤣\n", House[kingdom]);
}

void Big_battel (int kingdom1, int kingdom2, int war_x, int war_y) {
    int soldiers_kingdom1 = kingdom_soldiers[kingdom1];
    int soldiers_kingdom2 = kingdom_soldiers[kingdom2];

    if (soldiers_kingdom1 > soldiers_kingdom2) {

        int loss_kingdom2 = soldiers_kingdom1 - soldiers_kingdom2;
        if(loss_kingdom2 > kingdom_soldiers[kingdom2]){
            loss_kingdom2 = kingdom_soldiers[kingdom2];
        }
        kingdom_soldiers[kingdom2] -= loss_kingdom2;
        if (kingdom_soldiers[kingdom2] < 0) kingdom_soldiers[kingdom2] = 0;
        printf("⚔️ kingdom %s has been destroyed by kingdom %s ! \n",House[kingdom2],House[kingdom1]);
        delete_kingdom(kingdom2);

    } else if (soldiers_kingdom1 < soldiers_kingdom2) {
        int loss_kingdom1 = soldiers_kingdom2 - soldiers_kingdom1;
        if(loss_kingdom1 > kingdom_soldiers[kingdom1]){
            loss_kingdom1 = kingdom_soldiers[kingdom1];
        }
        kingdom_soldiers[kingdom1] -= loss_kingdom1;
        if (kingdom_soldiers[kingdom1] < 0) kingdom_soldiers[kingdom1] = 0;
        remove_roads(kingdom1,war_x,war_y);
    } else {
        remove_roads(kingdom1,war_x,war_y);
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
                    printf("⚔️ All-Out War! %s and %s are fighting near a kingdom.\n", House[current_kingdom], House[other_kingdom]);
                    Big_battel(current_kingdom, other_kingdom, current_x, current_y);
                    return;
                }

                if(map[i][j] == 'V' && abs(current_x - i) + abs(current_y - j) == 1){
                    if(!is_village_owned(i, j, current_kingdom)){
                        check_village_war(current_kingdom);
                        return;
                    }
                }

                if (map[i][j] == Kingdoms_road_name[other_kingdom] &&
                    abs(current_x - i) + abs(current_y - j) == 1) {
                    printf("⚔️ Road War! %s and %s are fighting near a road.\n", House[current_kingdom], House[other_kingdom]);
                    start_battle(current_kingdom, other_kingdom, current_x, current_y);
                    return;
                }
            }
        }

    }
}

void acting_kingdoms()
{
    int act;
    print_map();
    printf("🎮 what do you want to act %s ? : \n",House[turn]);
    printf("🍖 1.buying 1 food with spending 1 gold : \n");
    printf("👷 2.hiring a worker for your kingdom with spending 3 food : \n");
    printf("💂 3.hiring a soldier for your kingdom with spending 2 gold : \n");
    printf("🔨 4.creating a road in map with the consider cooardination : \n");
    printf("❌ 0.act nothing and continue : \n");
    scanf("%d",&act);
    switch (act) {
        case 1:
            if (kingdom_gold[turn] > 0) {
                kingdom_food[turn]++;
                kingdom_gold[turn]--;
                printf("🍖 Bought 1 food. Remaining gold: %d\n", kingdom_gold[turn]);
            } else {
                printf("⚠️ Not enough gold!\n");
            }
            break;
        case 2:
            if (kingdom_food[turn] >= 3) {
                kingdom_workers[turn]++;
                kingdom_food[turn] -= 3;
                printf("👷 Hired 1 worker. Remaining food: %d\n", kingdom_food[turn]);
            } else {
                printf("⚠️ Not enough food!\n");
            }
            break;
        case 3:
            if (kingdom_gold[turn] >= 2) {
                kingdom_soldiers[turn]++;
                kingdom_gold[turn] -= 2;
                printf("💂 Hired 1 soldier. Remaining gold: %d\n", kingdom_gold[turn]);
            } else {
                printf("⚠️ Not enough gold!\n");
            }
            break;
        case 4:
            move_kingdom();
            check_war(turn);
            for (int m=0; m<numKingdom; m++){
                check_connectivity(m);
            }
            print_map();
            break;

        case 0:
            printf("❌ No action taken.\n");
            break;
        default:
            printf("⚠️ Invalid action! Try again.\n");
    }

}
void update_resources() {
    for (int i = 0; i < numKingdom  && switch_kingdom[i]==1; i++) {
        kingdom_gold[i] += kingdom_gold_rate[i];
        kingdom_food[i] += kingdom_food_rate[i];
    }
}


void distance_maker()
{
    printf("\n___________________________________________________________________________________________________________\n");
}
void clrscr()
{
    system("cls");
}

void sortNames(char name[][100],int wins[], int n) {  
    for (int i = 0; i < n - 1; i++) {  
        for (int j = 0; j < n - i - 1; j++) {  
            if (wins[j] < wins[j + 1]) {  
                int temp = wins[j];  
                wins[j] = wins[j + 1];  
                wins[j + 1] = temp; 
                char tempName[100];
                strcpy(tempName,name[j]);
                strcpy(name[j],name[j+1]);
                strcpy(name[j+1],tempName);
            }  
        }  
    }  
} 

void displayRanks(char name[][100],int wins[], int n){
    sortNames(name,wins,n);
    printf("👑 ranking of players 👑\n");
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        if (i==0) printf("🥇 ");
        if (i==1) printf("🥈 ");
        if (i==2) printf("🥉 ");
        if (wins[i]>1){
            printf("%d- %s ---> %d wins\n",i+1,name[i],wins[i]);
        } else {
            printf("%d- %s ---> %d win\n",i+1,name[i],wins[i]);
        }
    }
    printf("\n");
}


int main() {
    srand(time(NULL));

    FILE *tabel;
    tabel = fopen("players.txt","r");
    fscanf(tabel,"%d",&totalPlayers);
    char name[totalPlayers+4][100];
    int wins[totalPlayers+4];
    for (int i = 0; i < totalPlayers; i++)
    {
        fscanf(tabel,"%s",name[i]);
        fscanf(tabel,"%d",&wins[i]);
    }

    displayRanks(name,wins,totalPlayers);
    fclose(tabel);

    start_game();
    distance_maker();
    // clrscr();
    //GAME IS STARTING 🗡️
    printf("\n--- Game Turn ---\n");
    int round = 0;
    int check = 1;
    for(;turn < numKingdom;turn++) {
        for (int m=0; m<numKingdom; m++){
            check_connectivity(m);
        }
        if (switch_kingdom[turn]==1){
            //update resources will work at the first of each round!
            if(check){
                round++;
                int save_choice;
                printf("🔃 Do you want to save the game? (1=✅ / 0=❌): ");
                scanf(" %d", &save_choice);
                if (save_choice == 1) {
                    save_game();
                }
                update_resources();
                if(spell)apply_spell();
            }
            check = 0;
            distance_maker();
            printf("it's round %d\n",round);
            printf("\nit's turn %s\n", House[turn]);
            print_map();
            VillageInfo();
            kingdominfo();
            kingdom_properties();
            if (is_computer_game==1 && turn == 1){
                computer_play();
            } else {
                acting_kingdoms();
            }
        }
        if(turn == numKingdom - 1){
            turn = -1;
            check = 1;
        }
        int alive=0;
        for (int l=0; l<numKingdom;l++){
            if (switch_kingdom[l]==1){
                alive++;
            }
        }
        int endList = totalPlayers;
        if (alive==1) {
            int winnerIndex;
            for (int k=0; k<numKingdom;k++){
                if (switch_kingdom[k]==1){
                    winnerIndex=k;
                }
            }
            int checkedKingdom[numKingdom];
            for (int i = 0; i < numKingdom; i++)
            {
                checkedKingdom[i]=0;               
                for (int j = 0; j < totalPlayers; j++){
                    if (strcmp(name[j],House_without_icon[i])==0 && i==winnerIndex){
                        checkedKingdom[i]=1;
                        wins[j]++;
                    } else if (strcmp(name[j],House_without_icon[i])==0 && i!=winnerIndex){
                        checkedKingdom[i]=1;
                    }
                }
                
            }

            for (int i = 0; i < numKingdom; i++){
                if (checkedKingdom[i]==0){
                    if (winnerIndex==i){
                        strcpy(name[endList],House_without_icon[i]);
                        wins[endList]=1;
                        checkedKingdom[i]=1;
                        endList++;
                    } else {
                        strcpy(name[endList],House_without_icon[i]);
                        wins[endList]=0;
                        checkedKingdom[i]=1;
                        endList++;                        
                    }
                }
            }            
            displayRanks(name,wins,endList);
            FILE *out;
            out = fopen("players.txt","w");
            fprintf(out,"%d\n",endList);
            for (int i=0; i<endList; i++){
                fprintf(out,"%s %d\n",name[i],wins[i]);
            }
            fclose(out);
            break;        
        }
        // clrscr();
    }
    for (int i=0; i<numKingdom;i++){
        if (switch_kingdom[i]==1){
            printf("%s won the game.🎉\n",House_without_icon[i]);
            distance_maker();
        }
    }      
    return 0;
}