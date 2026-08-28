#include "computorv1.h"

int main(int argc, char** argv) {
    char* expression;
    pol* expanded;

    switch (argc)
    {
        case 1:
            expression = get_next_line(0);
            break;
        case 2:
            expression = ft_strdup(argv[1]);
            break;
        default:
            ft_putstr_fd("Too many input arguments\n", 2);
            return 1;;
        }
        if (!expression) {
            ft_putstr_fd("Failed memory allocation\n", 2);
            return 1;
    }

    expanded = get_equal_zero(expression);
    free(expression);
    if (!expanded)
        return 1;
    show_results(expanded);
    free(expanded);
}
