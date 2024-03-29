/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Nicholas Gregorio, Jason Runzer, Albert Fung>
 * All rights reserved.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Used for random function
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];

pthread_mutex_t m_Lock;




/*
* The method run by each customer, to request and release resources.
* The customer will customerRequest a random numnber of resources and if it is granted,
* the customer will sleep for up to 5 seconds. Then the customer will release those resources granted.
* @param - customerNum - the number of the customer in the system
*/
void *customerMethod(void *customerNum){
    //cast the customer number
    int customer = *(int*)customerNum;
    bool acquiredResources = false;


    //the arrays of the resources for the specific customer
    int customerRequest [NUM_RESOURCES];
    
    while(1){
        for(int i = 0; i < NUM_RESOURCES; i++){
            customerRequest[i] = rand() % (maximum[customer][i] + 1); 
        }

        //init our mutex for our thread
        pthread_mutex_lock(&m_Lock);


        //Here we check to see if it customer Request returns true or false
        //It will return true if it is possible to allocate all requested resources to the customer 
        //and false if otherwise
        acquiredResources = customerResourceRequest(customer,customerRequest);
        pthread_mutex_unlock(&m_Lock);
        if(acquiredResources){
            
            //If we aquire the resources we get the customer to sleep for 5 seconds
            sleep(5);
            //reset aquiredResource boolean value to false after resource allocation procedure
            acquiredResources = false;
            //
            pthread_mutex_lock(&m_Lock);
            release_res(customer,customerRequest); //release the resources used
            pthread_mutex_unlock(&m_Lock);
            //simulate the customer has finished its task.
            if(rand() % 2 == 0){
                printf("\nCustomer : %d is finished\n", customer);
                for(int i = 0; i < NUM_RESOURCES; i++){
                    need[customer][i] = 0;
                    maximum[customer][i] = 0;
                }
                printf("Maximum Needs After the Customer Finished\n");
                for(int i = 0; i < NUM_CUSTOMERS; i++){
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        printf("%3d ",maximum[i][j]);
                    }
                    puts("");
                }
                sleep(2);
                break;
            }
        }
        sleep(1);
    }
    return 0;
}

