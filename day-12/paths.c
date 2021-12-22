#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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

void	add_edge(t_edge **edge, char line[20]);
int		count_nodes(t_edge **edges);
void	add_node(t_node **nodes, char node_name[10]);
t_node **separate_nodes(t_edge **edges);
char	*get_node_name(t_node **nodes, int pos);
void	create_matrix(t_node **nodes, t_edge **edges);
int		get_node_position(t_node **nodes, char *name);

int	main(void)
{
	FILE	*f;
	t_edge	**edges;
	char	line[20] = {0};
	t_edge	*aux;
	t_node	**nodes;

	nodes = 0;
	f = fopen("ex", "r");
	edges = malloc(sizeof(t_edge *));
	edges[0] = 0;
	while (fscanf(f, "%20[^\n]\n", line) != -1)
	{
		printf("%s\n", line);
		add_edge(edges, line);
		bzero(line, 20);
	}
	printf("\n---------\n\n");
	aux = *edges;
	nodes = separate_nodes(edges);
	create_matrix(nodes, edges);
	fclose(f);
}

void	create_matrix(t_node **nodes, t_edge **edges)
{
	int		**matrix;
	int		n_nodes;
	t_node	*aux_nodes;
	int		i;
	int		j;
	t_edge	*edge_aux;
	char	*node_name;

	node_name = 0;
	i = 0;
	j = 0;
	n_nodes = 0;
	matrix = 0;
	aux_nodes = *nodes;
	edge_aux = *edges;
	while (aux_nodes)
	{
		aux_nodes = aux_nodes->next;
		n_nodes++;
	}
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
}

int	get_node_position(t_node **nodes, char *name)
{
	int		i;
	t_node	*aux;

	i = 0;
	aux = *nodes;
	while (aux)
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
//	printf("added %s\n", new->name);
}

void	add_edge(t_edge **edge, char line[20])
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
