#include "computorv1.h"

node*   get_tree(char* exp) {
	char** letters = ft_split(exp, ' ');
	if (!letters) {
		ft_putendl_fd("Memory allocation failed", 2);
		return NULL;
	}

	if (!ft_splitlen(letters)) 
		ft_putendl_fd("One of the 2 sides of the equation is empty", 2);{
		free(letters);
		return NULL;
	}

	node** partial = calloc(sizeof(node*), (ft_strlen(exp) + 1));
	if (!partial)
		return NULL;
	ft_bzero(partial, sizeof(node*) * (ft_strlen(exp) + 1));

	size_t i = 0;
	double tmp;
	int status;
	size_t len;
	node* node;
	pol* p;
	while (letters[i]) {
		len = ft_strlen(letters[i]);
		if (!len) {
			free_split(letters);
			free_arr_fun(partial, free_node);
			return NULL;
		}
		if (ft_isdigit(*(letters[i]))) {
			status = get_num(letters[i], &tmp);
			if (status) {
				free_split(letters);
				free_arr_fun(partial, free_node);
				return NULL;
			}
			p = monomial(0, tmp);
			if (!p) {
				free_split(letters);
				free_arr_fun(partial, free_node);
				return NULL;
			}
			node = calloc();
		}
	}
	free_split(letters);
	return NULL;
}

pol*    expand(node* tree) {
	if (!tree)
		return NULL;

	pol* res = NULL;
	pol* l = expand(tree->left);
	if (!l)
		return NULL;

	pol* r = expand(tree->right);
	if (!r) {
		free_pol(l);
		return NULL;
	}

	switch (tree->type)
	{
		case POL:
			res = pol_copy(tree->p);
			break;
			
		case SUM:
			res = pol_sum(l, r);
			break;

		case SUB:
			res = pol_sub(l, r);
			break;

		case MULT:
			res = pol_mul(l, r);
			break;

		default:
			ft_putendl_fd("Bad code had bad node type", 2);
	}

	free_pol(l);
	free_pol(r);

	return (res);
}