#include "computorv1.h"

pol* get_equal_zero(char* string) {
    size_t i = 0;
    size_t len = ft_strlen(string);
    char* l = NULL;
    char* r = NULL;

    while (i < len) {
        if (*(string + i) == '=') {
            if (!i || *(string  + i - 1) != ' ') {
                ft_putstr_fd("Invalid left hand side", 2);
                return NULL;
            }
            *(string  + i - 1) = 0;
            if (i + 1 == len || *(string  + i + 1) != ' ') {
                ft_putstr_fd("Invalid left hand side", 2);
                return NULL;
            }
            l = string;
            r = string + i + 2;
            break;
        }
        i++;
    } 
    if (!l || !r) {
        ft_putstr_fd("NO = sign given, not an equation", 2);
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

    pol* left_full = expand(left);
    free(left);
    pol* right_full = expand(right);
    free(right);
    if (!right_full) {
        return NULL;
    }

    return sub_pol(left_full, right_full);
}