
/*
- This trick allows us to delete a node from a singly list in O(1) time when the node is NOT a tail
- This differs from delete_after where we know the predecessor node
*/

#include <assert.h>
#include <stdlib.h>

#include "singly_linked_list.h"
#include "test_helper.h"

// workaround for deleting node in O(1) time when predecessor is unknown
// this will segfault for tail nodes
void fast_delete(Node* node) {
    node->data = node->next->data;
    node->next = node->next->next;
    free(node->next);
}

void test_fast_delete() {
    print_test_func_name();
    int arr[] = {1, 2, 3};

    Node* head = create_nodes_from_array(arr, sizeof(arr) / sizeof(*arr));

    fast_delete(head->next);

    assert(head->next->data == 3);
    assert(head->data == 1);
    assert(head->next->next == NULL);

    free_all(head);
    passed();
}

int main(int argc, char** argv) {
    int should_run_tests = has_test_flag(argc, argv);

    if (should_run_tests)
        test_fast_delete();

    return 0;
}