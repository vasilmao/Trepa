#include "Treap.h"

    //printf("exiting: %d\n", node->x);


int main() {
    srand(time(NULL));
    Treap* tree = Construct(NULL);
    Insert(tree, 3, 27569);
    Insert(tree, 5, 18874);
    Insert(tree, 7, 6545);
    Insert(tree, 6, 24042);
    print_tree(tree->root);
    printf("%d\n", Find(tree, 5));
    Erase(tree, 7);
    Erase(tree, 5);
    Erase(tree, 3);
    Erase(tree, 1);
    Erase(tree, 6);
    Erase(tree, 8);
}
