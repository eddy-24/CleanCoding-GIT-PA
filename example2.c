#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int num_vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

Node *create_node(int v)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int num_vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    graph->num_vertices = num_vertices;
    graph->adjacency_lists = malloc(num_vertices * sizeof(Node *));
    graph->visited = malloc(sizeof(int) * num_vertices);

    for (int i = 0; i < num_vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph *graph, int src, int dest)
{
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

int insert_edges(int num_vertices, int num_edges, Graph *graph)
{
    int src, dest, i;
    printf("Adauga %d muchii (de la 0 la %d)\n", num_edges, num_vertices - 1);
    for (i = 0; i < num_edges; i++)
    {
        printf("Muchia %d: ", i + 1);
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_queue_empty(Node *queue)
{
    return queue == NULL;
}

void enqueue(Node **queue, int data)
{
    Node *new_node = create_node(data);

    if (is_queue_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        Node *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue)
{
    int data = (*queue)->vertex;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(Graph *graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        Node *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void wipe_visited_list(Graph *graph, int num_vertices)
{
    for (int i = 0; i < num_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// Traversal algorithms
void DFS(Graph *graph, int vertex)
{
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL)
    {
        int connected_vertex = temp->vertex;
        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start)
{
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_queue_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->vertex;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int num_vertices, num_edges, src, dest;
    int starting_vertex;

    printf("Cate noduri are graful?");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful?");
    scanf("%d", &num_edges);
    Graph *graph = create_graph(num_vertices);

    insert_edges(num_vertices, num_edges, graph);

    printf("De unde plecam in DFS?");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS:");
    DFS(graph, starting_vertex);
    printf("\n");

    wipe_visited_list(graph, num_vertices);

    printf("De unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS:");
    BFS(graph, starting_vertex);
    return 0;
}
