#include "computorv1.h"

int main(int argc, char** argv) {
    char* expression;
    pol* expanded;

    switch (argc)
    {
        case 1:
            expression = get_next_line(0);
            break;
        case 2:
            expression = ft_strdup(argv[1]);
            break;
        default:
            error("Too many input arguments");
            return 1;;
        }
        if (!expression) {
            error("Failed memory allocation");
            return 1;
    }

    expanded = get_equal_zero(expression);
    free(expression);
    if (!expanded)
        return 1;
    show_results(expanded);
    free(expanded);
}


//Tests for polynomial printing and operations
/* int main() {
    double coeffs1[] = {2.0, -5.0, 3.0, 0., -1.};
    pol p1 = {
        .deg = 4,
        .min_deg = 0,
        .poly = coeffs1
    };

    double coeffs2[] = {4.0, 2.0};
    pol p2 = {
        .deg = 4,
        .min_deg = 3,
        .poly = coeffs2
    };

    pol* f;

    show_pol(&p1);
    printf("\n");
    show_pol(&p2);
    printf("\n");

    f = pol_copy(&p1);
    show_pol(f);
    free_pol(f);
    printf("\n");

    f = pol_neg(&p1);
    show_pol(f);
    free_pol(f);
    printf("\n");

    f = pol_neg(&p2);
    show_pol(f);
    free_pol(f);
    printf("\n");

    f = pol_sum(&p1, &p2);
    show_pol(f);
    free_pol(f);
    printf("\n");

    f = pol_sub(&p1, &p2);
    show_pol(f);
    free_pol(f);
    printf("\n");

    f = pol_mul(&p1, &p2);
    show_pol(f);
    free_pol(f);
    printf("\n");

    double coeffs3[] = {0.};
    pol p3 = {
        .deg = 0,
        .min_deg = 0,
        .poly = coeffs3
    };

    show_pol(&p3);
    printf("\n");

    f = pol_mul(&p3, &p2);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = pol_mul(&p3, &p1);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    double coeffs4[] = {1.};
    pol p4 = {
        .deg = 0,
        .min_deg = 0,
        .poly = coeffs4
    };

    show_pol(&p4);
    printf("\n");

    f = pol_mul(&p4, &p2);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = pol_mul(&p4, &p1);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = monomial(10, 2.);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = monomial(5, 1.);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = monomial(10, -1.);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = monomial(1, 1.);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);

    f = monomial(10, 0);
    show_pol(f);
    printf("\n");
    printf("%lu, %lu\n", f->deg, f->min_deg);
    free_pol(f);
} */