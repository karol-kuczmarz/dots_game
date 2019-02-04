#include"communication.h"

PipesPtr Channel;

void fifo_init(int argc, char *argv[])
{
    Channel=initPipes(argc, argv);
}

void send_info(int index)
{
    char text[10];
    sprintf(text, "%d\n", index);
    sendStringToPipe(Channel, text);
}

void get_info(int *ans)
{
    char text[10];
    if(getStringFromPipe(Channel, text, 10)==1)
    {
        *ans=string_to_int(text);
        return;
    }
    *ans=-1;
}

int string_to_int(char text[])
{
    int ans=0;
    for(int i=0; i<(int)strlen(text) && isdigit(text[i]); i++)
    {
        ans=ans*10+text[i]-'0';
    }
    return ans;
}
