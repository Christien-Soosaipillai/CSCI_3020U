/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include "resources.h"

// Include your relevant FIFO queue functions declarations here they must start
// with the extern keyword such as in the following examples:

// Add a new process to the queue, returns the address of the next node added
// to the linked list
extern node_t* init_queue(proc process);
extern int q_empty(node_t* tail);
extern node_t *push(node_t *tail, proc process);
extern node_t *pop(node_t *tail);


#endif /* QUEUE_H_ */
