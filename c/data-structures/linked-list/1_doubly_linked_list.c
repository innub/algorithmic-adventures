/*
- this implementation uses NULL as an indicator of head and tail
- the append in this implementation assumes that the tail node is not stored: O(n)
- for fast appends, store the tail and use insert_after(tail, new_node): O(1)
*/

#include <assert.h>
#include <stdlib.h>

#include "test_helper.h"

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

void free_all(Node* head) {
    Node* node = head;
    while (node != NULL) {
        Node* prev_node = node;
        node = node->next;
        free(prev_node);
    }
}

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(*node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

Node* create_nodes_from_array(int a[], int size) {
    Node* head = NULL;
    Node* node = NULL;
    for (int i = 0; i < size; i++) {
        Node* n = create_node(a[i]);
        if (i == 0) {
            head = n;
            node = n;
        } else {
            node->next = n;
            n->prev = node;
            node = n;
        }
    }
    return head;
}

void delete_node(Node* node) {
    if (node->prev == NULL) {  // head
        node->next->prev = NULL;
    } else if (node->next == NULL) {  // tail
        node->prev->next = NULL;
    } else {  // middle
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);
}

void insert_after(Node* node, Node* new_node) {
    new_node->next = node->next;
    new_node->prev = node;
    if (node->next != NULL) node->next->prev = new_node;
    node->next = new_node;
}

Node* find_kth(Node* head, int k) {
    if (k == 0) return head;

    Node* node = head;
    for (int i = 0; i < k; i++) {
        node = node->next;
    }

    return node;
}

Node* search(Node* head, int key) {
    Node* n = head;
    while (n != NULL) {
        if (n->data == key)
            return n;
        else
            n = n->next;
    }

    return NULL;
}

void prepend(Node* head, Node* new_node) {
    new_node->next = head;
    head->prev = new_node;
}

void append(Node* head, Node* new_node) {
    Node* n = head;
    while (n->next != NULL) {
        n = n->next;
    }

    n->next = new_node;
    new_node->prev = n;
}

/*
###############################
###          tests          ###
###############################
*/
void test_create_node() {
    print_test_func_name();

    Node* node = create_node(10);

    assert(node->data == 10);
    assert(node->next == NULL);
    assert(node->prev == NULL);

    free_all(node);
    passed();
}

void test_create_nodes_from_array() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    assert(head != NULL);
    assert(head->data == 1);
    assert(head->next->data == 2);
    assert(head->next->next->data == 3);
    assert(head->prev == NULL);
    assert(head->next->prev == head);
    assert(head->next->next->prev == head->next);

    free_all(head);
    passed();
}

void test_delete_head() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    Node* new_head = head->next;
    delete_node(head);
    head = new_head;

    assert(head->data == 2);
    assert(head->next->data == 3);
    assert(head == head->next->prev);

    free_all(new_head);
    passed();
}

void test_delete_tail() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    delete_node(head->next->next);

    assert(head->next->data == 2);
    assert(head->next->next == NULL);

    free_all(head);
    passed();
}

void test_delete_middle() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    delete_node(head->next);

    assert(head->next->data == 3);
    assert(head == head->next->prev);

    free_all(head);
    passed();
}

void test_insert_after_middle() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));
    Node* new_node = create_node(10);

    insert_after(head, new_node);

    Node* inserted_node = head->next;

    assert(inserted_node->next->data == 2);
    assert(inserted_node->prev == head);

    free_all(head);
    passed();
}

void test_insert_after_tail() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));
    Node* new_node = create_node(10);

    Node* tail = head->next->next;

    insert_after(tail, new_node);

    Node* new_tail = tail->next;

    assert(new_tail->data == 10);
    assert(new_tail->prev == tail);
    assert(new_tail->next == NULL);

    free_all(head);
    passed();
}

void test_find_kth() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    Node* node_1 = find_kth(head, 0);
    assert(node_1->data == 1);

    Node* node_2 = find_kth(head, 1);
    assert(node_2->data == 2);

    Node* node_3 = find_kth(head, 2);
    assert(node_3->data == 3);

    free_all(head);
    passed();
}

void test_search() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    Node* node = search(head, 10);
    assert(node == NULL);

    node = search(head, 3);
    assert(node != NULL && node->data == 3);

    free_all(head);
    passed();
}

void test_prepend() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));
    Node* new_node = create_node(10);

    prepend(head, new_node);
    head = new_node;

    assert(head->data == 10);
    assert(head->next->data == 1);
    assert(head == head->next->prev);

    free_all(head);
    passed();
}

void test_append() {
    print_test_func_name();

    int arr[] = {1, 2, 3};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));
    Node* new_node = create_node(10);

    append(head, new_node);

    Node* appended_noded = head->next->next->next;
    assert(appended_noded->data == 10);
    assert(appended_noded->prev->data == 3);
    assert(appended_noded->next == NULL);

    free_all(head);
    passed();
}

int main(int argc, char** argv) {
    int should_run_tests = has_test_flag(argc, argv);
    if (should_run_tests) {
        test_create_node();
        test_create_nodes_from_array();
        test_delete_head();
        test_delete_tail();
        test_delete_middle();
        test_insert_after_middle();
        test_insert_after_tail();
        test_find_kth();
        test_search();
        test_prepend();
        test_append();
    }

    return 0;
}
