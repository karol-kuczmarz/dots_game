#include"coordinates.h"
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
    vec pom=dot_clicked(13.5, 26.7);
    printf("%d %d\n", pom.x, pom.y);

    return 0;
}
