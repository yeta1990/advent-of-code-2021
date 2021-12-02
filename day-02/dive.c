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
#include <string.h>

int	main(void)
{
	FILE	*f;
	int		read;
	long	x;
	long	y;
	char	instruction[10];
	long	instruction_num;

	x = 0;
	y = 0;
	f = fopen("input.txt", "r");
	read = fscanf(f, "%s %li\n", instruction, &instruction_num);
	while (read != -1)
	{
		if (!strcmp(instruction, "forward"))
			x += instruction_num;
		else if (!strcmp(instruction, "down"))
			y += instruction_num;
		else if (!strcmp(instruction, "up"))
			y -= instruction_num;
		read = fscanf(f, "%s %li\n", instruction, &instruction_num);
	}
	fclose(f);
	printf("Horizontal position: %li, depth %li. Result: %li", x, y, x * y);
}
