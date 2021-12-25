#include <stdlib.h>
#include <stdio.h>

typedef struct s_letter
{
	char			c;
	struct s_letter	*next;
}	t_letter;

typedef struct s_rule
{
	char			pair[3];
	char			conversion;
	struct s_rule	*next;
}	t_rule;

t_letter	*create_letter(char c);
void		create_template(char *line, t_letter **template);
void		print_list(t_letter **template);
void		add_rule(char *line, t_rule **rules);
t_rule		*create_rule(char *line);
void	print_rules(t_rule **rules);
void	apply_rules(t_letter **template, t_rule **rules);
void	count_letters(t_letter **template);

int	main(void)
{
	FILE		*f;
	char		*line;
	t_letter	**template;
	t_rule		**rules;
	size_t		i;

	i = 0;
	template = malloc(sizeof(t_letter *));
	template[0] = 0;
	rules = malloc(sizeof(t_rule *));
	rules[0] = 0;
	line = malloc(sizeof(char) * 50);
	f = fopen("ex", "r");
	fscanf(f, "%s\n", line);
	create_template(line, template);
	print_list(template);
	fscanf(f, "\n");
	while (fscanf(f, "%100[^\n]\n", line) != -1)
	{
		add_rule(line, rules);
	//	printf("%s\n", line);
	}
	print_rules(rules);
	while (i < 30)
	{
		apply_rules(template, rules);
		i++;
	}
//	print_list(template);
	count_letters(template);
	fclose(f);
}

void	count_letters(t_letter **template)
{
	char		c;
	t_letter	*aux;
	long long	count;

	count = 0;
	aux = *template;
	c = 'A';
	while (c <= 'Z')
	{
		count = 0;
		aux = *template;
		while (aux)
		{
			if (aux->c == c)
				count++;
			aux = aux->next;
		}
		printf("%c: %lld\n", c, count);
		c++;
	}
}

void	apply_rules(t_letter **template, t_rule **rules)
{
	t_rule		*aux;
	t_letter	*first;
	t_letter	*second;

	first = *template;
	second = first->next;
	while (second)
	{
		aux = *rules;
		while (aux)
		{
	//		printf("checking %c %c\n", first->c, second->c);
			if (first->c == aux->pair[0] && second->c == aux->pair[1])
			{
				first->next = create_letter(aux->conversion);
				first->next->next = second;
			//	print_list(template);
//				first = second;
//				second = second->next;
				break ;
			}
			aux = aux->next;
		}

		first = second;
		second = second->next;
	}
}

void	print_rules(t_rule **rules)
{
	t_rule	*aux;

	aux = *rules;
	while (aux)
	{
		printf("%s -> %c\n", aux->pair, aux->conversion);
		aux = aux->next;
	}
}

void	print_list(t_letter **template)
{
	t_letter *aux;

	aux = *template;
	while (aux)
	{
		printf("%c", aux->c);
		aux = aux->next;
	}
	printf("\n");
}

void	add_rule(char *line, t_rule **rules)
{
	t_rule	*aux;

	aux = *rules;
	if (!aux)
		*rules = create_rule(line);
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = create_rule(line);
	}
}

t_rule	*create_rule(char *line)
{
	t_rule	*new;

	new = malloc(sizeof(t_rule));
//	printf("%s\n", line);
	new->pair[0] = line[0];
	new->pair[1] = line[1];
	new->conversion = line[6];
	new->next = 0;
	return (new);
}

void	create_template(char *line, t_letter **template)
{
	t_letter *aux;

	*template = create_letter(*line);
	aux = *template;
	line++;
	while (line && *line)
	{
		aux->next = create_letter(*line);
		aux = aux->next;
		line++;
	}
}

t_letter	*create_letter(char c)
{
	t_letter	*new;

	new = malloc(sizeof(t_letter));
	new->c = c;
	new->next = 0;
	return (new);
}
