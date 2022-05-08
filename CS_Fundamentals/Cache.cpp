#include "Cache.h"
#include <array>
#include <thread>
#include <vector>
#include <atomic>


//All data in static storage duration can suffer from false sharing
//Heap allocated objects can also suffer from false sharing
struct ExpensiveObject
{
	char a[64];
	std::atomic<int> number = 0;
	char b[64];
};

void CacheLessons::slowThread2DArray()
{
	constexpr size_t MAX_THREADS = 10;
	std::vector<std::vector<int>> numbers(MAX_THREADS);
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		for (int j = 0; j < 5000; ++j)
		{
			numbers[i].push_back(j);
		}
	}

	ExpensiveObject object;
	std::array<std::thread, MAX_THREADS> threads;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threads[i] = std::thread([&numbers, &object, i]()
		{
			for (auto& number : numbers[i])
			{
				object.number += number;
			}
		});
	}

	for (auto& i : threads)
	{
		i.join();
	}

	std::cout << object.number << "\n";
}

void CacheLessons::fastThread2DArray()
{
	constexpr size_t MAX_THREADS = 10;
	std::vector<std::vector<int>> numbers(MAX_THREADS);
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		for (int j = 0; j < 50000; ++j)
		{
			numbers[i].push_back(j);
		}
	}

	ExpensiveObject object;
	std::array<std::thread, MAX_THREADS> threads;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threads[i] = std::thread([&numbers, &object, i]()
		{
			int tempCount = 0;
			for (auto& number : numbers[i])
			{
				tempCount += number;
			}
			object.number = tempCount;
		});
	}

	for (auto& i : threads)
	{
		i.join();
	}
	std::cout << object.number << "\n";
}

void CacheLessons::threadTraversalArray()
{
	std::vector<int> numbers(10000);
	std::array<std::thread, 10> threads;
	for (auto& t : threads)
	{
		t = std::thread([&]()
		{
			for (auto i : numbers)
			{
				i;
			}
		});
	}

	for (auto& t : threads)
	{
		t.join();
	}
}

void CacheLessons::threadLocalTest()
{
	int number = 10;
	std::array<std::thread, 10> threads;
	thread_local int value = 0;
	for (auto& t : threads)
	{
		t = std::thread([number]()
		{
			value += number;
		});
	}

	std::vector<int> numbers(10000, 1);
	for (auto& t : threads)
	{
		t = std::thread([&numbers]()
		{
			for (const auto& numb : numbers)
			{
				numb;
			}
		});
	}

	for (auto& t : threads)
	{
		t.join();
	}
}
