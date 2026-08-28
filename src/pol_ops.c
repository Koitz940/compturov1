#include "computorv1.h"

static void correct_degree(pol *p)
{
	if (!p)
		return;

	while (p->deg >= p->min_deg && p->deg > 0 && p->poly[p->deg - p->min_deg] == 0.0)
		p->deg--;

	if (p->deg < p->min_deg) {
		p->deg = 0;
		p->min_deg = 0;
		p->poly[0] = 0.;
	}
}

pol *pol_sum(pol *p, pol *g)
{
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to summing", 2);
		return NULL;
	}

	pol *res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	size_t min_deg = p->min_deg < g->min_deg ? p->min_deg: g->min_deg;
	size_t deg = p->deg > g->deg ? p->deg: g->deg;
	double *poly = malloc(sizeof(double) * (deg - min_deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	for (size_t i = 0; i <= deg - min_deg; i++) {
		poly[i] = 0.;
	}

	for (size_t i = 0; i <= p->deg - p->min_deg; i++) {
		poly[i + p->min_deg - min_deg] += p->poly[i];
	}

	for (size_t i = 0; i <= g->deg - g->min_deg; i++) {
		poly[i + g->min_deg - min_deg] += g->poly[i];
	}

	res->poly = poly;
	res->deg = deg;
	res->min_deg = min_deg;
	correct_degree(res);
	return res;
}

pol *pol_neg(pol *p)
{
	if (!p) {
		ft_putendl_fd("Null ptr passed to negating", 2);
		return NULL;
	}

	pol *res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	double *poly = malloc(sizeof(double) * (p->deg + 1 - p->min_deg));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	for (size_t i = 0; i <= p->deg - p->min_deg; i++)
		poly[i] = -p->poly[i];

	res->poly = poly;
	res->deg = p->deg;
	res->min_deg = p->min_deg;
	return res;
}

pol *pol_sub(pol *p, pol *g)
{
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to subtracting", 2);
		return NULL;
	}

	pol *h = pol_neg(g);
	if (!h)
		return NULL;

	pol *res = pol_sum(p, h);

	free_pol(h);
	return res;
}

pol *pol_mul(pol *p, pol *g)
{
	if (!p || !g) {
		ft_putendl_fd("Null ptr passed to multiplying", 2);
		return NULL;
	}

	size_t deg = p->deg + g->deg;
	size_t min_deg = p->min_deg > g->min_deg ? p->min_deg: g->min_deg;
	pol *res = malloc(sizeof(pol));
	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	double *poly = malloc(sizeof(double) * (deg - min_deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	res->poly = poly;
	res->deg = deg;
	res->min_deg = min_deg;

	for (size_t i = 0; i <= deg - min_deg; i++) {
		poly[i] = 0.0;
	}
	for (size_t i = 0; i <= p->deg - p->min_deg; i++) {
		for (size_t j = 0; j <= g->deg - g->min_deg; j++) {
			poly[i + j] += p->poly[i] * g->poly[j];
		}
	}

	correct_degree(res);
	return res;
}

pol *monomial(size_t deg, double coef)
{
	pol *p = malloc(sizeof(pol));
	if (!p)
		return NULL;

	double *poly = malloc(sizeof(double));
	if (!poly) {
		free(p);
		return NULL;
	}

	p->deg = deg;
	p->min_deg = deg;

	*poly = coef;

	p->poly = poly;

	return p;
}

pol *pol_sum_free(pol *p, pol *g)
{
	pol *res = pol_sum(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol *pol_sub_free(pol *p, pol *g)
{
	pol *res = pol_sub(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol *pol_neg_free(pol *p)
{
	pol *res = pol_neg(p);
	free_pol(p);
	return res;
}

pol *pol_mul_free(pol *p, pol *g)
{
	pol *res = pol_mul(p, g);
	free_pol(p);
	free_pol(g);
	return res;
}

pol *pol_copy(pol *p)
{
	pol *res = malloc(sizeof(pol));

	if (!res) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	res->deg = p->deg;
	res->min_deg = p->min_deg;

	double *poly = malloc(sizeof(double) * (res->deg - res->min_deg + 1));
	if (!poly) {
		free(res);
		ft_putendl_fd("Memory allocation failed", 2);
		return (NULL);
	}

	ft_memcpy(poly, p->poly, sizeof(double) * (res->deg - res->min_deg + 1));
	res->poly = poly;
	return res;
}