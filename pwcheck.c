#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 102

// finding out if a string contains a character
int strToInt(char *str)
{
    char *endptr;
    int retval = strtol(str, &endptr, 10);
    if(endptr != NULL)
    {
        return 0;
    }
    return retval;
}

// calculating the length of the password
int length(char *str)
{ 
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

bool contains(char *str, char c)
{
    int len = length(str);

    for(int i = 0; i<len; i++)
    {
        if(str[i] == c)
            return true;
    }
    return false;
}
// comparing 2 strings if they are indetical
bool cmpStr(char *str1, char *str2)
{
    int str1Len = length(str1);
    int str2Len = length(str2);

    if(str1Len == str2Len)
    {
        for(int i = 0; i<str1Len; i++)
        {
            if(str1[i]!=str2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
void clean(char *str)
{
    for(int i = 0; str[i]!='\0'; i++)
    {
        str[i] = '\0';
    }
}
int lvl1 (char *psswd)
{
    int len = length(psswd);
    bool upperCase = false;
    bool lowerCase = false;

    for(int i = 0; i<len; i++)
    {
        if(psswd[i] >= 'A' && psswd[i]<='Z')
        {
            upperCase = true;
        }
        else if(psswd[i] >='a' && psswd[i]<='z')
        {
            lowerCase = true;
        }
        if(upperCase && lowerCase)
            return 1;
    }
    return 0;
}

int commands(int argc, char **argv, char *psswd)
{
    if(argc >= 2)
    {
        /*if(contains(argv[1], '-'))
        {
            for(int i = 1; i < argc; i++)
            {
                if(cmpStr(argv[i], "-l"))
                {

                }
                else if(cmpStr(argv[i], "-p"))
                {

                }
                else if(cmpStr(argv[i], "--stats"))
                {

                }
            }
        }*/
        if(cmpStr(argv[1], "1"))
        {
            return lvl1(psswd);
        }
        /*else if(cmpStr(argv[1], "2"))
        {

        }
        else if(cmpStr(argv[1], "3"))
        {

        }
        else if(cmpStr(argv[1], "4"))
        {

        }*/
        
    }
    return 0;
}

int main(int argc, char **argv)
{
    char psswd[LENGTH];

    while(fgets(psswd, LENGTH, stdin))
    {
        if(commands(argc, argv, psswd) == 1)
        {
            printf("%s", psswd);
        }
        clean(psswd);
    }

}