#include "VectorContainer.h"
#include "DoublyLinkedList.h"
#include "SingleLinkedList.h"
#include "SharedPtr.h"
#include "UnorderedMap.h"
#include "Cache.h"
#include "StructPadding.h"
#include "ShortVector.h"
#include "InstructionCache.h"
#include "InitializerList.h"
#include "ConstexprTutorials.h"
#include "std_function.h"
#include "PriorityQueue.h"
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
#include <iterator>
#include <thread>
#include <optional>
#include <atomic>

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

void cacheThing()
{
	std::vector<int> numbers(100, 1);
	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}

	std::vector<std::unique_ptr<int>> moreNumbers;
	std::generate_n(std::back_inserter(moreNumbers), 50, []() { return std::make_unique<int>(5); });

	for (const auto& i : moreNumbers)
	{
		std::cout << *i << "\n";
	}

	std::list<int> evenMoreNumbers(100, 1);
	for (auto i : evenMoreNumbers)
	{
		std::cout << i << "\n";
	}
}

void slow2DThread()
{

}

void fast2DThread()
{

}

int main()
{
	//unordered_map_lesson::run();
	priority_queue::run();

	//for (auto& i : numbers)
	//{
	//	std::cout << i << "\n";
	//}

	//constexpr int number = constexpr_tutorials::getSum();
	//std::cout << number << "\n";

	//constexpr int resultv1 = constexpr_tutorials::maybe_allocate(1);
	//constexpr int resultv2 = constexpr_tutorials::maybe_allocate(2);
	//int resultv3 = constexpr_tutorials::maybe_allocate(3);
}