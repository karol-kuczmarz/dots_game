#include"move.h"
#include<stdlib.h>

/*
MAP LEGEND:
-2 - opponent's in base
-1 - opponent's
0 - empty or opponent's
1 - my dot
2 - borders necessary
3 - part of a border
4 - dot in base
5 - mine inside
6 - noone's illegal

*/

int main()
{
    int t[WIDTH*HEIGHT]=
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, -1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
/*    int t2[WIDTH*HEIGHT];
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        t2[i]=t[i];
    }
    */
    frame granice;
    granice.num=0;
    int opp=0, mine=0;
    move(t, &granice, 37, &opp, &mine);
    move(t, &granice, 30, &opp, &mine);
    move(t, &granice, 21, &opp, &mine);
    move(t, &granice, 26, &opp, &mine);
    move(t, &granice, 35, &opp, &mine);
    move(t, &granice, 19, &opp, &mine);
    move(t, &granice, 28, &opp, &mine);
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            printf("%d ", t[i*WIDTH+j]);
        }
        printf("\n");
    }
    printf("%d %d", mine, opp);

    return 0;
}
