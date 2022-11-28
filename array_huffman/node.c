#include "node.h"

void node_init(Node* node)
{
	node->symbol = ' ';
	node->frequency = 0;

	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
}
