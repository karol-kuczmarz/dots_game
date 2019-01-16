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

typedef
struct Frame
{
    int num;
    seg line[WIDTH*HEIGHT*4];
}
frame;

void base(int map[], poly res, int beg, int act);
void push_poly(poly a, int number);
int pop_poly(poly a);
_Bool sweep(poly test);
_Bool ifcross(seg a, seg b);
int det(int x1, int y1, int x2, int y2, int x3, int y3);
int sgn(int x);
_Bool ifinside(seg polynoid[], poly test, int point);
void checkinside(poly res, int map[]);

void wypisz(poly a);
