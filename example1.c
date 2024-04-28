#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int nr_restaurante;
    int *visited;
    Node **adjacency_list;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *arr;
    int *visited;
} Stack;

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = new_node;
}

Graph *create_graph(int nr_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    graph->nr_restaurante = nr_vertices;
    graph->adjacency_list = malloc(sizeof(Node *) * nr_vertices);
    graph->visited = malloc(sizeof(int) * nr_vertices);
    if (graph->adjacency_list == NULL || graph->visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nr_vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->arr = malloc(capacity * sizeof(int));
    stack->visited = malloc(capacity * sizeof(int));
    if (stack->arr == NULL || stack->visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(int pushed, Stack *stack) {
    stack->top++;
    stack->arr[stack->top] = pushed;
}

void DFS(Graph *graph, Stack *stack, int restaurant_nr) {
    Node *adj_list = graph->adjacency_list[restaurant_nr];
    Node *aux = adj_list;
    stack->visited[restaurant_nr] = 1;
    printf("%d ", restaurant_nr);
    push(restaurant_nr, stack);
    while (aux != NULL) {
        int connected_restaurant = aux->data;
        if (!stack->visited[connected_restaurant])
            DFS(graph, stack, connected_restaurant);
        aux = aux->next;
    }
}

void insert_edges(Graph *graph, int num_edges, int num_vertices) {
    int src, dest;
    printf("Introduceti %d conexiuni (de la 0 la %d)\n", num_edges, num_vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        do {
            printf("Conexiunea %d (de la 0 la %d): ", i + 1, num_vertices - 1);
            scanf("%d", &src);
        } while (src < 0 || src >= num_vertices);
        do {
            printf("cu (de la 0 la %d): ", num_vertices - 1);
            scanf("%d", &dest);
        } while (dest < 0 || dest >= num_vertices);
        add_edge(graph, src, dest);
    }
}

void clear_visited(Graph *graph, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        graph->visited[i] = 0;
    }
}

int can_reach(Graph *graph, int num_vertices, Stack *stack1, Stack *stack2) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (i != j) {
                clear_visited(graph, num_vertices);
                DFS(graph, stack1, i);
                if (graph->visited[j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


int main() {
    int num_vertices;
    int num_edges;
    int found_direct_path;

    printf("Cate restaurante are reteaua? ");
    scanf("%d", &num_vertices);

    printf("Cate conexiuni are reteaua? ");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);
    Stack *stack1 = create_stack(2 * num_vertices);
    Stack *stack2 = create_stack(2 * num_vertices);

    insert_edges(graph, num_edges, num_vertices);

    found_direct_path = can_reach(graph, num_vertices, stack1, stack2);

    if (found_direct_path) {
        printf("\nExista drum direct intre doua restaurante.\n");
    } else {
        printf("\nNu exista drum direct intre doua restaurante.\n");
    }

    free(stack1->arr);
    free(stack1->visited);
    free(stack1);
    free(stack2->arr);
    free(stack2->visited);
    free(stack2);
    for (int i = 0; i < num_vertices; i++) {
        Node *curr = graph->adjacency_list[i];
        while (curr != NULL) {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjacency_list);
    free(graph->visited);
    free(graph);

    return 0;
}
