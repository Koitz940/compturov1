#include "computorv1.h"

int get_num(char* str, double* num) {
    char* endptr;

    errno = 0;
    *num = strtod(str, &endptr);

    if (endptr == str) {
        error("No conversion could be performed");
        return 1;
    } 
    else if (errno == ERANGE) {
        error("Value out of range for a double");
        return 1;
    } 
    else if (*endptr != '\0') {
        printf("Error: Converted '%g', but stopped at leftover characters: '%s'\n", *num, endptr);
        return 1;
    }

    return 0;
}