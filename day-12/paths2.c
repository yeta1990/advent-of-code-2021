#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_edge
{
	char	node1[10];
	char	node2[10];
	struct s_edge	*next;
}	t_edge;

typedef struct s_node
{
	char			*name;
	struct s_node	*next;
}	t_node;

void	add_edge(t_edge **edge, char line[30]);
int		count_nodes(t_edge **edges);
void	add_node(t_node **nodes, char node_name[10]);
t_node **separate_nodes(t_edge **edges);
char	*get_node_name(t_node **nodes, int pos);
int		**create_matrix(t_node **nodes, t_edge **edges, int	n_nodes);
int		get_node_position(t_node **nodes, char *name);
int		get_num_nodes(t_node **nodes);
void	find_paths(int **matrix, t_node **nodes, int num_nodes);
void	continue_path(int **matrix, t_node **nodes, t_node **path, int num_nodes, int next_step, int *j, int start_col);
void	add_to_path(t_node **path, char *name);
int		check_path(t_node **path, int current, char	*next, t_node **nodes);
void	print_path(t_node **path);
void	remove_last(t_node **path, int end);
int		get_last_node_pos(t_node **path, t_node **nodes);

int	main(void)
{
	FILE	*f;
	t_edge	**edges;
	char	line[30] = {0};
	t_edge	*aux;
	t_node	**nodes;
	int		**matrix;
	int		num_nodes;

	matrix = 0;
	nodes = 0;
	f = fopen("input", "r");
	edges = malloc(sizeof(t_edge *));
	edges[0] = 0;
	while (fscanf(f, "%20[^\n]\n", line) != -1)
	{
		printf("%s\n", line);
		add_edge(edges, line);
		bzero(line, 30);
	}
	printf("\n---------\n\n");
	aux = *edges;
	nodes = separate_nodes(edges);
	num_nodes = get_num_nodes(nodes);
	matrix = create_matrix(nodes, edges, num_nodes);
	find_paths(matrix, nodes, num_nodes);
	fclose(f);
}

void	find_paths(int **matrix, t_node **nodes, int num_nodes)
{
	int	i;
	int	j;
	t_node	**path;

	path = malloc(sizeof(t_node *));
	path[0] = 0;
	j = 0;
	i = 0;
	path[0] = malloc(sizeof(path));
	path[0] = 0;
	add_to_path(path, "start");
	while (i < num_nodes - 1)
	{
		if (matrix[0][i] == 1)
		{
			add_to_path(path, get_node_name(nodes, i));
			printf("\n1. %i: %s\n", i, get_node_name(nodes, i));
			continue_path(matrix, nodes, path, num_nodes, i, &j, 1);
		}
		i++;
	}
}

void	continue_path(int **matrix, t_node **nodes, t_node **path, int num_nodes, int next_step, int *j, int start_col)
{
	int	i;
	int	final_next_pos;
	int	some_coinc;

	some_coinc = 0;
	final_next_pos = 0;
	i = start_col;
	if (next_step == num_nodes - 1)
	{
		printf("\nfinal: ");
		print_path(path);
		remove_last(path, 1);
		final_next_pos = get_last_node_pos(path, nodes);
		remove_last(path, 1);
		continue_path(matrix, nodes, path, num_nodes, get_last_node_pos(path, nodes), j, final_next_pos + 1);
		return ;
	}
	while (i < num_nodes)  
	{
		if (matrix[next_step][i] == 1)
		{
			some_coinc = 1;
			if (check_path(path, next_step, get_node_name(nodes, i), nodes))
			{
				add_to_path(path, get_node_name(nodes, i));
				continue_path(matrix, nodes, path, num_nodes, i, j, 1);
			}
			else
			{
				continue_path(matrix, nodes, path, num_nodes, next_step, j, i + 1);
			}
		}
		i++;
	}
	if (some_coinc == 0)
	{
		if (next_step == 0)
			exit(0);
		final_next_pos = get_last_node_pos(path, nodes);
		if (final_next_pos == next_step)
		{
			remove_last(path, 1);
			continue_path(matrix, nodes, path, num_nodes, get_last_node_pos(path, nodes), j, next_step + 1);
		}
		else
			continue_path(matrix, nodes, path, num_nodes, get_last_node_pos(path, nodes), j, next_step + 1);
	}
}

void	remove_last(t_node **path, int end)
{
	t_node *aux;
	t_node *aux_1;

	aux = *path;
	if (!aux)
		return ;
	while (aux->next)
	{
		aux_1 = aux;
		aux = aux->next;
	}
	if (aux->name[0] >= 97 && strcmp(aux->name, "end") != 0 && end == 0)
	{
		bzero(aux->name, strlen(aux->name));
		free(aux_1->next);
		aux_1->next = 0;
	}
	else if (end == 1)
	{
		bzero(aux->name, strlen(aux->name));
		free(aux_1->next);
		aux_1->next = 0;
	}

}

int	check_path(t_node **path, int current, char	*next, t_node **nodes)
{
	t_node	*aux;
	t_node	*aux_2;
	int		repeated;

	repeated = 0;
	aux = *path;
	aux_2 = *path;
	if (get_num_nodes(path) <= 1)
		return (1);
	while (aux)
	{
		aux_2 = aux->next;
		while (aux_2)
		{
			if (aux_2->name[0] >= 'a' && aux->name[0] >= 'a' && strcmp(aux_2->name, aux->name) == 0)
				repeated = 1;
			aux_2 = aux_2->next;
		}
		aux = aux->next;
	}
	aux = *path;
	while (aux)
	{
		if (next[0] >= 'a' && strcmp(next, aux->name) == 0 && repeated == 0)
			repeated = 1;
		else if (next[0] >= 'a' && strcmp(next, aux->name) == 0 && repeated == 1)
			return (0);
		aux = aux->next;
	}
	return (1);
}

