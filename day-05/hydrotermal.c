#include <stdio.h>
#include <stdlib.h>

void add_to_map(int (*map)[1000][1000], int x1, int x2, int y1, int y2);

int	main(void)
{

	int		map[1000][1000] = {0};
	FILE	*f;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		overlap;

	x1 = 0;
	y1 = 0;
	x1 = 0;
	x2 = 0;
	overlap = 0;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%i,%i %*s %i,%i", &x1, &y1, &x2, &y2) != -1)
	{
//		printf("%i,%i -> %i,%i\n", x1, y1, x2, y2);
		if (x1 == x2 || y1 == y2)
			add_to_map(&map, x1, x2, y1, y2);
	}
	x1 = 0;
	y1 = 0;
	while (y1 < 1000)
	{
		x1 = 0;
		while (x1 < 1000)
		{
			if (map[y1][x1] > 1)
				overlap++;
//			printf("%i", map[y1][x1]);
			x1++;
		}
//		printf("\n");
		y1++;
	}
	printf("overlap: %i points\n", overlap);
}

void add_to_map(int (*map)[1000][1000], int x1, int x2, int y1, int y2)
{
	int	final_x;
	int	final_y;
	int	x;
	int	y;
	
	final_x = 0;
	final_y = 0;
	x = 0;
	y = 0;
	if (x1 == x2)
	{
		if (y2 >= y1)
		{
			y = y1;
			final_y = y2;
		}
		else if (y1 > y2)
		{
			y = y2;
			final_y = y1;
		}
		while (y <= final_y)
		{
			(*map)[y][x1] += 1;
			y++;
		}
	}
	else if (y1 == y2)
	{
		if (x2 >= x1)
		{
			x = x1;
			final_x = x2;
		}
		else if (x1 > x2)
		{
			x = x2;
			final_x = x1;
		}
		while (x <= final_x)
		{
			(*map)[y1][x] += 1;
			x++;
		}
	}
}
