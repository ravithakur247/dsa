#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int vertex;
    Node *next;

} Node;

typedef struct
{
    int vertices;
    int **adjlist;

} Graph;

Node *create_node(int vertex)
{
    Node *new_node = malloc(sizeof(*new_node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int vertices)
{
    Graph *new_graph = malloc(sizeof(*new_graph));
    new_graph->vertices = vertices;

    new_graph->adjlist = malloc(vertices * sizeof(Node *));

    for (size_t i = 0; i < vertices; ++i)
    {
        new_graph->adjlist[i] = NULL;
    }
    return new_graph;
}

void add_edge(Graph *graph, int src, int dest)
{
    Node *dest_node = create_node(dest);
    dest_node->next = graph->adjlist[src];
    graph->adjlist[src] = dest_node;

    // unidirected
    Node *src_node = create_node(src);
    src_node->next = graph->adjlist[src];
    graph->adjlist[src] = src_node;
}

void print_graph(Graph *graph)
{
    for (size_t vertex = 0; vertex < graph->vertices; ++vertex)
    {
        printf("vertex %d", vertex);

        Node *node = graph->adjlist[vertex];

        while (node)
        {
            printf("-> %d", node->vertex);
            node = node->next;
        }
    }
}

int main()
{
    Graph *g = create_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 2, 4);
    add_edge(g, 3, 2);
}