#include "VectorContainer.h"
#include "LinkedListContainer.h"
#include <list>
#include <iostream>

int main()
{
	LinkedListContainer<int> linkedListContainer;
	for (int i = 0; i < 5; ++i)
	{
		linkedListContainer.pushFront(i);
	}

	if (!linkedListContainer.isEmpty())
	{
		LinkedListNode<int>* node = &linkedListContainer.getHead();
		while (node)
		{
			std::cout << node->data << "\n";
			node = node->next;
		}
	}

	linkedListContainer.clear();

	return 0;
}