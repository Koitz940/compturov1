#include "computorv1.h"

static void print_solution(double sol) {
	long int solint = (long int)round(sol);
	if (sol == round(sol)) {
        printf("x = %ld", solint);
    } else {
        printf("x = %lf", sol);
    }
} 

void    show_pol(pol* p) {
    double cur;
    long int curint;

	cur = p->poly[0];
	if (cur < 0) {
		printf("- ");
		cur = -cur;
	}
    for (size_t i = 0; i <= p->deg; i++) {
		if (cur == round(cur)) {
			curint = (long int)round(cur);
			printf("%ld * x^%lu", curint, i);
		}
		else
			printf("%lf * x^%lu", cur, i);
		if (i != p->deg) {
			if (p->poly[i + 1] < 0) {
				printf(" - ");
				cur = -p->poly[i + 1];
			} else {
				printf(" + ");
				cur = p->poly[i + 1];
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
    double sol = p->poly[0] / p->poly[1];

	printf("Got a linear polynomial\nSolution is: ");
    print_solution(sol);
	printf("\n");
}

static void solve_quad(pol* p) {
	double a = p->poly[2];
	double b = p->poly[1];
	double c = p->poly[0];

	printf("Got a quadratic polynomial\n");

	double d = b * b - 4 * a * c;
	long int dint = (long int)round(d);
	if (d == round(d)) {
		printf("Δ = %lu\n", dint);
	} else {
		printf("Δ = %lf\n", d);
	}

	double r;
	long int intr;
	if (d == 0.) {
		printf("Zero discriminant, only solution (double root) is:\n");
		print_solution(-b / (2 * a));
		printf("\n");
	} else if (d < 0.) {
		printf("negative discriminant, solutions (complex conjugates) are:\n");

		print_solution(-b / (2 * a));
		printf(" + ");
		r = sqrt(-d);
		intr = (long int)round(r);
		if (r == round(r)) {
        	printf("%ld", intr);
    	} else {
    		printf("%lf", r);
    	}
		printf("i\n");

		print_solution(-b / (2 * a));
		printf(" - ");
		if (r == round(r)) {
        	printf("%ld", intr);
    	} else {
    		printf("%lf", r);
    	}
		printf("i\n");
	} else {
		printf("positive discriminant, solutions are:\n");
		r = sqrt(d);

		print_solution((-b + r) / (2 * a));
		printf("\n");
		print_solution(-(b + r) / (2 * a));
		printf("\n");
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
            printf("Resulted polynomial is of degree %lu, which is greater than 4, there is no closed solution for polynomials of degree 5 or higher, lookup Galois Theory for more info\n", p->deg);
            break;
    }

    free_pol(p);
}