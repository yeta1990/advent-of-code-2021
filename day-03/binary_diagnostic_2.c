
#include <stdlib.h>
#include <stdio.h>

typedef struct s_num
{
	int	num;
	int	deleted;
	struct s_num *next;
}	t_num;

void	add_back(t_num **list, int n);
void	print_list(t_num **list);
int		count_ones(t_num **list, int i);
void	delete_coincident(t_num **list, int type, int right_shift);
int		sum_bytes(t_num **list, int i);
int		count_list(t_num **list);
int		get_last_active(t_num **list);

int	main(void)
{
	FILE	*f;
	int		lines;
	int		read;
	char	nums[13];
	int		sum_bytes;
	int		bin;
	int		i;
	t_num	**oxygen;
	t_num	**co2;

	sum_bytes = 0;
	oxygen = malloc(sizeof(t_num *));
	oxygen[0] = 0;
	co2 = malloc(sizeof(t_num *));
	co2[0] = 0;
	i = 0;
	lines = 0;
	f = 0;
	f = fopen("input.txt", "r");
	read = fscanf(f, "%s\n", nums);
	while (read != -1)
	{
		bin = strtoul(nums, 0, 2);
		add_back(oxygen, bin);
		add_back(co2, bin);
		read = fscanf(f, "%s\n", nums);
	}
	while (i < 12 && count_list(oxygen) > 1)
	{
		sum_bytes = count_ones(oxygen, i);
		lines = count_list(oxygen);	
		if (sum_bytes >= lines / 2)
			delete_coincident(oxygen, 0, i);
		else
			delete_coincident(oxygen, 1, i);
		lines = 0;
		sum_bytes = 0;
		i++;
	}
	i = 0;
	while (i < 12 && count_list(co2) > 1)
	{
		sum_bytes = count_ones(co2, i);
		lines = count_list(co2);
		if (sum_bytes >= lines / 2)
			delete_coincident(co2, 1, i);
		else
			delete_coincident(co2, 0, i);
		lines = 0;
		sum_bytes = 0;
		i++;
	}
	printf("oxygen: %d, ", get_last_active(oxygen));
	printf("co2: %d\n", get_last_active(co2));
	printf("life support rating: %i\n", get_last_active(oxygen) * get_last_active(co2));
	fclose(f);
}

int	get_last_active(t_num **list)
{
	t_num *aux;

	aux = *list;
	while (aux->deleted)
		aux = aux->next;
	return (aux->num);
}

int	count_ones(t_num **list, int i)
{
	t_num	*aux;
	int		sum;
	
	sum = 0;
	aux = *list;
	while (aux)
	{
		if (aux->deleted == 0)
			if ((aux->num >> (12 - i - 1)) & 1)
				sum += 1;
		aux = aux->next;
	}
	return (sum);
}

void	add_back(t_num **list, int n)
{
	t_num	*aux;
	t_num	*t;

	t = malloc(sizeof(t_num));
	t->num = n;
	t->deleted = 0;
	t->next = NULL;
	aux = *list;
	if (!aux)
	{
		*list = t;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = t;
}

int	count_list(t_num **list)
{
	t_num	*aux;
	int		size;

	size = 0;
	aux = *list;
	while (aux)
	{
		if (aux->deleted == 0)
			size++;
		aux = aux->next;
	}
	return (size);
}
void	print_list(t_num **list)
{
	t_num *aux;

	aux = *list;
	while (aux)
	{
		if (aux->deleted == 0)
			printf("%i\n", aux->num);
		aux = aux->next;
	}
}

void	delete_coincident(t_num **list, int type, int right_shift)
{
	t_num	*aux;
	t_num	*aux_2;
	t_num	*pen;
	aux = *list;
	aux_2 = 0;
	pen = 0;
	while (aux)
	{
		if (type && (aux->num >> (12 - right_shift - 1)) & 1)
			aux->deleted = 1;
		else if (!type && !((aux->num >> (12 - right_shift - 1)) & 1))
			aux->deleted = 1;
		aux = aux->next;
	}
}
