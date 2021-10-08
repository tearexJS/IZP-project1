#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 102
typedef struct CommandArgs
{
    char arg1;
    char arg2;
    char arg3;
}CommandArgs;

typedef struct Command
{
    char * name;
    int (*func_ptr)(CommandArgs);
    int argc;

}Command;
/*const Command CommandList[4]
{
    
};*/
int length(char *str[])
{ 
    int i = 0;
    while (str[i] != '\n')
    {
        i++;
    }
    return i;
}

/*bool cmpStr(char *str1[], char *str2[])
{
    
    for(int i = 0; i<LENGTH;i++)
    {
        for(int j = 0; j<)
    }
}*/

/*void commands(int argc, char **argv, char *psswd[])
{
    if(argc >= 2)
    {
        if(argv[0] == "")
        {

        }
    }
}*/

int main(int argc, char **argv)
{
    char psswd[LENGTH];

    while(fgets(psswd, LENGTH, stdin))
    {
        commands(argc, argv, &psswd);
    }

}