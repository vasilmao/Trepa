#include "Treap.h"

    //printf("exiting: %d\n", node->x);


int main() {
    srand(time(NULL));
    Treap* tree = Construct(NULL);
    for (int i = 0; i < 100; ++i) {
        Insert(tree, rand());
    }
    TreeDump(tree);
}
