#include"move.h"

void move(int map[], frame *lines, int chosen, int *opp_points, int *my_points)
{
    int mapcopy[WIDTH*HEIGHT];
    map[chosen]=1;
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if(map[i]==3 || map[i]==1)
        {
            mapcopy[i]=1;
        }
        else
        {
            mapcopy[i]=0;
        }
    }
    fig polyg;
    polyg.num=0;
    base(mapcopy, &polyg, chosen, chosen);
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if(map[i]==3)
        {
            mapcopy[i]=3;
        }
    }
    buildbase(lines, mapcopy);
    pointsandverify(map, mapcopy, opp_points, my_points);

}

void pointsandverify(int map[], int mapcopy[], int *opp_points, int *my_points)
{
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if(map[i]==-1 && mapcopy[i]==4)
        {
            *my_points=*my_points+2;
            *opp_points=*opp_points-1;
            map[i]=-2;
        }
        else
        {
            if(mapcopy[i]==4)
            {
                map[i]=6;
            }
            else
            {
                if(mapcopy[i]==3 && map[i]==1)
                {
                    map[i]=3;
                }
            }
        }
    }
}
