/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file
node_t* init_queue(proc process) {
    node_t* tail = (node_t*) malloc(sizeof(node_t));
    tail->process = process;
    tail->next = NULL;
    return tail;
}

int q_empty(node_t* tail) {
    return tail == NULL;
}

node_t *push(node_t *tail, proc process) {
    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }
    node->process = process;
    node->next = NULL;
    node_t* temp = tail;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    return node;
}

node_t *pop(node_t *tail) {
  if (tail == NULL) {
    return NULL;
  }
  node_t* node = tail->next;
  tail->next = NULL;
  return node;
}
