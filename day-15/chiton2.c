
#include <stdio.h>
#include <stdlib.h>

void	start_path(int x, int y, int *count, int map[500][500], int *min, char map2[500][500]);
void	print_map(int map[500][500]);
void	find_smallest_position(int	map[500][500], int *x, int *y, int closed[500][500]);
void	walk_paths(int map[500][500], int (*map2)[500][500], int x, int y, int (*closed)[500][500]);
void	create_big_map(int (*map)[500][500],int (*map2)[500][500], int (*closed)[500][500]);

int	main(void)
{
	FILE	*f;
	int		map[500][500] = {0};
	int		map2[500][500];
	int		closed[500][500];
	int		i;
	int		j;
	char	c;
	
	i = 0;
	j = 0;
	c = 0;
	f = fopen("input", "r");
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			fscanf(f, "%c", &c);
			map[i][j] = c - 48;
			map2[i][j] = -1;
			closed[i][j] = 0;
	//		printf("%i", map[i][j]);
			j++;
		}
		fscanf(f, "\n");
	//	printf("\n");
		i++;
	}
	create_big_map(&map, &map2, &closed);
//	print_map(map);
	i = 0;
	j = 0;
	walk_paths(map, &map2, 0, 0, &closed);
	while (i != 499 || j != 499)
	{
		find_smallest_position(map2, &i, &j, closed);
		walk_paths(map, &map2, i, j, &closed);
	}
	map2[499][499] = map2[499][499] + map[j][i];
	printf("path: %i\n", map2[499][499]);
	fclose(f);
}

void	create_big_map(int (*map)[500][500],int (*map2)[500][500], int (*closed)[500][500])
{
	int	z;
	int	h;
	int	i;
	int	j;

	z = 1;
	i = 0;
	j = 0;
	while (z < 5)
	{
		i = 0;
		while (i < 100)
		{
			j = 0;
			while (j < 100)
			{
				if ((*map)[i][j - 100 + z * 100] < 9)
					(*map)[i][j + z * 100] = (*map)[i][j - 100 + z * 100] + 1;
				else
					(*map)[i][j + z * 100] = 1;
				(*map2)[i][j + z * 100] = -1;
				(*closed)[i][j + z * 100] = 0;
				j++;
			}
			i++;
		}
		z++;
	}
	z = 0;
	h = 1;
	while (h < 5)
	{
		i = 0;
		j = 0;
		z = 1;
		while (z < 6)
		{
			i = 0;
			while (i < 100)
			{
				j = 0;
				while (j < 100)
				{
				//	printf("%i, %i: %i\n", i - 100 + h * 100, j - 100 + z * 100, (*map)[i - 100 + h * 100][j - 100 + z * 100]);
					if ((*map)[i - 100 + h * 100][j - 100 + z * 100] < 9)
						(*map)[i + h * 100][j - 100 + z * 100] = (*map)[i - 100 + h * 100][j - 100 + z * 100] + 1;
					else
						(*map)[i + h * 100][j - 100 + z * 100] = 1;
					(*map2)[i + h * 100][j - 100 + z * 100] = -1;
					(*closed)[i + h * 100][j - 100 + z * 100] = 0;
					j++;
				}
				i++;
			}
			z++;
		}
		h++;
	}
}

void	walk_paths(int map[500][500], int (*map2)[500][500], int x, int y, int (*closed)[500][500])
{
	if (x == 0 && y == 0)
	{
		(*map2)[y][x + 1] = 0;
		(*map2)[y + 1][x] = 0;
		(*closed)[y][x] = 1;
		return ;
	}
	if (x < 499)
	{
		if ((*map2)[y][x + 1] == -1)
			(*map2)[y][x + 1] = (*map2)[y][x] + map[y][x];
		else if ((*map2)[y][x] + map[y][x] < (*map2)[y][x + 1])
			(*map2)[y][x + 1] = (*map2)[y][x] + map[y][x];
	}
	if (x > 0)
	{
		if ((*map2)[y][x - 1] == -1)
			(*map2)[y][x - 1] = (*map2)[y][x] + map[y][x];
		else if ((*map2)[y][x] + map[y][x] < (*map2)[y][x - 1])
			(*map2)[y][x - 1] = (*map2)[y][x] + map[y][x];
	}
	if (y < 499)
	{
		if ((*map2)[y + 1][x] == -1)
			(*map2)[y + 1][x] = (*map2)[y][x] + map[y][x];
		else if ((*map2)[y][x] + map[y][x] < (*map2)[y + 1][x])
			(*map2)[y + 1][x] = (*map2)[y][x] + map[y][x];
	}
	if (y > 0)
	{
		if ((*map2)[y - 1][x] == -1)
			(*map2)[y - 1][x] = (*map2)[y][x] + map[y][x];
		else if ((*map2)[y][x] + map[y][x] < (*map2)[y - 1][x])
			(*map2)[y - 1][x] = (*map2)[y][x] + map[y][x];
	}
	(*closed)[y][x] = 1;
}
void	find_smallest_position(int	map[500][500], int *x, int *y, int closed[500][500])
{
	int	i;
	int	j;
	int	min;

	min = 50000;
	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			if (closed[i][j] == 0 && map[i][j] > -1 && map[i][j] < min)
			{
				min = map[i][j];
				*x = j;
				*y = i;
			}
			j++;
		}
		i++;
	}
}
/*
void	start_path(int x, int y, int *count, int map[500][500], int *min, char map2[500][500])
{
	if (x == 499499 && y == 499499)
	{
		*count += map[y][x];
		if (*count <= *min)
		{
			*min = *count;
		//	printf("min: %i\n", *count);
		}
		print_map(map2);
		*count -= map[y][x];
	}
	else if (*count < 400)
	{
	//	if (x < 499499)
//			printf("x: %i, y: %i\n", x, y);
		*count += map[y][x];
		map2[y][x] = 'X';

		if (x + 1 < 500)
			start_path(x + 1, y, count, map, min, map2);
//		if (x - 1 > 0)
			start_path(x - 1, y, count, map, min, map2);
		if (y + 1 < 500)
			start_path(x, y + 1, count, map, min, map2);
//		if (y - 1 > 0)
//			start_path(x, y - 1, count, map, min, map2);
		*count -= map[y][x];
		map2[y][x] = '.';
	}
	else
		print_map(map2);
}
*/
void	print_map(int	map[500][500])
{
	int	i;
	int	j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			printf("%i,", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}


