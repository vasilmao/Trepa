#include "Treap.h"
Treap* Construct(Treap* tree)
    {
    Treap* new_tree = (Treap*)calloc(1, sizeof(Treap));
    assert(new_tree);

    return new_tree;
    }

TreapNodePair Split(TreapNode* node, KeyType x)
    {
    if (node == nullptr)
        {
        return {nullptr, nullptr};
        }

    if (x > node->key)
        {
        TreapNodePair pair = Split(node->right, x);
        node->right        = pair.first;
        return {node, pair.second};
        }

    else
        {
        TreapNodePair pair = Split(node->left, x);
        node->left         = pair.second;
        return {pair.first, node};
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

    if (left->prior <= right->prior)
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

bool Find(Treap* tree, KeyType key)
    {
    return (FindNode(tree, key) != (TreapNode*)nullptr);
    }

TreapNode* FindNode(Treap* tree, KeyType key)
    {
    TreapNode* current_node = tree->root;
    while (true)
        {
        if (current_node == nullptr)
            {
            return nullptr;
            }

        if (current_node->key == key)
            {
            return current_node;
            }

        if (key < current_node->key )
            {
            current_node = current_node->left;
            }
        else
            {
            current_node = current_node->right;
            }
        }
    }

bool CheckLeftExists(TreapNode* node, KeyType key) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    while (node->left != nullptr) {
        node = node->left;
        if (node->key == key) {
            return true;
        }
    }
    return false;
}

TreapNode* NewTreapNode(KeyType key)
    {
    int prior = rand();
    TreapNode* new_node = (TreapNode*)calloc(1, sizeof(TreapNode));
    assert(new_node);

    new_node->key       = key;
    new_node->prior     = prior;
    return new_node;
    }

void Insert(Treap* tree, KeyType key)
    {
    if (tree->root == nullptr)
        {
        tree->root = NewTreapNode(key);
        return;
        }

    TreapNodePair pair = Split(tree->root, key);
    if (CheckLeftExists(pair.second, key))
        {
        tree->root = Merge(pair.first, pair.second);
        return;
        }
    TreapNode* new_node = NewTreapNode(key);
    TreapNode* node     = Merge(pair.first, new_node);
    tree->root          = Merge(node, pair.second);
    }

bool IsLastLeft(TreapNode* node) { return node != nullptr && node->left == nullptr; }

TreapNode* EraseLeft(TreapNode* node, KeyType key)
    {
    if (node == nullptr)
        {
        return nullptr;
        }

    if (IsLastLeft(node))
        {
        if (node->key == key)
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
    if (last_left->key == key)
        {
        node->left = last_left->right;
        free(last_left);
        }

    return current_root;
    }

void Erase(Treap* tree, KeyType key)
    {
    TreapNodePair pair = Split(tree->root, key);
    pair.second        = EraseLeft(pair.second, key);
    tree->root         = Merge(pair.first, pair.second);
    }









void PrintNodes(Treap* tree, TreapNode* node, FILE* DumpFile)
{

	fprintf(DumpFile, "\"%p\"[style=\"filled\", fillcolor=\"#E16456\", label=\"%d | %d\"]", node, node->key, node->prior);
	if (node->left != NULL)
	{
		fprintf(DumpFile, "\"%p\":sw->\"%p\";\n", node, node->left);
		PrintNodes(tree, node->left, DumpFile);
	}

	if (node->right != NULL)
	{
		fprintf(DumpFile, "\"%p\":se->\"%p\";\n", node, node->right);
		PrintNodes(tree, node->right, DumpFile);
	}
}

void PrintNodesHard(Treap* tree, TreapNode* node, FILE* DumpFile)
{
	fprintf(DumpFile, "\"%p\" [shape=\"record\", style=\"filled\", fillcolor=\"#E16456\","
			"fontcolor=\"black\", label=\"{%d|%p|%d|{%p|%p}}\"]", node, node->key, node, node->prior,
			node->left, node->right);
	if (node->left != NULL)
	{
		fprintf(DumpFile, "\"%p\":sw->\"%p\";\n", node, node->left);
		PrintNodesHard(tree, node->left, DumpFile);
	}

	if (node->right != NULL)
	{
		fprintf(DumpFile, "\"%p\":se->\"%p\";\n", node, node->right);
		PrintNodesHard(tree, node->right, DumpFile);
	}
}

void TreeDump(Treap* tree)
{
    FILE* DumpFile = fopen("Treap.txt", "w");

	fprintf(DumpFile, "digraph G{\n");
	fprintf(DumpFile, "node [shape=\"circle\", style=\"filled\", fillcolor=\"#C0FFC0\"]\n");

	PrintNodesHard(tree, tree->root, DumpFile);

	fprintf(DumpFile, "}");

	fclose(DumpFile);

	system("dot -Tsvg Treap.txt > Treap.svg");
	system("Treap.svg");
}
