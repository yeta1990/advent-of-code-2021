
#include <stdio.h>

int	main(void)
{
	int	x;
	int	y;
	int	map[4] = {169, 206, -108, -68};
	int	x_vel;
	int	y_vel;
	int	high_y;
	int	best_y;
	int	i;
	int	j;

	best_y = 0;
	high_y = 0;
	x = 0;
	y = 0;
	j = 1000;
	while (j >= map[2])
	{
		i = 1;
		while (i <= map[1])
		{
			x_vel = i;
			y_vel = j;
			x = 0;
			y = 0;
			high_y = 0;
			while (y >= map[2] && x <= map[1])
			{
				x = x + x_vel;
				y = y + y_vel;
				if (y > high_y)
					high_y = y;
				if (x >= map[0] && x <= map[1] && y >= map[2] && y <= map[3])
				{
					if (high_y > best_y)
						best_y = high_y;
					printf("velocity: %i, %i. contact point %i, %i. high_y: %i\n", i, j, x, y, high_y);
					break ;
				}
				else if (y < map[2] || x > map[1])
					break ;
				if (x_vel > 0)
					x_vel--;
				y_vel--;
			}
			i++;
		}
		j--;
	}
	printf("highest y: %i\n", best_y);
}
