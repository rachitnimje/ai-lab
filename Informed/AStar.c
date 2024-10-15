#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 50
// A* is specific implementation of Best-FS where we always get the most optimal path possible
/* Example
nodes: 6, connections: 8
heuristics: 10 8 7 3 2 0
connections:
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1
3 5 5
4 5 2
output: 0 1 2 4 5
most optimal solution
*/

// define struct for node
typedef struct {
    int node;
    int f_score;        // f_score = heuristic value of node + cost of path from start
} Node;

int graph[MAX_NODES][MAX_NODES];
int heuristics[MAX_NODES];
int numNodes;

void a_star(int start, int goal) {
    // define PQ
    Node* pq[MAX_NODES];
    int pqSize = 0;

    // define visited, parent, cost to keep track
    bool visited[MAX_NODES] = { false };
    int parent[MAX_NODES];
    int cost[MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        parent[i] = -1;
        cost[i] = INT_MAX;
    }

    cost[start] = 0;

    Node* startNode = malloc(sizeof(Node));
    startNode->node = start;
    startNode->f_score = heuristics[start];

    pq[pqSize++] = startNode;

    while (pqSize > 0) {
        // take out the node with lowest value
        int minIndex = 0;
        for (int i = 1; i < pqSize; i++) {
            if (pq[i]->f_score < pq[minIndex]->f_score) {
                minIndex = i;
            }
        }

        Node* current = pq[minIndex];
        pq[minIndex] = pq[--pqSize];

        // if the node is visited, continue
        if (visited[current->node]) {
            free(current);
            continue;
        }

        // set the current node as visited
        visited[current->node] = true;

        // if the node is goal, print the path and path cost
        if (current->node == goal) {
            printf("Goal node found! \nPath: ");

            int path[MAX_NODES], pathLen = 0;

            for (int i = goal; i != -1; i = parent[i]) {
                path[pathLen++] = i;
            }

            for (int i = pathLen - 1; i >= 0; i--) {
                printf("%d ", path[i]);
            }

            printf("\nCost: %d \n", cost[goal]);

            free(current);
            return;
        }

        // put the adjacent nodes into PQ
        for (int i = 0; i < numNodes; i++) {
            if (graph[current->node][i] > 0 && !visited[i]) {
                int adjNodePathCost = cost[current->node] + graph[current->node][i];

                if (adjNodePathCost < cost[i]) {
                    // calc path cost of node
                    cost[i] = adjNodePathCost;
                    parent[i] = current->node;

                    // create a new node and add into PQ
                    Node* adjNode = malloc(sizeof(Node));
                    adjNode->node = i;
                    adjNode->f_score = cost[i] + heuristics[i];
                    pq[pqSize++] = adjNode;
                }
            }
        }

        free(current);
    }

    printf("Goal is not reachable! \n");
}

int main() {
    int numConn;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the number of connections: ");
    scanf("%d", &numConn);

    printf("Enter the heuristics of each node: ");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &heuristics[i]);
    }

    printf("\nEnter connections (from, to, weight): \n");
    for (int i = 0; i < numConn; i++) {
        int node1, node2, weight;
        scanf("%d %d %d", &node1, &node2, &weight);

        graph[node1][node2] = graph[node2][node1] = weight;
    }

    int start, goal;
    printf("Enter the start and goal node: ");
    scanf("%d %d", &start, &goal);

    a_star(start, goal);

    return 0;
}