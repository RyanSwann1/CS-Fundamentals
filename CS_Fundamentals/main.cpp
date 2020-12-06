#include "VectorContainer.h"
#include "DoublyLinkedList.h"
#include "SingleLinkedList.h"
#include "SharedPtr.h"
#include "UnorderedMap.h"
#include <list>
#include <iostream>
#include <utility>
#include <forward_list>
#include <stack>
#include <vector>
#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <random>

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

int getRandomNumber(int min, int max)
{
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

int main()
{
	//std::map<int, int> container;

	//for (int i = 0; i < 10; ++i)
	//{
	//	container.emplace(getRandomNumber(0, 20), i);
	//}

	//for (auto& i : container)
	//{
	//	std::cout << i.first << "\n";
	//	std::cout << i.second << "\n";
	//	std::cout << "\n";
	//}
	
	UnorderedMap<std::string> names;
	names.insert(20, "John");
	names.insert(20, "Dave");
	names.insert(20, "Peter");
	names.insert(22, "Mike");

	UnorderedMap<std::string> moreNames;
	moreNames = std::move(names);

	return 0;
}