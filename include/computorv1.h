#ifndef COMPUTORV_H
# define COMPUTORV_H

# include <stdio.h>
# include "libft.h"
# include <math.h>

enum expr {
    POL,
    SUM,
    MULT,
};

typedef struct polynomial {
    size_t deg;
    double* poly;
}   pol;

typedef struct node {
    enum expr type;
    struct node* left;
    struct node* right;
}   node;

//General code flow
pol*    get_equal_zero(char* string);
node*   get_tree(char* exp);
pol*    expand(node* tree);

//free me from this hell that I put mysef on, actually tho why am I here
void    free_node(node* tree);
void    free_pol(pol* p);

//Polynomial operations
pol*    pol_sum(pol* p, pol* g);
pol*    pol_sub(pol* p, pol* g);
pol*    pol_mul(pol* p, pol* g);
pol*    monomial(size_t deg);

//show results
void    show_results(pol* p);
void    show_pol(pol* p);

#endif