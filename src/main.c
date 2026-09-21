#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");
    
    char str1[100] = "Operating ";
    const char* str2 = "Systems";
    char str3[100];
    char str4[100];

    printf("Length of \"%s\": %d\n", str1, mystrlen(str1));

    mystrcat(str1, str2);
    printf("After mystrcat: %s\n", str1);

    mystrcpy(str3, "Assignment 01");
    printf("After mystrcpy: %s\n", str3);

    mystrncpy(str4, "Kali Linux OS", 4);
    str4[4] = '\0'; // manually terminate string after partial copy
    printf("After mystrncpy (first 4 chars): %s\n", str4);

    
    printf("\n--- Testing File Functions ---\n");
    
    // 1. Create a temporary dummy file to test
    FILE* tempFile = fopen("dummy_test.txt", "w+");
    if (!tempFile) {
        printf("Error creating test file!\n");
        return -1;
    }
    
    // Write some test data into the file
    fprintf(tempFile, "This is line one.\nHello world from Kali Linux.\nThis assignment is great.\n");
    
    // Rewind file pointer back to the start before reading
    rewind(tempFile); 
    
    // Test wordCount
    int lines, words, chars;
    if (wordCount(tempFile, &lines, &words, &chars) == 0) {
        printf("wordCount result -> Lines: %d, Words: %d, Chars: %d\n", lines, words, chars);
    }

    // Rewind again before grep
    rewind(tempFile); 
    
    // Test mygrep
    char** matches = NULL;
    int count = mygrep(tempFile, "is", &matches);
    
    if (count != -1) {
        printf("mygrep found %d match(es) for 'is':\n", count);
        for (int i = 0; i < count; i++) {
            printf(" -> %s", matches[i]);
            free(matches[i]); // Important: free the memory allocated by strdup
        }
        free(matches); // Important: free the array of pointers
    }

    // Close and remove the temporary file
    fclose(tempFile);
    remove("dummy_test.txt");

    return 0;
}
