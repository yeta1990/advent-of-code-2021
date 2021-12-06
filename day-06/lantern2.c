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
	unsigned long long school[9] = {0};
	FILE		*f;
	int			age;
	int			days;
	int			i;
	unsigned long long	swap;
	unsigned long long	fishes;

	swap = 0;
	days = 0;
	fishes = 0;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%i,", &age) != -1)
		school[age] += 1;
	while (days < 256)
	{
		i = 1;
		swap = school[0];
		school[0] = 0;
		while (i < 9)
		{
			school[i - 1] = school[i];
			school[i] = 0;
			i++;
		}
		school[8] += swap;
		school[6] += swap;
		days++;
	}
	i = 0;
	while (i < 9)
	{
		fishes += school[i];
		i++;
	}
	printf("%llu\n", fishes);
}
