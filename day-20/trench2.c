#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
char	**apply_enhance(char **map, char algo[512]);

int	main(void)
{
	char	**map;
	char	**map2;
	char	algo[512] = "##.#.###.....###.#...###.#.##..#....##.#.######.......#.....###....###.##..#..####.##....#....#####.###.##....#.###.#...#..###.###....#..#..##..#.###..#..#..#...##..##...##.###..#.####..#.####..#...#.###..#.###..#...###..##.#...####..#.##.#....###...####.###.#..#.#.....##.#..#...#.####.##..#.##...##.#..#...###......###...##..#..####.....#.###.#.###..#...#.##....#...#.######....###.#.....###.##.#.#..#....##..#..#....###..####....#.#.##.#.##.#.#.#..#..##.#...####..###.##.####..#..#.#.##.#..#.#...#.#....#...#.";
	FILE	*f;
	int	i;

	i = 0;
	map = malloc(sizeof(char *) * 360);
	while (i < 360)
	{
		map[i] = malloc(sizeof(char) * 261);
		bzero(map[i], 261);
		i++;
	}
	f = fopen("input", "r");
	i = 0;
	while(i < 360)
	{
		fscanf(f, "%360c\n", map[i]);
	//	printf("%s\n", map[i]);
		i++;
	}
	i = 0;
	map2 = apply_enhance(map, algo);
	while (i < 49)
	{
		map2 = apply_enhance(map2, algo);
		i++;
	}
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
	map2 = malloc(sizeof(char *) * 360);
	while (x < 360)
	{
		y = 0;
		map2[x] = malloc(sizeof(char) * 361);
		while (y < 360)
		{
			map2[x][y] = '.';
			y++;
		}
		x++;
	}
	num = 0;
	j = 1;
	while (i < 359)
	{
		j = 1;
		while (j < 359)
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
	z = 0;
	i = 50;
	while (i < 300)
	{
		j = 50;
		while (j < 300)
		{
			if (map2[i][j] == '#')
				z++;
			printf("%c", map2[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	printf("\n");

	printf("num of #: %i\n", z);
	return (map2);
}
