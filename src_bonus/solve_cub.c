#include "computorv1_bonus.h"
#include "complex.h"

static void print_complex_solution(double r, double i) {
    printf("x = ");

    if (r == 0 && i == 0) {
        printf("0");
        return;
    } 

    if (r != 0) {
        printf("%g", r);
        if (i != 0) {
            if (i < 0)
                printf(" - %gi", -i);
            else
                printf(" + %gi", i);
        }
    } 
    
    else 
        printf("%gi", i);

}

static int are_roots_equal(double complex a, double complex b) {
    double eps = 1e-6;
    return fabs(creal(a) - creal(b)) < eps && fabs(cimag(a) - cimag(b)) < eps;
}

void solve_cub(pol* o) {
	double a = 0.;
	double b = 0.;
	double c = 0.;
	double d = 0.;

	switch (o->min_deg)
	{
		case 0:
			a = o->poly[3];
			b = o->poly[2];
			c = o->poly[1];
			d = o->poly[0];
			break;
		
		case 1:
			a = o->poly[2];
			b = o->poly[1];
			c = o->poly[0];
			break;

		case 2:
			a = o->poly[1];
			b = o->poly[0];
			break;

		case 3:
			a = o->poly[0];
			break;

		default:
			break;
	}

	if (a == 0.) {
		error("Bad code took a polynomial with cubic coefficient 0 as a cubic polynomial");
		return;
	}

	double p = c / a - (b * b) / (3 * a * a);
	double q = (2 * b * b * b) / (27 * a * a * a) - (b * c) / (3 * a * a) + d / a;

    double discriminant = (q * q / 4.0) + (p * p * p / 27.0);

    printf("Δ = %g\n", discriminant);
    
    double complex u, v;
    if (discriminant >= 0) {
        double sqrt_disc = sqrt(discriminant);
        u = cbrt(-q / 2.0 + sqrt_disc);
        v = cbrt(-q / 2.0 - sqrt_disc);
    } else {
        double complex sqrt_disc = csqrt(discriminant);
        u = cpow(-q / 2.0 + sqrt_disc, 1.0 / 3.0);
        v = cpow(-q / 2.0 - sqrt_disc, 1.0 / 3.0);
    }

    // Primitive cube roots of unity
    double complex omega = -0.5 + (sqrt(3.0) / 2.0) * I;
    double complex omega2 = -0.5 - (sqrt(3.0) / 2.0) * I;

    // Three roots for y in the depressed cubic
    double complex y1 = u + v;
    double complex y2 = omega * u + omega2 * v;
    double complex y3 = omega2 * u + omega * v;

    // Shift back to x
    double shift = b / (3.0 * a);
    double complex x1 = y1 - shift;
    double complex x2 = y2 - shift;
    double complex x3 = y3 - shift;

    double complex roots[3] = {x1, x2, x3};
    int printed[3] = {0, 0, 0};

    printf("Roots:\n");

    for (int i = 0; i < 3; i++) {
        if (printed[i]) continue;

        int multiplicity = 1;
        for (int j = i + 1; j < 3; j++) {
            if (are_roots_equal(roots[i], roots[j])) {
                multiplicity++;
                printed[j] = 1;
            }
        }

        print_complex_solution(creal(roots[i]), cimag(roots[i]));
        if (multiplicity == 2) {
            printf("  (double root)\n");
        } else if (multiplicity == 3) {
            printf("  (triple root)\n");
        } else {
            printf("\n");
        }
    }
}