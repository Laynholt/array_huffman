#include <stdio.h>
#include <string.h>

#include "node.h"

#define STRING_SIZE 7
#define TREE_SIZE (STRING_SIZE - 1) * 2 - 1

uint8_t number_of_symbols = 0;
uint8_t tree_size = 0;

void count_frequency(char* string, Node* tree)
{
	uint8_t found = 0;

	for (uint8_t i = 0; i < STRING_SIZE - 1; ++i)
	{
		found = 0;
		for (uint8_t j = 0; j < tree_size; ++j)
		{
			if (string[i] == tree[j].symbol)
			{
				tree[j].frequency += 1;
				found = 1;
				break;
			}
		}

		if (found == 0)
		{
			node_init(&tree[tree_size]);
			tree[tree_size].symbol = string[i];
			tree[tree_size].frequency += 1;
			tree_size += 1;
		}
	}
}

void create_parents(Node* tree)
{
	uint8_t left_min = 0;
	uint8_t right_min = 0;

	uint8_t left_min_val = STRING_SIZE;
	uint8_t right_min_val = STRING_SIZE;

	number_of_symbols = tree_size;
	for (uint8_t i = number_of_symbols; i < number_of_symbols * 2 - 1; ++i)
	{
		node_init(&tree[tree_size]);
		tree_size += 1;

		left_min = right_min = 0;
		left_min_val = right_min_val = STRING_SIZE;

		for (uint8_t j = 0; j < i; ++j)
		{
			if (!tree[j].parent)
			{ 
				if (tree[j].frequency < left_min_val)
				{
					right_min_val = left_min_val;
					left_min_val = tree[j].frequency;

					right_min = left_min;
					left_min = j;
				}
				else if (tree[j].frequency < right_min_val)
				{
					right_min_val = tree[j].frequency;
					right_min = j;
				}
			}
		}

		tree[i].frequency = left_min_val + right_min_val;
		tree[i].left = left_min;
		tree[i].right = right_min;

		tree[left_min].parent = i;
		tree[right_min].parent = i;
	}
}

void create_code(Node* tree)
{
	char buffer[4] = { '\0' };
	uint8_t buffer_index = 0;
	uint8_t current_index = 0;
	uint8_t prev_index = 0;

	for (uint8_t i = 0; i < number_of_symbols; ++i)
	{
		current_index = i;
		prev_index = i;

		buffer_index = 0;
		for (uint8_t k = 0; k < 4; ++k)
			buffer[k] = '\0';

		while (tree[current_index].parent)
		{
			current_index = tree[current_index].parent;

			if (prev_index == tree[current_index].left)
				buffer[buffer_index] = '0';
			else if (prev_index == tree[current_index].right)
				buffer[buffer_index] = '1';

			prev_index = current_index;
			buffer_index += 1;
		}

		// Перевертыш
		uint8_t size = strlen(buffer);
		for (uint8_t k1 = 0, k2 = size - 1; k1 < k2; ++k1, --k2)
		{
			char code = buffer[k1];
			buffer[k1] = buffer[k2];
			buffer[k2] = code;
		}

		printf("%c - %s\n", tree[i].symbol, buffer);
	}
}

int main()
{
	char input_string[STRING_SIZE] = { "qwerty" };
	Node tree[TREE_SIZE];

	count_frequency(input_string, tree);

	for (uint8_t i = 0; i < tree_size; ++i)
	{
		printf("%c - %d\n", tree[i].symbol, tree[i].frequency);
	}

	create_parents(tree);
	printf("\n");
	create_code(tree);

	return 0;
}