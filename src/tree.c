#include "computorv1.h"

char node_type(node* n) {
	switch (n->type)
	{
		case POL:
			return 'p';
			break;
		
		case SUM:
			return '+';
			break;

		case SUB:
			return '-';
			break;
		
		case MULT:
			return '*';
			break;
		
		default:
			break;
	}
	return 'a';
}

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

	node** partial = calloc((ft_strlen(exp) * 2), sizeof(node*));
	if (!partial) {
		free_split(letters);
		return NULL;
	}
	ft_bzero(partial, sizeof(node*) * (ft_strlen(exp) * 2));

	size_t i = 0;
	size_t len;
	while (letters[i]) {
		len = ft_strlen(letters[i]);
		//printf("%s\n", letters[i]);
		if (!len) {
			error("Bad empty weird symbol on equation");
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		}
		if (ft_isdigit(*(letters[i]))) {
			if (create_num(letters[i], partial, i)) {
				free_split(letters);
				free_node_arr(partial, free_node);
				return NULL;
			}
		} else if (*letters[i] == '+') {
			if (create_sum(len, partial, i, letters[i])) {
				free_split(letters);
				free_node_arr(partial, free_node);
				return NULL;
			}
		} else if (*letters[i] == '*') {
			if (create_mul(len, partial, i, letters[i])) {
				free_split(letters);
				free_node_arr(partial, free_node);
				return NULL;
			}
		} else if (*letters[i] == '-') {
			switch (len) {
				case 1:
					if (create_sub(len, partial, i, letters[i] + 1)) {
						free_split(letters);
						free_node_arr(partial, free_node);
						return NULL;
					}
					break;
				
				default:
					if (create_num(letters[i], partial, i)) {
						free_split(letters);
						free_node_arr(partial, free_node);
						return NULL;
					}
					break;
			}
		} else if (*letters[i] == 'x' || *letters[i] == 'X') {
			if (create_monomial(letters[i], partial, i)) {
				free_split(letters);
				free_node_arr(partial, free_node);
				return NULL;
			}
		} else {
			bad_char("Bad symbol on equation", *letters[i]);
			free_split(letters);
			free_node_arr(partial, free_node);
			return NULL;
		}
		i++;
	}
	free_split(letters);
	len = 0;
	while (partial[len]) 
		len++;
	if (len % 2 == 0) {
		error("Invalid operation expression");
		free_node_arr(partial, free_node);
		return NULL;
	}
	for (size_t j = 0; j + 1 < len; j += 2) {
		if (!(partial[j]->type == POL && partial[j + 1]->type != POL)) {
			free_node_arr(partial, free_node);
			error("Bad expression, found 2 numbers/x/X/operations in a row");
			return NULL;
		}
	}
	if (partial[len - 1]->type != POL) {
		free_node_arr(partial, free_node);
		char c = node_type(partial[len - 1]);
		printf("Error: Bad expression, expected number or x/X for last element, found: %c\n", c);
		return NULL;
	}

	node* res = compress(partial);
	free(partial);
	return res;
}

node* copy_node(node* n) {
	node* res = calloc(1, sizeof(node));
	if (!res) {
		error("Memory allocation failed");
		return NULL;
	}
	res->type = n->type;
	if (n->p) {
		res->p = pol_copy(n->p);
		if (!res->p) {
			free_node(res);
			error("Memory allocation failed");
			return NULL;
		}
	}
	if (n->left) {
		res->left = copy_node(n->left);
		if (!res->left) {
			free_node(res);
			error("Memory allocation failed");
			return NULL;
		}
	}
	if (n->right) {
		res->right = copy_node(n->right);
		if (!res->right) {
			free_node(res);
			error("Memory allocation failed");
			return NULL;
		}
	}

	return res;
}

node*	compress(node** list) {
	int len = 0;
	while (list[len]) 
		len++;

	int i = len - 2;
	node* n = NULL;

	while (i > 0) {
		if (list[i]->type == SUM || list[i]->type == SUB) {
			n = list[i];
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i -= 2;
	}

	i = len - 2;
	while (i > 0) {
		if (list[i]->type == MULT) {
			n = list[i];
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i -= 2;
	}

	n = *list;
	*list = NULL;
	//printf("%c\n", node_type(n));
	return n;
}

pol*    expand(node* tree) {
	if (!tree)
		return NULL;

	pol* res = NULL;
	if (tree->type == POL) {
		res = pol_copy(tree->p);
		return res;
	}
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
