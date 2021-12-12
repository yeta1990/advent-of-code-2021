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

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_chunk
{
	int				type;
	int				open;
	struct s_chunk	*next;
}	t_chunk;

void	add_back_chunk(t_chunk **chunks, int type);
int	close_last_chunk(t_chunk **chunks, int type);

int	main()
{
	char	open[5] = "([{<";
	char	close[5] = ")]}>";
	char	*line;
	FILE	*f;
	size_t	i;
	size_t	size;
	t_chunk	**chunks;
	int		values[5] = { 3, 57, 1197, 25137 };
	int		cl;
	long	score;

	i = 0;
	score = 0;
	chunks = malloc(sizeof(t_chunk *));
	chunks[0] = 0;
	f = fopen("input.txt", "r");
	line = 0;
	cl = 0;
	while (getline(&line, &size, f) != -1)
	{
		i = 0;
		size = strlen(line);
		while (i < size)
		{
			if (strrchr(open, line[i]))
			{
				add_back_chunk(chunks, strrchr(open, line[i]) - open);
				printf("%c", line[i]);
			}
			else if (strrchr(close, line[i]))
			{
				printf("%c", line[i]);
				cl = (close_last_chunk(chunks, strrchr(close, line[i]) - close));
				if (cl != 100)
				{
					printf("got %c", close[cl]);
					score += values[cl];
					printf(", sum %i", values[cl]);
					break ;
				}
			}
			i++;
		}
		printf("\n");
	}
	fclose(f);
	printf("score: %li\n", score);
}

int	close_last_chunk(t_chunk **chunks, int type)
{
	t_chunk	*aux;
	t_chunk *aux2;

	aux = *chunks;
	aux2 = 0;
	while (aux->next)
	{
		aux2 = aux;
		aux = aux->next;
	}
	if (aux->type == type)
	{
		aux2->next = aux->next;
		free(aux);
		aux = aux2;
		aux->open = 0;
		return (100);
	}
	else
	{
		printf(" expected-> %i, ", aux->type);
		return (type);
	}
}

void	add_back_chunk(t_chunk **chunks, int type)
{
	t_chunk	*aux;
	t_chunk *new_chunk;

	aux = 0;
	new_chunk = malloc(sizeof(t_chunk));
	new_chunk->type = type;
	new_chunk->open = 1;
	new_chunk->next = 0;
	if (!*chunks)
	{
		*chunks = new_chunk;
		return ;
	}
	aux = *chunks;
	while (aux->next)
		aux = aux->next;
	aux->next = new_chunk;
}
