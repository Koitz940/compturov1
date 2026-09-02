#include "computorv1_bonus.h"

static int is_flag(char* str) {
	//printf("%i %i\n", ft_strlen(str) == 2, ft_strncmp(str, "-s", 2));
	return ft_strlen(str) == 2 && ft_strncmp(str, "-s", 2) == 0;
}

static int one_arg(char* arg, char** buf, int* flag) {
	if (is_flag(arg)) {
		*buf = get_next_line(0);
		if (!*buf) {
			error("Reading stding failed");
			return FAILURE;
		}

		char* c = *buf + ft_strlen(*buf) - 1;
		if (*c == '\n') 
			*c = 0;

		*flag = 0;
	} else {
		*buf = ft_strdup(arg);
		if (!*buf) {
			error("Failed memory allocation");
			return FAILURE;
		}
	}

	return SUCCESS;
}

static int two_arg(char* arg1, char* arg2, char** buf, int* flag) {
	*flag = 1;
	if (!is_flag(arg1)) {
		if (!is_flag(arg2)) {
			error("Too many input expressions");
            return FAILURE;
		}

		*buf = ft_strdup(arg1);
		if (!*buf) {
			error("Failed memory allocation");
			return FAILURE;
		}

		return SUCCESS;
	}

	*buf = ft_strdup(arg2);
	if (!*buf) {
		error("Failed memory allocation");
		return FAILURE;
	}

	return SUCCESS;
}


int main(int argc, char** argv) {
    char* expression = NULL;
    pol* expanded = NULL;
	char* final = NULL;
	int steps = 0;

    switch (argc)
    {
        case 1:
            expression = get_next_line(0);
			if (!expression) {
				error("Reading stding failed");
				return FAILURE;
			}
			char* c = expression + ft_strlen(expression) - 1;
			if (*c == '\n') 
				*c = 0;
            break;

        case 2:
            if (one_arg(argv[1], &expression, &steps))
				return FAILURE;
            break;

        case 3:
            if (two_arg(argv[1], argv[2], &expression, &steps))
				return FAILURE;
			break;

		default:
			error("Too many input arguments");
            return FAILURE;
    }

	final = parse(expression);
	free(expression);
	if (!final)
		return FAILURE;
	//printf("%s\n", final);
	int status = 0;
    expanded = get_equal_zero(final, &status, steps);
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