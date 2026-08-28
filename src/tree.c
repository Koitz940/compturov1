#include "computorv1.h"

node*   get_tree(char* exp) {
	char** letters = split(expr);
	if (!letters) {
		return NULL;
	}
	
	
}

pol*    expand(node* tree) {
	if (!tree) {
		return NULL;
	}

	pol* res;
	pol* l = expand(tree->left);
	pol* r = expand(tree->right);

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