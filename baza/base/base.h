#include<stdio.h>

#define HEIGHT 6
#define WIDTH 6

typedef
struct Polygon
{
    int num;
    int node[HEIGHT*WIDTH+5];
}
fig, *poly;

typedef
struct Segment
{
    int x1;
    int y1;
    int x2;
    int y2;
}
seg;

void base(_Bool map[], poly res, int beg, int act);
void push_poly(poly a, int number);
int pop_poly(poly a);
void wypisz(poly a);
