#ifndef COMPUTORV_H
# define COMPUTORV_H

# include <stdio.h>
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <errno.h>
# include <inttypes.h>
# include <stddef.h>
# include <stdint.h>

# define DELTA = (int)(-12652)

enum expr {
    POL,
    SUM,
	SUB,
    MULT,
};

typedef struct polynomial {
    size_t deg;
    size_t min_deg;
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
node*	get_tree(char* exp);
pol*    expand(node* tree);
node*	compress(node** list);

//free me from this hell that I put mysef on, actually tho why am I here
void    free_node(node* tree);
void    free_pol(pol* p);
void	free_split(char** s);
void    free_node_arr(node** arr, void (*del)(node *));

//Polynomial operations
pol*    pol_sum(pol* p, pol* g);
pol*    pol_sub(pol* p, pol* g);
pol*    pol_neg(pol* p);
pol*    pol_mul(pol* p, pol* g);

pol*    pol_sum_free(pol* p, pol* g);
pol*    pol_sub_free(pol* p, pol* g);
pol*    pol_neg_free(pol* p);
pol*    pol_mul_free(pol* p, pol* g);

pol*    monomial(size_t deg, double coef);
pol*	pol_copy(pol* p);

//show results
void    show_results(pol* p);
void    show_pol(pol* p);
void    print_solution(double sol, int symbol);

//reading equation
int		get_num(char* str, double* num);
int		get_exp(char* str, size_t* num);
size_t	strtosize(const char *nptr, char **endptr);
int		create_num(char* str, node** partial, size_t i);
int		create_mul(size_t len, node** partial, size_t i, char* str);
int		create_sum(size_t len, node** partial, size_t i, char* str);
int		create_sub(size_t len, node** partial, size_t i, char* str);
int		create_monomial(char* str, node** partial, size_t i);

//error
void    error(char* reason);
void	bad_char(char* reason, char c);

//Binary trees
node*	copy_node(node* n);
char	node_type(node* n);

#endif