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

/* Global definitions */
int available[RESOURCES];
/*Hardcoded max_demand*/
int max[CUSTOMERS][RESOURCES] = {
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}};
int allocation[CUSTOMERS][RESOURCES];
int need[CUSTOMERS][RESOURCES];

/* Defines the program's runtime, in seconds. */
int runtime = 0;
/* Defines the program's current runtime, in seconds*/
int currenttime = 0;

/* Defines the customer array, to hold all instances of customers. */
pthread_t customers_array[CUSTOMERS];

/*Sync tool, bank system = 1 teller*/
pthread_mutex_t teller;

/* Function declarations. */
bool all_true(bool* a);
bool is_safe();
int find_i(int* work, bool* finish);
int vector_cmp(int* a, int* b);
void add_vectors(int* a, int* b);
void copy_array(int *src, int* dest);
void initialize_demand();
void set_all_false(bool* a);
void keep_time();
void printout_state();

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
        int i = 0,j; 
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
        /*Initialize the synchronization tool*/
        pthread_mutex_init(&teller, NULL);
        
        /*Assign How much customer Need, they will never request more*/
        for(i=0; i<CUSTOMERS; i++){
            for(j=0; j<RESOURCES; j++){
                need[i][j] = max[i][j]; 
            }
        }
        printout_state();
        printf("Creating Customers ");
        for(i = 0; i < CUSTOMERS; i++){ 
            /* Create customer. */
            pthread_t customers_array[i];
            /* Create pthreads for each customer. */
            pthread_attr_t attr; //atributes for all threads?
            pthread_attr_init(&attr);
            pthread_create(&customers_array[i], &attr, customer, i);
           // pthread_join(customers_array[i], NULL);
            printf(" #%d ",i);
        }
        printf("\n");
        keep_time();
        printf("====Run Time End====\n");
        printf("Waiting for child threads to finish..\n");
        sleep(10);
        printf("\n\nItems still needed\n");
        printout_state();
    }
    return EXIT_SUCCESS;
}
/*Timekeeper of main program, used to update every tick and used to printout current time*/
void keep_time() {
    while(true) {
        sleep(1); //wait 1 second
        currenttime+=1;
        if(currenttime >= runtime) break;
    }
    return;
}
/*Prints out the state*/
void printout_state() {
    int i,j;
    /*Print out Need*/
    for(i=0;i<CUSTOMERS;i++) {
        printf("Customer %d: ", i);
        for(j=0;j<RESOURCES;j++){ 
            printf(" %d ",need[i][j]);
        }
        printf("\n");
    }
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

bool resource_request(int customer) {
    /*Add Easy Test to see if what you need is DONE!*/
   /* if((need[customer][0] <= 0 ) && 
       (need[customer][1] <= 0 ) && 
       (need[customer][2] <= 0 )) {
        printf("DONE?");
        //return -1; //can I do this?? 
    }*/

    /*Randomize the request of three resource types*/
    int req_a, req_b, req_c;
    req_a = my_rand(need[customer][0]);
    req_b = my_rand(need[customer][1]);
    req_c = my_rand(need[customer][2]);
    /*If request is more than ANY max limit, exit program as there is an error*/
    if (req_a > max[customer][0] || 
        req_b > max[customer][1] ||
        req_c > max[customer][2]) {

        printf("ERROR! Exceeding max claim:\n");
        printf("Res_A: %d <= %d\n", req_a, max[customer][0]);
        printf("Res_B: %d <= %d\n", req_b, max[customer][1]);
        printf("Res_C: %d <= %d\n", req_c, max[customer][2]);
        //exit(1);
        return false;
    }
    /*Lock teller*/
    pthread_mutex_lock(&teller);
    /*Start buffer printout*/
    printf("At time %d Customer %d requesting <%d,%d,%d> Available = <%d,%d,%d>\n",
            currenttime, customer, 
            req_a, req_b, req_c,
            available[0], available[1], available[2]);

    /*See if what your requesting is available*/
    if (req_a <= available[0] && 
        req_b <= available[1] &&   
        req_c <= available[2]) {
        
        /*Create backup array, incase this array wont work*/
        int backup_available[RESOURCES]; 
        int backup_max[CUSTOMERS][RESOURCES];
        int backup_allocation[CUSTOMERS][RESOURCES];
        int backup_need[CUSTOMERS][RESOURCES];
        
        /*Create backupstate, to revert to if the state is NOT safe*/
        copy_array(available, backup_available);
        copy_array((int *) max, (int *)backup_max);
        copy_array((int *) allocation, (int *) backup_allocation);
        copy_array((int *) need, (int *) backup_need);
        
        /*Now update actual main state, to use is_safe*/
        int i;
        int temparr[3] = {req_a, req_b, req_c}; //put requests in an array 
        /*Iterate through three resource types*/
        for(i=0;i<3;i++){
            available[i] = available[i] - temparr[i];
            allocation[customer][i] = allocation[customer][i] + temparr[i];
            need[customer][i] = need[customer][i] - temparr[i];
        }
        /*Now check if backup state is safe*/
        if(is_safe()) {
            /*Second Buffer Printout*/
            printf(">>>Customer %d is granted resources<<<<\n",customer);
            printf("Available = <%d,%d,%d> Allocated = <%d,%d,%d>\n\n",
                 available[0],available[1],available[2],
                 allocation[customer][0],allocation[customer][1],allocation[customer][2]);
        } else {
            printf("!!!Customer %d is denied resources!!!\n\n",customer);
            copy_array(backup_available, available);
            copy_array((int *) backup_max, (int *)max);
            copy_array((int *) backup_allocation, (int *) allocation);
            copy_array((int *) backup_need, (int *) need);
            /*End Critical Section*/
            pthread_mutex_unlock(&teller);
            return false;
        }
        /*End Critical Section*/
        pthread_mutex_unlock(&teller);
       return true; 
    }else { //not enough resources
        printf("===Not Enough Resources===\n");
        pthread_mutex_unlock(&teller);
        return false;
    }
} 
/*Release resources that are allocated to customer_id*/
void return_resources(int customer){
    int types=3,i, bin_a,bin_b,bin_c;
    /*Critical Section*/
    pthread_mutex_lock(&teller);

    /*Calculate available*/
    bin_a = available[0] + allocation[customer][0]; 
    bin_b = available[1] + allocation[customer][1];
    bin_c = available[2] + allocation[customer][2];
    /*Print Buffer*/
    printf("At time %d Customer %d releasing <%d,%d,%d> Available <%d,%d,%d>\n\n",
            currenttime, customer, 
            allocation[customer][0],allocation[customer][1],allocation[customer][2],
            bin_a, bin_b, bin_c);

    /*Remove allocated, and return that to available for each resource*/
    for(i=0;i<types;i++) {
        available[i] = available[i] + allocation[customer][i];
        allocation[customer][i] = 0; 
    }
    /*End Critical Section*/
    pthread_mutex_unlock(&teller);
}
/*returns true if the customer is done with what it "needs"*/
bool is_done(int customer) {
    if((need[customer][0] <= 0) &&
       (need[customer][1] <= 0) &&
       (need[customer][2] <= 0)) {
        printf("\n\n\n  [Customer %d Done]  \n\n\n", customer);
        return true;
    }
    return false;
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
