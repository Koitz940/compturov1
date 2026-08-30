#include "computorv1_bonus.h"

void print_solution(double sol, int symbol) {
    printf("%c = %g", symbol, sol);
} 

void show_pol(pol* p) {
    size_t count = p->deg - p->min_deg + 1;
    int first = 1;

    for (size_t i = count - 1; i + 1 != 0; i--) {
        double coeff = p->poly[i];
        if (coeff == 0.0) 
            continue;

        size_t current_deg = p->min_deg + i;

        if (!first) {
            if (coeff > 0) {
                printf(" + ");
            } else {
                printf(" - ");
            }
        } else {
            if (coeff < 0) {
                printf("-");
            }
        }

        double abs_coeff = (coeff < 0) ? -coeff : coeff;

        if (abs_coeff != 1.0 || current_deg == 0) {
            printf("%g", abs_coeff);
        }

        if (current_deg > 0) {
            printf("x");
            if (current_deg > 1) {
                printf("^%lu", current_deg);
            }
        }

        first = 0;
    }

    if (first) {
        printf("0");
    }
}