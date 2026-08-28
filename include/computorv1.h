#ifndef COMPUTORV_H
# define COMPUTORV_H

# include <stdio.h>
# include "libft.h"
# include <math.h>

enum expr {
    POL,
    SUM,
	SUB,
    MULT,
};

typedef struct polynomial {
    size_t deg;
    double* poly;
}   pol;

typedef struct node {
    enum expr type;
	pol* p;
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
void	free_split(char** s);

//Polynomial operations
pol*    pol_sum(pol* p, pol* g);
pol*    pol_sub(pol* p, pol* g);
pol*    pol_neg(pol* p);
pol*    pol_mul(pol* p, pol* g);

pol*    pol_sum_free(pol* p, pol* g);
pol*    pol_sub_free(pol* p, pol* g);
pol*    pol_neg_free(pol* p);
pol*    pol_mul_free(pol* p, pol* g);

pol*    monomial(size_t deg);
pol*	pol_copy(pol* p);

//show results
void    show_results(pol* p);
void    show_pol(pol* p);

#endif