#include "Treap.h"

Treap* Construct(Treap* tree)
    {
    Treap* new_tree = (Treap*)calloc(1, sizeof(Treap));
    return new_tree;
    }

TreapNodePair Split(TreapNode* node, ElemT x)
    {
    if (node == NULL)
        {
        return {NULL, NULL};
        }
    if (x > node->x)
        {
        TreapNodePair pp = Split(node->right, x);
        node->right      = pp.first;
        return {node, pp.second};
        }

    else
        {
        TreapNodePair pp = Split(node->left, x);
        node->left       = pp.second;
        return {pp.first, node};
        }
    }

TreapNode* Merge(TreapNode* left, TreapNode* right)
    {
    if (!left)
        {
        return right;
        }
    if (!right)
        {
        return left;
        }
    if (left->y <= right->y)
        {
        left->right = Merge(left->right, right);
        return left;
        }
    else
        {
        right->left = Merge(left, right->left);
        return right;
        }
    }

bool Find(Treap* tree, ElemT key) { return (FindNode(tree, key) != (TreapNode*)NULL); }

TreapNode* FindNode(Treap* tree, ElemT key)
    {
    TreapNode* current_node = tree->root;
    while (true)
        {
        if (current_node == NULL)
            {
            return NULL;
            }
        printf("ye %d\n", current_node->x);
        if (current_node->x == key)
            {
            return current_node;
            }
        if (key < current_node->x )
            {
            current_node = current_node->left;
            }
        else
            {
            current_node = current_node->right;
            }
        }
    }

void Insert(Treap* tree, ElemT key, int prior)
    {
    TreapNode* one_element = (TreapNode*)calloc(1, sizeof(TreapNode));
    one_element->x         = key;
    one_element->y         = prior;
    if (tree->root == NULL)
        {
        tree->root = one_element;
        return;
        }
    TreapNodePair pp = Split(tree->root, key);
    TreapNode* new1  = Merge(pp.first, one_element);
    tree->root       = Merge(new1, pp.second);
    }

bool IsLastLeft(TreapNode* node) { return node != NULL && node->left == NULL; }

TreapNode* EraseLeft(TreapNode* node, ElemT key)
    {
    if (node == NULL)
        {
        return NULL;
        }
    if (IsLastLeft(node))
        {
        if (node->x == key)
            {
            TreapNode* new_left = node->right;
            free(node);
            return new_left;
            }
        return node;
        }
    TreapNode* current_root = node;
    while (!IsLastLeft(node->left))
        {
        node = node->left;
        }
    TreapNode* last_left = node->left;
    if (last_left->x == key)
        {
        node->left = last_left->right;
        free(last_left);
        }
    return current_root;
    }

void Erase(Treap* tree, ElemT key)
    {
    TreapNodePair pp = Split(tree->root, key);
    pp.second = EraseLeft(pp.second, key);
    tree->root = Merge(pp.first, pp.second);
    }
