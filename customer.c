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
    int customer_id, r, flag;
    customer_id = (int) customer_args_ptr;
    /* Customer main loop. */
    /*Stagard start*/
    r = my_rand(5);
    sleep(r); 
    while(1) {
        /*Request resources*/
        if(resource_request(customer_id)){
            flag = 1; //we did get resources!
        } else {
            flag = 0; //we didn't get resources
        }

        /* Determine random amount of time before action. */
        r = my_rand(5); 
        sleep(r);
        
        /*Release resources*/
        if(flag) { //only go in here if we GOT resources
            
        }
    }
}

/* Returns number between 0 and x. */
int my_rand(int x) {
    srand(time(NULL)); 
    return (rand() % x); 
}
