#include "computorv1.h"

void free_node(node* tree) {
	if (!tree)
		return;
    if (tree->left) {
        free_node(tree->left);
    }
    if (tree->right) {
        free_node(tree->right);
    }
    free(tree);
}

void free_pol(pol* p) {
	if (!p)
		return;
    free(p->poly);
    free(p);
}

void free_split(char** s) {
	while (*s) {
		free(*s);
        s++;
	}
	free(s);
}

void free_arr_fun(void** arr, void (*del)(void *)) {
    while (*arr) {
		del(*arr);
        arr++;
	}
	free(arr);
}