
// pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// main function taking arguments from the command line given by the user
// mainly keyfile and plaintextfile
int main(int argc, char *argvector[]) {

    // if statement used to detect the case where there is an argument missing
    // from the command line or if there are extra arguments
    if (argc != 3) {

        printf("\nThe number of arguments entered is wrong\n\n");
        exit(0);

    }

    // create file pointers for the key and plaintext
    // open the files for the key and plaintext in read mode
    FILE * key = fopen(argvector[1], "r");
    FILE * ptext = fopen(argvector[2], "r");

    // allocate memory for two arrays
    // keyy to store the key given
    // plaintext to store the plaintext given
    char *keyy = malloc(sizeof(char) * (512 + 1));
    char *plaintext = malloc(sizeof(char) * (512 + 1));

    // i, j, c, k and counter are counters
    // counter will be used to check if the total of 512 characters was reached
    int i = 0, j = 0, c = 0, k = 0, counter = 0;

    // create an integer to store the ASCII value of the character being scaned
    int current_ch;

    // if statement used in the case where the key file is NULL
    if (key == NULL) {

        printf("\nThe Key File is not valid! \n\n");
        exit(0);

    }

    // if statement used in the case where the plaintext file is NULL
    if (ptext == NULL) {

        printf("\nThe plaintext File is not valid! \n\n");
        exit(0);

    }

    // get the ASCII value of the first character from the key file
    current_ch = fgetc(key);

    // while loop that stores the key characters up to 512 characters
    // unless the key is shorter, then the loop stops at the end of the file
    // characters stored are lowercase and alphabetical only
    while (current_ch != EOF) {

        // check if the character scanned is an alphabet
        // and if the limit of 512 characters wasn't reached
        if (isalpha(current_ch) && (counter < 512)) {

            keyy[i] = tolower(current_ch);
            counter++; // increment counter
            i++; // increment i

        }

        // break if the limit of 512 characters was reached
        else if (counter >= 512) {

            break;

        }

        // get the ASCII value of the next character from the key file
        current_ch = fgetc(key);

    }

    // terminate the key array
    keyy[i] = '\0';

    // set counter to 0
    counter = 0;

    // get the ASCII value of the first character from the plaintext file
    current_ch = fgetc(ptext);

    // while loop that stores the plaintext characters up to 512 characters
    // unless the plaintext is shorter, then the loop stops at the end of the file
    // characters stored are lowercase and alphabetical only
    while (current_ch != EOF) {

        // check if the character scanned is an alphabetical
        // and if the limit of 512 characters wasn't reached
        if (isalpha(current_ch) && counter < 512) {

            plaintext[j] = tolower(current_ch);
            counter++; // increment counter
            j++; // increment j

        }

        // break if the limit of 512 characters was reached
        else if (counter >= 512) {

            break;

        }

        // get the ASCII value of the next character from the plaintext file
        current_ch = fgetc(ptext);

    }

    // terminate the plaintext array
    plaintext[j] = '\0';

    // plainlen represents the length of the plaintext stored
    // keylen represents the length of the key stored
    int plainlen = strlen(plaintext);
    int keylen = strlen(keyy);

    // if statement used to pad with x to reach the total of 512 characters
    // if the current plaintext stored has less than 512 characters
    if (plainlen < 512) {

        for (k = plainlen; k < 512; k++) {

            plaintext[k] = 'x';

        }

        // terminate the plaintext array after the padding
        plaintext[k] = '\0';

    }

    // update plainlen to store the new length of the plaintext array
    plainlen = strlen(plaintext);

    // allocate memory for the ciphertext array that will store the resulting
    // ciphertext
    char *ciphertext = malloc(sizeof(char) * plainlen);

    // for loop used to generate the ciphertext through the vigenere cipher method
    for (i = 0; i < plainlen; i++) {

        ciphertext[i] = (((plaintext[i] - 'a') + (keyy[i % keylen] - 'a')) % 26 + 'a');

    }

    // terminate the ciphertext array
    ciphertext[i] = '\0';

    printf("\n\nVigenere Key:\n");

    // while loop used to print the Vigenere key with 80 characters maximum
    // per line
    while (c < keylen) {

        if (c % 80 == 0) {

            printf("\n");

        }

        printf("%c", keyy[c]);

        c++;

    }

    // set c to 0 to use it again to print the plaintext
    c = 0;

    printf("\n\n\nPlaintext:\n");

    // while loop used to print the Plaintext with 80 characters maximum
    // per line
    while (c < plainlen) {

        if (c % 80 == 0) {

            printf("\n");

        }

        printf("%c", plaintext[c]);

        c++;

    }

    // set c to 0 to use it as a counter to print the ciphertext
    c = 0;

    printf("\n\n\nCiphertext:\n");

    // while loop used to print the ciphertext with 80 characters maximum
    // per line
    while (c < plainlen) {

        if (c % 80 == 0) {

            printf("\n");

        }

        printf("%c", ciphertext[c]);

        c++;

    }

    printf("\n");

    // free the previously allocated memory for the arrays holding
    // the key, plaintext and ciphertext.
    free(keyy);
    free(plaintext);
    free(ciphertext);

    // close the files representing the key and plaintext
    fclose(key);
    fclose(ptext);

    // return 0 and end the program
    return 0;

}
