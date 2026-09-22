#include "../include/mystrfunctions.h"

int mystrlen(const char* s) {
    if (!s) return 0;
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

int mystrcpy(char* dest, const char* src) {
    if (!dest || !src) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; 
    return 0; 
}

int mystrncpy(char* dest, const char* src, int n) {
    if (!dest || !src) return -1;
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for ( ; i < n; i++) {
        dest[i] = '\0';
    }
    return 0; 
}

int mystrcat(char* dest, const char* src) {
    if (!dest || !src) return -1;
    int dest_len = mystrlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0'; 
    return 0; 
}
