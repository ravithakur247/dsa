#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;

} Node;

typedef struct Graph
{
    int vertices;
    Node **adjlist;

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

    for (int i = 0; i < vertices; ++i)
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
    // Node *src_node = create_node(src);
    // src_node->next = graph->adjlist[src];
    // graph->adjlist[src] = src_node;
}

void print_graph(Graph *graph)
{
    for (int vertex = 0; vertex < graph->vertices; ++vertex)
    {
        printf("vertex %d", vertex);

        Node *node = graph->adjlist[vertex];

        while (node)
        {
            printf("-> %d", node->vertex);
            node = node->next;
        }
        printf("\n");
    }
}

void free_graph(Graph *graph)
{
    if (!graph)
        return;

    for (int vertex = 0; vertex < graph->vertices; ++vertex)
    {
        Node *node = graph->adjlist[vertex];

        while (node)
        {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->adjlist);
    free(graph);
}

static void dfs_helper(int src, Graph *graph, int *visited)
{
    visited[src] = 1;
    printf("%d-----", src);
    Node *temp = graph->adjlist[src];
    while (temp)
    {
        if (!visited[temp->vertex])
        {
            dfs_helper(temp->vertex, graph, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph *graph)
{
    int *visited = calloc(graph->vertices, sizeof(*visited));
    int components = 0;
    for (int i = 0; i < graph->vertices; ++i)
    {
        if (!visited[i])
        {
            dfs_helper(i, graph, visited);
            components++;
        }
    }

    printf("\ncomponents in graphs %d \n", components);
    free(visited);
}

void bfs(Graph *graph)
{
    int f = 0, r = 0;
    int *visited = calloc(graph->vertices, sizeof(*visited));
    int *queue = malloc(graph->vertices * sizeof(*queue));

    queue[r++] = 0;
    visited[0] = 1;

    while (f < r)
    {
        int curr = queue[f++];
        printf("%d----", curr);
        Node *temp = graph->adjlist[curr];
        while (temp)
        {
            int v = temp->vertex;
            if (!visited[v])
            {
                visited[v] = 1;
                queue[r++] = v;
            }
            temp = temp->next;
        }
    }
    free(queue);
    free(visited);
}

int main()
{
    Graph *g = create_graph(9);
    // Node 0 has neighbors 1 and 2
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);

    // Other connections
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);

    add_edge(g, 2, 5);
    add_edge(g, 2, 6);

    add_edge(g, 3, 7);
    add_edge(g, 4, 7);

    add_edge(g, 5, 8);
    add_edge(g, 6, 8);

    add_edge(g, 7, 9);
    add_edge(g, 8, 9);

    print_graph(g);
    // dfs(g);
    bfs(g);
    free_graph(g);

    ///////
    // Graph *g1 = create_graph(9);
    // add_edge(g1, 0, 1);
    // add_edge(g1, 0, 2);
    // add_edge(g1, 1, 3);
    // add_edge(g1, 1, 4);

    // // Component 2: Cycle
    // add_edge(g1, 5, 6);
    // add_edge(g1, 6, 7);
    // add_edge(g1, 7, 5);

    // // Component 3: Single chain (just one edge)
    // add_edge(g1, 8, 8); // or leave 8 disconnected if self-loops not allowed

    // // Component 4: Isolated node
    // // Node 9 has no edges
    // print_graph(g1);
    // dfs(g1);
    // free_graph(g1);
}