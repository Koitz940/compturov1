#include "computorv1_bonus.h"

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
        bad_char("Bad number", *endptr);
        return 1;
    }

    return 0;
}

int get_exp(char* str, size_t* num) {
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
        bad_char("Bad number", *endptr);
        return 1;
    }

	return 0;
}

size_t strtosize(const char *nptr, char **endptr) {
    uintmax_t val;
    
    errno = 0;
    val = strtoumax(nptr, endptr, 10);

    if (val > SIZE_MAX) {
        errno = ERANGE;
        return SIZE_MAX;
    }
    
    return (size_t)val;
}