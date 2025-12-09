#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256
#define FILENAME "input.txt"
 
void countChar() {
    long long frequency[ASCII_SIZE] = {0};
    FILE *file;
    int c;

    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    while ((c = fgetc(file)) != EOF) {
        if (c >= 0 && c < ASCII_SIZE) {
            frequency[c]++;
        }
    }

    if (ferror(file)) {
        perror("Error reading file");
    }

    fclose(file);

    printf("\n--- ASCII Character Frequency ---\n");
    printf("Code\tChar\tFrequency\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequency[i] > 0) {
            // Only display non-zero frequencies
            if (i >= 32 && i <= 126) {
                // Printable ASCII characters
                printf("%d\t'%c'\t%lld\n", i, (char)i, frequency[i]);
            } else if (i == 10) {
                // Newline character
                printf("%d\t'\\n'\t%lld\n", i, frequency[i]);
            } else if (i == 9) {
                // Tab character
                printf("%d\t'\\t'\t%lld\n", i, frequency[i]);
            } else if (i == 13) {
                 // Carriage return
                printf("%d\t'\\r'\t%lld\n", i, frequency[i]);
            }
             else {
                // Non-printable/control characters
                printf("%d\t(CTL)\t%lld\n", i, frequency[i]);
            }
        }
    }
}
//counts the frequency of each ASCII character within it
//handle potential file opening errors
//detect when it has reached the end of the file.

int main() {
    countChar(FILENAME);
    return 0;
}