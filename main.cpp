#include "Treap.h"

    //printf("exiting: %d\n", node->x);


int main() {
    srand(time(NULL));
    Treap* tree = Construct(NULL);
    Insert(tree, 3);
    Insert(tree, 5);
    Insert(tree, 7);
    Insert(tree, 6);
    printf("%d\n", Find(tree, 5));
    Erase(tree, 7);
    Erase(tree, 5);
    Erase(tree, 3);
    Erase(tree, 1);
    Erase(tree, 6);
    Erase(tree, 8);
}
