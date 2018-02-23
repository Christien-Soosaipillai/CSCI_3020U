/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here




int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    
    // input argument variables
    
        
    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    
    // for ( int i = 0; i < argc; i++) {
    //     strcpy (buffer,argv[i]);
    // }

    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
        


        if( strstr(buffer, " ")!=NULL) {
            char *token2 = strtok(buffer," ");
            strcpy(command, token2);

            char *token3 = strtok(NULL,"\n");
            strcpy(arg, token3);
            // while (token2) {
            //     printf("%s\n",token2);
            //     token2 = strtok(NULL," ");
            //     strcpy(arg, token2);
            // }
        }

        char *token1 = strtok(buffer,"\n");
        strcpy(command, token1);

        printf("\n");

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            if(arg == NULL){
                printf("ARGUMENT MISSING");
            }
            else if (arg != NULL){
                printf("%s", arg);
            }
            printf("\n");
            // chdir(arg);
        }
         else if (strcmp(command, "clr") == 0) {
         
        }

        else if (strcmp(command, "dir") == 0) {
          
        }
        
        else if (strcmp(command, "environ") == 0) {
            
        }
        
        else if (strcmp(command, "echo") == 0) {

            printf("%s\n",arg);
                
        }

        else if (strcmp(command, "pause") == 0) {
            
            printf("Press a key to continue");
            char key = NULL;
            while(key== NULL){
                key=getchar();
            }
            printf("Continue...\n");

        }

        // other commands here...
        //help command
        else if (strcmp(command, "help") == 0) {
            FILE *fp;
            char buff[1000];
            fp = fopen("README.md","r");
            if(!fp){
                printf("FILE DOESN'T EXIST");
            }
            while (fgets (buff, 1000, fp)!=NULL){
                printf("%s", buff);
            }
            printf("\n");
        }

        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
    }
    return EXIT_SUCCESS;
}
