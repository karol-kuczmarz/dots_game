#include"definitions.h"

typedef
struct pipes
{
    FILE *fifo_in, *fifo_out;
    int isA;
}
*PipesPtr;

PipesPtr initPipes(int argc, char *argv[]);
void     sendStringToPipe(PipesPtr channel, const char *data);
_Bool     getStringFromPipe(PipesPtr channel, char *buffer, size_t size);
void     closePipes(PipesPtr channel);
