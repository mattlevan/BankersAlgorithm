/*
 * customer.c
 * Project 4
 * CSC 341: Operating Systems
 * Dr. Bin Tang
 *
 * Matt Levan
 * Brad Taniguchi
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "headers.h"

/*Local file declarations below*/
int my_rand(int x);
void use_resources(int n);

/* Primary Customer function, used to hold the logic and variables that 
 * pertain to each thread. No classes in C but this will do.*/
void *customer(void *customer_args_ptr) {
    int customer_id, r;
    
    /* Customer main loop. */
    while(1) {
        /* Determine random amount of time before action. */
        r = my_rand(5); 
        sleep(r);

        /*Now request those resources*/
        resource_request(customer_id); //request resource a
    }
}

/* Returns number between 0 and x. */
int my_rand(int x) {
    srand(time(NULL)); 
    return (rand() % x); 
}
