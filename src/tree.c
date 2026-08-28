#include "computorv1.h"

node*   get_tree(char* exp) {
	char** letters = ft_split(exp, ' ');
	if (!letters) {
		error("Memory allocation failed");
		return NULL;
	}

	if (!ft_splitlen(letters)) {
		error("One of the 2 sides of the equation is empty");
		free(letters);
		return NULL;
	}

	node** partial = calloc((ft_strlen(exp) + 1), sizeof(node*));
	if (!partial)
		return NULL;
	ft_bzero(partial, sizeof(node*) * (ft_strlen(exp) + 1));

	size_t i = 0;
	size_t len;
	while (letters[i]) {
		len = ft_strlen(letters[i]);
		if (!len) {
			error("Bad empty weird symbol on equation");
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		}
		if (ft_isdigit(*(letters[i])) && create_num(letters[i], partial, i)) {
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		} else if (*letters[i] == '+' && create_sum(len, partial, i, letters[i])) {
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		} else if (*letters[i] == '*' && create_mul(len, partial, i, letters[i])) {
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		} else if (*letters[i] == '-' && create_sub(len, partial, i, letters[i])) {
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		} else if ((*letters[i] == 'x' || *letters[i] == 'X') && create_monomial(letters[i], partial, i)) {
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		} else {
			bad_char("Bad symbol on equation", *letters[i]);
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		}
		i++;
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
			error("Bad code had bad node type");
	}

	free_pol(l);
	free_pol(r);

	return (res);
}