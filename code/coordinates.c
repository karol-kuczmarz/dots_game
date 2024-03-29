#include"coordinates.h"

vec dot_clicked(double x, double y)
{
    int column=(int)(x)/GAP;
    int line=(int)(y)/GAP;
    vec answer;
    if((x-(double)(column*GAP))*(x-(double)(column*GAP))+(y-(double)(line*GAP))*(y-(double)(line*GAP))<=RADIOUS*RADIOUS)
    {
        answer.x=column;
        answer.y=line;
        return answer;
    }
    if((x-(double)((column+1)*GAP))*(x-(double)((column+1)*GAP))+(y-(double)(line*GAP))*(y-(double)(line*GAP))<=RADIOUS*RADIOUS)
    {
        answer.x=column+1;
        answer.y=line;
        return answer;
    }
    if((x-(double)(column*GAP))*(x-(double)(column*GAP))+(y-(double)((line+1)*GAP))*(y-(double)((line+1)*GAP))<=RADIOUS*RADIOUS)
    {
        answer.x=column;
        answer.y=line+1;
        return answer;
    }
    if((x-(double)((column+1)*GAP))*(x-(double)((column+1)*GAP))+(y-(double)((line+1)*GAP))*(y-(double)((line+1)*GAP))<=RADIOUS*RADIOUS)
    {
        answer.x=column+1;
        answer.y=line+1;
        return answer;
    }
    answer.x=-1;
    answer.y=-1;
    return answer;
}

_Bool verify_click(int map[], vec test, int const WIDTH, int const HEIGHT)
{
	if(test.x<=0 || test.y<=0 || test.x>=WIDTH-1 || test.y>=HEIGHT-1)
	{
		return 0;
	}
	if(map[test.x+test.y*WIDTH]==0)
	{
		return 1;
	}
	return 0;
}
