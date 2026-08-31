#include "computorv1.h"

pol* get_equal_zero(char* string) {
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
            string[i - 1] = 0;
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
        error("NO = sign given, not an equation");
        return NULL;
    }

    node* left = get_tree(l);
    if (!left) {
        return NULL;
    }
    node* right = get_tree(r);
    if (!right) {
        free_node(left);
        return NULL;
    }

    pol* left_full = expand(left);
	if (!left_full) {
		free_node(left);
		free_node(right);
		return NULL;
	}
    pol* right_full = expand(right);
	if (!right_full) {
		free_node(left);
		free_node(right);
		free_pol(left_full);
		return NULL;
	}
	free_node(left);
    free_node(right);

    return pol_sub_free(left_full, right_full);
}