/*
- This trick allows us to merge two SORTED linked lists in one iteration: O(n)
- A naive approach would simply append the lists before sorting it
- Appending runs in O(1) time but sorting runs in O(n*log(n)) time
*/

#include <assert.h>

#include "singly_linked_list.h"
#include "test_helper.h"

Node* merge_two_sorted(Node* head1, Node* head2) {
    Node* sentinel = create_node(0);

    Node* n = sentinel;
    while (head1 && head2) {
        if (head1->data <= head2->data) {
            n->next = head1;
            head1 = head1->next;
        } else {
            n->next = head2;
            head2 = head2->next;
        }
        n = n->next;
    }

    n->next = head1 ? head1 : head2;

    Node* real_head = sentinel->next;
    free(sentinel);  // free sentinel because free_all(head) does not do this for singly

    return real_head;
}

void test_merge_two_sorted() {
    print_test_func_name();

    int arr1[] = {10, 11, 121, 200, 300, 400, 909, 1001};
    int arr2[] = {90, 100, 909, 1000};
    Node* head1 = create_nodes_from_array(arr1, sizeof(arr1) / sizeof(*arr1));
    Node* head2 = create_nodes_from_array(arr2, sizeof(arr2) / sizeof(*arr2));

    Node* head = merge_two_sorted(head1, head2);

    assert(head);

    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");

    free_all(head);
    passed();
}

int main(int argc, char** argv) {
    int should_run_tests = has_test_flag(argc, argv);

    if (should_run_tests)
        test_merge_two_sorted();

    return 0;
}