// working for only AND or OR nodes
// example
// Enter the number of nodes : 7
// Enter node information (ID Heuristic):
// 0 5 1 4 2 3 3 2 4 1 5 0 6 0
// Enter the number of connections: 6
// Enter connections (Parent_ID Child_ID Cost Is_AND(1/0)):
// 0 1 1 0 0 2 2 0 1 3 3 1 1 4 4 1 2 5 5 1 2 6 6 1
// Enter the root node ID: 0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 50
#define MAX_CHILDREN 10

typedef struct Node {
    int id;
    bool is_and_node;
    int num_children;
    struct Node* children[MAX_CHILDREN];
    int cost[MAX_CHILDREN];
    int heuristic;
    int solution_cost;
    bool solved;
} Node;

Node nodes[MAX_NODES];
int num_nodes = 0;

Node* create_node(int id, bool is_and_node, int heuristic) {
    nodes[num_nodes].id = id;
    nodes[num_nodes].is_and_node = is_and_node;
    nodes[num_nodes].num_children = 0;
    nodes[num_nodes].heuristic = heuristic;
    nodes[num_nodes].solution_cost = INT_MAX;
    nodes[num_nodes].solved = false;
    return &nodes[num_nodes++];
}

void add_child(Node* parent, Node* child, int cost) {
    parent->children[parent->num_children] = child;
    parent->cost[parent->num_children] = cost;
    parent->num_children++;
}

void update_node(Node* node) {
    if (node->num_children == 0) {
        node->solution_cost = 0;
        node->solved = true;
        return;
    }

    if (node->is_and_node) {
        int total_cost = 0;
        bool all_solved = true;
        for (int i = 0; i < node->num_children; i++) {
            if (!node->children[i]->solved) {
                all_solved = false;
                break;
            }
            total_cost += node->cost[i] + node->children[i]->solution_cost;
        }
        if (all_solved) {
            node->solution_cost = total_cost;
            node->solved = true;
        } else {
            node->solution_cost = INT_MAX;
            node->solved = false;
        }
    } else {
        int min_cost = INT_MAX;
        for (int i = 0; i < node->num_children; i++) {
            int child_cost = node->cost[i] + node->children[i]->solution_cost;
            if (child_cost < min_cost) {
                min_cost = child_cost;
            }
        }
        node->solution_cost = min_cost;
        node->solved = (min_cost != INT_MAX);
    }
}

void ao_star(Node* root) {
    bool changed;
    do {
        changed = false;
        for (int i = num_nodes - 1; i >= 0; i--) {
            int old_cost = nodes[i].solution_cost;
            update_node(&nodes[i]);
            if (nodes[i].solution_cost != old_cost) {
                changed = true;
            }
        }
    } while (changed);
}

void print_solution(Node* node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("Node %d (%s): Cost = %d, Heuristic = %d\n", 
           node->id, 
           node->is_and_node ? "AND" : "OR", 
           node->solution_cost, 
           node->heuristic);

    if (node->is_and_node) {
        for (int i = 0; i < node->num_children; i++) {
            print_solution(node->children[i], depth + 1);
        }
    } else if (node->num_children > 0) {
        int best_child = 0;
        int min_cost = INT_MAX;
        for (int i = 0; i < node->num_children; i++) {
            int child_cost = node->cost[i] + node->children[i]->solution_cost;
            if (child_cost < min_cost) {
                min_cost = child_cost;
                best_child = i;
            }
        }
        print_solution(node->children[best_child], depth + 1);
    }
}

