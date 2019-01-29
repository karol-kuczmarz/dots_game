#include"definitions.h"

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
_Bool ifinside(seg polynoid[], poly test, int point);
void checkinside(poly res, int map[]);
void buildbase(frame *lines, int map[]);
void findbase(frame *lines, int map[], int index);
void push_frame(frame *lines, int n1, int n2, int map[]);
int det(int x1, int y1, int x2, int y2, int x3, int y3);
int sgn(int x);
void swap(int *a, int *b);
