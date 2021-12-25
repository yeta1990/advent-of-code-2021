#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void	fill_blank(char map[1500][1500]);
void	print_map(char map[1500][1500]);
void	fold(char (*map)[1500][1500], int point);

int	main(void)
{
	FILE	*f;
	char	map[1500][1500];
	char	*line;
	int		x;
	int		y;

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
	//	printf("%i-%i\n", x, y);
		map[y][x] = '#';
		bzero(line, 50);
	}
	while (fscanf(f, "%100[^\n]\n", line) != -1)
	{
		while (*line != 'y' && *line != 'x')
			line++;
		if ((*line) == 'y')
		{
			line += 2;
			fold(&map, atoi(line));
//			fold(0, &map, atoi(line));
		}
		else
		{
			line++;
			line++;
		//	fold(map, atoi(line));
		}
		printf("fold: %s\n", line);
	}
	print_map(map);
	fclose(f);
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

	i = point + 1;
	while (i <= max)
	{
		j = 0;
		while (j < 1500)
		{
			printf("%i %i %i %i\n", i, point, copy, max);
			if ((*map)[i][j] == '#')
				(*map)[point - copy][j] = (*map)[i][j];
			j++;
		}
		copy++;
		i++;
	}
	print_map(*map);
}

void	print_map(char map[1500][1500])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
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
