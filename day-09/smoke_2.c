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

#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int	height;
	int	low_point;
	int	**basis;
	int basis_count;
}	t_point;

void	fill_basis(int i, int j, int ***basis, t_point (*map)[100][100]);
int	count_basis(int ***basis);

int	main(void)
{
	t_point	map[100][100];
	FILE	*f;
	char	num;
	int		i;
	int		j;
	int		risk;
	int		h;
	int		k;

	risk = 0;
	i = 0;
	j = 0;

	num = 0;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%c", &num) != -1)
	{
		if (num != '\n')
		{
			map[j][i].height = num - 48;
			h = 0;
			map[j][i].basis = malloc(sizeof(int *) * 100);
			map[j][i].basis[0] = 0;
			map[j][i].basis_count = 0;
			while (h < 100)
			{
				map[j][i].basis[h] = malloc(sizeof(int) * 100);
				k = 0;
				while (k < 100)
				{
					map[j][i].basis[h][k] = -1;
					k++;
				}
				h++;
			}
			map[j][i].low_point = 0;
			i++;
		}
		else
		{
			i = 0;
			j++;
		}
	}
	i = 0;
	j = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			if (i == 0 && j == 0)
			{
				if (map[i][j].height < map[i + 1][j].height && map[i][j].height < map[i][j + 1].height)
					map[i][j].low_point = 1;
			}
			else if (i == 0 && j == 99)
			{
				if (map[i][j].height < map[i + 1][j].height && map[i][j].height < map[i][j - 1].height)
					map[i][j].low_point = 1;
			}
			else if (i == 99 && j == 99)
			{
				if (map[i][j].height < map[i - 1][j].height && map[i][j].height < map[i][j - 1].height)
					map[i][j].low_point = 1;
			}
			else if (j == 0 && i == 99)
			{

				if (map[i][j].height < map[i - 1][j].height && map[i][j].height < map[i][j + 1].height)
					map[i][j].low_point = 1;
			}
			else if (j == 0)
			{

				if (map[i][j].height < map[i + 1][j].height && map[i][j].height < map[i][j + 1].height && map[i][j].height < map[i - 1][j].height)
					map[i][j].low_point = 1;
			}
			else if (i == 0)
			{
				if (map[i][j].height < map[i][j - 1].height && map[i][j].height < map[i][j + 1].height && map[i][j].height < map[i + 1][j].height)
					map[i][j].low_point = 1;
			}
			else if (j == 99)
			{
				if (map[i][j].height < map[i][j - 1].height && map[i][j].height < map[i + 1][j].height && map[i][j].height < map[i - 1][j].height)
					map[i][j].low_point = 1;
			}
			else if (i == 99)
			{
				if (map[i][j].height < map[i][j - 1].height && map[i][j].height < map[i][j + 1].height && map[i][j].height < map[i - 1][j].height)
					map[i][j].low_point = 1;
			}
			else if (i > 0 && i < 99 && j > 0 && j < 99)
			{

				if (map[i][j].height < map[i][j - 1].height && map[i][j].height < map[i][j + 1].height && map[i][j].height < map[i - 1][j].height && map[i][j].height < map[i + 1][j].height )
				{
					map[i][j].low_point = 1;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			if (map[i][j].low_point == 1)
			{
				fill_basis(i, j, &(map[i][j].basis), &map);
				map[i][j].basis_count = count_basis(&(map[i][j].basis));
			}
			j++;
		}
		i++;
	}
}

int	count_basis(int ***basis)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			if ((*basis)[i][j] != -1)
				count++;
			j++;
		}
		i++;
	}
	printf("%i\n", count);
	return (count);
}

void	fill_basis(int i, int j, int ***basis, t_point (*map)[100][100])
{
	if (i > 0 && i < 99 && j > 0 && j < 99 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
	else if (i == 0 && j == 0 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
	}
	else if (i == 0 && j == 99 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
	else if (i == 99 && j == 0 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
	}
	else if (i == 99 && j == 99 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
	else if (i == 0 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
	else if (j == 0 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
	}
	else if (i == 99 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j + 1, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
	else if (j == 99 && (*map)[i][j].height < 9 && (*basis)[i][j] == -1)
	{
		(*basis)[i][j] = (*map)[i][j].height;
		fill_basis(i + 1, j, basis, map);
		fill_basis(i - 1, j, basis, map);
		fill_basis(i, j - 1, basis, map);
	}
}
