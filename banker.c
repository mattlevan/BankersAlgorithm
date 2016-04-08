/* Banker's Algorithm
 * Project 4
 * CSC 341: Operating Systems
 * Dr. Bin Tang
 *
 * Matt Levan
 * Brad Taniguchi
 *
 * A multi-threaded implementation of the banker's algorithm.
 * More info on page 345 of Operating Systems Concepts by Abraham Silberschatz.
 */


/* Include statements. */
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include "headers.h" //for utilize customer_args, global variables

/* Global definitions, more found in headers.h. */
/* Defines the program's runtime, in seconds. */
int runtime = 0;

/* Defines the customer array, to hold all instances of customers. */
pthread_t customers_array[CUSTOMERS];

/*Sync tool, bank system = 1 teller*/
sem_t teller;

/* Function declarations. */
bool all_true(bool* a);
bool is_safe();
int find_i(int* work, bool* finish);
int vector_cmp(int* a, int* b);
void add_vectors(int* a, int* b);
void copy_array(int *src, int* dest);
void initialize_demand();
void set_all_false(bool* a);


/* Main function. */
int main(int argc, char *argv[]) {
    /* Check that enough args were submitted by the user. */
    if (argc <= 4) {
        printf("\n");
        printf("Not enough arguments!");
        printf("\n");
        printf("Usage: ./banker.o <int num first resource> <int num second> " \
               "<int num third> <int runtime seconds>");
        printf("\n");
    }
    /* Else, process the arguments from the command line. */
    else {
        /* Initialize the available vector with args. */
        int i = 0; 
        for (i = 1; i <= 3; i++) {
            available[i-1] = atoi(argv[i]);
        }

        /* Get the runtime. */
        runtime = atoi(argv[4]);

        /* Print a status report. */
        printf("\nNUMBER OF RESOURCES\n");
        printf("FIRST: %d\n", available[0]);
        printf("SECOND: %d\n", available[1]);
        printf("THIRD: %d\n", available[2]);
        printf("\nRUNTIME: %d seconds\n", runtime);

        /* Get the max demand for each customer from max_demand.txt. */
        //copy 2d array max into max demand       

//        printarray((int *) max, CUSTOMERS, RESOURCES); //debug print        

        pthread_attr_t attr; //atributes for all threads?

        /* Create struct to assign to customer thread. */
        struct customer_args *args =  malloc(sizeof(args));
        /* Assign arguments as starting resources. */
        args->resource_a = *argv[1];
        args->resource_b = *argv[2];
        args->resource_c = *argv[3];

        /*Initialize the synchronization tools NOTE 1 teller?*/
        sem_init(&teller, 0, 1);
        for(i = 0; i < CUSTOMERS; i++){
            /* Create customer. */
            pthread_t customers_array[i];
            /* Create pthreads for each customer. */
            pthread_attr_init(&attr);
            pthread_create(customers_array[i], &attr, Customer, args);
            pthread_join(customers_array[i], NULL);
        }
        //work here
    }
    return EXIT_SUCCESS;
}

/* Checks state safety. Returns true if safe, else false. */
bool is_safe() {
    /* Work vector, length m. */
    int work[RESOURCES];
    /* Finish vector, length n. */
    bool finish[CUSTOMERS];

    /* Initialize work vector = available vector. */
    copy_array(available, work);

    /* Set all elements in finish vector to false. */
    set_all_false(finish);

    /* Find index i such that finish[i] == false && need[i] <= work. */
    int i = find_i(work, finish);

    /* If no such i exists, check if all finish elements are true. */
    if (i == -1) { //such I does not exist
        if (all_true(finish) == true) {
            /* The system is in a safe state! */
            return true;
        }
    }
    else { 
        /* work = work + allocation */
        add_vectors(work, allocation[i]);
        finish[i] = true;
        /* Go to step 2. */
        i = find_i(work, finish);
    }
}


/* Adds vectors. a[i] += b[i] for all i in range 0..n-1. */
void add_vectors(int* a, int* b) {
    while (*(a) != NULL && *(b) != NULL) {
        *(a++) += *(b++);
    }
}


/* Find index i such that finish[i] == false && need[i] <= a. */
int find_i(int* work, bool* finish) {
    int i;
    for (i = 0; i < CUSTOMERS; i++) { //no for loop initial declarations
        bool* finish_ptr = finish + i;
        if (*(finish_ptr) == false && vector_cmp(need[i], work)) {
            /* Such i exists. */
            return i;
        }
    }
    
    /* Such i does not exist. */
    return -1; //return -1 instead of null, to comply with int return type
}


/* Compare two vectors.
 * if (a <= b) { return -1; }
 * if (a == b) { return 0; }
 */
int vector_cmp(int* a, int* b) {
    /* Boolean flags for tracking vector comparison. */
    bool less_equal, equal = false;

    /* Check if a <= b. If so, return -1. */
    while (*(a) != NULL) {
        if (*(a) <= *(b)) {
            less_equal = true;
            equal = false;

            /* Increment pointers. */
            a++;
            b++;

            continue;
        }
        else if (*(a) == *(b)) {
            equal = true;

            /* Increment pointers. */
            a++;
            b++;

            continue;
        }
        else {
            /* a must be > than b. */
            return 1;
        }

        /* Check boolean flags. */
        if (equal == true) {
            return 0;
        }
        else if (less_equal == true) {
            return -1;
        }
    }
        /* Default case. */
        return 1;
}

/*Resource-Request Algorithn section below
 * 1. if requesti <= Needi, goto step 2: ELSE raise error
 *      since process has exceeded its max claim (liar!)
 * 2. If request <= Available goto step3, ELSE make it WAIT
 *      since resources are not available.
 * 3. Test to allocate requested resource to Processi by modify state:
 *          Available = available - request
 *          Allocation = allocationi + request
 *          Needi = Needi - requesti
 *          if safe state 
 * Int customer = customer # (0-4)
 * Int res = resource type to be requested(type 0-2)
 * Int req = amount of resource trying to be requested
 * Int max*/

bool Resource_Request(int customer, int res, int req, int max) {
    if (req <= max) {
        printf("ERROR! Exceeding max claim: %d <= %d", req, max);
    }
    while(TRUE) {
        
        /*If resource type amount isn't available*/
        if (req <= available[res] ){
            //WORK HERE SEE IF CAN CREATE SAFE STATE!!!
            //USED COPIED STATES OF EVERYTHING
            //IF SAFE, THEN EXECUTE, IF NOT SAFE DO NOTHING!
            
            /*wait until teller is available*/
            sem_wait(&teller);
            
            /*CRITICAL SECTION*/        
            available[res] = available[res] - req;
            allocation[customer][res] = allocation[customer][res] + req;
            Need
        }//else go thru while again
    }
}
/* Check if all elements in given array are true. */
bool all_true(bool* a) {
    /* While the next int in the a array is not NULL... */
    while (*(a) != NULL) {
        if (*(a) != false) {
            /* A false element exists, so return false. */
            return false;
        }
    }
    /* All elements are true, so return true. */
    return true;
}


/* Copies array. Returns true if successful, else false. */
void copy_array(int* src, int* dest) {
    /* While the next int in the src array is not NULL... */
    while (*(src) != NULL) {
        /* Set the int at dest pointer to the int at src pointer. */
        *(dest++) = *(src++);
    }
}


/* Sets all elements of boolean array to false. */
void set_all_false(bool* a) {
    while (*(a) != NULL) {
        *(a) = false;
    }
}
