#include "computorv1_bonus.h"

void free_node(node* tree) {
	if (!tree)
		return;
    if (tree->left) {
        free_node(tree->left);
    }
    if (tree->right) {
        free_node(tree->right);
    }
	if (tree->p) {
		free_pol(tree->p);
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
	size_t i = 0;
	while (s[i]) {
		free(s[i]);
        i++;
	}
	free(s);
}

void free_node_arr(node** arr, void (*del)(node *)) {
	size_t i = 0;
    while (arr[i]) {
		del(arr[i]);
        i++;
	}
	free(arr);
}