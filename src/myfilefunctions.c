#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myfilefunctions.h"

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file) return -1;

    *lines = 0;
    *words = 0;
    *chars = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        (*chars)++;
        
        if (ch == '\n') {
            (*lines)++;
        }
        
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
    return 0; 
}


int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str || !matches) return -1;

    int match_count = 0;
    int capacity = 5; 
    
    *matches = (char**)malloc(capacity * sizeof(char*));
    if (*matches == NULL) return -1;

    char buffer[1024]; 

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, search_str) != NULL) { 
            
            if (match_count >= capacity) {
                capacity *= 2;
                char** temp = (char**)realloc(*matches, capacity * sizeof(char*));
                if (!temp) return -1; 
                *matches = temp;
            }
            
            (*matches)[match_count] = strdup(buffer); 
            match_count++;
        }
    }
    return match_count; 
}