/*
*Checks if the system is safe with the newly allocated resources.
* Returns true if the system will be able to execute all processes, false otherwise.
*/
bool isSafe(){

    //assign the work array to the current available resources
    int work[NUM_RESOURCES];
    for(int i = 0; i < NUM_RESOURCES; i++){
        work[i] = available[i];
    }
    //assign all customers a finish of false, in order to find a safe state
    bool finish [NUM_CUSTOMERS];
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        finish[i] = false;
    }

    int count = 0;
    //used to check if the system could not find any customer that can execute with the resources currently
    int indexFinish = -1;
    int prevFinishIndex = -1;
    bool finishCustomer = true;

    //go through all the customers and see if the system is safe
    while (count < NUM_CUSTOMERS){
        prevFinishIndex = indexFinish; //assign the previous finish index to the last one
        //go through all the customers
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            //if the customer is not done, check to see if it can be completed
            if(!finish[i]){
                for(int j = 0; j < NUM_RESOURCES; j++){
                    if (need[i][j] > work[j])
                        finishCustomer = false;
                }
                //if it can be completed, set the finish array to true, and the inxedFinish to the current index
                if(finishCustomer){
                    indexFinish = i;
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        work[j] += allocation[i][j]; //give back the resources for work
                    }
                    finish[i] = true;
                    count++;
                    finishCustomer = true;
                    break; //exit loop and go through the list again
                }
            }
        }

        //see if the system has aquired a safe path for the customer execution
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            if(!finish[i])
                break;
        }
        //see if there was no change in the finish array after going though each customer
        if(prevFinishIndex == indexFinish)
            return false;
    }
    return true;
}
/*
* Requests and alloctes resources for a customer if possible.
* Returns false if it is not possbile to allocate the resources for the customer
* @param - n_customer - the customer number
* @param customerRequest - the array of resources the customer wishes to recieve
*/
bool customerResourceRequest(int n_customer, int customerRequest[]){
   
    printf("\nCustomer: %d Requesting Resources\n",n_customer);
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",customerRequest[i]);
    }
    puts("");


    //check reourcecs before that are available
    printf("Resources to Borrow\n");
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",available[i]);
    }
    puts("");



    //checks if the system is safe 
     for(int i = 0; i < NUM_RESOURCES; i++){
        if(customerRequest[i] <= need[n_customer][i]){
            if(customerRequest[i] > available[i]){
                printf("Unsafe System for this Request\n\n");
                sleep(1); //used for readability
                return false;
            }
            else{
            	//system is safe proceed
            	//in bankers  algorithm we first test taking the resources and then we actually provide them
            	//so lets implement that here
                printf("testing...\n");
                for(int j = 0; j < NUM_RESOURCES; j++){

                	//allocation array modified per customer request since we validated
                    allocation[n_customer][j] += customerRequest[j];

                    //take away from  the available resources
                    available[j] -= customerRequest[j];

                    //subtract from the need resources
                    need[n_customer][j] -= customerRequest[j];
                }

                //if we can confirm that the tested resource allocation is safe
                if(isSafe()){
                    printf("SAFE SYSTEM FOR CUSTOMER REQUEST-----> GRANTED!\n");
                    printf("What little resources we have left... \n:(\n");
                    for(int i = 0; i < NUM_RESOURCES; i++){
                        printf("%d ",available[i]);
                    }
                    puts("\n");
                    sleep(2);
                    return true;
                }
                //else we deny the request
                else{
                    printf("UNSAFE SYSTEM FOR CUSTOMER REQUEST------> DENIED!\n");
                    for(int k = 0; k < NUM_RESOURCES; k++){
                    	//add back all values to global array available
                        available[k] += customerRequest[k]; 
                        //add back all values to global array need
                        need[n_customer][k] += customerRequest[k]; 
                        //subtract all values from global array allocation
                        allocation[n_customer][k] -= customerRequest[k]; 
                    }
                    return false;
                }
            }
        } else{
            printf("Customer: %d REQUESTED TOO MANY RESOURCES\n",n_customer);
            sleep(2);
            return false;
        }

    }
 
    return true;
}


/*Release resources, returns true if successful
* @param - n_customer - the customer number wishing to release resources
* @param - release - the array of resources to release
*/
bool release_res(int n_customer, int release[])
{  
    printf("\nCustomer: %d Giving up resources, send back to available\n", n_customer);
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",release[i]);
        available[i] += release[i]; //add to the available resources
        need[n_customer][i] += release[i]; //add to the customers need array
        allocation[n_customer][i] -= release[i]; //reduce the allocation for the specific customer
    }

    puts("");
    printf("Resources that are now available\n");
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",available[i]);
    }
    puts("");
    
    return true;
}



int main(int argc, char *argv[])
{   

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments   
    pthread_t threads[NUM_CUSTOMERS];
    pthread_mutex_init(&m_Lock, NULL);
    for (int i =0; i < NUM_RESOURCES; i++) {
        //Specifies the max INITIAL availale resources. MAX cannot exceed this
        available[i] = atoi(argv[i+1]);
        //go through the customers and randomly state how many resources they need at maximum
        for(int j=0; j<NUM_CUSTOMERS; j++) {
            maximum[j][i] = rand() % (available[i] + 1);
            need[j][i] = maximum[j][i];
            allocation[j][i] = 0;
        }        
    }

    //print out the needs of all customers
    printf("Maximum amount Needed\n");
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        for(int j = 0; j < NUM_RESOURCES; j++){
            printf("%3d ",maximum[i][j]);
        }
        puts("");
    }
    srand(time(NULL));
    //make all the customers
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        int *c_num = malloc(sizeof(*c_num));
        //make an integer pointer to be used to send into the customer thread
        if(c_num ==NULL){
            exit(1);
        }
        *c_num = i;
        //create the customer thread
        pthread_create(&threads[i],NULL,&customerMethod, c_num);
    }
    
    //join all the threads (will never happen)
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        pthread_join(threads[i],0);
    }
    printf("All done\n");
    pthread_mutex_destroy(&m_Lock);
    
    return EXIT_SUCCESS;
}