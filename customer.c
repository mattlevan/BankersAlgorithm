/*
 * Customer "class"
 * Project 4
 * CSC 341: Operating Systems
 * Dr. Bin Tang
 *
 * Matt Levan
 * Brad Taniguchi
 *
 * The customer function, with a few extra functions to debug*/

#include <stdio.h>
//#include <unistd.h>
//#include <pthread.h>
#include "headers.h"

/*Primary Customer function, used to hold the logic and variables that pertain to
 * each thread. No classes in C but this will do.*/
void *Customer(void *customer_args_ptr) {
    int res_a, res_b, res_c;
    /*cast so compiler knows what is going on*/
    struct customer_args *args = (struct customer_args *)customer_args_ptr; 
    res_a = args->resource_a;
    res_b = args->resource_b;
    res_c = args->resource_c;
    /*add rest of logic here*/
}
