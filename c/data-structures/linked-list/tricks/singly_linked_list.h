/*
- a basic singly linked list setup with only basic methods
- to see a full (basic) implementation see: data-structures/1_singly_linked_list.c
- this implementation uses NULL as an indicator of head and tail
*/

#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

static inline void free_all(Node* head) {
    Node* node = head;
    while (node != NULL) {
        Node* prev_node = node;
        node = node->next;
        free(prev_node);
    }
}

static inline Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(*node));
    node->data = data;
    node->next = NULL;
    return node;
}

static inline Node* create_nodes_from_array(int a[], int size) {
    Node* head = NULL;
    Node* node = NULL;
    for (int i = 0; i < size; i++) {
        Node* n = create_node(a[i]);
        if (i == 0) {
            head = n;
            node = n;
        } else {
            node->next = n;
            node = n;
        }
    }
    return head;
}

#endif