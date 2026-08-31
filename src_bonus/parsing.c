#include "computorv1_bonus.h"

int add_char(t_str* str, char c) {
	if (extend(str))
		return FAILURE;
	str->str[str->len++] = c;
	return SUCCESS;
}

int isbracket(char c) {
	return c == '(' || c == ')';
}

int isop(char c) {
	return c == '*' || c == '/' || c == '^';
}

int isespop(char c) {
	return c == '+' || c == '-';
}

int isvar(char c) {
	return c == 'x' || c == 'X';
} 

int isvalid(char c) {
	return isop(c) || isespop(c) || isvar(c) || c == '=' || isbracket(c) || isvalidnum(c) || isspecialnum(c);
}

int isvalidnum(char c) {
	return ft_isdigit(c) || c == '.';
}

int isspecialnum(char c) {
	return c == 'e' || c == 'p';
}

int accepts_implied(char c) {
	return c == '(' || isvar(c) || isspecialnum(c);
}

int append_num(char* input, size_t* i, t_str* buf) {
	int saw_dot = 0;

	while (input[*i] && isvalidnum(input[*i])) {
		if (input[*i] == '.') {
			if (saw_dot) {
				error("Bad number, found decimal number with 2 decimal points");
				free(buf->str);
				return FAILURE;
			}
			saw_dot = 1;
		}
		if (add_to_str(i, buf, input)) {
			return FAILURE;
		}
	}

	while (isspace(input[*i]))
			(*i)++;

	if (accepts_implied(input[*i])) {
		if (add_char(buf, ' '))
			return FAILURE;

		if (add_char(buf, 'X')) 
			return FAILURE;
	}

	return SUCCESS;
}

int append_point(char* input, size_t* i, t_str* buf) {
	add_char(buf, '0');
	if (!isdigit(input[*i + 1])) {
		free(buf->str);
		error("I am NOT accepting `.' as a shorthand for 0.0, and I shouldn't accept 0. or .0 either");
		return FAILURE;
	}

	return append_num(input, i, buf);
}

char* parse(char* input) {
	t_str buf;
	size_t bracket = 0;
	int next_unary = 1;
	int last_op = 1;

	buf.str = calloc(1000, sizeof(char));
	buf.capacity = 1000;
	buf.len = 0;
	if (!buf.str) {
		error("Memory allocation failed");
		return NULL;
	}

	size_t i = 0;
	while (isspace(input[i]))
		i++;
	while (input[i]) {
		if (ft_isdigit(input[i])) {
			if (append_num(input, &i, &buf))
				return NULL;

			next_unary = 0;
			last_op = 0;

		} 

		else if (input[i] == '.') {
			if (append_point(input, &i, &buf))
				return NULL;

			next_unary = 0;
			last_op = 0;
		}
		
		else if (isop(input[i])) {
			if (last_op) {
				bad_char("Unexpected operator", input[i]);
				free(buf.str);
				return NULL;
			}

			if (add_to_str(&i, &buf, input)) 
				return NULL;

			while (isspace(input[i]))
				i++;

			if (!input[i] || input[i] == '=' || input[i] == ')') {
				bad_char("expression ends on operator, delimiter is", input[i]);
				free(buf.str);
				return NULL;
			}

			next_unary = 0;
			last_op = 1;
		}

		else if (input[i] == '(') {

			if (add_to_str(&i, &buf, input)) 
				return NULL;

			bracket++;

			while (isspace(input[i]))
				i++;

			if (!input[i] || input[i] == '=') {
				bad_char("expression ends on bracket, delimiter is", input[i]);
				free(buf.str);
				return NULL;
			}

			next_unary = 1;
			last_op = 1;
		} 

		else if (isvar(input[i]) || isspecialnum(input[i])) {
			if (isvar(input[i]) && add_char(&buf, 'x')) 
				return NULL;

			if (isspecialnum(input[i]) && add_char(&buf, input[i])) 
				return NULL;
			
			i++;
			next_unary = 0;

			while (isspace(input[i]))
				i++;
			
			if (accepts_implied(input[i])) {
				if (add_char(&buf, ' '))
					return NULL;

				if (add_char(&buf, 'X')) 
					return NULL;
			}

			last_op = 0;
		}

		else if (isespop(input[i])) {
			if (next_unary) {
				input[i] = (input[i] == '+'? '|': '_');

				if (input[i] != '|') {
					if (add_to_str(&i, &buf, input)) 
					return NULL;
				} else {
					i++;
					while (isspace(input[i]))
						i++;
					if (!input[i] || input[i] == '=' || input[i] == ')') {
						bad_char("expression ends on unary + or -, delimiter is", input[i]);
						free(buf.str);
						return NULL;
					}
					continue;
				}
				
				while (isspace(input[i]))
					i++;

			}

			else {
				if (last_op) {
					bad_char("Unexpected operator", input[i]);
					free(buf.str);
					return NULL;
				}

				if (add_to_str(&i, &buf, input)) 
					return NULL;
			}
			
			next_unary = 0;
			last_op = 1;
		} 

		else if (input[i] == ')') {
			if (add_to_str(&i, &buf, input)) 
				return NULL;

			if (!bracket) {
				bad_char("Unexpected token", ')');
				free(buf.str);
				return NULL;
			}

			bracket--;

			while (isspace(input[i]))
				i++;
			
			if (accepts_implied(input[i])) {
				if (add_char(&buf, ' '))
					return NULL;

				if (add_char(&buf, 'X')) 
					return NULL;
			}
			next_unary = 0;
			last_op = 0;
		} 

		else if (input[i] == '=') {
			if (add_to_str(&i, &buf, input)) 
				return NULL;
			
			if (bracket) {
				error("A bracket was not closed");
				free(buf.str);
				return (NULL);
			}
			next_unary = 1;
			last_op = 1;
		}

		else {
			bad_char("Invalid character", input[i]);
			free(buf.str);
			return NULL;
		}

		if (add_char(&buf, ' '))
			return NULL;

		while (isspace(input[i]))
			i++;
	}

	if (bracket) {
		error("A bracket was not closed");
		free(buf.str);
		return (NULL);
	}
	return buf.str;
}