#pragma once

#include <vector>
#include <list>
#include <iostream>


//cpu fetch
//Temporal Cache coherency
//cache associativity

//Register
//L1 -- small size collection of 64 chunks
//L2 -- medium size collectio of 64 chunks
//L3 -- bigger size collection of 64 chunks 
//Main Memory
//HDD / SSD

//Cache line == ~64bytes 

//Cache line goes directly into L1 cache? 
//CPU will navigate old cache lines from L1 into L2 and then L3 on new arrival? 

//Access memory
//L1 - not found - cache miss 
//L2 - not found - cache miss
//L3 - not found - cache miss
//Main Memory - found - next 64 bytes from location added to L1 cache

namespace CacheLessons
{	
	//constexpr size_t CONTAINER_SIZE = 4096;
	//struct Object
	//{
	//	char c;
	//	float f;
	//	int i;
	//};

	//struct ObjectOfObjects
	//{
	//	ObjectOfObjects()
	//	:	chars(CONTAINER_SIZE),
	//		floats(CONTAINER_SIZE),
	//		ints(CONTAINER_SIZE)
	//	{}

	//	std::vector<char> chars;
	//	std::vector<float> floats;
	//	std::vector<int> ints;
	//};

	//void listContainerTraversal()
	//{
	//	std::list<int> numbers;
	//	for (int i = 0; i < CONTAINER_SIZE; ++i)
	//	{
	//		numbers.emplace_back();
	//	}

	//	for (auto& i : numbers)
	//	{
	//		i = 0;
	//	}
	//}

	//void vectorContainerTraversal()
	//{
	//	std::vector<int> numbers;
	//	numbers.resize(CONTAINER_SIZE);

	//	for (auto& i : numbers)
	//	{
	//		i = 0;
	//	}
	//}

	//void arrayOfStructs()
	//{
	//	std::vector<Object> objects(CONTAINER_SIZE);
	//	for (const auto& object : objects)
	//	{
	//		std::cout << object.i << "\n";
	//	}
	//}

	//void structsOfArrays()
	//{
	//	ObjectOfObjects object;
	//	for (const auto& i : object.ints)
	//	{
	//		std::cout << i << "\n";
	//	}
	//}
	//
	//void rowMajorOrder()
	//{
	//	std::vector<int> numbers(CONTAINER_SIZE * CONTAINER_SIZE);
	//	for (int y = 0; y < CONTAINER_SIZE; ++y)
	//	{
	//		for (int x = 0; x < CONTAINER_SIZE; ++x)
	//		{
	//			int index = y * CONTAINER_SIZE + x;
	//			numbers[index] = 0;
	//		}
	//	}
	//}

	//void columnMajorOrder()
	//{
	//	std::vector<int> numbers(CONTAINER_SIZE * CONTAINER_SIZE);
	//	for (int y = 0; y < CONTAINER_SIZE; ++y)
	//	{
	//		for (int x = 0; x < CONTAINER_SIZE; ++x)
	//		{
	//			int index = x * CONTAINER_SIZE + y;
	//			numbers[index] = 0;
	//		}
	//	}
	//}

	//void differentIncrements()
	//{
	//	std::vector<int> numbers(CONTAINER_SIZE * CONTAINER_SIZE);
	//	for (int i = 0; i < numbers.size(); ++i)
	//	{
	//		numbers[i] = 0;
	//	}

	//	for (int i = 0; i < numbers.size(); i += 8)
	//	{
	//		numbers[i] = 0;
	//	}

	//	for (int i = 0; i < numbers.size(); i += 32)
	//	{
	//		numbers[i] = 0;
	//	}
	//}

	void slowThread2DArray();
	void fastThread2DArray();
	void threadTraversalArray();
	void threadLocalTest();
};