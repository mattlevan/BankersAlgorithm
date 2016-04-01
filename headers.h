/*
 * 
 *
 *
 */
/*Struct to pass arguments to customers*/
struct customer_args {
    int resource_a;
    int resource_b;
    int resource_c;
};
/*NOTE for the following two functions use the following syntaxt to call:
 * get_array_from_file((int *)array,2,3,0)*/

/*2D Array printer*/
void printarray(int* array, int row, int col);
/*Builds 2D array from integers in CSV text file*/
void get_array_from_file(char *fname, int *array, int row, int col, int buff_len);

/*Customer function declaration*/
void *Customer(void *customer_args_ptr);
