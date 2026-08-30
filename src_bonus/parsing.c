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
	if (!isdigit(input[*i + 1])) {
		free(buf->str);
		error("I am NOT accepting `.' as a shorthand for 0.0, and I shouldn't accept 0. or .0 either");
	}

	return append_num(input, i, buf);
}

char* parse(char* input) {
	t_str buf;
	size_t bracket = 0;
	int last_op = 1;
	int last_unary = 0;

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

			last_op = 0;
			last_unary = 0;
		} 

		else if (input[i] == '.') {
			if (append_point(input, &i, &buf))
				return NULL;

			last_op = 0;
			last_unary = 0;
		}
		
		else if (isop(input[i]) || input[i] == '(') {
			if (add_to_str(&i, &buf, input)) 
				return NULL;

			if (input[i - 1] == '(')
				bracket++;
			last_op = 1;
			last_unary = 0;
		} 

		else if (isvar(input[i]) || isspecialnum(input[i])) {
			if (isvar(input[i]) && add_char(&buf, 'x')) 
				return NULL;

			if (isspecialnum(input[i]) && add_char(&buf, input[i])) 
				return NULL;
			
			i++;
			last_op = 0;

			while (isspace(input[i]))
				i++;
			
			if (accepts_implied(input[i])) {
				if (add_char(&buf, ' '))
					return NULL;

				if (add_char(&buf, 'X')) 
					return NULL;
			}

			last_unary = 0;
		}

		else if (isespop(input[i])) {
			if (last_op) {
				if (last_unary) {
					bad_char("Multiple unary operators in a row, unexpected sign", input[i]);
					free(buf.str);
					return NULL;
				}
				input[i] = (input[i] == '+'? '|': '_');
				last_unary = 1;
			}

			if (add_to_str(&i, &buf, input)) 
				return NULL;
			
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
			last_unary = 0;
		} 

		else if (input[i] == '=') {
			if (add_to_str(&i, &buf, input)) 
				return NULL;
			
			if (bracket) {
				error("A bracket was not closed");
				free(buf.str);
				return (NULL);
			}
			last_unary = 0;
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