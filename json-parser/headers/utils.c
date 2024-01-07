/* SPDX-License-Identifier: Apache-2.0 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "constants.h"


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

/*
 * read json file
 */
char *read_file(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char *json_str = (char *)malloc(MAX_JSON_SIZE * sizeof(char));
    if (json_str == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(json_str, sizeof(char), MAX_JSON_SIZE, file);

    json_str[bytesRead] = '\0';

    fclose(file);
    return json_str;
}