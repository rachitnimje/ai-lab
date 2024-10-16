// Example 1:
// Nodes 10
// 0 5
// 1 4
// 2 2
// 3 3
// 4 6
// 5 8
// 6 2
// 7 0
// 8 0
// 9 0
// Connections 9
// 0 1 1 0
// 0 2 1 1
// 0 3 1 1
// 1 4 1 0
// 1 5 1 0
// 2 6 1 0
// 2 7 1 1
// 2 8 1 1
// 3 9 1 0
// OUTPUT: 0 2 7 8 3 9

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 50

typedef struct Node {
    int id;
    int heuristic;
    int expanded;
    int optimal;
    int num_children;
    int children[MAX_NODES];
    int type[MAX_NODES]; // 0 for OR, 1 for AND
    int cost[MAX_NODES];
} Node;

Node graph[MAX_NODES];
int num_nodes, num_connections;

void inputGraph() {
    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    printf("Enter node id and heuristics of each node:\n");
    for (int i = 0; i < num_nodes; i++) {
        graph[i].id = i;
        graph[i].expanded = 0;
        graph[i].optimal = 0;
        graph[i].num_children = 0;
        scanf("%d %d", &graph[i].id, &graph[i].heuristic);
    }

    printf("Enter the number of connections: ");
    scanf("%d", &num_connections);

    printf("Enter parent_id child_id cost AND/OR(1 for AND, 0 for OR):\n");
    for (int i = 0; i < num_connections; i++) {
        int parent, child, cost, type;
        scanf("%d %d %d %d", &parent, &child, &cost, &type);
        graph[parent].children[graph[parent].num_children] = child;
        graph[parent].cost[graph[parent].num_children] = cost;
        graph[parent].type[graph[parent].num_children] = type; // 1 for AND, 0 for OR
        graph[parent].num_children++;
    }
}

void aoStar(int node) {
    if (graph[node].expanded) {
        return;
    }

    graph[node].expanded = 1;

    int min_heuristic = INT_MAX;
    int selected_child = -1;

    for (int i = 0; i < graph[node].num_children; i++) {
        int child = graph[node].children[i];
        if (!graph[child].expanded) {
            aoStar(child); // Expand the child first
        }

        if (graph[node].type[i] == 0) { // OR connection
            int current_heuristic = graph[child].heuristic + graph[node].cost[i];
            if (current_heuristic < min_heuristic) {
                min_heuristic = current_heuristic;
                selected_child = i;
            }
        } else if (graph[node].type[i] == 1) { // AND connection
            int total_cost = 0;
            for (int j = 0; j < graph[node].num_children; j++) {
                if (graph[node].type[j] == 1) {
                    int sibling = graph[node].children[j];
                    total_cost += graph[sibling].heuristic + graph[node].cost[j];
                }
            }
            if (total_cost < min_heuristic) {
                min_heuristic = total_cost;
                selected_child = i;
            }
        }
    }

    if (min_heuristic != INT_MAX) {
        graph[node].heuristic = min_heuristic;
        graph[node].optimal = selected_child;
    }
}

void printOptimalPath(int node) {
    printf("%d ", node);
    if (graph[node].num_children == 0) {
        return; // It's a leaf node
    }

    int optimal_child = graph[node].optimal;
    if (graph[node].type[optimal_child] == 0) { // OR connection
        printOptimalPath(graph[node].children[optimal_child]);
    } else if (graph[node].type[optimal_child] == 1) { // AND connection
        for (int i = 0; i < graph[node].num_children; i++) {
            if (graph[node].type[i] == 1) {
                printOptimalPath(graph[node].children[i]);
            }
        }
    }
}

int main() {
    inputGraph();
    aoStar(0); // Start AO* from node 0 (root)

    printf("\nUpdated Heuristics:\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("Node %d: Heuristic = %d\n", i, graph[i].heuristic);
    }

    printf("\nOptimal Path: ");
    printOptimalPath(0);
    printf("\n");

    return 0;
}