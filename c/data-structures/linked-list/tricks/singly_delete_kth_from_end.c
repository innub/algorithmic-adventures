/*
- This trick allows us to find and delete the kth element, from the end of the list, in one iteration
- Remember that the length is unknown
- A naive approach would calculate the length and delete the node in two different iterations
*/

#include <assert.h>
#include <stdlib.h>

#include "singly_linked_list.h"
#include "test_helper.h"

void delete_kth_from_end(Node* head, int kth) {
    Node* sentinel = create_node(0);
    sentinel->next = head;

    Node *first = head, *second = sentinel;  // you will see why we use sentinel later

    for (int i = 0; i < kth; i++) {
        first = first->next;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    // without the sentinel node, second would be the kth element
    // but in order to delete, we need it's predecessor (ie. the k+1 th element from the end)
    Node* node_to_del = second->next;

    second->next = second->next->next;

    free(node_to_del);
}

void test_delete_kth_from_end() {
    print_test_func_name();

    int arr[] = {1, 2, 3, 4, 5};

    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    printf("##### Before #####\n");

    Node* n = head;
    while (n != NULL) {
        printf("%d\n", n->data);
        n = n->next;
    }

    delete_kth_from_end(head, 4);

    printf("##### After #####\n");
    n = head;
    while (n != NULL) {
        printf("%d\n", n->data);
        n = n->next;
    }

    assert(head->next->data == 3);

    free_all(head);
    passed();
}

int main(int argc, char** argv) {
    int should_run_tests = has_test_flag(argc, argv);

    if (should_run_tests)
        test_delete_kth_from_end();

    return 0;
}