void	print_path(t_node **path)
{
	t_node	*aux;
	aux = *path;
	printf("path: ");
	while (aux)
	{
		printf("%s,", aux->name);
		aux = aux->next;
	}
	printf("\n");
}


void	add_to_path(t_node **path, char *name)
{
	t_node	*aux;
	t_node	*new;

	aux = *path;
	new = malloc(sizeof(t_node));
	new->name = strdup(name);
	new->next = 0;
	if (!aux)
	{
		*path = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

int	get_num_nodes(t_node **nodes)
{
	t_node	*aux_nodes;
	int		n_nodes;

	n_nodes = 0;
	aux_nodes = *nodes;
	while (aux_nodes)
	{
		aux_nodes = aux_nodes->next;
		n_nodes++;
	}
	return (n_nodes);
}

int	**create_matrix(t_node **nodes, t_edge **edges, int	n_nodes)
{
	int		**matrix;
	int		i;
	int		j;
	t_edge	*edge_aux;
	char	*node_name;

	node_name = 0;
	i = 0;
	j = 0;
	matrix = 0;
	edge_aux = *edges;
	matrix = malloc(sizeof(int *) * n_nodes);
	while (i < n_nodes)
	{
		matrix[i] = malloc(sizeof(int) * n_nodes);
		i++;
	}
	i = 0;
	while (i < n_nodes)
	{
		j = 0;
		while (j < n_nodes)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < n_nodes)
	{
		edge_aux = *edges;
		node_name = get_node_name(nodes, i);
		while (edge_aux)
		{
			if (strcmp(edge_aux->node1, node_name) == 0)
				matrix[i][get_node_position(nodes, edge_aux->node2)] = 1;
			else if (strcmp(edge_aux->node2, node_name) == 0)
				matrix[i][get_node_position(nodes, edge_aux->node1)] = 1;
			edge_aux = edge_aux->next;
		}
		i++;
	}
	i = 0;
	while (i < n_nodes)
	{
		j = 0;
		printf("%s\t", get_node_name(nodes, i));
		while (j < n_nodes)
		{
			printf("%i ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (matrix);
}

int	get_last_node_pos(t_node **path, t_node **nodes)
{
	t_node	*aux;

	aux = *path;
	while (aux->next)
		aux = aux->next;
	return (get_node_position(nodes, aux->name));
}

int	get_node_position(t_node **nodes, char *name)
{
	int		i;
	t_node	*aux;

	i = 0;
	aux = *nodes;
	while (aux && name)
	{
		if (strcmp(aux->name, name) == 0)
			return (i);
		i++;
		aux = aux->next;
	}
	return (i);
}

char	*get_node_name(t_node **nodes, int pos)
{
	int	i;
	t_node	*aux;

	aux = *nodes;
	i = 0;
	while (i < pos)
	{
		aux = aux->next;
		i++;
	}
	return (aux->name);
}

t_node **separate_nodes(t_edge **edges)
{
	int		count;
	t_edge	*aux;
	t_node	**nodes;
	t_node	*node_aux;

	nodes = malloc(sizeof(t_node *));
	nodes[0] = 0;
	node_aux = *nodes;
	count = 0;
	aux = *edges;
	add_node(nodes, aux->node1);
	while(aux)
	{
		node_aux = *nodes;
		while (node_aux)
		{
			if (strcmp(aux->node1, node_aux->name) == 0)
				break ;
			node_aux = node_aux->next;
		}
		if (aux && !node_aux)
			add_node(nodes, aux->node1);
		node_aux = *nodes;
		while (node_aux)
		{
			if (strcmp(aux->node2, node_aux->name) == 0)
				break ;
			node_aux = node_aux->next;
		}
		if (aux && !node_aux)
			add_node(nodes, aux->node2);
		aux = aux->next;
	}
	return (nodes);
}

void	add_node(t_node **nodes, char node_name[10])
{
	t_node	*new;
	t_node	*aux;

	aux = 0;
	new = malloc(sizeof(t_node));
	new->next = 0;
	new->name = strdup(node_name);
	if (!(*nodes))
		*nodes = new;
	else
	{
		if (strcmp((*nodes)->name, "start") == 0)
		{
			if ((*nodes)->next)
			{
				new->next = (*nodes)->next;
				(*nodes)->next = new;
			}
			else
				(*nodes)->next = new;
		}
		else if (strcmp(new->name, "start") == 0)
		{
			new->next = *nodes;
			*nodes = new;
		}
		else if (strcmp(new->name, "end") == 0)
		{
			aux = *nodes;
			while (aux->next)
				aux = aux->next;
			aux->next = new;
		}
		else
		{
			new->next = *nodes;
			*nodes = new;
		}
	}
}

void	add_edge(t_edge **edge, char line[30])
{
	t_edge	*new;

	new = malloc(sizeof(t_edge));
	bzero(new->node1, 10);
	bzero(new->node2, 10);
	new->next = 0;
	sscanf(line, "%[^-]-%s", new->node1, new->node2);
	if (!(*edge))
		*edge = new;
	else
	{
		new->next = *edge;
		*edge = new;
	}
}
