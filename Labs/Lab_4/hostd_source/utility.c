/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define BUF_LEN 1024

// Define your utility functions here, you will likely need to add more...

extern char** tokenize(char* input, int* num_tokens, const char* delim) {
    int i = 0;
    size_t c_len;
    size_t in_len = strlen(input)+1;
    char* input_copy = (char*) malloc(in_len*sizeof(char));
    strncpy(input_copy, input, in_len);

    char** ret = (char**) malloc(BUF_LEN*sizeof(char*));
    *num_tokens = 0;

    char* c = strtok(input_copy, delim);

    while (c != NULL) {
      c_len = strlen(c)+1;
      *(ret+i) = malloc(c_len*sizeof(char));
      strncpy(*(ret+i), c, c_len);
      c = strtok(NULL, delim);
      i++;
    }
    *num_tokens = i;
    free(input_copy);
    return ret;
}

int find_free(int memory[], int size) {
    return -1;
}

void load_dispatch(char *dispatch_file, node_t **q) {
  FILE* file = fopen(dispatch_file, "r");
  char* buffer = NULL;
  size_t len = 0;
  ssize_t read;
  if (!file) {
      exit(EXIT_FAILURE);
  }

  char** tokens;
  int num_lines = 0;
  while ((read = getline(&buffer, &len, file)) > 0) {
      int num_tok = 0;
      tokens = tokenize(buffer, &num_tok, ",");
      if (num_tok != 8) {
          fprintf(stderr, "Error while parsing %s: incorrect number of elements on line\n", dispatch_file);
          exit(EXIT_FAILURE);
      }
      proc p;
      p.arrival_time   = atoi(tokens[0]);
      p.priority       = atoi(tokens[1]);
      p.proc_time      = atoi(tokens[2]);
      p.memory_s       = atoi(tokens[3]);
      p.n_printers     = atoi(tokens[4]);
      p.n_scanners     = atoi(tokens[5]);
      p.n_modems       = atoi(tokens[6]);
      p.n_cds          = atoi(tokens[7]);

      if (num_lines == 0) {
          *q = init_queue(p);
      }
      else {
          push(*q, p);
      }
      num_lines++;
  }
}

int queues_empty(node_t* qs[], int num_queues) {
    int ret = 1;
    for (int i = 0; i < num_queues; i++) {
      ret = ret && q_empty(qs[i]);
    }
    return ret;
}
