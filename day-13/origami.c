#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void	fill_blank(char map[1500][1500]);
void	print_map(char map[1500][1500], int x, int y);
void	fold(char (*map)[1500][1500], int point);
void	fold_x(char (*map)[1500][1500], int point);
int		count_dots(char map[1500][1500], int x, int y);
int		get_max_x(char map[1500][1500]);
int		get_max_y(char map[1500][1500]);

int	main(void)
{
	FILE	*f;
	char	map[1500][1500];
	char	*line;
	int		x;
	int		maxx;
	int		y;
	int		maxy;

	maxx = 0;
	maxy = 0;
	x = 0;
	y = 0;
	line = calloc(500, sizeof(char));
	f = fopen("ex", "r");
	fill_blank(map);
	while (fscanf(f, "%s\n", line) != -1)
	{
		if (strchr(line, ',') == 0)
			break ;
		x = atoi(line);
		while (line && *line != ',')
			line++;
		line++;
		y = atoi(line);
		if (y > maxy)
			maxy = y;
		if (x > maxx)
			maxx = x;
		map[y][x] = '#';
		bzero(line, 50);
	}
	printf("max_ x %i, y %i\n", maxx, maxy);
	x = 0;
	y = 0;
	while (fscanf(f, "%100[^\n]\n", line) != -1)
	{
		while (*line != 'y' && *line != 'x')
			line++;
		if ((*line) == 'y')
		{
			line++;
			line++;
			printf("%i\n", atoi(line));
			y = atoi(line);
			fold(&map, atoi(line));
			x = get_max_x(map) + 1;
			break ;
		}
		else if ((*line) == 'x')
		{
			line++;
			line++;
			x = atoi(line);
			fold_x(&map, atoi(line));
			y = get_max_y(map) + 1;
			break ;
		}
	}
//	print_map(map, x, y);
	printf("\n%i dots\n", count_dots(map, x, y));
	fclose(f);
}

int	get_max_x(char map[1500][1500])
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (i < 1500)
	{
		j = 0;
		while (j < 1500)
		{
			if (j > max && map[i][j] == '#')
				max = j;
			j++;
		}
		i++;
	}
	return (max);
}

int	get_max_y(char map[1500][1500])
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (i < 1500)
	{
		j = 0;
		while (j < 1500)
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


void	fold_x(char (*map)[1500][1500], int point)
{
	int	i;
	int	j;
	int	copy;
	int	max;

	i = 0;
	j = 0;
	copy = 1;
	max = 0;
	while (i < 1500)
	{
		j = 0;
		while (j < 1500)
		{
			if ((*map)[i][j] == '#')
				max = i;
			j++;
		}
		i++;
	}


	i = 0;
	while (i < 1500)
	{
		j = point + 1;
		copy = 1;
		while (j <= max)
		{
//			printf("%i %i %i %i\n", i, point, copy, max);
			if ((*map)[i][j] == '#')
				(*map)[i][point - copy] = (*map)[i][j];
			j++;
			copy++;
		}
		i++;
	}
//	print_map(*map);
}

int	count_dots(char map[1500][1500], int x, int y)
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

void	fold(char (*map)[1500][1500], int point)
{
	int	i;
	int	j;
	int	copy;
	int	max;

	i = 0;
	j = 0;
	copy = 1;
	max = 0;
	while (i < 1500)
	{
		j = 0;
		while (j < 1500)
		{
			if ((*map)[i][j] == '#')
				max = i;
			j++;
		}
		i++;
	}
	printf("max %i", max);
	i = point + 1;
	while (i <= max)
	{
		j = 0;
		while (j < 1500)
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

void	print_map(char map[1500][1500], int x, int y)
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

void	fill_blank(char map[1500][1500])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 1500)
	{
		j = 0;
		while (j < 1500)
		{
			map[i][j] = '.';
			j++;
		}
		i++;
	}
}
