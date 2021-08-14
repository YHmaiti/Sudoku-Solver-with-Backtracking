//This Program was made by Yohan Hmaiti GitHub: YHmaiti
// pre-processor directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function prototypes
unsigned long int calculatechecksum8bit(char *array8);
unsigned long int calculatechecksum16bit(char *array16);
unsigned long int calculatechecksum32bit(char *array32);
void printtoscreen(char *arraytoprint);

// main functions taking arguments from the command line
int main(int argc, char **argv) {

    // i is a counter
    int i = 0;

    // file pointer that will be used to point to the input file
    FILE *ifp;

    // arr_input will serve later as an array to store all the characters scanned from the 
    // input file
    char *arr_input;

    // currentchar represent the character scanned at each loop iteration from the input file
    char currentchar;

    // variables that will store the total returned from the calculation functions
    // depending on the size accordingly
    unsigned long int totalfor8bit = 0;
    unsigned long int totalfor16bit = 0;
    unsigned long int totalfor32bit = 0;

    // checksum is a variable that will store the checksum calculated
    // and will be updated depending on the case (either for the 8, 16 or 32 bit case)
    unsigned long int checksum = 0;

    // characterCnt is the character count
    int characterCnt = 0;
    
    // checkSumSize stores the size of the checksum to be calculated either 8, 16 or 32 
    int checkSumSize = 0;

    // Check if the number of arguments passed is correct, otherwise exit and notify the user
    if (argc != 3) {

        fprintf(stderr, "The number of arguments entered is not sufficient, try again!\n");
        return -999;

    }

    // Update checkSumSize depending on the size of the checksum to be calculated
    // this number is passed from the command line to main
    checkSumSize = atoi(argv[2]);

    // Check if the checkSumSize is valid otherwise notify the user and exit
    if ((checkSumSize != 8) && (checkSumSize != 16) && (checkSumSize != 32)) {

        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return -999;

    }

    // open the input file in read mode 
    // the input file is passed from the command line
    ifp = fopen(argv[1], "r");

    // Check if the opening of the file was successful
    // if it did not work notify the user and exit
    if (ifp == NULL) {

        fprintf(stderr, "The input file %s could not be opened, try again!\n", argv[1]);
        return -999;

    }

    // allocate memory for the array that will store the content of the input file
    // I chose 1025 as it represents two times 512 + 1 (which is a quite significant size that can store enough data)
    arr_input = malloc(sizeof(char) * 1025);

    // get the first character from the input file
    currentchar = fgetc(ifp);

    // while loop used to scan all the elements within the input file
    // the while loop stops when we attain the end of the file or i becomes >= 1024
    while (currentchar != EOF) {

        // if statement used to break from the while loop if the size of the 
        // array is surpassed
        if (i >= 1025) {

            break;

        }

        // store the current character and indrement the counter (i) after
        arr_input[i] = currentchar;
        i++;

        // get the next character
        currentchar = fgetc(ifp);

    }

    // terminate the array
    arr_input[i] = '\0';

    // Close the input file
    fclose(ifp);

    // switch statement based on the checkSumSize stored
    switch (checkSumSize) {
    
        // case where we need an 8bit checksum
        case 8:
            // calculate checksum for 8 bits through the use of the function calculatechecksum8bit
            // which takes the array containing the elements scanned from the file
            totalfor8bit = calculatechecksum8bit(arr_input);

            // call the print function to print the input elements from the file to the screen
            printtoscreen(arr_input);
            printf("\n");

            // determine the checksum using bitmasking with 0xff in order to get only the last 2 hexadecimal values
            // update the character count through the use of strlen
            checksum = (totalfor8bit & 0xff);
            characterCnt = (int)strlen(arr_input);

            // print the checksum line as requested through the assignment
            printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);
            break;

        // case where we need a 16bit checksum
        case 16:
            // Pad using X as needed
            if (strlen(arr_input) % 2) {

                strcat(arr_input, "X");

            }

            // call the print function to print the input elements from the file to the screen
            printtoscreen(arr_input);
            printf("\n");

            // calculate checksum for 16 bits through the use of the function calculatechecksum16bit
            // which takes the array containing the elements scanned from the file
            // determine the checksum using bitmasking with 0xffff in order to get only the last 4 hexadecimal values
            // update the character count through the use of strlen
            totalfor16bit = calculatechecksum16bit(arr_input);
            checksum = (totalfor16bit & 0xffff);
            characterCnt = (int)strlen(arr_input);

            // print the checksum line as requested through the assignment
            printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);
            break;

        // case where we need a 32bit checksum
        case 32:
            // Pad using X as needed
            while (strlen(arr_input) % 4) {

                strcat(arr_input, "X");

            }

            // call the print function to print the input elements from the file to the screen
            printtoscreen(arr_input);
            printf("\n");

            // calculate checksum for 32 bits through the use of the function calculatechecksum32bit
            // which takes the array containing the elements scanned from the file
            // determine the checksum using bitmasking with 0xffffffff in order to get only the last 8 hexadecimal values
            // update the character count through the use of strlen
            totalfor32bit = calculatechecksum32bit(arr_input);
            checksum = (totalfor32bit & 0xffffffff);
            characterCnt = (int)strlen(arr_input);

            // print the checksum line as requested through the assignment
            printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);
            break;

    }

    // free the allocated memory for the array arr_input
    free(arr_input);

    // end of the main function
    return 0;

}

// function used to calculate the checksum when we have an 8bit size
// the function takes an input array passed to it from main 
// the function return an unsigned long int that contains the checksum calculated
unsigned long int calculatechecksum8bit(char *array8) {

    // total8 will store the total calculated and will be returned to main
    int total8 = 0;

    // i is a counter
    int i = 0;

    for (i = 0; i < strlen(array8); i++) {

        total8 += array8[i];

    }

    return total8;

}

// function used to calculate the checksum when we have a 16bit size
// the function takes an input array passed to it from main
// the function return an unsigned long int that contains the checksum calculated
// in this function we will operate through increments of 2 when it comes to the counter
unsigned long int calculatechecksum16bit(char *array16) {

    // total16 will store the total calculated and will be returned to main
    int total16 = 0;

    // i is a counter
    int i = 0;

    while (i < strlen(array16)) {

        total16 += (array16[i] << 8);
        total16 += (array16[i + 1]);

        // increment by 2
        i += 2;

    }

    return total16;

}

// function used to calculate the checksum when we have a 32bit size
// the function takes an input array passed to it from main
// the function return an unsigned long int that contains the checksum calculated
// in this function we will operate through increments of 4 when it comes to the counter
unsigned long int calculatechecksum32bit(char *array32) {

    // total32 will store the total calculated and will be returned to main
    unsigned long int total32 = 0;

    // i is a counter
    int i = 0;

    while (i < strlen(array32)) {

        total32 += (array32[i] << 24);
        total32 += ((array32[i + 1]) << 16);
        total32 += ((array32[i + 2]) << 8);
        total32 += (array32[i + 3]);

        // increment by 4
        i += 4;

    }

    return total32;

}

// function used to print the elemnts gathered from the input file 
// according to the assignment requirements of 80 characters per line
// the function takes an array passed to it from main containing the information
// from the input file to print 
void printtoscreen(char *arraytoprint) {

    int counter = 0;

    for (counter = 0; counter < strlen(arraytoprint); counter++) {

        if (counter % 80 == 0) {

            printf("\n");
            
        }

        printf("%c", arraytoprint[counter]);

    }

}
