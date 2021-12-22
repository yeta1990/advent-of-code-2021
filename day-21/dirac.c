#include <stdlib.h>
#include <stdio.h>

typedef struct s_side
{
	int	value;
	struct s_side *next;
}	t_side;

t_side	**make_dice(int n);
t_side	*new_side(int value);
t_side	*board_forward(t_side *player_position, int value);

int	main(void)
{
	t_side	**dice;
	t_side	**board;
	t_side	*p1_pos;
	t_side	*p2_pos;
	t_side	*dice_position;
	int		i;
	int		p1;
	int		p2;
	int		start;
	int		j;
	FILE	*f;
	int		moves;

	board = make_dice(10);
	p1_pos = *board;
	p2_pos = *board;
	f = fopen("ex", "r");
	start = 0;
	fscanf(f, "%*27c%i\n", &start);
	i = 0;
	while (i < start - 1)
	{
		p1_pos = p1_pos->next;
		i++;
	}
	i = 0;
	fscanf(f, "%*27c%i\n", &start);
	while (i < start - 1)
	{
		p2_pos = p2_pos->next;
		i++;
	}
	i = 0;
	fclose(f);
	i = 0;
	j = 0;
	p1 = 0;
	p2 = 0;
	dice = make_dice(100);
	dice_position = *dice;
	while (p1 < 1000 && p2 < 1000)
	{
		moves = 0;
		j = 0;
		while (j < 3)
		{
			moves += dice_position->value;
			printf("roll %i\n", dice_position->value);
			dice_position = dice_position->next;
			j++;
		}
		p1_pos = board_forward(p1_pos, moves);
		p1 += p1_pos->value;
		printf("score p1: %i\n", p1);
		i += j;
		moves = 0;
		if (p1 >= 1000)
			break ;
		j = 0;
		while (j < 3)
		{
			moves += dice_position->value;
			printf("roll %i\n", dice_position->value);
			dice_position = dice_position->next;
			j++;
		}
		p2_pos = board_forward(p2_pos, moves);
		p2 += p2_pos->value;

		i += j;
	}
	printf("\np1: %i, p2: %i\nrolls: %i\n", p1, p2, i);
}

t_side	*board_forward(t_side *player_position, int value)
{
	int	i;
	i = 0;
	while (i < value)
	{	
		player_position = player_position->next;
		i++;
	}
	return (player_position);
}

t_side	**make_dice(int n)
{
	t_side	**dice;
	t_side	*aux;
	int		i;

	i = 1;
	aux = 0;
	dice = malloc(sizeof(t_side *));
	dice[0] = malloc(sizeof(t_side));
	dice[0]->value = 1;
	dice[0]->next = 0;
	aux = dice[0];
	while (i < n)
	{
		aux->next = new_side(i + 1);
		aux = aux->next;
		i++;
	}
	aux->next = *dice;
	return (dice);
}

t_side	*new_side(int value)
{
	t_side *new;

	new = malloc(sizeof(t_side));
	new->value = value;
	new->next = 0;
	return (new);
}
