#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

int stack[MAX_VERTICES];
int top = -1;

bool graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int vertices;
bool found = false;

void initGraph(int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; i++) {
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
    return top == -1;
}

bool isFull() {
    return top == MAX_VERTICES - 1;
}

void push(int val) {
    if(!isFull()) {
        stack[++top] = val;
    }
    else {
        printf("Stack is full!\n");
    }
}

int pop() {
    if(!isEmpty()) {
        int temp = stack[top--];
        return temp;
    }
    printf("Stack is empty!\n");
    return -1;
}

int peek() {
    if(!isEmpty()) {
        return stack[top];
    }
    printf("Stack is empty! \n");
    return -1;
}


// void dfs(int start) {
//     push(start);

//     while(!isEmpty()) {
//         int current = pop();

//         if(!visited[current]) {
//             visited[current] = true;
//             printf("%d ", current);

//             for (int i = 0; i < vertices; i++) {
//                 if(!visited[i] && graph[current][i]) {
//                     push(i);
//                 }
//             }
//         }
//     }
// }

// recursive
void dfs(int start, int goal) {
    if(found) {
        return;
    }
    visited[start] = true;
    printf("%d ", start);

    if(start == goal) {
        found = true;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        if(!visited[i] && graph[start][i]) {
            dfs(i, goal);
            if(found) {
                return;
            }
        }
    }
}

int main() {
    printf("Enter the number of vertices/nodes: ");
    scanf("%d", &vertices);

    // initGraph(vertices);

    printf("debug");

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        int src, dest;
        printf("Enter the source and destination for edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        addEdge(src, dest);
    }

    int start, goal;
    printf("Enter the starting node: ");
    scanf("%d", &start);

    printf("Enter the goal node: ");
    scanf("%d", &goal);

    dfs(start, goal);
    printf("\n");
}