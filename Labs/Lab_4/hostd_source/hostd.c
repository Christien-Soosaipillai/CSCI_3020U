/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024
#define MEMORY 1024
#define BUF_LEN 1024
#define NUM_Q   4

// Put global environment variables here
node_t* priority_queues[NUM_Q];
resources res;

// Define functions declared in hostd.h here
extern void initResources(resources* res) {
    res->printers  = 2;
    res->scanners  = 1;
    res->modems    = 1;
    res->cd_drives = 2;
    for (int i = 0; i < MEMORY; i++)
    {
        res->memory[i] = 0;
    }
}

int main(int argc, char *argv[]) {
  initResources(&res);
    // initialize our queues
    for (int i = 0; i < NUM_Q; i++) {
        priority_queues[i] = NULL;
    }

    // Load the dispatchlist
    node_t* queue = NULL;
    load_dispatch(argv[1], &queue);

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
    node_t* q = queue;
    node_t* last = NULL;
    while (q != NULL) {
        int priority = q->process.priority;
        if (priority < 0 || priority > 3) {
            fprintf(stderr, "Invalid priority\n");
            exit(EXIT_FAILURE);
        }
        if (priority_queues[priority] == NULL){
            priority_queues[priority] = init_queue(q->process);
          }
        else {
            push(priority_queues[priority], q->process);
          }
        last = q;
        q = q->next;
        free(last);
    }
    q = queue;
    while (q != NULL)
    {
        printf("arrival time = %d\n", q->process.arrival_time);
        q = q->next;
    }

    while (!queues_empty(priority_queues, NUM_Q)) {
        pid_t child;
        child = fork();
        if (child == 0) {
            execl("./process", "./process");
            exit(EXIT_SUCCESS);
        }
        else {
            int status = 0;
            waitpid(child, &status, WUNTRACED);
        }
        // Perform the appropriate signal handling / resource allocation and de-alloaction

        // Repeat until all processes have been executed, all queues are empty
    }
    return EXIT_SUCCESS;
}
