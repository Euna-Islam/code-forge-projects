/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_JSON_SIZE 100
#define MAX_KEY_NO 10
#define MAX_KEY_SIZE 50
#define MAX_VAL_SIZE 100

typedef struct
{
    char key[MAX_KEY_SIZE];
    char value[MAX_VAL_SIZE];
} key_value_pair;

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
char *read_file()
{
    const char *json_file = "source.json";
    FILE *file = fopen(json_file, "r");
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
    return remove_spaces(json_str);
}
/*
 * parse json content
 */
void parse_json(const char *json)
{
    key_value_pair json_data[MAX_KEY_NO];
    int key_count = 0;

    const char *delimiters = strtok((char *)json, "{},\":");
    char currentKey[MAX_KEY_SIZE];
    int keyFlag = 0;

    while (delimiters != NULL)
    {
        if (strcmp(delimiters, " ") != 0)
        {
            if (keyFlag == 0)
            {
                strcpy(currentKey, delimiters);
                keyFlag = 1;
            }
            else
            {
                strcpy(json_data[key_count].key, currentKey);
                strcpy(json_data[key_count].value, delimiters);
                key_count++;
                keyFlag = 0;
            }
        }
        delimiters = strtok(NULL, "{},\":");
    }

    for (int i = 0; i < key_count; i++)
    {
        printf("Key: %s, Value: %s\n", json_data[i].key, json_data[i].value);
    }
}

int main()
{
    char *json_str = read_file();
    parse_json(json_str);
    return 0;
}
