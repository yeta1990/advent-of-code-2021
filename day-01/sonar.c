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

int	main(void)
{
	FILE	*f;
	int		num;
	int		prev_num;
	int		read;
	int		increased;

	f = fopen("input.txt", "r");
	increased = 0;
	num = 0;
	read = fscanf(f, "%i\n", &prev_num);
	while (read != -1)
	{
		read = fscanf(f, "%i\n", &num);
		if (num > prev_num)
			increased++;
		prev_num = num;
	}
	printf("Increased: %i\n", increased);
}
