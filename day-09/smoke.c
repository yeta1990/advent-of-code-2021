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

}	t_point;

int	main(void)
{
	t_point	map[100][100];
	FILE	*f;
	char	num;
	int		i;
	int		j;
	int		risk;

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
				risk = risk + map[i][j].height + 1;
			}
			j++;
		}
		i++;
	}
	printf("risk: %i\n", risk);
}
