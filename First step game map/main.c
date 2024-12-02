#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
int rows,columns;

void generate_map(char map[rows][columns]) {
    for(int j =0; j<columns; j++){
        map[0][j]=j;
    }
    for(int i =0; i<rows; i++){
        map[i][0]=i;
    }
    for (int i=1; i<columns; i++){
        for (int j=1; j<rows; j++){
            map[rows][columns]='O'
        }
    }
}
int main()
{
    printf("enter rows = ");
    scanf("%d",&rows);
    rows=rows+1;
    printf("enter columns = ");
    scanf("%d",&columns);
    columns=columns+1;
    char map[rows][columns];
    generate_map();
    print_map();
    return 0;
}
