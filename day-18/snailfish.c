#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_num
{
	int				type;
	int				num;
	struct s_pair	*p;
}	t_num;

typedef struct s_pair
{
	struct	s_pair *parent;
	struct	s_pair *next;
	struct	s_num *left;
	struct	s_num *right;
}	t_pair;

t_pair	*new_pair(void);
t_pair	*parse_snailfish_num(char **str);
void	print_pair(t_pair *p);
t_pair	*sum_snailfish_num(t_pair *p1, t_pair *p2);
void	deepest_pair(t_pair *p, int i, int *deep, t_pair **deepest);
void	explode(t_pair *p);
void	split(t_pair *p, t_pair *head);
int	main(void)
{
	t_pair	*p;
	t_pair	*p2;
	t_pair	*sum;
	char	*str1;
	char	*str2;
	FILE	*f;

	str1 = malloc(sizeof(char) * 300);
	str2 = malloc(sizeof(char) * 300);
	
	f = fopen("ex2", "r");
	fscanf(f, "%300[^\n]\n", str1);
	p = parse_snailfish_num(&str1);
	while(fscanf(f, "%300[^\n]\n", str2) != -1)
	{
		p2 = parse_snailfish_num(&str2);
		sum = sum_snailfish_num(p, p2);
		explode(sum);
		split(sum, sum);
	//	printf("\n\n");
		p = sum;
	}
	print_pair(sum);
	printf("\n");
	fclose(f);
}

void	split(t_pair *p, t_pair *head)
{
	int	type_zero;

	type_zero = 0;
	if (p && p->left && p->left->type == 0)
	{
		if (p->left->num > 9)
		{
			p->left->type = 1;
			p->left->p = new_pair();
			p->left->p->left->type = 0;
			p->left->p->right->type = 0;
			p->left->p->left->num = p->left->num / 2;
			p->left->p->right->num = p->left->num - p->left->p->left->num;
			p->left->p->parent = p;
		//	printf("reduce-> ");
		//	print_pair(head);
		//	printf("\n");
			explode(head);
			split(head, head);
		}
	}
	else if (p && p->left)
		split(p->left->p, head);
	if (p && p->right && p->right->type == 0)
	{
		if (p->right->num > 9)
		{
			p->right->type = 1;
			p->right->p = new_pair();
			p->right->p->left->type = 0;
			p->right->p->right->type = 0;
			p->right->p->left->num = p->right->num / 2;
			p->right->p->right->num = p->right->num - p->right->p->left->num;
			p->right->p->parent = p;
		//	printf("reduce-> ");
		//	print_pair(head);
		//	printf("\n");
			explode(head);
			split(head, head);
		}
	}
	else if (p && p->right)
		split(p->right->p, head);
}

void	explode(t_pair *p)
{
	int		i;
	t_pair	**deepest;
	t_pair	*aux;
	t_pair	*aux2;
	int		deep;

	i = 0;
	deep = 0;
	deepest = malloc(sizeof(t_pair *));
	deepest[0] = 0;
	deepest_pair(p, 1, &deep, deepest);
	while (deep >= 5)
	{
		aux = (*deepest)->parent;
		aux2 = (*deepest);
		while (aux->left->p == aux2 && aux->parent)
		{
			aux = aux->parent;
			aux2 = aux2->parent;
		}
		if (aux->left->p != aux2)
		{
			if (aux->left->type == 0)
				aux->left->num += (*deepest)->left->num;
			else
			{
				aux = aux->left->p;
				while (aux->right->type == 1)
					aux = aux->right->p;
				aux->right->num += (*deepest)->left->num;
			}
		}

		aux = (*deepest)->parent;
		aux2 = (*deepest);
		while (aux->right->p == aux2 && aux->parent)
		{
			aux = aux->parent;
			aux2 = aux2->parent;
		}
		if (aux->right->p != aux2)
		{
			if (aux->right->type == 0)
				aux->right->num += (*deepest)->right->num;
			else
			{
				aux = aux->right->p;
				while (aux->left->type == 1)
					aux = aux->left->p;
				aux->left->num += (*deepest)->right->num;
			}
		}
		aux = (*deepest)->parent;
		if (aux->left->p == (*deepest))
		{
			aux->left->type = 0;
			aux->left->num = 0;
		}
		else if (aux->right->p == (*deepest))
		{
			aux->right->type = 0;
			aux->right->num = 0;
		}
	//	printf("explode->");
	//	print_pair(p);
		*deepest = 0;
		deep = 0;
		deepest_pair(p, 1, &deep, deepest);
	//	printf("deepest pair %i\n", deep);
	//	print_pair(*deepest);
	//	printf("\n");
	}
}
	
void	deepest_pair(t_pair *p, int i, int *deep, t_pair **deepest)
{
	int	type_zero;

	type_zero = 0;
	if (p && p->left && p->left->type == 0)
		type_zero++;
	else if (p && p->left)
		deepest_pair(p->left->p, i + 1, deep, deepest);
	if (p && p->right && p->right->type == 0)
		type_zero++;
	else if (p && p->right)
		deepest_pair(p->right->p, i + 1, deep, deepest);
	if (type_zero == 2 && i > (*deep))
	{
		*deep = i;
		*deepest = p;
	}
}

t_pair	*sum_snailfish_num(t_pair *p1, t_pair *p2)
{
	t_pair *new;
	
	new = new_pair();
	new->left->type = 1;
	new->left->p = p1;
	new->left->p->parent = new;
	new->right->type = 1;
	new->right->p = p2;
	new->right->p->parent = new;
	return (new);
}

void	print_pair(t_pair *p)
{
	if (p && p->left && p->left->type == 0)
		printf("left: %i, ", p->left->num);
	else if (p && p->left)
		print_pair(p->left->p);
	if (p && p->right && p->right->type == 0)
		printf("right: %i ", p->right->num);
	else if (p && p->right)
		print_pair(p->right->p);
//	printf("\n");
}

t_pair *parse_snailfish_num(char **str)
{
	t_pair	*p;

	p = 0;
//	printf("->%s\n", *str);
	if (*str && **str == '[')
	{
		p = new_pair();
		(*str)++;
		if (isdigit((**str)))
		{
			p->left->type = 0;
			p->left->num = atoi(*str);
			while (isdigit((**str)))
				(*str)++;
		}
		else
		{
			p->left->type = 1;
			p->left->p = parse_snailfish_num(str);
			p->left->p->parent = p;
			*str += strchr(*str, ']') - *str + 1;
		}
		if ((**str) == ',')
			(*str)++;
		if (*str && isdigit((**str)))
		{	
			p->right->type = 0;
			p->right->num = atoi(*str);
			while (isdigit((**str)))
				(*str)++;
		}
		else
		{
			p->right->type = 1;
			p->right->p = parse_snailfish_num(str);
			p->right->p->parent = p;
			*str += strchr(*str, ']') - *str + 1;
		}
	}
	return (p);
}

t_pair	*new_pair(void)
{
	t_pair	*new;
	t_num	*left;
	t_num	*right;

	new = malloc(sizeof(t_pair));
	left = malloc(sizeof(t_num));
	right = malloc(sizeof(t_num));
	new->next = 0;
	new->parent = 0;
	left->type = -1;
	right->type = -1;
	new->left = left;
	new->right = right;
	return (new);
}
