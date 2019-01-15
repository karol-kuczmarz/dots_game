#include"base.h"
#include<stdlib.h>

int main()
{
    _Bool t[WIDTH*HEIGHT]=
    {
        0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
    };
    fig wielokat;
    wielokat.num=0;
    base(t, &wielokat, 15, 15);
    return 0;
}
