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

int	main(void)
{
	FILE	*f;
	int		num;
	int		j;
	int		crabs[2500] = {0};
	int		steps;
	int		fuel;

	j = 0;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%i,", &num) != -1)
		crabs[num] += 1;
	num = 0;
	fuel = 0;
	while (num < 2500)
	{
		steps = 0;
		j = 0;
		while (j < 2500)
		{
			if (num != j)
				steps += crabs[j] * abs(num-j);
			j++;
		}
		if (fuel == 0 || (fuel > 0 && steps < fuel))
			fuel = steps;
		num++;
	}
	printf("\nfuel: %i", fuel);
}
