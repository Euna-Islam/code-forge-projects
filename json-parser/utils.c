#include <string.h>
#include "utils.h"

/*
 * remove spaces and new lines from the json content
 */
char *remove_spaces(char *str)
{
    int len = strlen(str);
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ' && str[i] != '\n')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
    return str;
}