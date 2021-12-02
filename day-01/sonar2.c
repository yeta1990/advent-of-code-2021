/********************************************************************************************/
/*          ____   _____ ___   ___ ___  __                   _       __  ___   ___   ___	*/
/*    /\   / __ \ / ____|__ \ / _ \__ \/_ |                 | |     /_ |/ _ \ / _ \ / _ \	*/
/*   /  \ | |  | | |       ) | | | | ) || |______ _   _  ___| |_ __ _| | (_) | (_) | | | |	*/
/*  / /\ \| |  | | |      / /| | | |/ / | |______| | | |/ _ \ __/ _` | |\__, |\__, | | | |	*/
/* / ____ \ |__| | |____ / /_| |_| / /_ | |      | |_| |  __/ || (_| | |  / /   / /| |_| |	*/
/*/_/    \_\____/ \_____|____|\___/____||_|       \__, |\___|\__\__,_|_| /_/   /_/  \___/	*/
/*                                                 __/ |									*/
/*                                                |___/										*/
/*																							*/
/********************************************************************************************/

#include <stdio.h>

int	sum_array(int *nums, int size);

int	main(void)
{
	FILE	*f;
	int		nums[3];
	int		window_1;
	int		window_2;
	int		read;
	int		increased;

	f = fopen("input.txt", "r");
	increased = 0;
	nums[0] = 0;
	nums[1] = 0;
	nums[2] = 0;
	read = fscanf(f, "%i\n", &nums[0]);
	read = fscanf(f, "%i\n", &nums[1]);
	read = fscanf(f, "%i\n", &nums[2]);
	window_1 = sum_array(nums, 3);
	while (1)
	{
		nums[0] = nums[1];
		nums[1] = nums[2];
		read = fscanf(f, "%i\n", &nums[2]);
		if (read == -1)
			break ;
		window_2 = sum_array(nums, 3);
		if (window_2 > window_1)
			increased++;
		window_1 = window_2;
	}
	printf("Increased: %i\n", increased);
}

int	sum_array(int *nums, int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		sum += nums[i];
		i++;
	}
	return (sum);
}
