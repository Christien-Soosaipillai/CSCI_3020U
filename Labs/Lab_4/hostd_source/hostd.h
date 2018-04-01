/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Miral Panchal, Christien Soosapillai
 * All rights reserved.
 *
 */
#ifndef HOSTD_H_
#define HOSTD_H_

#include "utility.h"
#include "queue.h"
#include "resources.h"

// Include any relevant data structures here thay may be needed

// Include any relevant functions declarations here they must start with the
// extern keyword such as in the following example:
// extern void print_process(proc process);
extern void initResources(resources* res);

#endif /* HOSTD_H_ */
