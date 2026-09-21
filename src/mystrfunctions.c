#include "../include/mystrfunctions.h"

// Return length of string (without null terminator)
int mystrlen(const char* s) {
    if (!s) return 0;
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Copy src to dest
int mystrcpy(char* dest, const char* src) {
    if (!dest || !src) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Add null terminator at the end
    return 0; // Return 0 on success
}

// Copy first n characters of src to dest
int mystrncpy(char* dest, const char* src, int n) {
    if (!dest || !src) return -1;
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    // If src is shorter than n, pad with null bytes
    for ( ; i < n; i++) {
        dest[i] = '\0';
    }
    return 0; // Return 0 on success
}

// Concatenate src to the end of dest
int mystrcat(char* dest, const char* src) {
    if (!dest || !src) return -1;
    int dest_len = mystrlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0'; // Add null terminator
    return 0; // Return 0 on success
}
