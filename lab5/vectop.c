/*********************************************************
* Filenmae: vectop.c
* Author: Zach Campbell
* Description: Vector Calculator UI program
* Date: 10/1/26
* Version: 1.0
* Notes:
*   - 
* Compile:
*   - gcc -Wall -Wextra -o main vectop.c vector.c
* Run:
*   - ./main
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "vector.h"



int main (void)
{
    char input[100];
    Command command;

    printf("Vector Calculator\n");
    printf("Enter -h or help for help.\n");

    while(1)
    {
        printf("> ");

        if (fgets (input, sizeof (input), stdin) == NULL)
        {
            break;
        }
        
        command = get_command (input);

     switch (command)
     {
        case CMD_QUIT:
            quit();
            return 0;
        
        case CMD_HELP:
            help();
            break;

        case CMD_LIST:
            list();
            break;

        case CMD_CLEAR:
            clear();
            break;

        case CMD_OPERATION:
            getvect (input);
            break;

        default:
            error();
            break;
        }
    }
    return 0;
}