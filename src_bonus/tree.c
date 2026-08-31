#include "computorv1_bonus.h"

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

		case BIG_MULT:
			return 'X';
			break;
		
		case NEG:
			return '_';
			break;

		case SOM:
			return '|';
			break;

		case DIV:
			return '/';
			break;

		case EXP:
			return '^';
			break;

		default:
			break;
	}
	return 'a';
}

char op_type(char c) {
	switch (c)
	{	
		case '+':
			return SUM;
			break;

		case '-':
			return SUB;
			break;
		
		case '*':
			return MULT;
			break;

		case 'X':
			return BIG_MULT;
			break;
		
		case '_':
			return NEG;
			break;

		case '|':
			return SOM;
			break;

		case '/':
			return DIV;
			break;

		case '^':
			return EXP;
			break;

		default:
			break;
	}
	return POL;
}

double special_num(char c) {
	switch (c)
	{
		case 'e':
			return (exp(1.));
			break;

		case 'p':
			return PI;
			break;
	
		default:
			break;
	}

	return 0.0;
}

static void free_both(node** list, char* tmp) {
	free_node_arr(list, free_node);
	free(tmp);
}

static int isnum(node* n) {
	return n->type == POL || n->type == SOM || n->type == NEG;
}

node*   get_tree(char* exp) {
	size_t len = ft_strlen(exp);

	node** list = calloc((len * 2), sizeof(node*));
	if (!list) {
		error("Memory allocation failed");
		return NULL;
	}

	size_t i = 0;
	size_t elem = 0;
	size_t bracket = 0;
	node* n;

	char *tmp = calloc(len + 1, sizeof(char));
	if (!tmp) {
		free(list);
		error("Memory allocation failed");
		return NULL;
	}

	while (exp[i]) {
		if (ft_isdigit(exp[i])) {
			for (size_t j = 0; ft_isdigit(exp[i]) || exp[i] == '.'; j++) {
				tmp[j] = exp[i];
				i++;
			}

			if (create_num(tmp, list, elem)) {
				free_both(list, tmp);
				return NULL;
			}

			ft_bzero(tmp, len + 1);
			i++;

			continue;
		}

		else if (op_type(exp[i])) {
			if (create_op(list, elem, exp[i])) {
				free_both(list, tmp);
				return NULL;
			}
		}

		else if (special_num(exp[i]) != 0.0) {
			if (create_const(list, elem, special_num(exp[i]))) {
				free_both(list, tmp);
				return NULL;
			}
		}

		else if (exp[i] == 'x') {
			if (create_monomial(list, elem)) {
				free_both(list, tmp);
				return NULL;
			}
		}

		else if (exp[i] == '(') {
			bracket = 1;
			i++;

			for (size_t j = 0; bracket; j++) {
				tmp[j] = exp[i];

				if (exp[i] == '(')
					bracket++;
				else if (exp[i] == ')')
					bracket--;
				
				i++;
			}

			n = get_tree(tmp);
			if (!n) {
				free_both(list, tmp);
				return NULL;
			}

			list[elem] = n;

			ft_bzero(tmp, len + 1);
			i++;

			continue;
		}

		else {
			bad_char("Bad code allowed bad char", exp[i]);
			free_both(list, tmp);
			return NULL;
		}

		i += 2;
		elem++;
	}

	free(tmp);
	elem = 0;

	while (list[elem])
		elem++;

	if (!elem) {
		error("Found empty expression");
		free_node_arr(list, free_node);
		return NULL;
	}

	i = 0;
	while (list[i]) {
		if (list[i]->type == NEG || list[i]->type == SOM) {
			list[i]->right = list[i+1];
			for (size_t j = i + 2; list[j]; j++)
				list[j - 1] = list[j];
		}
		i++;
	}

	if (i % 2 == 0) {
		error("Final element count turned out even, something is wrong with the expression");
		free_node_arr(list, free_node);
		return NULL;
	}

	for (size_t j = 0; j + 1 < i; j += 2) {
		if (!(isnum(list[j]) && !isnum(list[j + 1]))) {
			free_node_arr(list, free_node);
			error("Bad expression, found 2 numbers/x/X/operations in a row");
			return NULL;
		}
	}

	if (!isnum(list[i - 1])) {
		free_node_arr(list, free_node);
		char c = node_type(list[i - 1]);
		printf("Error: Bad expression, expected number or x/X for last element, found: %c\n", c);
		return NULL;
	}
	
	node* res = compress(list);
	free(list);
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
		if (list[i]->type == MULT || list[i]->type == DIV) {
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
		if (list[i]->type == BIG_MULT) {
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
		if (list[i]->type == EXP) {
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
