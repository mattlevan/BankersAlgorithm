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
/*2D Array printer*/
void printarray(int* array, int row, int col);
/*Builds 2D array from integers in CSV text file*/
void get_array_from_file(char *file_name, int *array, int row, int col, int buff_len);
