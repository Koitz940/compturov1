#include "computorv1_bonus.h"

int main(int argc, char** argv) {
    char* expression;
    pol* expanded;
	char* final;

    switch (argc)
    {
        case 1:
            expression = get_next_line(0);
			char* c = expression + ft_strlen(expression) - 1;
			if (*c == '\n') 
				*c = 0;
            break;
        case 2:
            expression = ft_strdup(argv[1]);
            break;
        default:
            error("Too many input arguments");
            return FAILURE;
        }
        if (!expression) {
            error("Failed memory allocation");
            return FAILURE;
    }
	if (!expression) {
		error("Memory allocation failed");
		return FAILURE;
	}

	final = parse(expression);
	free(expression);
	if (!final)
		return FAILURE;
	//printf("%s\n", final);
	int status = 0;
    expanded = get_equal_zero(final, &status);
	free(final);
	if (status) 
		return 0;
    if (!expanded)
        return FAILURE;
    show_results(expanded);
	free_pol(expanded);
}

/* int main(int argc, char** argv) {
	char* expression;
	char* final;

	switch (argc)
    {
        case 1:
            expression = get_next_line(0);
			if (!expression) {
				error("Reading stdin failed");
				return 1;
			}
			size_t n = ft_strlen(expression); 
			if (n) {
				char* c = expression + n - 1;
				if (*c == '\n') 
					*c = 0;
			}
            break;
        case 2:
            expression = ft_strdup(argv[1]);
            break;
        default:
            error("Too many input arguments");
            return FAILURE;
	}
	if (!expression) {
		error("Failed memory allocation");
		return FAILURE;
    }

	final = parse(expression);
	free(expression);
	if (!final)
		return FAILURE;
	printf("%s\n", final);
	free(final);
} */