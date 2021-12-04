
#include <stdio.h>
#include <stdlib.h>

typedef struct s_num
{
	int	num;
	int	marked;
}	t_num;

typedef struct s_board
{
	t_num num[5][5];
	struct s_board *next;
}	t_board;

typedef struct s_bingo
{
	int num;
	struct s_bingo *next;
}	t_bingo;

void	add_back_bingo(t_bingo **bingo_sequence, int num);
void	print_bingo_list(t_bingo **bingo_sequence);

int	main(void)
{
	FILE *f;
	int		read;
	char	*s;
	char	*aux;
	int		i;
	t_bingo	**bingo_sequence;
	t_board	**boards;
	char	*line;
	
	s = 0;
	i = 0;
	bingo_sequence = malloc(sizeof(t_bingo *));
	bingo_sequence[0] = 0;
	boards = malloc(sizeof(t_board *));
	boards[0] = 0;
	line = malloc(sizeof(char) * 16);
	f = fopen("input.txt", "r");
	s = malloc(sizeof(char) * 1024);
	read = fscanf(f, "%s\n", s);
	aux = s;
	while (s && *s)
	{
	 	add_back_bingo(bingo_sequence, atoi(s));
		while (s && *s && *s != ',')
			s++;
		s++;
	}
	free(aux);
	print_bingo_list(bingo_sequence);
	
	while (read != -1)
	{
		read = fscanf(f, "\n");
		while (read != -1 && i < 5)
		{
			read = fscanf(f, "%14[^\n]\n", line);
			if (read != -1)
				printf("%s, \n", line);
			i++;
		}
		i = 0;
	}
	
	fclose(f);

}

void	print_bingo_list(t_bingo **bingo_sequence)
{
	t_bingo *aux;

	aux = *bingo_sequence;
	while (aux)
	{
		printf("%i, ", aux->num);
		aux	= aux->next;

	}
	printf("\n");
}

void	add_back_bingo(t_bingo **bingo_sequence, int num_to_add)
{
	t_bingo	*aux;
	t_bingo *bingo_num;
	
	aux = 0;
	bingo_num = malloc(sizeof(t_bingo));
	bingo_num->num = num_to_add;
	bingo_num->next = NULL;
	if (!*bingo_sequence)
	{
		*bingo_sequence = bingo_num;
		return ;
	}
	aux = *bingo_sequence;
	while (aux->next)
		aux = aux->next;
	aux->next = bingo_num;
}
