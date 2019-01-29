#include"sizes.h"

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

void swap(int *a, int *b)
{
    int c=*a;
    *a=*b;
    *b=c;
}
