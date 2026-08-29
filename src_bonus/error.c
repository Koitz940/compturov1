#include "computorv1.h"

void error(char* reason) {
    printf("Error: %s\n", reason);
}

void bad_char(char* reason, char c) {
	printf("Error: %s: %c\n", reason, c);
}
