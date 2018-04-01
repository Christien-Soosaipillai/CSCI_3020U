/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#include "resources.h"
#include "queue.h"


// The amount of available memory
#define MEMORY 1024

// Include your relevant functions declarations here they must start with the
// extern keyword such as in the following examples:
extern char** tokenize(char* input, int* num_tokens, const char* delim);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
// extern void load_dispatch(char *dispatch_file, node_t *queue);
extern void load_dispatch(char *dispatch_file, node_t **q);
extern int queues_empty(node_t* qs[], int num_queues);


#endif /* UTILITY_H_ */
