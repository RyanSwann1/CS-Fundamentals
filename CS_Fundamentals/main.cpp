#include "VectorContainer.h"
#include "DoublyLinkedList.h"
#include "SingleLinkedList.h"
#include "SharedPtr.h"
#include <list>
#include <iostream>
#include <utility>
#include <forward_list>
#include <stack>
#include <vector>
#include <deque>
#include <memory>

template <class T>
void printContainer(const SingleLinkedList<T>& container)
{
	if (!container.isEmpty())
	{
		const SingleLinkedListNode<T>* node = &container.getHead();
		while (node)
		{
			std::cout << node->data << "\n";
			node = node->next;
		}
	}

	std::cout << "\n";
}

template <class T>
void printContainerFromStart(const DoublyLinkedList<T>& container)
{
	if (!container.isEmpty())
	{
		const auto* node = &container.getHead();
		while (node)
		{
			std::cout << node->data << "\n";
			node = node->next;
		}
	}
}

template <class T>
void printContainerFromEnd(const DoublyLinkedList<T>& container)
{
	if (!container.isEmpty())
	{
		const auto* node = &container.getTail();
		while (node)
		{
			std::cout << node->data << "\n";
			node = node->previous;
		}
	}
}

void removeFromDoublyLinkedList()
{
	std::list<int> numbers;
	for (int i = 0; i < 5; ++i)
	{
		numbers.push_back(i);
	}

	auto iter = std::find(numbers.begin(), numbers.end(), 4);
	if (iter != numbers.end())
	{
		numbers.erase(iter);
	}

	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}
}

void removeFromLinkedList()
{
	std::forward_list<int> numbers;
	for (int i = 0; i < 5; ++i)
	{
		numbers.push_front(i);
	}

	auto cIter = std::find(numbers.begin(), numbers.end(), 4);
	if (cIter != numbers.end())
	{
		numbers.remove(4);
	}

	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}
}

int main()
{
	SharedPtr<int> number(2);
	SharedPtr<int> anotherNumber(number);

	anotherNumber.reset();


	return 0;
}