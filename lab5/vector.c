/***************************************************************
* Filename: vector.c
* Author: Zach Campbell
* Description: Function definitions for vector calculator
* Date: 10/1/26
* Version: 2.0
* Notes:
*   - getvect() was over 600 lines, split into 
*   internal command handlers
* Compile:
*   - gcc -Wall -Wextra -o main vectop.c vector.c
* Run:
*   - ./main
****************************************************************/

/***************************************************************************************************
* Pseudo Code:
* User inputs at least 2 vectors
* getvect function gets vectors, places them into vector array
* User calls operation helper function
* Perform vectop via helper function  
* Pass by reference in new_vect array //WANT TO CYCLE THROUGH THESE TO MINIMIZE STACK MEMORY USAGE
* Return values
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "vector.h"

// Permanant vector storage
static Vector vectors[MAX_VECTORS];

// Working vector storage
static Vector new_vect[MAX_VECTORS];

// Current working-vector position
static int new_vect_index = 0;

// Internal command handlers
static void display_vector_command (char *tokens[]);
static void handle_operation (char *tokens[]);
static void handle_assignment (char *tokens[], int count);
static void handle_assignment_operation (char *tokens)

// Vector memory functions

int findvect (const char *name) 
{
    for (int i = 0; i < MAX_VECTORS; i++)
    {
        if (strcmp(vectors[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}


int add_vector (Vector new_vector)
{
    int index;

    index = findvect (new_vector.name);

    if (index >= 0)
    {
        vectors[index] = new_vector;
        return 0;
    }

    for (int i = 0; i < MAX_VECTORS; i++)
    {
        if (vectors[i].name[0] == '\0')
        {
            vectors[i] = new_vector;
            return 0;
        }
    }

    return -1;

}

int get_vector (const char *name, Vector *result)
{
    int index = findvect (name);
    
    if (index < 0)
    {
        return -1;
    }

    *result = vectors[index];

    return 0;
}

void clear (void) 
{
    for (int i = 0; i < MAX_VECTORS; i++)
    {
        vectors[i].name[0] = '\0';
    }
}

// Vectop functions

void addvect (Vector *a, Vector *b, Vector *result) 
{ 
    result -> x = a -> x + b -> x;
    result -> y = a -> y + b -> y;
    result -> z = a -> z + b -> z;
}

void subvect (Vector *a, Vector *b, Vector *result) 
{
    result -> x = a -> x - b -> x;
    result -> y = a -> y - b -> y;
    result -> z = a -> z - b -> z;
}

void scalmult (Vector *a, double scalar, Vector *result) 
{
    result -> x = a -> x * scalar;
    result -> y = a -> y * scalar;
    result -> z = a -> z * scalar;
}

double dotprod (Vector *a, Vector *b)
{
    return (a -> x * b -> x) 
    + (a -> y * b -> y)
    + (a -> z * b -> z);
}

void crossprod (Vector *a, Vector *b, Vector *result)
{
    result -> x = (a -> y * b -> z) - (a -> z * b -> y);
    result -> y = (a -> z * b -> x) - (a -> x * b -> z);
    result -> z = (a -> x * b -> y) - (a -> y * b-> x);
}

// Operation helper

int resopvect (Vector *a, Vector *b, char operation, double scalar, Vector *result, double *scalar_result)
{
    switch (operation)
    {
        case OP_ADD:
            addvect (a, b, result);
            break;

        case OP_SUB:
            subvect (a, b, result);
            break;
    
        case OP_MULT:
            scalmult (a, scalar, result);
            break;
        
        case OP_DOT:
            *scalar_result = dotprod (a, b);
            break;
        
        case OP_CROSS:
            crossprod (a, b, result);
            break;
        
        default:
            return -1;
    }

    return 0;

    }

// Vector display functions

void disvect (Vector vector) 
{
    printf("%s = %f %f %f\n",
    vector.name,
    vector.x,
    vector.y,
    vector.z);
}

void list (void) 
{
    for (int i = 0; i < MAX_VECTORS; i++)
    {
        if (vectors[i].name[0] != '\0')
        {
            disvect (vectors[i]);
        }
    }
}

// UI Layer

int tokenize (char *input, char *tokens[])
{
    int count = 0;
    char *token;

    token = strtok (input, " ,\n");

    while (token != NULL)
    {
        if (count >= 5)
        {
            return 6;
        }
        tokens[count] = token;
        count++;

        token = strtok (NULL, " ,\n");
    }

    return count;
}

int is_number (const char *token)
{
    char *endptr;

    strtof (token, &endptr);

    return token[0] != '\0' && *endptr == '\0';
}

Command get_command (const char *input)
{
    char command[20];

    if (sscanf (input, "%19s", command) != 1)
    {
        return CMD_OPERATION;
    }

    switch (command[0])
    {
        case 'q':
            if (strcmp (command, "quit") == 0)
            {
                return CMD_QUIT;
            }
            break;

        case 'h':
            if (strcmp (command, "help") == 0)
            {
                return CMD_HELP;
            }
            break;
        
        case 'l':
            if (strcmp (command, "list") == 0)
            {
                return CMD_LIST;
            }
            break;
        
        case 'c':
            if (strcmp (command, "clear") == 0)
            {
                return CMD_CLEAR;
            }
            break;

        case '-':
            if (strcmp (command, "-h") == 0)
            {
                return CMD_HELP;
            }
            break;

        default:
            break;
    }

    return CMD_OPERATION;
}

void getvect (char *input)
{
    char *tokens[5];
    int count = tokenize (input, tokens);

    switch (count)
    {
        //case # = tokens handled
        case 1:
            display_vector_command (tokens);
            break;

        case 3:
            handle_operation (tokenize);
            break;

        case 4:
        case 5:
            handle_assignment (tokens, count);
            break;

        default:
            error();
            break;
    }
}

static void display_vector_command (char *tokens[])
{
    int index = findvect (tokens[0]);

    if (index == -1)
    {
        printf("Error: Vector not found.\n");
        return;
    }

    disvect (vectors[index]);
}
          

void quit (void)
{
    printf("Exiting Vector Calculator.\n");
}

void help (void)
{
    printf("\nVector Calculator Commands:\n");
    printf("> a = 1 2 3     Create a vector\n");
    printf("> a             Display a vector\n");
    printf("> a + b         Add two vectors\n");
    printf("> c = a + b     Add two vectors and assign result\n");
    printf("> c = a - b     Subtract two vectors and assign result\n");
    printf("> c = a * 2     Scalar multiplication and assign result\n");
    printf("> c = a . b     Dot product of two vectors and assign result\n");
    printf("> c = a x b     Cross product of two vectors and assign result\n");
    printf("> list          List all vectors\n");
    printf("> clear         Clear all vectors\n");
    printf("> -h            Display help menu\n");
    printf("> help          Display help menu\n");
    printf("> quit          Exit program\n\n");
}

void error (void)
{
    printf("Error: Invalid command.\n");
}



