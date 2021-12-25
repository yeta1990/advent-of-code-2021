#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	fill_blank(char map[2000][2000]);
void	print_map(char map[2000][2000], int x, int y);
void	fold(char (*map)[2000][2000], int point);
void	fold_x(char (*map)[2000][2000], int point);
int		count_dots(char map[2000][2000], int x, int y);
int		get_max_x(char map[2000][2000]);
int		get_max_y(char map[2000][2000]);

int	main(void)
{
	FILE	*f;
	char	map[2000][2000];
	char	*line;
	int		x;
	int		maxx;
	int		y;
	int		maxy;
	int		i;
	int		read;

	read = -2;
	i = 0;
	maxx = 0;
	maxy = 0;
	x = 0;
	y = 0;
	line = malloc(sizeof(char) * 50);
	f = fopen("input", "r");
	fill_blank(map);
	while (fscanf(f, "%i,%i\n", &x, &y) != 0)// && i < 10)
	{
		printf("x: %i, y: %i\n", x, y);
		if (y > maxy)
			maxy = y;
		if (x > maxx)
			maxx = x;
		map[y][x] = '#';
		i++;
	}
	printf("max_ x %i, y %i\n", maxx, maxy);
	x = 0;
	y = 0;
	while ((read = fscanf(f, "%100[^\n]\n", line)) != 0)
	{
		if (read == 0)
			break ;
	//	printf("%s\n", line);	
		if (strlen(line) <= 1)
			break ;
		while (*line != 'y' && *line != 'x')
			line++;
		if ((*line) == 'y')
		{
			line++;
			line++;
			printf(".%i\n", atoi(line));
			y = atoi(line);
			fold(&map, atoi(line));
			if (x == 0)
				x = get_max_x(map) + 1;
			if (y == 6)
				break ;
		}
		else if ((*line) == 'x')
		{
			line++;
			line++;
			printf("-%i\n", atoi(line));
			x = atoi(line);
			fold_x(&map, atoi(line));
			if (y == 0)
				y = get_max_y(map) + 1;
		}
	}
	printf("print x %i, y %i\n", x, y);
	print_map(map, x, y);
	printf("\n%i dots\n", count_dots(map, x, y));
	fclose(f);
}

int	get_max_x(char map[2000][2000])
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (i < 2000)
	{
		j = 0;
		while (j < 2000)
		{
			if (j > max && map[i][j] == '#')
				max = j;
			j++;
		}
		i++;
	}
	return (max);
}

int	get_max_y(char map[2000][2000])
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (i < 2000)
	{
		j = 0;
		while (j < 2000)
		{
			if (i > max && map[i][j] == '#')
				max = i;
			j++;
		}
		i++;
	}
	printf("max %i\n", max);
	return (max);
}


void	fold_x(char (*map)[2000][2000], int point)
{
	int	i;
	int	j;
	int	copy;
	int	max;

	i = 0;
	j = 0;
	copy = 1;
	max = 0;
	while (i < 2000)
	{
		j = 0;
		while (j < 2000)
		{
			if (i >= max && (*map)[i][j] == '#')
				max = i;
			j++;
		}
		i++;
	}


	i = 0;
	while (i <= max)
	{
		j = point + 1;
		copy = 1;
		while (j <= point * 2)
 		{
	//		printf("%i %i %i %i\n", i, point, copy, max);
			if ((*map)[i][j] == '#')
				(*map)[i][point - copy] = (*map)[i][j];
			j++;
			copy++;
		}
		i++;
	}
//	print_map(*map);
}

int	count_dots(char map[2000][2000], int x, int y)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (map[i][j] == '#')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	fold(char (*map)[2000][2000], int point)
{
	int	i;
	int	j;
	int	copy;
	int	max;

	i = 0;
	j = 0;
	copy = 1;
	max = 0;
	while (i < 2000)
	{
		j = 0;
		while (j < 2000)
		{
			if ((*map)[i][j] == '#')
				max = i;
			j++;
		}
		i++;
	}
//	printf("max %i", max);
	i = point + 1;
	while (i <= max)
	{
		j = 0;
		while (j < 2000)
		{
		//	printf("%i %i %i %i\n", i, point, copy, max);
			if ((*map)[i][j] == '#')
				(*map)[point - copy][j] = (*map)[i][j];
			j++;
		}
		copy++;
		i++;
	}
//	print_map(*map);
}

void	print_map(char map[2000][2000], int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	fill_blank(char map[2000][2000])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 2000)
	{
		j = 0;
		while (j < 2000)
		{
			map[i][j] = '.';
			j++;
		}
		i++;
	}
}
