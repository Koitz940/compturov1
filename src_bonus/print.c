#include "computorv1_bonus.h"

void print_solution(double sol, int symbol) {
    printf("%c = %g", symbol, sol);
} 

void show_pol(pol* p) {
    size_t count = p->deg - p->min_deg + 1;
    int first = 1;

    for (size_t i = count - 1; i + 1 != 0; i--) {
        double coeff = p->poly[i];
        if (coeff == 0.0) 
            continue;

        size_t current_deg = p->min_deg + i;

        if (!first) {
            if (coeff > 0) {
                printf(" + ");
            } else {
                printf(" - ");
            }
        } else {
            if (coeff < 0) {
                printf("-");
            }
        }

        double abs_coeff = (coeff < 0) ? -coeff : coeff;

        if (abs_coeff != 1.0 || current_deg == 0) {
            printf("%g", abs_coeff);
        }

        if (current_deg > 0) {
            printf("x");
            if (current_deg > 1) {
                printf("^%lu", current_deg);
            }
        }

        first = 0;
    }

    if (first) {
        printf("0");
    }
}

static int priority(enum expr l) {
	switch (l) {
		case POL:
			return 0;
			break;

		case SUM:
			return 1;
			break;

		case SUB:
			return 1;
			break;

		case MULT:
			return 2;
			break;

		case DIV:
			return 2;
			break;

		case BIG_MULT:
			return 2;
			break;

		case NEG:
			return 3;
			break;

		case SOM:
			return 3;
			break;

		case EXP:
			return 4;
			break;

		default: 
			break;
	}

	return -1;
}

static int bracket_left(enum expr l, enum expr cur) {
	return priority(l) >= priority(cur); 
}

static int bracket_right(enum expr l, enum expr cur) {
	return priority(l) >= priority(cur);
}

void print_tree(node* tree) {
	char c;
	int r;
	int l;

	if (tree->type == POL) {
		show_pol(tree->p);
	}

	else if (tree->type == NEG || tree->type == SOM) {
		r = bracket_right(tree->right->type, tree->type);
		if (r) 
			printf("(");
		
		c = node_type(tree);
		printf("%c", c);
		print_tree(tree->right);

		if (r) 
			printf(")");
	}

	else {
		r = bracket_right(tree->right->type, tree->type);
		l = bracket_left(tree->left->type, tree->type);

		if (l) 
			printf("(");
		
		print_tree(tree->left);

		if (l)
			printf(")");
		

		if (r) 
			printf("(");
		
		c = node_type(tree);
		printf("%c", c);
		print_tree(tree->right);

		if (r) 
			printf(")");
	}
}