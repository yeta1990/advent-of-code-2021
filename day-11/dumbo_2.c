/********************************************************************************************/
/*          ____   _____ ___   ___ ___  __                   _       __  ___   ___   ___    */
/*    /\   / __ \ / ____|__ \ / _ \__ \/_ |                 | |     /_ |/ _ \ / _ \ / _ \   */
/*   /  \ | |  | | |       ) | | | | ) || |______ _   _  ___| |_ __ _| | (_) | (_) | | | |  */
/*  / /\ \| |  | | |      / /| | | |/ / | |______| | | |/ _ \ __/ _` | |\__, |\__, | | | |  */
/* / ____ \ |__| | |____ / /_| |_| / /_ | |      | |_| |  __/ || (_| | |  / /   / /| |_| |  */
/*/_/    \_\____/ \_____|____|\___/____||_|       \__, |\___|\__\__,_|_| /_/   /_/  \___/   */
/*                                                 __/ |                                    */
/*                                                |___/                                     */
/*                                                                                          */
/********************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

void	flash_around(int i, int j, int (*map)[10][10], int (*flashes)[10][10]);
void	add_one(int (*map)[10][10]);
void	update_flashes(int (*map)[10][10], int (*flashes)[10][10]);
void	reset(int (*map)[10][10]);
size_t	count_flashes(int (*flashes)[10][10]);
int		print_map(int (*map)[10][10]);

int	main(void)
{
	int	map[10][10] = {0};
	int	flashes[10][10] = {0};
	FILE	*f;
	int		i;
	int		j;
	char	num;
	int		read;

	read = 0;
	f =	fopen("input.txt", "r");
	i = 0;
	j = 0;
	while(read != -1)
	{
		i = 0;
		while (read != -1 && i < 10)
		{
			read = fscanf(f, "%c", &num);
			if (read != -1)
			{
				map[j][i] = num - 48;
				printf("%i", map[j][i]);
			}
			i++;
		}
		j++;
		fscanf(f, "\n");
		printf("\n");
	}
	i = 0;
	while (i < 500)
	{
		add_one(&map);
		printf("\n");
		update_flashes(&map, &flashes);
		if (print_map(&map))
		{
			i++;
			break ;
		}
		reset(&map);
		i++;
	}
	printf("step: %i", i);
}

int	print_map(int (*map)[10][10])
{
	int	i;
	int	j;
	int	sym;

	sym = 0;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((*map)[i][j] >= 10)
			{
				sym++;
				printf("0");
			}
			else
				printf("%i", (*map)[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("\n");
	if (sym == 100)
		return (1);
	return (0);
}

size_t	count_flashes(int (*flashes)[10][10])
{
	int		i;
	int		j;
	size_t	count;

	count = 0;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			count += (*flashes)[i][j];
			j++;
		}
		i++;
	}
	return (count);
}

void	add_one(int (*map)[10][10])
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			(*map)[i][j]++;
			j++;
		}
		i++;
	}
}

void	update_flashes(int (*map)[10][10], int (*flashes)[10][10])
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((*map)[i][j] == 10)
				flash_around(i, j, map, flashes);
			j++;
		}
		i++;
	}
}

void	reset(int (*map)[10][10])
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((*map)[i][j] >= 10)
				(*map)[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	flash_around(int i, int j, int (*map)[10][10], int (*flashes)[10][10])
{
	(*flashes)[i][j]++;
	(*map)[i][j] = 11;
	if (j > 0 && i > 0)
	{
		if ((*map)[i - 1][j - 1] < 10)
			(*map)[i - 1][j - 1]++;
	}
	if (i > 0)
	{
		if ((*map)[i - 1][j] < 10)
			(*map)[i - 1][j]++;
	}
	if (i > 0 && j < 9)
	{
		if ((*map)[i - 1][j + 1] < 10)
			(*map)[i - 1][j + 1]++;
	}
	if (j > 0)
	{
		if ((*map)[i][j - 1] < 10)
			(*map)[i][j - 1]++;
	}
	if (j < 9)
	{
		if ((*map)[i][j + 1] < 10)
			(*map)[i][j + 1]++;
	}
	if (i < 9)
	{
		if ((*map)[i + 1][j] < 10)
			(*map)[i + 1][j]++;
	}	
	if (i < 9 && j < 9)
	{
		if ((*map)[i + 1][j + 1] < 10)
			(*map)[i + 1][j + 1]++;
	}
	if (i < 9 && j > 0)
	{
		if ((*map)[i + 1][j - 1] < 10)
			(*map)[i + 1][j - 1]++;
	}
	update_flashes(map, flashes);
}

