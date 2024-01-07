/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/constants.h"

/*
 * struct for JSON key-value pair
 */
typedef struct
{
    char key[MAX_KEY_SIZE];
    char value[MAX_VAL_SIZE];
} key_value_pair;


/*
 * parse json content
 */
void parse_json(const char *json)
{
    printf("The json content from file : \n");
    printf("................................\n");
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

/*
 * read json file name form user
 */
void read_json_file_name() {
    char file_name[MAX_FILENAME_SIZE];
    printf("Enter JSON file name[max 30 characters]: \n");

    if(fgets(file_name, sizeof(file_name), stdin) != NULL) {
        size_t name_len = strlen(file_name);

        if(name_len > 0 && file_name[name_len - 1] == '\n') {
            file_name[name_len - 1] = '\0';
        }

        if (strlen(file_name) > MAX_FILENAME_SIZE - 1) {
            printf("Filename is too long!");
        } else {
            //start processing JSON
            char *json_str = read_file(file_name);
            parse_json(remove_spaces(json_str));
        }
    } else {
        printf("Error reading input");
        exit(EXIT_FAILURE);
    }
}

/*
 * take user input
 * process input
 */
void start_app() {
    printf("*************WELCOME************\n");
    printf("................................\n");
    printf("Enter 0 for help:\n");
    while(1) {
        printf("Select Option: ");
        int user_input  = -1;
        scanf("%d", &user_input);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (user_input)
        {
        case 0:
            char *file_content = read_file("config/help.txt");
            printf(file_content);
            printf("\n");
            break;
        case 1:
            printf("Quiting Application!");
            exit(EXIT_SUCCESS);
            break;
        case 2:
            read_json_file_name();
            break;
        default:
            break;
        }
            
    }
}

int main()
{
    start_app();
    return 0;
}
