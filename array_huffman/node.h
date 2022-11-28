#ifndef _NODE_H_
#define _NODE_H_

#include "types.h"

typedef struct Node
{
	char symbol;
	uint8_t frequency;

	uint8_t left;
	uint8_t right;
	uint8_t parent;

}Node;

extern void node_init(Node* node);

#endif