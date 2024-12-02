#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

int rows,columns;
// function to genrating empty map
void generate_map(char map[rows][columns]) {
    for (int i=0; i<columns; i++){
        for (int j=0; j<rows; j++){
            map[i][j]='O';
        }
    }
}
// Function to print the map
void print_map(char map[rows][columns])
{
    for(int i = 0;i < rows;++i)
    {
        for(int j = 0;j < columns;++j)
        {
            printf("%c",map[i][j]);
        }
    }
}
int main()
{
    printf("enter rows = ");
    scanf("%d",&rows);
    printf("enter columns = ");
    scanf("%d",&columns);
    char map[rows][columns];
    generate_map(map);
    print_map(map);

    return 0;
}
