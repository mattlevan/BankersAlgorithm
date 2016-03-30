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


/* Global definitions. */
#define CUSTOMERS 5 // Referred to as 'n' in the book.
#define RESOURCES 3 // Referred to as 'm' in the book.
#define MAX_SLEEP 5


/* Global variables. */
/* Stores the number of available resources of each type. */
int available[RESOURCES];
/* Defines the max demand of each customer. */
int max[CUSTOMERS][RESOURCES];
/* Defines number of resources of each type allocated to each customer. */
int allocation[CUSTOMERS][RESOURCES];
/* Indicates the remaining resource need of each customer. */
int need[CUSTOMERS][RESOURCES];
/* Defines the program's runtime, in seconds. */
int runtime = 0;


/* Function declarations. */
bool is_safe();
void add_vectors(); //added missing declaration
bool all_true(bool* a);
int find_i(int* work, bool* finish);
void copy_array(int *src, int* dest);
void set_all_false(bool* a);


/* Main function. */
int main(int argc, char *argv[]) {
    /* Check that enough args were submitted by the user. */
    if (argc < 4) {
        printf("\n");
        printf("Not enough arguments!");
        printf("\n");
        printf("Usage: ./banker.o <int num first resource> <int num second> \
                <int num third> <int runtime seconds>");
        printf("\n");
    }
    /* Else, process the arguments from the command line. */
    else {
        /* Initialize the available vector with args. */
        int i = 0; 
        for (i = 1; i <= 3; i++) { //no for loop initial declarations
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
        /* Code goes here. */   
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


/* Adds vectors. a[i] += b[i] for all i 0..n-1. */
void add_vectors(int* a, int* b) {
    while (a != NULL && b != NULL) { //only pointers can be NULL
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
    while (a != NULL) {
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

        /* Default case. */
        return 1;
    }
}


/* Check if all elements in given array are true. */
bool all_true(bool* a) {
    /* While the next int in the a array is not NULL... */
    while (a != NULL) {
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
    while (src != NULL) {
        /* Set the int at dest pointer to the int at src pointer. */
        *(dest++) = *(src++);
    }
}


/* Sets all elements of boolean array to false. */
void set_all_false(bool* a) {
    while (a != NULL) {
        *(a) = false;
    }
}

