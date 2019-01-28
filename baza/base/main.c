#include"base.h"
#include<stdlib.h>

/*
MAP LEGEND:
-1 - opponent's
0 - empty or opponent's
1 - my dot
2 - borders necessary
3 - part of a border
4 - already in base
*/

int main()
{
    int t[WIDTH*HEIGHT]=
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 0, 0, 0,
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
    fig wielokat;
    wielokat.num=0;
    base(t, &wielokat, 27, 27);
    frame granice;
    granice.num=0;
    buildbase(&granice, t);
    for(int i=0; i<granice.num; i++)
    {
        printf("%d %d \n", granice.line[i].x1+granice.line[i].y1*WIDTH, granice.line[i].x2+granice.line[i].y2*WIDTH);
    }
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            printf("%d ", t[i*WIDTH+j]);
        }
        printf("\n");
    }

    return 0;
}
