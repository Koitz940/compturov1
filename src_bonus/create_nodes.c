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

int create_sum(size_t len, node** partial, size_t i, char* str) {
	if (len != 1) {
		bad_char("no space after sum sign, found", str[1]);
		return 1;
	}

	node* tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		return 1;
	}
	
	tree->type = SUM;
	partial[i] = tree;

	return 0;
}

int create_mul(size_t len, node** partial, size_t i, char* str) {
	if (len != 1) {
		bad_char("no space after mult sign, found", str[1]);
		return 1;
	}

	node* tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		return 1;
	}
	
	tree->type = MULT;
	partial[i] = tree;

	return 0;
}

int create_sub(size_t len, node** partial, size_t i, char* str) {
	if (len != 1) {
		bad_char("no space after sub sign, found", str[1]);
		return 1;
	}

	node* tree = calloc(1, sizeof(node));
	if (!tree) {
		error("Memory allocation failed");
		return 1;
	}
	
	tree->type = SUB;
	partial[i] = tree;

	return 0;
}

int create_monomial(char* str, node** partial, size_t i) {
	size_t exp;
	pol* p;
	node* tree;

	if (!str[1]) 
		exp = 1;
	else if (str[1] != '^') {
		bad_char("Bad exponent sign", str[1]);
		return 1;
	} else if (!ft_isdigit(str[2])) {
		bad_char("Bad exponent number", str[2]);
		return 1;
	}
	else if (get_exp(str + 2, &exp))
		return 1;

	p = monomial(exp, 1.);
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