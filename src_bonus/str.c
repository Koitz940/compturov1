#include "computorv1_bonus.h"

int	add_to_str(size_t *i, t_str *str, char* raw)
{
	if (extend(str))
		return (FAILURE);
	str->str[str->len++] = raw[*i];
	(*i)++;
	return (SUCCESS);
}

int	extend(t_str *str)
{
	char	*new;

	if (str->capacity != str->len)
		return (SUCCESS);
	if (str->capacity < (ULONG_MAX - 1) / 2)
	{
		new = ft_calloc(sizeof(char), str->capacity * 2 + 1);
		str->capacity *= 2;
	}
	else
	{
		if (str->capacity == ULONG_MAX - 1) {
			free(str->str);
			error("Out of memory");
			return FAILURE;
		}
		new = ft_calloc(sizeof(char), str->capacity + 2);
		str->capacity += 1;
	}
	if (!new) {
		free(str->str);
		error("Memory allocation failed");
		return FAILURE;
	}
	ft_memcpy(new, str->str, str->len);
	free(str->str);
	str->str = new;
	return (SUCCESS);
}
