#include<stdio.h>
#include"supporting_functions.h"
#include"sizes.h"

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

void wypisz(poly a);
