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
t_pair	*parse_snailfish_num(char *str);
void	print_pair(t_pair *p);
t_pair	*sum_snailfish_num(t_pair *p1, t_pair *p2);

int	main(void)
{
	t_pair	*p;
//	t_pair	*p2;
//	t_pair	*sum;

//	char	*str = "[1,2]";
//	char	*str2 = "[[1,2],3]";
//	char	*str = "[2,[8,8]]";
//	char	*str2 = "[8,[7,[1,0]]]";
//	char	*str = "[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]";
	char	*str = "[[[1,3],[5,3]],[[1,3],[8,7]]]";
//	char	*str = "[7,[8,[7,[1,0]]]]";
//	char	*str = "[[8,[7,[1,0]]],7]";
	p = parse_snailfish_num(str);
//	p2 = parse_snailfish_num(str2);
	print_pair(p);
//	sum = sum_snailfish_num(p, p2);
//	print_pair(sum);
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

t_pair *parse_snailfish_num(char *str)
{
	t_pair	*p;

	p = 0;
	printf("->%s\n", str);
	if (str && *str == '[')
	{
		p = new_pair();
		str++;
		if (isdigit((*str)))
		{
			p->left->type = 0;
			p->left->num = atoi(str);
			while (isdigit((*str)))
				str++;
		}
		else
		{
			p->left->type = 1;
			p->left->p = parse_snailfish_num(str);
		//	p->left->p->parent = p;
			printf("%li\n", strchr(str, ']') - str + 1);
			str += strchr(str, ']') - str + 1;
			printf("-->%s\n", str);
		}
		if ((*str) == ',')
			str++;
		if (str && isdigit((*str)))
		{
			p->right->type = 0;
			p->right->num = atoi(str);
			while (isdigit((*str)))
				str++;
		}
		else
		{
			p->right->type = 1;
			p->right->p = parse_snailfish_num(str);
		//	p->right->p->parent = p;
			printf("%li\n", strchr(str, ']') - str + 1);
			str += strchr(str, ']') - str + 1;
			printf("--->%s\n", str);
		}
		str++;
	}
	printf("<-%s\n", str);
	//	str++;
//	}
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
