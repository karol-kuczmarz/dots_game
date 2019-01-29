#include<stdio.h>

#define RADIOUS 5
#define GAP 20
#define HEIGHT 8
#define WIDTH 8


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

typedef
struct Vector
{
    int x;
    int y;
}vec;

int det(int x1, int y1, int x2, int y2, int x3, int y3);
int sgn(int x);
void swap(int *a, int *b);
