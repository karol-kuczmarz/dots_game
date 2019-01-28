#include"base.h"

void base(int map[], poly res, int beg, int act)
{
    if(act==beg && res->num>3 && sweep(res)==1)
    {
        checkinside(res, map);
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
    int det1=det(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1);
    if(det1!=0 && (-1)*sgn(det1)==sgn(det(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2)))
    {
        int det2=det(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1);
        if(det2!=0 && (-1)*sgn(det2)==sgn(det(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2)))
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

int sgn(int x)
{
    if(x>0)
    {
        return 1;
    }
    if(x<0)
    {
        return -1;
    }
    return 0;
}

_Bool ifinside(seg polynoid[], poly test, int point)
{
    int px=point%WIDTH, py=point/WIDTH;
    int signum=sgn(det(polynoid[0].x1, polynoid[0].y1, polynoid[0].x2, polynoid[0].y2, px, py));
    for(int i=1; i<test->num; i++)
    {
        if(signum!=sgn(det(polynoid[i].x1, polynoid[i].y1, polynoid[i].x2, polynoid[i].y2, px, py)))
        {
            return 0;
        }
    }
    return 1;
}

void checkinside(poly res, int map[])
{
    seg polynoid[res->num];
    for(int i=0; i<res->num-1; i++)
    {
        polynoid[i].x1=res->node[i]%WIDTH;
        polynoid[i].y1=res->node[i]/WIDTH;
        polynoid[i].x2=res->node[i+1]%WIDTH;
        polynoid[i].y2=res->node[i+1]/WIDTH;
    }
    polynoid[res->num-1].x1=res->node[res->num-1]%WIDTH;
    polynoid[res->num-1].y1=res->node[res->num-1]/WIDTH;
    polynoid[res->num-1].x2=res->node[0]%WIDTH;
    polynoid[res->num-1].y2=res->node[0]/WIDTH;
    for(int i=0; i<HEIGHT*WIDTH; i++)
    {
        if(map[i]==0)
        {
            if(ifinside(polynoid, res, i)==1)
            {
                map[i]=2;
            }
        }
    }
}

void buildbase(frame *lines, int map[])
{
    for(int i=0; i<HEIGHT*WIDTH; i++)
    {
        if(map[i]==2)
        {
            findbase(lines, map, i);
        }
    }
}

void findbase(frame *lines, int map[], int index)
{
    map[index]=4;
    if(map[index-1]==2 || map[index-1]==4)
    {
        if(map[index-1]==2)
        {
            findbase(lines, map, index-1);
        }
    }
    else
    {
        if(map[index-WIDTH]==1 || map[index-WIDTH]==3)
        {
            push_frame(lines, index-1, index-WIDTH, map);
        }
        else
        {
            if(map[index-WIDTH-1]==1 || map[index-WIDTH-1]==3)
            {
                    push_frame(lines, index-1, index-WIDTH-1, map);
            }
        }
        if(map[index+WIDTH]==1 || map[index+WIDTH]==3)
        {
            push_frame(lines, index-1, index+WIDTH, map);
        }
        else
        {
            if(map[index+WIDTH-1]==1 || map[index+WIDTH-1]==3)
            {
                push_frame(lines, index-1, index+WIDTH-1, map);
            }
        }
    }
    if(map[index+1]==2 || map[index+1]==4)
    {
        if(map[index+1]==2)
        {
            findbase(lines, map, index+1);
        }
    }
    else
    {
        if(map[index-WIDTH]==1 || map[index-WIDTH]==3)
        {
                push_frame(lines, index+1, index-WIDTH, map);
        }
        else
        {
            if(map[index-WIDTH+1]==1 || map[index-WIDTH+1]==3)
            {
                push_frame(lines, index+1, index-WIDTH+1, map);
            }
        }
        if(map[index+WIDTH]==1 || map[index+WIDTH]==3)
        {
            push_frame(lines, index+1, index+WIDTH, map);
        }
        else
        {
            if(map[index+WIDTH+1]==1 || map[index+WIDTH+1]==3)
            {
                push_frame(lines, index+1, index+WIDTH+1, map);
            }
        }
    }
    if(map[index-WIDTH]==2 || map[index-WIDTH]==4)
    {
        if(map[index-WIDTH]==2)
        {
            findbase(lines, map, index-WIDTH);
        }
    }
    else
    {
        if(map[index-1]==1 || map[index-1]==3)
        {
            push_frame(lines, index-1, index-WIDTH, map);
        }
        else
        {
            if(map[index-WIDTH-1]==1 || map[index-WIDTH-1]==3)
            {
                push_frame(lines, index-WIDTH, index-WIDTH-1, map);
            }
        }
        if(map[index+1]==1 || map[index+1]==3)
        {
                push_frame(lines, index+1, index-WIDTH, map);
        }
        else
        {
            if(map[index-WIDTH+1]==1 || map[index-WIDTH+1]==3)
            {
                push_frame(lines, index-WIDTH, index-WIDTH+1, map);
            }
        }
    }
    if(map[index+WIDTH]==2 || map[index+WIDTH==4])
    {
        if(map[index+WIDTH]==2)
        {
            findbase(lines, map, index+WIDTH);
        }
    }
    else
    {
        if(map[index-1]==1 || map[index-1]==3)
        {
                push_frame(lines, index-1, index+WIDTH, map);
        }
        else
        {
            if(map[index+WIDTH-1]==1 || map[index+WIDTH-1]==3)
            {
                    push_frame(lines, index+WIDTH, index+WIDTH-1, map);
            }
        }
        if(map[index+1]==1 || map[index+1]==3)
        {
                push_frame(lines, index+1, index+WIDTH, map);
        }
        else
        {
            if(map[index+WIDTH+1]==1 || map[index+WIDTH+1]==3)
            {
                push_frame(lines, index+WIDTH, index+WIDTH+1, map);
            }
        }
    }
}

void push_frame(frame *lines, int n1, int n2, int map[])
{
    map[n1]=3;
    map[n2]=3;
    if(n1>n2)
    {
        swap(&n1, &n2);
    }
    for(int i=0; i<lines->num; i++)
    {
        if(lines->line[i].x1+lines->line[i].y1*WIDTH==n1)
        {
            if(lines->line[i].x2+lines->line[i].y2*WIDTH==n2)
            {
                return;
            }
        }
    }
    lines->line[lines->num].x1=n1%WIDTH;
    lines->line[lines->num].y1=n1/WIDTH;
    lines->line[lines->num].x2=n2%WIDTH;
    lines->line[lines->num].y2=n2/WIDTH;
    lines->num++;
}

void swap(int *a, int *b)
{
    int c=*a;
    *a=*b;
    *b=c;
}

void wypisz(poly a)
{
    for(int i=0; i<a->num; i++)
    {
        printf("%d %d       ", a->node[i]/WIDTH, a->node[i]%HEIGHT);
    }
    printf("\n");
}
