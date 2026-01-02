#include "string.h"

int strcmp(char* p_str1, char* p_str2) {
    int returnCode = 0;
    int idx = 0;

    while(1) {
        if(p_str1[idx] != p_str2[idx]) {
            returnCode = p_str1[idx] - p_str2[idx];
            break;
        }
        if(p_str1[idx] == '\0' || p_str2[idx] == '\0') {
            returnCode = p_str1[idx] - p_str2[idx];
            break;
        }
        idx++;
    }

    return returnCode;
}
