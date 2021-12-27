
#include <stdio.h>
#include <stdlib.h>

void	start_path(int x, int y, int *count, int map[100][100], int *min, char map2[100][100]);
void	print_map(char	map[100][100]);

int	main(void)
{
	FILE	*f;
	int		map[100][100] = {0};
	char	map2[100][100] = {{46}};
	int		i;
	int		j;
	char	c;
	int		min;
	int		count;
	
	i = 0;
	j = 0;
	c = 0;
	count = 0;
	min = 11002;
	f = fopen("input", "r");
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			fscanf(f, "%c", &c);
			map[i][j] = c - 48;
			map2[i][j] = '.';
			printf("%i", map[i][j]);
			j++;
		}
		fscanf(f, "\n");
		printf("\n");
		i++;
	}
	
//	print_map(map2);
	fclose(f);
	start_path(0, 0, &count, map, &min, map2);
	printf("min path: %i\n", min - map[0][0]);	
}

void	start_path(int x, int y, int *count, int map[100][100], int *min, char map2[100][100])
{
	if (x == 99 && y == 99)
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
	//	if (x < 99)
//			printf("x: %i, y: %i\n", x, y);
		*count += map[y][x];
		map2[y][x] = 'X';

		if (x + 1 < 100)
			start_path(x + 1, y, count, map, min, map2);
//		if (x - 1 > 0)
			start_path(x - 1, y, count, map, min, map2);
		if (y + 1 < 100)
			start_path(x, y + 1, count, map, min, map2);
//		if (y - 1 > 0)
//			start_path(x, y - 1, count, map, min, map2);
		*count -= map[y][x];
		map2[y][x] = '.';
	}
	else
		print_map(map2);
}

void	print_map(char	map[100][100])
{
	int	i;
	int	j;

	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}


