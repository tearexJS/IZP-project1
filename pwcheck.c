#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 102
#define NUMBER_OF_POSSIBLE_CHARS 95

#define INVALIG_ARGUMENT 2
#define NOT_ENOUGH_ARGS 3
#define TOO_MANY_ARGS 4
#define TOO_MANY_CHARS 5


#define ERROR(msg, errCode)       \
    {                             \
        do                        \
        {                         \
            fprintf(stderr, msg); \
            return errCode;       \
        } while (0);              \
    }

// checking if the password is longer than MAX_STRING_LENGTH characters
// if the password is not longer than MAX_STRING_LENGTH characters the function returns true otherwise false
bool isTooLong(char *psswd)
{
    for (int i = 0; psswd[i] != '\n'; i++)
    {
        if (i >= (MAX_STRING_LENGTH-2))
        {
            return true;
        }
    }
    return false;
}
// checking if the string contains only numbers, returns false if it contains something else than numbers otherwise true
bool isNum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
// returns true if the string contains a specified character otherwise false
bool containsChar(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
            return true;
    }
    return false;
}
// sums the number of characters from the array which contains the number of each character present in the passwords
// returns the number of characters
float charSum(int *charCount)
{
    float sum = 0;

    for (int i = 0; i < NUMBER_OF_POSSIBLE_CHARS; i++)
    {
        if (charCount[i] > 0)
            sum += charCount[i];
    }
    return sum;
}
// counts every element of int array which are bigger than 0, the array contains the number of each character present in the passwords
// returns the count
int uniqueCount(int *charCount)
{
    int uniqueCounter = 0;
    for (int i = 0; i < NUMBER_OF_POSSIBLE_CHARS; i++)
    {
        if (charCount[i] > 0)
            uniqueCounter++;
    }
    return uniqueCounter;
}
// converts the string to int
// returns the number if the string does not start with a number it returns -1
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
//sets all the elemnts of the string with '\0' thus clearing it's contents

void clean(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = '\0';
    }
}

//copies len bytes of source to destination

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

