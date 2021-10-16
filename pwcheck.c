#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 102
#define INVALIG_ARGUMENT 2
#define NOT_ENOUGH_ARGS 3

#define ERROR(msg, errCode)       \
    {                             \
        do                        \
        {                         \
            fprintf(stderr, msg); \
            return errCode;       \
        } while (0);              \
    }

// finding out if a string contains a character
int strToInt(char *str)
{
    char *endptr;
    int num = strtol(str, &endptr, 10);
    if (endptr != NULL)
    {
        return num;
    }
    return -1;
}

void clean(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = '\0';
    }
}

void strNcpy(char *src, char * dest, int len)
{
    int i = 0;
    for (; i < len && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
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

bool containsNChars(char *str, char c, int len)
{
    int occurences = 0;
    for (int i = 0; i < len && str[i] != '\0'; i++)
    {
        if (str[i] == c)
            occurences++;
        if (len == occurences)
            return true;
    }
    return false;
}
// comparing 2 strings if they are indetical
bool cmpStr(char *str1, char *str2)
{
    int str1Len = length(str1);
    int str2Len = length(str2);

    if (str1Len == str2Len)
    {
        for (int i = 0; i < str1Len; i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
// checking if the password contains 1 uppercase and 1 lowercase character
int lvl1(char *psswd)
{
    int len = length(psswd);
    bool upperCase = false;
    bool lowerCase = false;

    for (int i = 0; i < len; i++)
    {
        if (psswd[i] >= 'A' && psswd[i] <= 'Z')
        {
            upperCase = true;
        }
        else if (psswd[i] >= 'a' && psswd[i] <= 'z')
        {
            lowerCase = true;
        }
        if (upperCase && lowerCase)
            return 1;
    }
    return 0;
}
int ruleSum(bool *rules)
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += rules[i];
    }
    return sum;
}
// checking if the password matches the number of rules defined by the variable param
int lvl2(char *psswd, int param)
{
    bool rules[4] = {false};

    int len = length(psswd);

    if (lvl1(psswd))
    {
        if (param >= 1 && param <= 4)
        {
            for (int i = 0; i < len; i++)
            {
                if (psswd[i] >= 'A' && psswd[i] <= 'Z')
                    rules[0] = true;

                else if (psswd[i] >= 'a' && psswd[i] <= 'z')
                    rules[1] = true;

                else if (psswd[i] >= '0' && psswd[i] <= '9')
                    rules[2] = true;

                else if ((psswd[i] >= 32 && psswd[i] <= 47) || (psswd[i] >= 58 && psswd[i] <= 64) || (psswd[i] >= 91 && psswd[i] <= 96) || (psswd[i] >= 123 && psswd[i] <= 126))
                    rules[3] = true;
            }
            return ruleSum(rules) >= param ? 1 : 0;
        }
        else
        {
            // char  errMsg[] = "The argument is invalid";
            ERROR("errMsg", INVALIG_ARGUMENT);
        }
    }
    return 0;
}
// checking if the password does not contain a sequence of matching characters
int lvl3(char *psswd, int param)
{
    if (lvl2(psswd, param) == 1)
    {
        int len = length(psswd);

        for (int i = 0; i < len; i++)
        {
            if (containsNChars((psswd + i), psswd[i], param))
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int lvl4(char *psswd, int param)
{
    int len = length(psswd);
    char tmp1[LENGTH];
    char tmp2[LENGTH];

    if (lvl3(psswd, param))
    {
        if(param >= (len-1))
            return 1;

        for (int i = 0; i < len; i++)
        {
            strNcpy((psswd + i), tmp1,param); 
            
            for (int j = i; j < (len-param); j++)
            {

                strNcpy((psswd + j + param), tmp2,param);
                if (cmpStr(tmp1, tmp2))
                    return 0;
                clean(tmp2);
            }
            clean(tmp1);
        }
        return 1;
    }
    return 0;
}



int commands(int argc, char **argv, char *psswd)
{
    if (argc >= 2)
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

        if (cmpStr(argv[1], "1"))
        {
            return lvl1(psswd);
        }

        else if (cmpStr(argv[1], "2"))
        {
            return lvl2(psswd, strToInt(argv[2]));
        }

        else if (cmpStr(argv[1], "3"))
        {
            return lvl3(psswd, strToInt(argv[2]));
        }
        else if(cmpStr(argv[1], "4"))
        {
            return lvl4(psswd, strToInt(argv[2]));
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    char psswd[LENGTH];

    while (fgets(psswd, LENGTH, stdin))
    {
        if (commands(argc, argv, psswd) == 1)
        {
            printf("%s", psswd);
        }
        clean(psswd);
    }
    return 0;
}