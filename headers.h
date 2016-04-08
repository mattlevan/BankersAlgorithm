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
/*GLOBAL VARIABLES
 * declared here so they can be accessed in customer.c and banker.c*/
#define CUSTOMERS 5
#define RESOURCES 3
#define MAX_SLEEP 5
#define FILE_NAME "max_demand.txt"
#define TRUE 1

/*Hard Coded Max Demand*/
int max_demand[][] = {
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}};
/*Defined in banker.c*/
/* Stores the number of available resources of each type. */
extern int available[RESOURCES];
/* Defines the max demand of each customer. */
extern int max[CUSTOMERS][RESOURCES];
/* Defines number of resources of each type allocated to each customer. */
extern int allocation[CUSTOMERS][RESOURCES];
/* Indicates the remaining resource need of each customer. */
extern int need[CUSTOMERS][RESOURCES];

/*Struct to pass arguments to customers*/
struct customer_args {
    int resource_a;
    int resource_b;
    int resource_c;
};
/*NOTE for the following two functions use the following syntaxt to call:
 * get_array_from_file((int *)array,2,3,0)*/

/*2D Array printer*/
extern void printarray(int* array, int row, int col);
/*Builds 2D array from integers in CSV text file*/
extern void get_array_from_file(char *fname, int *array, int row, int col, int buff_len);

/*Customer function declaration*/
extern void *Customer(void *customer_args_ptr);
