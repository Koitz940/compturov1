#include "computorv1_bonus.h"

static void solve_const(pol* p) {
    if (*p->poly == 0.0)
        printf("Got 0 = 0, identity, expression is true for all x, if there even was an x on the given equation\n");
    else
        printf("Got a = 0, with a != 0, no solutions\n");
}

static void solve_linear(pol* p) {
	double a;
	double b;

	if (p->min_deg) {
		a = 0;
		b = *p->poly;
	} else {
		a = p->poly[0];
		b = p->poly[1];
	}
    double sol = -a / b;


	printf("Got a linear polynomial\nSolution is:\n");
    print_solution(sol, 'x');
	printf("\n");
}

static void solve_quad(pol* p) {
	double a = 0.;
	double b = 0.;
	double c = 0.;

	switch (p->min_deg)
	{
		case 0:
			a = p->poly[2];
			b = p->poly[1];
			c = p->poly[0];
			break;
		
		case 1:
			a = p->poly[1];
			b = p->poly[0];
			break;

		case 2:
			a = p->poly[0];
			break;

		default:
			break;
	}

	if (a < 0) {
		a = -a;
		b = -b;
		c = -c;
	}

	printf("Got a quadratic polynomial\n");

	double d = b * b - 4 * a * c;
	printf("Δ = %g\n", d);

	double r;
	if (d == 0.) {
		printf("Zero discriminant, only solution (double root) is:\n");
		print_solution(-b / (2 * a), 'x');
		printf("\n");
	} else if (d < 0.) {
		printf("negative discriminant, solutions (complex conjugates) are:\n");
		r = sqrt(-d);
		d = -b / (2 * a);

		if (d != 0) {
			print_solution(d, 'x');
			printf(" + ");
		}
    	printf("%g", r / (2 * a));
		printf("i\n");

		if (d != 0) {
			print_solution(d, 'x');
			printf(" - ");
		} else {
			printf("-");
		}
		printf("%g", r / (2 * a));
		printf("i\n");
	} else {
		printf("positive discriminant, solutions are:\n");
		r = sqrt(d);

		print_solution((-b + r) / (2 * a), 'x');
		printf("\n");
		print_solution(-(b + r) / (2 * a), 'x');
		printf("\n");
	}
}

void    show_results(pol* p) {
    printf("Reduced form: ");
    show_pol(p);
    printf(" = 0\n");

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
            solve_cub(p);
            break;
        
        case 4:
            printf("Resulted a quartic polynomial, closed solution exists but it's not asked and I respect myself enough not to code it, just google the formula and you'll understand\n");
            break;
        
        default:
            printf("Resulted polynomial is of degree %lu, which is greater than 4, there is no closed solution for polynomials of degree 5 or higher, lookup Galois Theory for more info\n", p->deg);
            break;
    }
}