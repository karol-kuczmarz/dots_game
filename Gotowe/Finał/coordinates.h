#include"definitions.h"

typedef
struct Vector
{
    int x;
    int y;
}vec;

vec dot_clicked(double x, double y);
_Bool verify_click(int map[], vec test, int const WIDTH, int const HEIGHT);
