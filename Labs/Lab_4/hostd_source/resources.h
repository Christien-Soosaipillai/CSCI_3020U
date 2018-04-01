#ifndef RESOURCES_H_
#define RESOURCES_H_

// The amount of available memory
#define MEMORY 1024

// Processes structure containing all of the process details parsed from the
// input file, should also include the memory address (an index) which indicates
// where in the resources memory array its memory was allocated
typedef struct {
    int arrival_time;
    int priority;
    int proc_time;
    int memory_s;
    int n_printers;
    int n_scanners;
    int n_modems;
    int n_cds;
} proc;


// Your linked list structure for your queue
struct node {
  proc process;
  struct node* next;
};

typedef struct node node_t;


// Resources structure containing integers for each resource constraint and an
// array of 1024 for the memory
typedef struct {
    int printers;
    int scanners;
    int modems;
    int cd_drives;
    int memory[MEMORY];
} resources;

#endif /* RESOURCES_H_ */
