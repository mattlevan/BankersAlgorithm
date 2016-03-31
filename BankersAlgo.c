/**
 * Matt Levan
 * Bradley Taniguchi
 * 03/27/16
 * Banker's Algorithm
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>

int main(int argc, int** argv) {
    return 0;
}
/**Prints out to file specified
 * Pass length of string, and pointer to string*/
void outprint(char* filename, char* string ) {
    FILE *filePtr;
    filePtr = fopen(filename, "a");
    fprintf(filePtr, "Test");
    fclose(filePtr);
}
