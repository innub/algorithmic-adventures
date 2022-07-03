/*
- This trick allows us to reverse a sublist in one pass: O(k) where k is the ending index of the sublist
- Sublist from s to k inclusive, 1-indexed
*/

#include <assert.h>
#include <stdio.h>

#include "singly_linked_list.h"
#include "test_helper.h"

Node* reverse_sublist(Node* head, int s, int k) {
    Node* sentinel = create_node(0);
    sentinel->next = head;
    Node* s_node_prev = sentinel;
    for (int i = 1; i < s; i++) {
        s_node_prev = s_node_prev->next;
    }

    Node* sublist_head = NULL;
    Node* sublist_tail = s_node_prev->next;  // the s-th node will become the tail
    Node* sec = s_node_prev->next;           // s-th node
    for (int i = s; i <= k; i++) {
        Node* next_sec = sec->next;

        sec->next = sublist_head;

        sublist_head = sec;
        sec = next_sec;
    }

    s_node_prev->next = sublist_head;
    sublist_tail->next = sec;  // sec is the (k+1)-th node

    return sentinel->next;
}

void test_reverse_sublist() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    printf("##### Before #####\n");

    Node* n = head;
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");

    head = reverse_sublist(head, 2, 5);

    printf("##### After #####\n");

    n = head;
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int should_run_tests = has_test_flag(argc, argv);

    if (should_run_tests)
        test_reverse_sublist();

    return 0;
}