#include"move.h"

void move(int map[], frame *lines, int chosen, int *opp_points, int *my_points, int const WIDTH, int const HEIGHT)
{
    int mapcopy[WIDTH*HEIGHT];
    int mapcopy2[WIDTH*HEIGHT];
    map[chosen]=1;
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        mapcopy2[i]=0;
        if(map[i]==3 || map[i]==1)
        {
            mapcopy[i]=1;
        }
        else
        {
            if(map[i]<=0)
            {
                mapcopy[i]=0;
            }
            else
            {
                mapcopy[i]=-1;
            }
        }
    }
    fig polyg;
    polyg.num=0;
    base(map, mapcopy, mapcopy2, &polyg, chosen, chosen, WIDTH, HEIGHT);
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if(map[i]==3)
        {
            mapcopy[i]=3;
        }
    }
    buildbase(lines, mapcopy, WIDTH, HEIGHT);
    pointsandverify(map, mapcopy, mapcopy2, opp_points, my_points, WIDTH, HEIGHT);
}

void pointsandverify(int map[], int mapcopy[], int mapcopy2[], int *opp_points, int *my_points, int const WIDTH, int const HEIGHT)
{
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if(map[i]<0 && map[i]>-6 && mapcopy[i]==4)
        {
            *my_points=*my_points+2;
            *opp_points=*opp_points-1;
            map[i]=-6;
        }
        else
        {
            if(mapcopy[i]==4 && map[i]!=-6)
            {
                map[i]=7;
            }
            else
            {
                if(mapcopy[i]==3 && map[i]==1 && mapcopy2[i]==0)
                {
                    map[i]=3;
                }
                else
                {
                    if(mapcopy2[i]==2)
                    {
                        map[i]=5;
                    }
                }
            }
        }
    }
}
