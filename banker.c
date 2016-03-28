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

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>

/* Global variables. */
/* Stores the number of available resources of each type. */
int available[];
/* Defines the max demand of each process. */
int max[][];
/* Defines number of resources of each type allocated to each process. */
int allocation[][];
/* Indicates the remaining resource need of each process. */
int need[][];

/* Functions. */
bool is_safe() {

}

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
        /* Declare an int[] available. */
        available = int[4];

        /* Initialize the available array. */
        for (int i = 1; i <= 3; i++) {
            available[i-1] = atoi(argv[i]);
        }

        /* Get the runtime. */
        int runtime = atoi(arv[4]);

        /* Print a status report. */
        printf("\nNUMBER OF RESOURCES\n");
        printf("FIRST: %d\n", available[0]);
        printf("SECOND: %d\n", available[1]);
        printf("THIRD: %d\n", available[2]);
        printf("\nRUNTIME: %d\n", runtime);
    }

    return EXIT_SUCCESS;
}
