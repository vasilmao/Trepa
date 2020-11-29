#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int ElemT;

struct TreapNode {
    ElemT x;
    int y;
    TreapNode* left;
    TreapNode* right;
    int mynumber;
};

struct Treap {
    TreapNode* root;
};

struct TreapNodePair {
    TreapNode* first;
    TreapNode* second;
};

Treap*        Construct (Treap* tree);
TreapNodePair Split     (TreapNode* node, ElemT x);
TreapNode*    Merge     (TreapNode* left, TreapNode* right);
bool          Find      (Treap* tree, ElemT key);
TreapNode*    FindNode  (Treap* tree, ElemT key);
void          Insert    (Treap* tree, ElemT key, int prior);
bool          IsLastLeft(TreapNode* node);
TreapNode*    EraseLeft (TreapNode* node, ElemT key);
void          Erase     (Treap* tree, ElemT key);
