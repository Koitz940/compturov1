#include "computorv1_bonus.h"

pol* get_equal_zero(char* string, int* status, int show) {
    size_t i = 0;
    size_t len = ft_strlen(string);
    char* l = NULL;
    char* r = NULL;

    while (i < len) {
        if (string[i] == '=') {
            if (!i || string[i - 1] != ' ') {
                error("Invalid left hand side");
                return NULL;
            }
            string[i] = 0;
            if (string[i + 1] != ' ') {
                error("Invalid right hand side");
                return NULL;
            }
            l = string;
            r = string + i + 2;
            break;
        }
        i++;
    } 
    if (!l || !r) {
        printf("NO = sign given, will simply simplify the expression\n");
        node* exp = get_tree(string);
        if (!exp)
            return NULL;
        pol* p = expand(exp, show);
        free_node(exp);
        if (!p)
            return NULL;
		printf("Reduced form: ");
        show_pol(p);
        free_pol(p);
        printf("\n");
        *status = 1;
        return NULL;
    }

    node* left = get_tree(l);
    if (!left) {
        return NULL;
    }
    node* right = get_tree(r);
    if (!right) {
        free(left);
        return NULL;
    }

    pol* left_full = expand(left, show);
	if (!left_full) {
		free_node(left);
		free_node(right);
		return NULL;
	}
    pol* right_full = expand(right, show);
	if (!right_full) {
		free_node(left);
		free_node(right);
		free_pol(left_full);
		return NULL;
	}
	free_node(left);
    free_node(right);

	printf("Calculating: (");
	show_pol(right_full);
	printf(")");
	printf(" - ");
	printf("Calculating: (");
	show_pol(left_full);
	printf(")");
	printf("\n");
    return pol_sub_free(left_full, right_full);
}