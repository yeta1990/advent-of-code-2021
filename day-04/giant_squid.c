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

typedef struct s_num
{
	int	num;
	int	marked;
}	t_num;

typedef struct s_board
{
	t_num			nums[5][5];
	struct s_board	*next;
}	t_board;

typedef struct s_bingo
{
	int num;
	struct s_bingo *next;
}	t_bingo;

t_board	*create_board(char **raw_board);
void	add_back_bingo(t_bingo **bingo_sequence, int num);
void	print_bingo_list(t_bingo **bingo_sequence);
void	print_boards(t_board **b);
void	add_back_board(t_board **boards, t_board *new);
t_board	*check_board(t_board **b);
void	play_bingo(t_bingo **bingo_sequence, t_board **b);
void	mark_boards(t_board **b, int num);
void	free_boards(t_board **b);

int	main(void)
{
	FILE *f;
	int		read;
	char	*s;
	char	*aux;
	t_bingo	**bingo_sequence;
	t_board	**boards;
	char	*raw_board;

	s = 0;
	bingo_sequence = malloc(sizeof(t_bingo *));
	bingo_sequence[0] = 0;
	boards = malloc(sizeof(t_board *));
	boards[0] = 0;
	raw_board = malloc(sizeof(char) * 7900);
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
	while (read != -1)
		read = fscanf(f, "%[^\r]s", raw_board);
	while (raw_board && *raw_board)
		add_back_board(boards, create_board(&raw_board));
	play_bingo(bingo_sequence, boards);
	fclose(f);
}

void	calculate_score(t_board *winner, int num)
{
	int	i;
	int	j;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (winner->nums[i][j].marked == 0)
				sum += winner->nums[i][j].num;
			j++;
		}
		i++;
	}
	printf("sum: %i, last called number: %i, final score: %i", sum, num, sum * num);
}

t_board *check_board(t_board **b)
{
	t_board *aux;
	int		i;
	int		j;

	aux = *b;
	while (aux)
	{
		i = 0;
		while (i < 5)
		{
			j = 0;
			while (j < 5)
			{
				if (aux->nums[i][j].marked == 0)
					break ;
				j++;
			}
			if (j == 5)
				return (aux);
			j = 0;
			while (j < 5)
			{
				if (aux->nums[j][i].marked == 0)
					break ;
				j++;
			}
			if (j == 5)
				return (aux);
			i++;
		}
		aux = aux->next;
	}
	return (0);
}

t_board *create_board(char **raw_board)
{
	int i;
	int	j;
	t_board *b;
	
	b = malloc(sizeof(t_board));
	i = 0;
	while (raw_board && *raw_board && **raw_board && i < 5)
	{
		j = 0;
		while (raw_board && *raw_board && **raw_board && j < 5)
		{
			b->nums[i][j].num = atoi(*raw_board);
			b->nums[i][j].marked = 0;
			while (raw_board && *raw_board && **raw_board && **raw_board != ' ' && **raw_board != '\n')
				(*raw_board)++;
			while (**raw_board == ' ' || **raw_board == '\n')
				(*raw_board)++;
			j++;
		}
		i++;
	}
	b->next = 0;
	return (b);
}

void	mark_boards(t_board **b, int num)
{
	int		i;
	int		j;
	t_board	*aux;

	aux = *b;
	while (aux)
	{
		i = 0;
		while (i < 5)
		{
			j = 0;
			while (j < 5)
			{
				if (aux->nums[i][j].num == num)
					aux->nums[i][j].marked = 1;
				j++;
			}
			i++;
		}
		aux = aux->next;
	}
}

void	play_bingo(t_bingo **bingo_sequence, t_board **b)
{
	t_bingo *aux;
	t_board	*winner_board;

	winner_board = 0;
	aux = *bingo_sequence;
	while (aux && winner_board == 0)
	{
		mark_boards(b, aux->num);
		winner_board = check_board(b);
		if (winner_board)
			break ;
		aux	= aux->next;
	}
	calculate_score(winner_board, aux->num);
}

void	add_back_board(t_board **boards, t_board *new)
{
	t_board *aux;
	
	if (!*boards)
	{	
		*boards = new;
		return ;
	}
	aux = *boards;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
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
