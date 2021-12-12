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

typedef struct s_line
{
	long long		score;
	char			*incomplete;
	struct s_line	*next;
}	t_line;

void	add_back_chunk(t_chunk **chunks, int type);
int		close_last_chunk(t_chunk **chunks, int type);
int		close_last_chunk_2(t_chunk **chunks, int type);
void	add_incomplete_line(t_line **lines, char *line);
int		complete_last_chunk(t_chunk **chunks);
void	complete_line(t_line *line, char *open, char *close);

int	main()
{
	char	open[5] = "([{<\0";
	char	close[5] = ")]}>\0";
	char	*line;
	FILE	*f;
	size_t	i;
	size_t	size;
	t_chunk	**chunks;
	t_line	**lines;
	int		cl;

	i = 0;
	chunks = malloc(sizeof(t_chunk *));
	chunks[0] = 0;
	lines = malloc(sizeof(t_line *));
	lines[0] = 0;
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
				add_back_chunk(chunks, strrchr(open, line[i]) - open);
			else if (strrchr(close, line[i]))
			{
				cl = (close_last_chunk(chunks, strrchr(close, line[i]) - close));
				if (cl != 100)
					break ;
			}
			i++;
		}
		if (i == size)
			add_incomplete_line(lines, line);
	}
	fclose(f);
	t_line *aux;
	aux = *lines;
	while (aux)
	{
		complete_line(aux, open, close);
		printf("%lli\n", aux->score);
		aux = aux->next;
	}
}

void	complete_line(t_line *line, char *open, char *close)
{
	t_chunk **chunks;
	size_t		i;
	size_t	size;
	int		added_type;
	t_chunk	*aux;

	chunks = malloc(sizeof(t_chunk *));
	chunks[0] = 0;
	i = 0;
	size = strlen(line->incomplete);
	added_type = 0;
	while (i < size)
	{
		if (strrchr(open, line->incomplete[i]))
			add_back_chunk(chunks, strrchr(open, line->incomplete[i]) - open);
		else if (strrchr(close, line->incomplete[i]))
			close_last_chunk_2(chunks, strrchr(close, line->incomplete[i]) - close);
		i++;
	}
	aux = *chunks;
	while ((added_type = complete_last_chunk(chunks)) > 0)
		line->score = line->score * 5 + added_type;
}

void	add_incomplete_line(t_line **lines, char *line)
{
	t_line	*aux;
	t_line *new_line;

	aux = 0;
	new_line = malloc(sizeof(t_line));
	new_line->incomplete = strdup(line);
	new_line->score = 0;
	new_line->next = 0;
	if (!*lines)
	{
		*lines = new_line;
		return ;
	}
	aux = *lines;
	while (aux->next)
		aux = aux->next;
	aux->next = new_line;
}

int	complete_last_chunk(t_chunk **chunks)
{
	t_chunk	*aux;
	t_chunk *aux2;
	int		type;

	type = 0;
	aux = *chunks;
	aux2 = 0;
	if (!*chunks)
		return (-1);
	while (aux->next)
	{
		aux2 = aux;
		aux = aux->next;
	}
	if (aux && aux2)
	{
		type = aux->type + 1;
		aux2->next = aux->next;
		free(aux);
		aux = aux2;
		aux->open = 0;
	}
	else if (aux)
	{
		type = aux->type + 1;
		*chunks = 0;
		free(aux);
	}
	return (type);
}

int	close_last_chunk_2(t_chunk **chunks, int type)
{
	t_chunk	*aux;
	t_chunk *aux2;

	aux = *chunks;
	aux2 = 0;
	if (!*chunks || !chunks)
		return (-1);
	while (aux && aux->next)
	{
		aux2 = aux;
		aux = aux->next;
	}
	if (aux->type == type)
	{
		if (aux2 && aux)
		{
			aux2->next = aux->next;
			free(aux);
			aux = aux2;
			aux->open = 0;
		}
		else if (aux)
		{
			*chunks = 0;
			free(aux);
		}
		return (100);
	}
	else
		return (type);
}


int	close_last_chunk(t_chunk **chunks, int type)
{
	t_chunk	*aux;
	t_chunk *aux2;

	aux = *chunks;
	aux2 = 0;
	if (!*chunks || !chunks)
		return (-1);
	while (aux && aux->next)
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
		return (type);
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
