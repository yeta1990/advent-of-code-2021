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

int	main(void)
{
	FILE	*f;
	int		lines;
	int		read;
	char	nums[13];
	int		sum_bytes[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int		bin;
	int		i;
	char	gamma_raw[13];
	char	epsilon_raw[13];
	int		gamma;
	int		epsilon;

	gamma = 0;
	epsilon = 0;
	i = 0;
	lines = 0;
	f = 0;
	f = fopen("input.txt", "r");
	read = fscanf(f, "%s\n", nums);
	while (read != -1)
	{
		lines++;
		bin = strtoul(nums, 0, 2);
		while (i < 12)
		{
			if ((bin >> (12 - i - 1)) & 1)
			{
				printf("%i, ", nums[i] - '0');
				sum_bytes[i] += 1;
			}
			printf("\n");
			i++;
		}
		i = 0;
		read = fscanf(f, "%s\n", nums);
	}
	while (i < 12)
	{
		if (sum_bytes[i] > lines / 2)
		{
			gamma_raw[i] = '1';
			epsilon_raw[i] = '0';
		}
		else
		{
			gamma_raw[i] = '0';
			epsilon_raw[i] = '1';
		}
		i++;
	}
	gamma_raw[12] = 0;
	printf("lines: %i\n", lines);
	gamma = strtoul(gamma_raw, 0, 2);
	epsilon = strtoul(epsilon_raw, 0, 2);
	printf("gamma: %d, ", gamma);
	printf("epsilon: %d\n", epsilon);
	printf("power consumption: %i", gamma * epsilon);
	fclose(f);
}
