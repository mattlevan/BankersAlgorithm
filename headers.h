/* Banker's Algorithm
 * Project 4
 * CSC 341: Operating Systems
 * Dr. Bin Tang
 *
 * Matt Levan
 * Brad Taniguchi
 *
 * Headerfile to hold global definitions, and function definitions
 */
#include <stdbool.h>
/*GLOBAL VARIABLES
 * declared here so they can be accessed in customer.c and banker.c*/
#define CUSTOMERS 5
#define RESOURCES 3
#define MAX_SLEEP 5
#define TRUE 1

/*Defined in banker.c*/
/* Stores the number of available resources of each type. */
extern int available[RESOURCES];
/* Defines the max demand of each customer. */
extern int max[CUSTOMERS][RESOURCES];
/* Defines number of resources of each type allocated to each customer. */
extern int allocation[CUSTOMERS][RESOURCES];
/* Indicates the remaining resource need of each customer. */
extern int need[CUSTOMERS][RESOURCES];

/*Customer function declaration*/
extern void *customer(void *customer_args_ptr);

/*Allow Customer function to use Resource_Request*/
extern bool resource_request(int customer, int res, int req);
