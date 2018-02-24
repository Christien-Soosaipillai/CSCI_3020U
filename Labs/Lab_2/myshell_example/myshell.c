/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char PATH[BUFFER_LEN];
    char env[BUFFER_LEN];

    //char *token2, *token1, *token3;

// Define functions declared in myshell.h here
void getPath();
void changeDirectory(char *arg);
void clearScreen();
void printDirList();
void printEnviroVar();
void printEcho(char *arg);
void pauseSceen();
void printHelp();

int main(int argc, char *argv[], char *envp[]) {
    strcpy(env,envp);
    if(argc==2){
      char bat_file[BUFFER_LEN];
      strcpy(bat_file,argv[1]);
      //printf("\n%s\n", bat_file);

      FILE *fp;
      char buff[1000];
      fp = fopen(bat_file,"r");
      if(!fp){
          printf("FILE DOESN'T EXIST");
      }
      int count = 0;
      char *token2,*token3;
      while (fgets (buff, 1000, fp)!=NULL){
        count++;
        printf("%s", buff);
        if(strstr(buff, " ")!=NULL) {
            // Perform string tokenization to get the command and argument
            if( strstr(buff, " ")!=NULL) {
                *token2 = strtok(buff," ");
                //char *token2 = strtok(buff,"\n");
                strcpy(command, token2);

                *token3 = strtok(NULL,"\n");
                strcpy(arg, token3);


                printf("%s %s", token2, token3);

            }

            printf("\n");
            // Check the command and execute the operations for each command
            // cd command -- change the current directory
            if (strcmp(command, "cd") == 0)
              changeDirectory(arg);
             else if (strcmp(command, "clr") == 0)
               clearScreen();
            else if (strcmp(command, "dir") == 0)
              printDirList();
            else if (strcmp(command, "environ") == 0)
              printEnviroVar();
            else if (strcmp(command, "echo") == 0)
              printEcho(arg);
            else if (strcmp(command, "pause") == 0)
              pauseSceen();
            // other commands here...
            //help command
            else if (strcmp(command, "help") == 0)
                printHelp();
            // quit command -- exit the shell
            else if (strcmp(command, "quit") == 0)
              return EXIT_SUCCESS;
            // Unsupported command
            else
            {
                fputs("Unsupported command, use help to display the manual\n", stderr);
                getPath();
            }
        }
      }
      fclose(fp);
    }

    if(argc==1){
      getPath();
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
      // Perform string tokenization to get the command and argument
      if( strstr(buffer, " ")!=NULL) {
          char *token2 = strtok(buffer," ");
          strcpy(command, token2);

          char *token3 = strtok(NULL,"\n");
          strcpy(arg, token3);
      }
      //
      // char *token1 = strtok(buffer,"\n");
      // strcpy(command, token1);

      printf("\n");
      // Check the command and execute the operations for each command
      // cd command -- change the current directory
      if (strcmp(command, "cd") == 0){
        changeDirectory(arg);
        getPath();
      }
      else if (strcmp(command, "clr") == 0){
        clearScreen();
        getPath();
      }
      else if (strcmp(command, "dir") == 0){
        printDirList();
        getPath();
      }
      else if (strcmp(command, "environ") == 0){
        printEnviroVar();
        getPath();
      }
      else if (strcmp(command, "echo") == 0){
        printEcho(arg);
        getPath();
      }
      else if (strcmp(command, "pause") == 0){
        pauseSceen();
        // getPath();
      }
      // other commands here...
      //help command
      else if (strcmp(command, "help") == 0){
        printHelp();
        getPath();
      }
      // quit command -- exit the shell
      else if (strcmp(command, "quit") == 0)
      return EXIT_SUCCESS;
      // Unsupported command
      else
      {
        fputs("Unsupported command, use help to display the manual\n", stderr);
      }
    }
    return EXIT_SUCCESS;
  }
}

void getPath(){
  getcwd(PATH,sizeof(PATH));
  strcat(PATH,"$ ");
  printf("%s",PATH);
}

void changeDirectory(char *arg){
  if(arg == NULL){
    char cwd[BUFFER_LEN] = { 0 };
    printf("%s\n", getcwd(cwd,sizeof(cwd)));
  }

  else if (arg != NULL){
    struct stat sb;
    if(stat(arg, &sb) == 0 && S_ISDIR(sb.st_mode)){
      chdir(arg);
      setenv("PWD",arg,1);
    }
    else{
      printf("%s\n", "ERROR: Directory doesn't exist.");
    }
  }
}

void clearScreen(){
  system("clear");
}

void printDirList(){
  struct dirent *entry;
  DIR *dir = opendir(".");
  while ((entry = readdir(dir)) != NULL)
    printf("%s\n", entry->d_name);
  closedir(dir);
}

void printEnviroVar(){
  for (int i = 0; env[i] != NULL; i++) {
    printf("\n%s", env[i]);
  }
  printf("\n");
}

void printEcho(char *arg){
  printf("%s\n",arg);
}

void pauseSceen(){
  printf("Press a key to continue");
  char key = NULL;
  while(key== NULL){
      key=getchar();
  }
  printf("Continue...\n");
}

void printHelp(){
  FILE *fp;
  char buff[1000];
  fp = fopen("readme.md","r");
  if(!fp){
      printf("FILE DOESN'T EXIST");
  }
  while (fgets (buff, 1000, fp)!=NULL){
      printf("%s", buff);
  }
  printf("\n");
  fclose(fp);
}
