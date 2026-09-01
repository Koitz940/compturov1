#ifndef COMPUTORV_BONUS_H
# define COMPUTORV_BONUS_H

# include <stdio.h>
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <errno.h>
# include <inttypes.h>
# include <stddef.h>
# include <stdint.h>
# include <ctype.h>
# include <limits.h>

# define DELTA (int)(-12652)
# define PI 3.14159265358979323846

enum expr {
    POL,
    SUM,
	SUB,
    MULT,
	DIV,
	BIG_MULT,
	NEG,
	SOM,
	EXP,
};

enum {
	SUCCESS,
	FAILURE
};

typedef struct str {
	size_t capacity;
	size_t len;
	char* str; 
}	t_str;

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
pol* get_equal_zero(char* string, int* status);
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
pol*	pol_exp(pol* p, pol* g);

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
void 	print_tree(node* tree);

//reading equation
int		get_num(char* str, double* num);
int		get_exp(char* str, size_t* num);
size_t	strtosize(const char *nptr, char **endptr);
int		create_op(node** partial, size_t i, char op);
int		create_monomial(node** partial, size_t i);
int 	create_num(char* str, node** partial, size_t i);
int		create_const(node** partial, size_t i, double c);

//error
void    error(char* reason);
void	bad_char(char* reason, char c);

//Binary trees
node*	copy_node(node* n);
char	node_type(node* n);
enum expr op_type(char c);

//str
int	add_to_str(size_t *i, t_str *str, char* raw);
int	extend(t_str *str);
int add_char(t_str* str, char c);
int append_num(char* input, size_t* i, t_str* buf);
int append_point(char* input, size_t* i, t_str* buf);

//Parsing
char* parse(char* input);
int isespop(char c);
int isop(char c);
int isvar(char c);
int isvalid(char c);
int isvalidnum(char c);
int accepts_implied(char c);
int isspecialnum(char c);

//solving cubic polynomial adventure
void solve_cub(pol* p);

#endif