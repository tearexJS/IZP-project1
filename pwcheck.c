#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define LENGTH 102
#define INVALIG_ARGUMENT 2
#define NOT_ENOUGH_ARGS 3
#define TOO_MANY_ARGS 4
#define NUMBER_OF_POSSIBLE_CHARS 95
#define ERROR(msg, errCode)       \
    {                             \
        do                        \
        {                         \
            fprintf(stderr, msg); \
            return errCode;       \
        } while (0);              \
    }

// finding out if a string contains a character
bool isNum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
bool isAlpha(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
            return false;
    }
    return true;
}
bool containsChar(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
            return true;
    }
    return false;
}
float charSum(char *charCount)
{
    float sum = 0;

    for (int i = 0; i < NUMBER_OF_POSSIBLE_CHARS; i++)
    {
        if (charCount[i] > 0)
            sum += charCount[i];
    }
    return sum;
}
int uniqueCount(char *charCount)
{
    int uniqueCounter = 0;
    for (int i = 0; i < NUMBER_OF_POSSIBLE_CHARS; i++)
    {
        if (charCount[i] > 0)
            uniqueCounter++;
    }
    return uniqueCounter;
}
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

void strNcpy(char *src, char *dest, int len)
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
void shortestStr(char *psswd, int *minLength)
{
    int len = containsChar(psswd, '\n') ? length(psswd) - 1 : length(psswd);

    if (*minLength > len)
    {
        *minLength = len;
    }
}
bool containsSequenceOfChars(char *str, char c, int len)
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
            if (containsSequenceOfChars((psswd + i), psswd[i], param))
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
        if (param >= (len - 1))
            return 1;

        for (int i = 0; i < len; i++)
        {
            strNcpy((psswd + i), tmp1, param);

            for (int j = i; j < (len - param); j++)
            {

                strNcpy((psswd + j + param), tmp2, param);
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

void charCounter(char *psswd, char *charCount)
{
    int len = containsChar(psswd, '\n') ? length(psswd) - 1 : length(psswd);

    for (int i = 0; i < len; i++)
    {
        charCount[psswd[i] - 32]++;
    }
}
int parseArgument(int argc, int *level, int *param, char **argv, bool *statsFlag)
{

    if (containsChar(argv[1], '-'))
    {
        for (int i = 0; i < argc; i++)
        {
            if (cmpStr(argv[i], "-l"))
            {
                if ((i + 1) < argc && isNum(argv[i + 1]))
                    *level = strToInt(argv[i + 1]);
                else
                    ERROR("Invalid argument", INVALIG_ARGUMENT);
            }
            else if (cmpStr(argv[i], "-p"))
            {
                if ((i + 1) < argc && isNum(argv[i + 1]))
                    *param = strToInt(argv[i + 1]);
                else
                    ERROR("Invalid argument", INVALIG_ARGUMENT);
            }
            else if (cmpStr(argv[i], "--stats"))
            {
                *statsFlag = true;
            }
        }
        return 1;
    }
    else if (argc == 1)
        return 1;

    if (argc >= 3 && argc <= 4)
    {
        if (isNum(argv[1]))
            *level = strToInt(argv[1]);
        else
            ERROR("Invalid argument", INVALIG_ARGUMENT);
        if (isNum(argv[2]))
            *param = strToInt(argv[1]);
        else
            ERROR("Invalid argument", INVALIG_ARGUMENT);
        if (argc == 4 && cmpStr(argv[3], "--stats"))
            *statsFlag = true;

        return 1;
    }
    else if (argc > 4)
    {
        ERROR("Too many arguments", TOO_MANY_ARGS);
    }
    else
    {
        ERROR("Not enough arguments", NOT_ENOUGH_ARGS);
    }
}
int commands(int argc, char **argv, char *psswd, bool *statsFlag, char *charCount, int *minLength)
{
    int level = 1;
    int param = 1;

    if (parseArgument(argc, &level, &param, argv, statsFlag)==1)
    {
        if (level > 0 && level < 5 && param > 0)
        {
            if (*statsFlag)
            {
                shortestStr(psswd, minLength);
                charCounter(psswd, charCount);
            }
            if (level == 1)
            {
                return lvl1(psswd);
            }

            else if (level == 2)
            {
                return lvl2(psswd, param);
            }

            else if (level == 3)
            {
                return lvl3(psswd, param);
            }
            else if (level == 4)
            {
                return lvl4(psswd, param);
            }
        }
        else
            ERROR("Invalid argument", INVALIG_ARGUMENT);
    }
    else
        return parseArgument(argc, &level, &param, argv, statsFlag);

    return 0;
}

int main(int argc, char **argv)
{
    char psswd[LENGTH];
    char charCount[NUMBER_OF_POSSIBLE_CHARS] = {'\0'};

    bool statsFlag = false;
    int numberOfPasswords = 0;
    int minLength = INT_MAX;

    while (fgets(psswd, LENGTH, stdin))
    {
        numberOfPasswords++;
        int printPass = commands(argc, argv, psswd, &statsFlag, charCount, &minLength);
        if (printPass == 1)
        {
            printf("%s", psswd);
        }
        else if(printPass > 1)
            return commands(argc, argv, psswd, &statsFlag, charCount, &minLength);
        clean(psswd);
    }
    if (statsFlag)
    {
        printf("\nStatistika:\n");
        printf("Pocet roznych znakov:\t%d\n", uniqueCount(charCount));
        printf("Minimalna dlzka:\t\t%d\n", minLength);
        printf("Priemerna dlzka:\t\t%.1f", (charSum(charCount) / numberOfPasswords));
    }
    return 0;
}