// compares the length of the password with the previous password length 
// keeps the smaller length
void shortestStr(char *psswd, int *minLength)
{
    int len = containsChar(psswd, '\n') ? length(psswd) - 1 : length(psswd);

    if (*minLength > len)
    {
        *minLength = len;
    }
}
// if a string contais a len sequence of character c returns true, otherwise false
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
// if one not matching character is found or the lengths are not equal returns false, otherwise true
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
// returns 1 if the password contains both uppercase and lowercase character, otherwise 0
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
//sums the contents of bool array and returns the sum
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
// returns 1 if the matched number of rules is greater than or equal to param, otherwise 0
int lvl2(char *psswd, int param)
{
    bool rules[4] = {false};

    int len = length(psswd);

    param = (param > 4) ? 4 : param;

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
// checking if the password does not contain a substring of specified length or longer
// returns 1 if does not contain a substring of specified length, otherwise 0 
int lvl4(char *psswd, int param)
{
    int len = length(psswd);
    char tmp1[MAX_STRING_LENGTH];
    char tmp2[MAX_STRING_LENGTH];

    if (lvl3(psswd, param))
    {
        if (param >= (len - 1))
            return 1;

        for (int i = 0; i < len; i++)
        {
            strNcpy((psswd + i), tmp1, param);

            for (int j = i + 1; j < (len - param); j++)
            {
                strNcpy((psswd + j), tmp2, param);
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
// counts the number of occurences of each character
void charCounter(char *psswd, int *charCount)
{
    int len = containsChar(psswd, '\n') ? length(psswd) - 1 : length(psswd);

    for (int i = 0; i < len; i++)
    {
        charCount[psswd[i] - 32]++;
    }
}
// parsing the input argument
// returns the values of level and param or an error code if an unexpected input occures
int parseArgument(int argc, int *level, int *param, char **argv, bool *statsFlag)
{

    if (argc > 1 && containsChar(argv[1], '-'))
    {
        for (int i = 1; i < argc; i++)
        {
            if (cmpStr(argv[i], "-l"))
            {
                if ((i + 1) < argc && isNum(argv[i + 1]))
                {
                    *level = strToInt(argv[i + 1]);
                    i++;
                }
                else
                    ERROR("Invalid argument", INVALIG_ARGUMENT);
            }
            else if (cmpStr(argv[i], "-p"))
            {
                if ((i + 1) < argc && isNum(argv[i + 1]))
                {
                    *param = strToInt(argv[i + 1]);
                    i++;
                }
                else
                    ERROR("Invalid argument", INVALIG_ARGUMENT);
            }
            else if (cmpStr(argv[i], "--stats"))
            {
                *statsFlag = true;
            }
            else if (!isNum(argv[i]))
            {
                ERROR("Invalid argument", INVALIG_ARGUMENT);
            }
        }
        return 1;
    }
    else if (argc == 1)
        return 1;

    if (argc >= 3 && argc <= 4)
    {
        if (isNum(argv[1]))
        {
            *level = strToInt(argv[1]);
        }
        else
        {
            ERROR("Invalid argument", INVALIG_ARGUMENT);
        }
        if (isNum(argv[2]))
        {
            *param = strToInt(argv[2]);
        }
        else
        {
            ERROR("Invalid argument", INVALIG_ARGUMENT);
        }
        if (argc == 4 && cmpStr(argv[3], "--stats"))
        {
            *statsFlag = true;
        }
        else if (argc == 4 && !cmpStr(argv[3], "--stats"))
        {
            ERROR("Invalid argument", INVALIG_ARGUMENT);
        }
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
// calls the functions responsible for checking the security levels specified by the variable level
// return what the previous functions return or an error code if an unexpected input occures
int commands(int argc, char **argv, char *psswd, bool *statsFlag, int *charCount, int *minLength)
{
    int level = 1;
    int param = 1;

    if (parseArgument(argc, &level, &param, argv, statsFlag) == 1)
    {
        if (param <= 0)
            ERROR("Invalid argument", INVALIG_ARGUMENT);

        if (*statsFlag)
        {
            shortestStr(psswd, minLength);
            charCounter(psswd, charCount);
        }
        switch (level)
        {
        case 1:
            return lvl1(psswd);
            break;

        case 2:
            return lvl2(psswd, param);
            break;
        case 3:
            return lvl3(psswd, param);
            break;
        case 4:
            return lvl4(psswd, param);
            break;
        default:
            ERROR("Invalid argument", INVALIG_ARGUMENT);
            break;
        }

    }
    else
        return parseArgument(argc, &level, &param, argv, statsFlag);

    return 0;
}

int main(int argc, char **argv)
{
    char psswd[MAX_STRING_LENGTH]; //stores the password
    int charCount[NUMBER_OF_POSSIBLE_CHARS] = {0}; // array to count the occurence of each character

    bool statsFlag = false; // variable for the stats flag
    int numberOfPasswords = 0; // variable to count the number of passwords
    int minLength = MAX_STRING_LENGTH; // variable to store the minimum length

    while (fgets(psswd, MAX_STRING_LENGTH, stdin))
    {
        numberOfPasswords++;
        if (isTooLong(psswd))
        {
            ERROR("The input is too long", TOO_MANY_CHARS);
        }

        int printPassword = commands(argc, argv, psswd, &statsFlag, charCount, &minLength);

        if (printPassword == 1)
        {
            printf("%s", psswd);
        }
        else if (printPassword > 1)
        {
            return commands(argc, argv, psswd, &statsFlag, charCount, &minLength);
        }
        clean(psswd);
    }
    if (statsFlag)
    {
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", uniqueCount(charCount));
        printf("Minimalni delka: %d\n", minLength);
        printf("Prumerna delka: %.1f", (charSum(charCount) / numberOfPasswords));
    }
    return 0;

}