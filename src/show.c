#include "computorv1.h"

void    show_pol(pol* p) {
    double cur;
    long int curint;

    for (size_t i = 0; i <= p->deg; i++) {
        if (*(p->poly + i) != 0.) {
            cur = *(p->poly + i);
            if (cur == round(cur)) {
                curint = (long int)round(cur);
                printf("%ld * x^%lu", curint, i);
            }
            else
                printf("%lf * x^%lu", cur, i);
            if (i != p->deg) {
                printf(" + ");
            }
        }
    }
}

static void solve_const(pol* p) {
    if (*p->poly == 0.0)
        printf("Got 0 = 0, identity, expression is true for all x, if there even was an x on the given equation\n");
    else
        printf("Got a = 0, with a != 0, no solutions\n");
}

static void solve_linear(pol* p) {
    double sol = *p->poly / *(p->poly + 1);
    long int solint = (long int)round(sol);
    if (sol == round(sol)) {
        printf("Solution is:\n%ld\n", solint);
    } else {
        printf("Solution is:\n%lf\n", sol);
    }
}

void    show_results(pol* p) {
    printf("Reduced form: ");
    show_pol(p);
    printf("\n");

    switch (p->deg)
    {
        case 0:
            solve_const(p);
            break;
        
        case 1:
            solve_linear(p);
            break;

        case 2:
            solve_quad(p);
            break;

        case 3:
            printf("Resulted a cubic polynomial, implemented in bonus, why? I don't even know myself\n");
            break;
        
        case 4:
            printf("Resulted a quartic polynomial, closed soluton exists but it's not asked and I respect myself enough not to code it, just google the formula and you'll understand\n");
            break;
        
        default:
            printf("Resulted polynomial is of degree %lu, which is greater than 4, there is no closed solution for polynomials of degree 5 or higher, lookup Galois Theory for more info\n");
            break;
    }

    free_pol(p);
}