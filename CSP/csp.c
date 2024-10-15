#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 50

int graph[MAX_NODES][MAX_NODES];
int colors[MAX_NODES];
int nodes, edges, color;

bool safe(int node, int currentColor) {
    for (int i = 0; i < nodes; i++) {
        if (graph[node][i] && currentColor == colors[i]) {
            return false;
        }
    }

    return true;
}

bool graphColor(int node) {
    if (node == nodes) {
        return true;
    }

    for (int i = 1; i <= color; i++) {
        if (safe(node, i)) {
            colors[node] = i;

            if (graphColor(node + 1)) {
                return true;
            }

            colors[node] = -1;
        }
    }

    return false;
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    while (nodes > MAX_NODES) {
        printf("Number of nodes should not exceed %d. \nEnter again: ", MAX_NODES);
        scanf("%d", &nodes);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the number of colors allowed: ");
    scanf("%d", &color);

    printf("Enter the edges: \n");
    for (int i = 0; i < edges; i++) {
        printf("Edge %d: ", i + 1);
        
        int node1, node2;
        scanf("%d %d", &node1, &node2);
        
        graph[node1][node2] = true;
        graph[node2][node1] = true;
    }

    for (int i = 0; i < nodes; i++) {
        colors[i] = -1;
    }

    if (graphColor(0)) {
        printf("A solution exist! \n");
        for (int i = 0; i < nodes; i++) {
            printf("Color of node %d: %d \n", i, colors[i]);
        }
    }
    else {
        printf("A solution does not exist with given input! \n");
    }

    return 1;
}