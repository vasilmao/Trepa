#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int KeyType;

struct TreapNode {
    KeyType key;
    int prior;
    TreapNode* left;
    TreapNode* right;
};

struct Treap {
    TreapNode* root;
};

struct TreapNodePair {
    TreapNode* first;
    TreapNode* second;
};

Treap*        Construct (Treap* tree);
TreapNodePair Split     (TreapNode* node, KeyType x);
TreapNode*    Merge     (TreapNode* left, TreapNode* right);
bool          Find      (Treap* tree, KeyType key);
TreapNode*    FindNode  (Treap* tree, KeyType key);
void          Insert    (Treap* tree, KeyType key);
bool          IsLastLeft(TreapNode* node);
TreapNode*    EraseLeft (TreapNode* node, KeyType key);
void          Erase     (Treap* tree, KeyType key);
