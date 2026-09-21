#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myfilefunctions.h"

// Count lines, words, and characters
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file) return -1;

    *lines = 0;
    *words = 0;
    *chars = 0;
    int in_word = 0;
    int ch;

    // Read file character by character until End of File (EOF)
    while ((ch = fgetc(file)) != EOF) {
        (*chars)++;
        
        if (ch == '\n') {
            (*lines)++;
        }
        
        // Logic for word counting (spaces, tabs, newlines separate words)
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
    return 0; // Success
}

// Search lines and dynamically fill array of matching lines
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str || !matches) return -1;

    int match_count = 0;
    int capacity = 5; // Initial array capacity
    
    // Allocate memory for the array of string pointers
    *matches = (char**)malloc(capacity * sizeof(char*));
    if (*matches == NULL) return -1;

    char buffer[1024]; // Assuming max line length is 1024 characters

    // Read line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // strstr checks if search_str exists in buffer
        if (strstr(buffer, search_str) != NULL) { 
            
            // If our array is full, double its capacity
            if (match_count >= capacity) {
                capacity *= 2;
                char** temp = (char**)realloc(*matches, capacity * sizeof(char*));
                if (!temp) return -1; // memory fail
                *matches = temp;
            }
            
            // Duplicate the matching line and store it
            (*matches)[match_count] = strdup(buffer); 
            match_count++;
        }
    }
    return match_count; // Return total matches found
}
