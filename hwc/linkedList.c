#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node;

void printList(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void insertFront(Node **head_ref, int new_data) {
    Node *new_node = (Node *)malloc(sizeof(Node)); 
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

Node* reverseList(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        
        current->next = prev;
        
        prev = current;
        current = next;
    }
    return prev;
}

void freeList(Node *head) {
    Node *current = head;
    Node *next;

    printf("\nFreeing allocated memory...\n");
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    printf("Memory successfully freed.\n");
}

int main() {
    Node *head = NULL;

    insertFront(&head, 10);
    insertFront(&head, 20);
    insertFront(&head, 30);
    insertFront(&head, 40);
    
    printf("Before Reversal: \n");
    printList(head);

    head = reverseList(head);
    
    printf("\nAfter Reversal\n");
    printList(head);

    freeList(head);
    head = NULL;

    return 0;
}