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

enum expr op_type(char c) {
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


node*   get_tree(char* exp) {
	size_t len = ft_strlen(exp);

	if (!len) {
		error("Empty expression found");
		return NULL;
	}

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

			elem++;

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
			i += 2;

			for (size_t j = 0; bracket; j++) {
				tmp[j] = exp[i];

				if (exp[i] == '(')
					bracket++;
				else if (exp[i] == ')')
					bracket--;
				
				i++;
			}

			tmp[ft_strlen(tmp) - 1] = 0; 

			n = get_tree(tmp);
			if (!n) {
				free_both(list, tmp);
				return NULL;
			}

			list[elem] = n;

			ft_bzero(tmp, len + 1);
			i++;
			elem++;

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

/* 	for (int j = 0; list[j]; j++) {
		printf("%c ", node_type(list[j]));
	}
	printf("\n"); */

	node* res = compress(list);
	//printf("\n");
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

	int i = len - 1;
	node* n = NULL;

	while (i > 0) {
		//printf("%i+\n", i);
		if (list[i]->type == SUM || list[i]->type == SUB) {
			n = list[i];
			if (n->right) {
				i--;
				continue;
			}
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i--;
	}

	i = len - 2;
	while (i > 0) {
		//printf("%i*\n", i);
		if (list[i]->type == MULT || list[i]->type == DIV) {
			n = list[i];
			if (n->right) {
				i--;
				continue;
			}
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i--;
	}

	i = len - 2;
	while (i > 0) {
		//printf("%iX\n", i);
		if (list[i]->type == BIG_MULT) {
			n = list[i];
			if (n->right) {
				i--;
				continue;
			}
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i--;
	}

	i = len - 2;
	while (i >= 0) {
		//printf("%i_\n", i);
		if (list[i]->type == NEG || list[i]->type == SOM) {
			n = list[i];
			if (n->right) {
				i--;
				continue;
			}
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->right = compress(list + i + 1);
			return n;
		}
		i--;
	}

	i = len - 2;
	while (i > 0) {
		//printf("%i^\n", i);
		if (list[i]->type == EXP) {
			n = list[i];
			if (n->right) {
				i--;
				continue;
			}
			list[i] = NULL;
			//printf("%c\n", node_type(n));
			n->left = compress(list);
			n->right = compress(list + i + 1);
			return n;
		}
		i--;
	}

	n = *list;
	*list = NULL;
	//printf("%c\n", node_type(n));
	return n;
}

static pol* show_step(pol* l, pol* r, char op, pol *(*func)(pol *, pol *)) {
	printf("Calculating: (");
	show_pol(l);
	printf(")");
	printf(" %c ", op);
	printf("(");
	show_pol(r);
	printf(")\n");
	pol* res = func(l, r);
	if (res) {
		show_pol(res);
		printf("\n");
		printf("\n");
	}

	return res;
}

static pol* show_div(pol* l, pol* r) {
	pol* res = NULL;

	printf("Calculating: (");
	show_pol(l);
	printf(")");
	printf(" / ");
	printf("(");
	show_pol(r);
	printf(")");
	if (r->deg) {
		printf("\n");
		error("Division by non constant detected, not implemented, it is: ");
		show_pol(r);
	}
	
	else if (r->poly[0] == 0.0) {
		printf("\n");
		error("Division by 0 detected");
	}

	else {
		r->poly[0] = 1. / r->poly[0];
		res = pol_mul(l, r);
	}
	printf("\n");
	if (res) {
		show_pol(res);
		printf("\n");
		printf("\n");
	}
	return res;
}

pol*    expand(node* tree, int show) {
	if (!tree)
		return NULL;

	pol* res = NULL;
	if (tree->type == POL) {
		res = pol_copy(tree->p);
		return res;
	}

	pol* r = expand(tree->right, show);
	if (!r)
		return NULL;

	if (tree->type == NEG) {
		printf("Calculating: -(");
		show_pol(r);
		printf(")\n");
		res = pol_neg(r);
		if (res) {
			show_pol(res);
			printf("\n");
			printf("\n");
		}
		return res;
	}

	if (tree->type == SOM) {
		res = pol_copy(r);
		free_pol(r);
		return res;
	}

	pol* l = expand(tree->left, show);
	if (!l){
		free_pol(r);
		return NULL;
	}

	switch (tree->type)
	{
		case SUM:
			if (show)
				res = show_step(l, r, '+', pol_sum);
			else
				res = pol_sum(l, r);
			break;

		case SUB:
			if (show)
				res = show_step(l, r, '-', pol_sub);
			else
				res = pol_sub(l, r);
			break;

		case MULT:
			if (show)
				res = show_step(l, r, '*', pol_mul);
			else
				res = pol_mul(l, r);
			break;

		case BIG_MULT:
			if (show)
				res = show_step(l, r, '*', pol_mul);
			else
				res = pol_mul(l, r);

			break;
		case DIV:
			if (show)
				res = show_div(l, r);
			else {
				if (r->deg) {
					printf("\n");
					error("Division by non constant detected, not implemented, it is: ");
					show_pol(r);
				}
				
				else if (r->poly[0] == 0.0) {
					printf("\n");
					error("Division by 0 detected");
				}

				else {
					r->poly[0] = 1. / r->poly[0];
					res = pol_mul(l, r);
				}
			}
			break;

		case EXP:
			if (show)
				res = show_step(l, r, '^', pol_exp);
			else
				res = pol_exp(l, r);
			break;

		default:
			error("Bad code had bad node type");
	}

	free_pol(l);
	free_pol(r);

	return (res);
}
