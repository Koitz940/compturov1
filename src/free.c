#include "computorv1.h"

void free_node(node* tree) {
    if (tree->left) {
        free_node(tree->left);
    }
    if (tree->right) {
        free_node(tree->right);
    }
    free(tree);
}

void free_pol(pol* p) {
    free(p->poly);
    free(p);
}