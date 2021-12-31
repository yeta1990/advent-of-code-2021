#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
char	**apply_enhance(char **map, char algo[512]);

int	main(void)
{
	char	**map;
	char	**map2;
	char	algo[512] = "..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#";
	FILE	*f;
	int	i;

	i = 0;
	map = malloc(sizeof(char *) * 15);
	while (i < 15)
	{
		map[i] = malloc(sizeof(char) * 16);
		bzero(map[i], 16);
		i++;
	}
	f = fopen("ex", "r");
	i = 0;
	while(i < 15)
	{
		fscanf(f, "%15c\n", map[i]);
		printf("%s\n", map[i]);
		i++;
	}

	map2 = apply_enhance(map, algo);
	apply_enhance(map2, algo);
}

char	**apply_enhance(char **map, char algo[512])
{
	int	i;
	int	j;
	int	z;
	int	h;
	int	num;
	int	x;
	int	y;
	char	**map2;

	i = 1;
	x = 0;
	y = 0;
	map2 = malloc(sizeof(char *) * 15);
	while (x < 15)
	{
		y = 0;
		map2[x] = malloc(sizeof(char) * 15);
		while (y < 15)
		{
			map2[x][y] = '.';
			y++;
		}
		x++;
	}
	num = 0;
	j = 1;
	while (i < 14)
	{
		j = 1;
		while (j < 14)
		{
			num = 0;
			z = -1;
			while (z < 2)
			{
				h = -1;
				while (h < 2)
				{
					if (map[i + z][j + h] == '.')
						num = num << 1 | 0;
					else
						num = num << 1 | 1;
					h++;
				}
				z++;
			}
			map2[i][j] = algo[num];
			j++;
		}
		i++;
	}

	i = 1;
	while (i < 14)
	{
		j = 1;
		while (j < 14)
		{
			printf("%c", map2[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	printf("\n");
	return (map2);
}


