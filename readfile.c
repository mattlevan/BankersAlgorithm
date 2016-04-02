/* Banker's Algorithm
 * Project 4
 * CSC 341: Operating Systems
 * Dr. Bin Tang
 *
 * Matt Levan
 * Bradley Taniguchi
 *
 * ReadFile source code that can create a 2D array from integers in a text file.
 * Also a print arry test function, that can print out a 2D array
 */
#include <stdio.h>
#include "headers.h"

void printarray(int* array, int row, int col);
void get_array_from_file(char *fname, int *array, int row, int col, int buff_len);

/*int main() {
    int testarray[][3] = {
        {1,2,3},
        {4,5,6}
        };
    printarray((int *)testarray, 2, 3);
    printf("\n");
    int array[2][3]; //2 rows, 3 columns
    char filename[] = "arraytest.txt";
    get_array_from_file(filename, (int *)array, 2,3,0);
    printarray((int *) array,2,3); //print out second array
}*/
/*Prints 2D array with [row][col]*/
void printarray(int* array, int row, int col) {
    int i,j; //iterators
    printf("\n===Printout Of Array===\n");
    for(i=0; i<row; i++) {
        for(j=0; j<col; j++) {
            printf("%d ",*((array+i*col)+j)); 
        }
        printf("\n");
    }
    printf("========================\n");
}
/* Reads file for integers, and returns 2D array with [X][Y] spots
 * Provide buffer length, or 0 as default
 * int* array: 2D Array pointer to enter values in
 * int row: Number of rows in 2D array
 * int col: Number of columns in 2D array
 * int buff_len: number of integers to be read, 0 for default of 25*/
void get_array_from_file(char *fname, int *array, int row, int col, int buff_len) {
    if (buff_len == 0) buff_len = 50; //default buff_len
    
    int temp_arr[buff_len]; //1D array
    int i,j,k,bin;
    char c;
    FILE *file_ptr = fopen(fname, "r");
    if(!file_ptr) {
        printf("ERROR File Doesnt Exist %s", fname);
        return; //ERROR
    }
    /*Get integers from whole file in 1D array*/
    i=0;
    fscanf(file_ptr, "%d", &bin);
    while(!feof (file_ptr)) {
            /*printf("Found Character");*/
            /*printf("%d\n", bin); //debug print*/
            fscanf(file_ptr, "%d", &bin); //put int into bin
            fscanf(file_ptr, "%c", &c); //Remove Characters in the way also
           /*Put chracter into 1D array*/ 
            temp_arr[i] = bin;
            
            if( i == buff_len) {
                printf("Buff_Len not long enough!");
                fclose(file_ptr); //close file
                return;
            }
            i++;
    }// end of while
    fclose(file_ptr); //close file 
    k =0; //1D array counter
    for(i=0; i < row; i++) {
       for(j=0; j < col; j++) {
           *((array+i*col)+j) = temp_arr[k]; //move values from 1D array to 2D array
           k++; //increment 1D array
       }
    }
}
