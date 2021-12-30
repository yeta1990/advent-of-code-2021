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
int		deepest_pair(t_pair *p, int i, t_pair **deepest);
void	explode(t_pair *p);

int	main(void)
{
	t_pair	*p;
	t_pair	*p2;
	t_pair	*sum;

//	char	*str = "[1,2]";
//	char	*str = "[[1,2],3]";
//	char	*str = "[2,[8,8]]";
//	char	*str = "[8,[7,[1,0]]]";
//	char	*str = "[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]";
//	char	*str = "[[[1,3],[5,3]],1]";
//	char	*str = "[[1,3],[5,3]]";
//	char	*str = "[7,[8,[7,[1,0]]]]";
//	char	*str = "[[8,[7,[1,0]]],7]";
//	char	*str = "[[[[4,3],4],4],[7,[[8,4],9]]]";
//	char	*str = "[[[[[9,8],1],2],3],4]";
//	char	*str = "[7,[6,[5,[4,[3,2]]]]]";
//	char	*str = "[[6,[5,[4,[3,2]]]],1]";
	char	*str = "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]";
//	char	*str = "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]";
	char	*str2 = "[1,1]";
	p = parse_snailfish_num(&str);
	p2 = parse_snailfish_num(&str2);
//	print_pair(p);
	sum = sum_snailfish_num(p, p2);
//	print_pair(sum);
	explode(p);
	print_pair(p);

}


void	explode(t_pair *p)
{
	int		i;
	t_pair	**deepest;
	t_pair	*aux;
	t_pair	*aux2;

	i = 0;
	deepest = malloc(sizeof(t_pair *));
	deepest[0] = 0;
	i = deepest_pair(p, 1, deepest);
	printf("deepest pair %i\n", i);
//	print_pair((*deepest));
	if (i >= 4)
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
	}
}

int	deepest_pair(t_pair *p, int i, t_pair **deepest)
{
	int	type_zero;

	type_zero = 0;
	if (p && p->left && p->left->type == 0)
		type_zero++;
//		printf("left: %i, ", p->left->num);
	else if (p && p->left)
		return deepest_pair(p->left->p, i + 1, deepest);
	if (p && p->right && p->right->type == 0)
		type_zero++;
//		printf("right: %i ", p->right->num);
	else if (p && p->right)
		return deepest_pair(p->right->p, i + 1, deepest);
	if (type_zero == 2)
	{
		*deepest = p;
		return (i);
	}
	return (-1);
//	printf("\n");
}

t_pair	*sum_snailfish_num(t_pair *p1, t_pair *p2)
{
	t_pair *new;
	
	new = new_pair();
	new->left->type = 1;
	new->left->p = p1;
	new->right->type = 1;
	new->right->p = p2;
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
