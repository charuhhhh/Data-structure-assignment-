

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_QUEUE    100
#define NAME_LEN     30

typedef struct Node {
    char name[NAME_LEN];
    struct Node *children[MAX_CHILDREN];
    int childCount;
} Node;

Node* createNode(const char *name) {
    Node *n = (Node*) malloc(sizeof(Node));
    strcpy(n->name, name);
    n->childCount = 0;
    return n;
}


void addChild(Node *parent, Node *child) {
    parent->children[parent->childCount++] = child;
}


typedef struct {
    Node* items[MAX_QUEUE];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = 0; q->rear = 0; }
int isEmpty(Queue *q)    { return q->front == q->rear; }
void enqueue(Queue *q, Node *n) { q->items[q->rear++] = n; }
Node* dequeue(Queue *q) { return q->items[q->front++]; }


void levelOrderTraversal(Node *root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int level = 0;
    printf("\n--- Level-Order Traversal (Hierarchy Display) ---\n");

    while (!isEmpty(&q)) {
        int levelSize = q.rear - q.front;   /* nodes present at this level */
        printf("Level %d: ", level);

        for (int i = 0; i < levelSize; i++) {
            Node *cur = dequeue(&q);
            printf("%s", cur->name);
            if (i != levelSize - 1) printf(", ");

            for (int j = 0; j < cur->childCount; j++)
                enqueue(&q, cur->children[j]);
        }
        printf("\n");
        level++;
    }
}


int treeHeight(Node *root) {
    if (root == NULL || root->childCount == 0) return 0;
    int maxH = 0;
    for (int i = 0; i < root->childCount; i++) {
        int h = treeHeight(root->children[i]);
        if (h > maxH) maxH = h;
    }
    return maxH + 1;
}


int countNodes(Node *root) {
    if (root == NULL) return 0;
    int total = 1;
    for (int i = 0; i < root->childCount; i++)
        total += countNodes(root->children[i]);
    return total;
}

int main() {
   
    Node *CEO         = createNode("CEO");
    Node *HR          = createNode("HR");
    Node *Finance     = createNode("Finance");
    Node *IT          = createNode("IT");
    Node *Development = createNode("Development");
    Node *Testing     = createNode("Testing");
    Node *Frontend    = createNode("Frontend");
    Node *Backend     = createNode("Backend");

    addChild(CEO, HR);
    addChild(CEO, Finance);
    addChild(CEO, IT);

    addChild(IT, Development);
    addChild(IT, Testing);

    addChild(Development, Frontend);
    addChild(Development, Backend);

    printf("Tree constructed successfully with %d nodes.\n", countNodes(CEO));

  
    levelOrderTraversal(CEO);

 
    printf("\n--- Structural Analysis ---\n");
    printf("Height of tree (root = level 0): %d\n", treeHeight(CEO));
    printf("Total number of departments (nodes): %d\n", countNodes(CEO));

    return 0;
}
