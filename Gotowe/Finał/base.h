#include"definitions.h"

typedef
struct Polygon
{
    int num;
    int node[HEIGHT_MAX*WIDTH_MAX+5];
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
    seg line[WIDTH_MAX*HEIGHT_MAX*4];
}
frame;

void base(int maporg[], int map[], int map_help[], poly res, int beg, int act, int const WIDTH, int const HEIGHT);
void push_poly(poly a, int number);
int pop_poly(poly a);
_Bool sweep(poly test, int const WIDTH, int const HEIGHT);
_Bool ifcross(seg a, seg b);
_Bool ifinside(seg polynoid[], poly test, int point, int const WIDTH, int const HEIGHT);
void checkinside(poly res, int maporg[],  int map[], int map2[], int const WIDTH, int const HEIGHT);
void buildbase(frame *lines, int map[], int const WIDTH, int const HEIGHT);
void findbase(frame *lines, int map[], int index, int const WIDTH, int const HEIGHT);
void push_frame(frame *lines, int n1, int n2, int map[], int const WIDTH, int const HEIGHT);
int det(int x1, int y1, int x2, int y2, int x3, int y3);
int sgn(int x);
void swap(int *a, int *b);