int main() {
    int num_nodes, num_connections;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    printf("Enter node information (ID Is_AND_node(0/1) Heuristic):\n");
    for (int i = 0; i < num_nodes; i++) {
        int id, is_and_node, heuristic;
        scanf("%d %d %d", &id, &is_and_node, &heuristic);
        create_node(id, is_and_node, heuristic);
    }

    printf("Enter the number of connections: ");
    scanf("%d", &num_connections);

    printf("Enter connections (Parent_ID Child_ID Cost):\n");
    for (int i = 0; i < num_connections; i++) {
        int parent_id, child_id, cost;
        scanf("%d %d %d", &parent_id, &child_id, &cost);
        add_child(&nodes[parent_id], &nodes[child_id], cost);
    }

    printf("Enter the root node ID: ");
    int root_id;
    scanf("%d", &root_id);

    ao_star(&nodes[root_id]);

    printf("\nAO* Solution:\n");
    print_solution(&nodes[root_id], 0);

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <limits.h>

// #define MAX_NODES 50
// #define MAX_CHILDREN 10

// typedef struct Node {
//     int id;
//     int num_children;
//     struct Node* children[MAX_CHILDREN];
//     bool child_type[MAX_CHILDREN];  // true for AND, false for OR
//     int cost[MAX_CHILDREN];
//     int heuristic;
//     int solution_cost;
//     bool solved;
// } Node;

// Node nodes[MAX_NODES];
// int num_nodes = 0;

// Node* create_node(int id, int heuristic) {
//     nodes[num_nodes].id = id;
//     nodes[num_nodes].num_children = 0;
//     nodes[num_nodes].heuristic = heuristic;
//     nodes[num_nodes].solution_cost = INT_MAX;
//     nodes[num_nodes].solved = false;
//     return &nodes[num_nodes++];
// }

// void add_child(Node* parent, Node* child, bool is_and_child, int cost) {
//     parent->children[parent->num_children] = child;
//     parent->child_type[parent->num_children] = is_and_child;
//     parent->cost[parent->num_children] = cost;
//     parent->num_children++;
// }

// void update_node(Node* node) {
//     if (node->num_children == 0) {
//         node->solution_cost = 0;
//         node->solved = true;
//         return;
//     }

//     int total_cost = 0;
//     bool all_solved = true;
//     int min_or_cost = INT_MAX;

//     for (int i = 0; i < node->num_children; i++) {
//         if (node->child_type[i]) {  // AND child
//             if (!node->children[i]->solved) {
//                 all_solved = false;
//             }
//             total_cost += node->cost[i] + node->children[i]->solution_cost;
//         } else {  // OR child
//             int child_cost = node->cost[i] + node->children[i]->solution_cost;
//             if (child_cost < min_or_cost) {
//                 min_or_cost = child_cost;
//                 if (node->children[i]->solved) {
//                     all_solved = true;
//                 } else {
//                     all_solved = false;
//                 }
//             }
//         }
//     }

//     if (node->num_children > 0 && !node->child_type[0]) {  // If it's an OR node
//         total_cost = min_or_cost;
//     }

//     if (all_solved) {
//         node->solution_cost = total_cost;
//         node->solved = true;
//     } else {
//         node->solution_cost = total_cost;
//         node->solved = false;
//     }
// }

// void ao_star(Node* root) {
//     bool changed;
//     do {
//         changed = false;
//         for (int i = num_nodes - 1; i >= 0; i--) {
//             int old_cost = nodes[i].solution_cost;
//             update_node(&nodes[i]);
//             if (nodes[i].solution_cost != old_cost) {
//                 changed = true;
//             }
//         }
//     } while (changed);
// }

// void print_solution(Node* node, int depth) {
//     for (int i = 0; i < depth; i++) printf("  ");
//     printf("Node %d: Cost = %d, Heuristic = %d\n", 
//            node->id, 
//            node->solution_cost, 
//            node->heuristic);

//     if (node->num_children == 0) return;  // Leaf node

//     if (node->child_type[0]) {  // AND node
//         for (int i = 0; i < node->num_children; i++) {
//             print_solution(node->children[i], depth + 1);
//         }
//     } else {  // OR node
//         int best_child = 0;
//         int min_cost = INT_MAX;
//         for (int i = 0; i < node->num_children; i++) {
//             int child_cost = node->cost[i] + node->children[i]->solution_cost;
//             if (child_cost < min_cost) {
//                 min_cost = child_cost;
//                 best_child = i;
//             }
//         }
//         print_solution(node->children[best_child], depth + 1);
//     }
// }

// int main() {
//     int num_nodes, num_connections;
    
//     printf("Enter the number of nodes: ");
//     scanf("%d", &num_nodes);

//     printf("Enter node information (ID Heuristic):\n");
//     for (int i = 0; i < num_nodes; i++) {
//         int id, heuristic;
//         scanf("%d %d", &id, &heuristic);
//         create_node(id, heuristic);
//     }

//     printf("Enter the number of connections: ");
//     scanf("%d", &num_connections);

//     printf("Enter connections (Parent_ID Child_ID Is_AND_child(0/1) Cost):\n");
//     for (int i = 0; i < num_connections; i++) {
//         int parent_id, child_id, is_and_child, cost;
//         scanf("%d %d %d %d", &parent_id, &child_id, &is_and_child, &cost);
//         add_child(&nodes[parent_id], &nodes[child_id], is_and_child, cost);
//     }

//     printf("Enter the root node ID: ");
//     int root_id;
//     scanf("%d", &root_id);

//     ao_star(&nodes[root_id]);

//     printf("\nAO* Solution:\n");
//     print_solution(&nodes[root_id], 0);

//     return 0;
// }