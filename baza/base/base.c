#include"base.h"

void base(_Bool map[], poly res, int beg, int act)
{
    if(act==beg && res->num>3 && sweep(res)==1)
    {
        wypisz(res);
        return;
    }
    if(map[act+WIDTH]==1)
    {
        map[act+WIDTH]=0;
        push_poly(res, act+WIDTH);
        base(map, res, beg, act+WIDTH);
        pop_poly(res);
        map[act+WIDTH]=1;
    }
    if(map[act+WIDTH+1]==1)
    {
        map[act+WIDTH+1]=0;
        push_poly(res, act+WIDTH+1);
        base(map, res, beg, act+WIDTH+1);
        pop_poly(res);
        map[act+WIDTH+1]=1;
    }
    if(map[act+WIDTH-1]==1)
    {
        map[act+WIDTH-1]=0;
        push_poly(res, act+WIDTH-1);
        base(map, res, beg, act+WIDTH-1);
        pop_poly(res);
        map[act+WIDTH-1]=1;
    }
    if(map[act-WIDTH]==1)
    {
        map[act-WIDTH]=0;
        push_poly(res, act-WIDTH);
        base(map, res, beg, act-WIDTH);
        pop_poly(res);
        map[act-WIDTH]=1;
    }
    if(map[act-WIDTH-1]==1)
    {
        map[act-WIDTH-1]=0;
        push_poly(res, act-WIDTH-1);
        base(map, res, beg, act-WIDTH-1);
        pop_poly(res);
        map[act-WIDTH-1]=1;
    }
    if(map[act-WIDTH+1]==1)
    {
        map[act-WIDTH+1]=0;
        push_poly(res, act-WIDTH+1);
        base(map, res, beg, act-WIDTH+1);
        pop_poly(res);
        map[act-WIDTH+1]=1;
    }
    if(map[act+1]==1)
    {
        map[act+1]=0;
        push_poly(res, act+1);
        base(map, res, beg, act+1);
        pop_poly(res);
        map[act+1]=1;
    }
    if(map[act-1]==1)
    {
        map[act-1]=0;
        push_poly(res, act-1);
        base(map, res, beg, act-1);
        pop_poly(res);
        map[act-1]=1;
    }
}

void push_poly(poly a, int number)
{
    a->node[a->num]=number;
    a->num++;
}

int pop_poly(poly a)
{
    a->num--;
    return a->node[a->num];
}

_Bool sweep(poly test)
{
    _Bool online[test->num];
    seg lines[test->num];
    for(int i=0; i<test->num-1; i++)
    {
        lines[i].x1=test->node[i]%WIDTH;
        lines[i].y1=test->node[i]/WIDTH;
        lines[i].x2=test->node[i+1]%WIDTH;
        lines[i].y2=test->node[i+1]/WIDTH;
    }
    lines[test->num-1].x1=test->node[test->num-1]%WIDTH;
    lines[test->num-1].y1=test->node[test->num-1]/WIDTH;
    lines[test->num-1].x2=test->node[0]%WIDTH;
    lines[test->num-1].y2=test->node[0]/WIDTH;
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<test->num; j++)
        {
            if((lines[j].y1<=i && lines[j].y2>=i) || (lines[j].y1>=i && lines[j].y2<=i))
            {
                online[j]=1;
            }
            else
            {
                online[j]=0;
            }
        }
        for(int j=0; j<test->num-1; j++)
        {
            for(int k=j+1; k<test->num; k++)
            {
                if(online[j] && online[k])
                {
                    if(ifcross(lines[j], lines[k])==1)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

_Bool ifcross(seg a, seg b)
{
    int det1=det(a.x1, a.y1, a.x2, a.y2, b.x1, b.x2);
    if(det1!=0 && (-1)*det1==det(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2)
    {
        int det2=det(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1);
        if(det!=0 && (-1)*det2==det(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2))
        {
            return 1;
        }
    }
    return 0;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

void wypisz(poly a)
{
    for(int i=0; i<a->num; i++)
    {
        printf("%d %d       ", a->node[i]/WIDTH, a->node[i]%HEIGHT);
    }
    printf("\n");
}
