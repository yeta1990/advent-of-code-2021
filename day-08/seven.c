#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_num(char **nums, char *str);

int	main(void)
{
	char	*nums[5];
	FILE	*f;
	char	**output;
	int		i;
	int		coinc;

	i = 0;
	coinc = 0;
//	nums[0] = "abcefg\0";
	nums[0] = "cf\0";
//	nums[2] = "acdeg\0";
//	nums[3] = "acdfg\0";
	nums[1] = "bcdf\0";
//	nums[5] = "abdfg\0";
//	nums[6] = "abdefg\0";
	nums[2] = "acf\0";
	nums[3] = "abcdefg\0";
//	nums[9] = "abcdfg\0";
	nums[4] = 0;
	output = malloc(sizeof(char *) * 5);
	while (i < 4)
	{
		output[i] = malloc(sizeof(char) * 8);
		i++;
	}
	output[i] = 0;
	i = 0;	
	f = fopen("input.txt", "r");
	while (fscanf(f, "%*60[^|] | %s %s %s %s\n", output[0], output[1], output[2], output[3]) !=  -1)
	{
		i = 0;
		while (i < 4)
		{
			coinc += check_num(nums, output[i]);
			i++;
		}
	//	printf("%s %s %s %s\n", output[0], output[1], output[2], output[3]);
	}
	fclose(f);
	printf("coincident %i\n", coinc);
}

int	check_num(char **nums, char *str)
{
	int	len;
	int	coinc;
	int	i;
	int	j;
	int	total;

	total = 0;
	j = 0;
	coinc = 0;
	len = strlen(str);
	while (nums[j])
	{
		i = 0;
		coinc = 0;
	/*	while (i < len)
		{
			if (strchr(nums[j], str[i]) != 0)
			{
				printf("%s, %c\n", nums[j], str[i]);
				coinc++;
			}
			i++;
		}
		if (coinc == len)
		{
			printf("------------->%i, %i\n", coinc, len);	
			total++;
		}

		printf("%s \n", nums[j]);*/
		if ((int) strlen(nums[j]) == len)
			total++;
		j++;
		
	}
	return (total);
}
