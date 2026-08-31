#include "computorv1_bonus.h"

int create_num(char* str, node** partial, size_t i) {
	double tmp;
	node* tree;
	pol* p;

	if (get_num(str, &tmp))
		return 1;

	p = monomial(0, tmp);
	if (!p) 
		return 1;

	tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		free_pol(p);
		return 1;
	}
	tree->p = p;
	partial[i] = tree;
	tree->type = POL;

	return 0;
}

int create_op(node** partial, size_t i, char c) {
	node* tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		return 1;
	}
	
	tree->type = op_type(c);
	partial[i] = tree;

	return 0;
}

int create_monomial(node** partial, size_t i) {
	pol* p;
	node* tree;

	p = monomial(1, 1.);
	if (!p) 
		return 1;

	tree = calloc(1, sizeof(node));
	if (!tree) {
		free_pol(p);
		error("Memory allocation failed");
		return 1;
	}
	
	tree->type = POL;
	partial[i] = tree;
	tree->p = p;

	return 0;
}

int create_const(node** partial, size_t i, double c) {
	node* tree;
	pol* p;

	p = monomial(0, c);
	if (!p) 
		return 1;

	tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		free_pol(p);
		return 1;
	}
	tree->p = p;
	partial[i] = tree;
	tree->type = POL;

	return 0;
}