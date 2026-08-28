#include "computorv1.h"

static void correct_degree(pol* p) {
	if (!p)
		return; 

	while (p->deg > 0 && p->poly[p->deg] == 0.0) {
			p->deg--;
		}
}

pol*    pol_sum(pol* p, pol* g) {
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to summing", 2);
		return NULL;
	}

	pol* res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	double* poly = malloc(sizeof(double) * (fmax(p->deg, g->deg) + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	size_t tmp = fmin(p->deg, g->deg) + 1;
	for (size_t i = 0; i < tmp; i++) {
		poly[i] = p->poly[i] + g->poly[i];
	}

	pol* big = p->deg > g->deg ? p: g;
	for (size_t i = tmp; i <= big->deg; i++) {
		poly[i] = big->poly[i];
	}

	res->poly = poly;
	res->deg = big->deg;
	correct_degree(res);
	return res;
}

pol*	pol_neg(pol* p) {
	if (!p) {
		ft_putendl_fd("Null ptr passed to negating", 2);
		return NULL;
	}

	pol* res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	double* poly = malloc(sizeof(double) * (p->deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}


	for (size_t i = 0; i <= p->deg; i++) {
		poly[i] = -p->poly[i];
	}

	res->poly = poly;
	res->deg = p->deg;
	return res;
}

pol*    pol_sub(pol* p, pol* g) {
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to subtracting", 2);
		return NULL;
	}

	pol* h = pol_neg(g);
	if (!h) {
		return NULL;
	}

	pol* res = pol_sum(p, h);

	free_pol(h);
	return res;
}

pol*    pol_mul(pol* p, pol* g) {
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to multiplying", 2);
		return NULL;
	}

	size_t deg = p->deg + g->deg;
	pol* res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	double* poly = malloc(sizeof(double) * (deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	res->poly = poly;
	res->deg = deg;

	for (size_t i = 0; i <= deg; i++) {
		poly[i] = 0.0;
	}
	for (size_t i = 0; i <= p->deg; i++) {
		for (size_t j = 0; j <= g->deg; j++) {
			poly[i + j] += p->poly[i] * g->poly[j];
		}
	}

	correct_degree(res);
	return res;
}

pol*    monomial(size_t deg) {
	pol* p = malloc(sizeof(pol));
	if (!p) {
		return NULL;
	}

	double* poly = malloc(sizeof(double) * (deg + 1));
	if (!poly) {
		free(p);
		return NULL;
	}

	p->deg = deg;

	for (size_t i = 0; i < deg; i++) {
		poly[i] = 0.;
	}
	poly[deg] = 1.;

	p->poly = poly;

	return p;
}

pol*    pol_sum_free(pol* p, pol* g) {
	pol* res = pol_sum(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol*    pol_sub_free(pol* p, pol* g) {
	pol* res = pol_sub(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol*    pol_neg_free(pol* p) {
	pol* res = pol_neg(p);
	free_pol(p);
	return res;
}

pol*    pol_mul_free(pol* p, pol* g) {
	pol* res = pol_mul(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol*	pol_copy(pol* p) {
	pol* res = malloc(sizeof(pol));

	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}
	res->deg = p->deg;

	double* poly = malloc(sizeof(double) * (res->deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return (NULL);
	}

	ft_memcpy(poly, p->poly, sizeof(double) * (res->deg + 1));
	res->poly = poly;
	return res;
}