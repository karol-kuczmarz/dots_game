#include"base.h"
#include<stdlib.h>

/*
MAP LEGEND:
-1 - opponent's
0 - empty or opponent's
1 - occupied mine
2 - inside something, borders in future
3 - part of a border
4 - inside base
*/

int main()
{
    int t[WIDTH*HEIGHT]=
    {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 0,
        0, 1, 0, 0, 1, 0,
        0, 0, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
    };
    int t2[WIDTH*HEIGHT];
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        t2[i]=t[i];
    }
    fig wielokat;
    wielokat.num=0;
    base(t, &wielokat, 14, 14);
    frame granice;
    granice.num=0;

    return 0;
}
