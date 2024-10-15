#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

int queue[MAX_VERTICES];
int front = -1, rear = -1;

bool graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int vertices;

void initGraph(int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; i++)
        {
            graph[i][j] = false;
        }
        visited[i] = false;
    }
}

void addEdge(int src, int dest) {
    graph[src][dest] = true;
    graph[dest][src] = true;
}

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return rear == MAX_VERTICES - 1;
}

void enque(int val) {
    if (!isFull()) {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = val;
    }
    else
        printf("Queue is full!\n");
}

int deque() {
    if (!isEmpty()) {
        int ans = queue[front];
        front++;
        if (front > rear) {
            front = rear = -1;
        }
        return ans;
    }

    printf("Queue is empty!");
    return -1;
}

void bfs(int edges, int start) {
    enque(start);
    visited[start] = true;
    printf("BFS: ");

    while (!isEmpty()) {
        int current = deque();
        printf("%d ", current);

        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && graph[current][i]) {
                enque(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    printf("Enter the number of vertices/nodes: ");
    scanf("%d", &vertices);

    initGraph(vertices);

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        int src, dest;
        printf("Enter the source and destination for edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        addEdge(src, dest);
    }

    int start;
    printf("Enter the starting node: ");
    scanf("%d\n", &start);

    bfs(edges, start);
    printf("/n");
}