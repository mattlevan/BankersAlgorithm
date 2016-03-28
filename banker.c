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

/* Declare functions here. */

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
        int num_first = atoi(argv[1]);
        int num_second = atoi(argv[2]);
        int num_third = atoi(argv[3]);
        int runtime = atoi(argv[4]);

        /* Print a status report. */
        printf("\nNUMBER OF RESOURCES\n");
        printf("FIRST: %d\n", num_first);
        printf("SECOND: %d\n", num_second);
        printf("THIRD: %d\n", num_third);
        printf("\nRUNTIME: %d\n", runtime);
    }

    return EXIT_SUCCESS;
}
