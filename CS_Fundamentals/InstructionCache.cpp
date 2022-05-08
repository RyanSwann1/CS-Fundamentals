#include "InstructionCache.h"
#include <vector>
#include <memory>

namespace
{
	struct Base { virtual void process() = 0; };
	struct DerivedA : public Base { void process() override {} };
	struct DerivedB : public Base { void process() override {} };
	struct DerivedC : public Base { void process() override {} };
}

void InstructionCache::slowProcessExample()
{
	std::vector<std::unique_ptr<Base>> objects;
	for (int i = 1; i < 30; ++i)
	{
		if (i % 3 == 0)
		{
			objects.emplace_back(std::make_unique<DerivedA>());
		}
		else if (i % 3 == 1)
		{
			objects.emplace_back(std::make_unique<DerivedB>());
		}
		else if (i % 3 == 2)
		{
			objects.emplace_back(std::make_unique<DerivedC>());
		}
	}

	for (auto& object : objects)
	{
		object->process();
	}
}

void InstructionCache::fastProcessExample()
{
	std::vector<std::unique_ptr<DerivedA>> objectsA;
	std::vector<std::unique_ptr<DerivedB>> objectsB;
	std::vector<std::unique_ptr<DerivedC>> objectsC;
	for (int i = 0; i < 50; ++i)
	{
		objectsA.emplace_back(std::make_unique<DerivedA>());
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsB.emplace_back(std::make_unique<DerivedB>());
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsC.emplace_back(std::make_unique<DerivedC>());
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsA[i]->process();
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsB[i]->process();
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsC[i]->process();
	}
}

//Less instructions due to the lack of pointer chasing
void InstructionCache::fasterProcessExample()
{
	std::vector<DerivedA> objectsA(50);
	std::vector<DerivedB> objectsB(50);
	std::vector<DerivedC> objectsC(50);

	for (int i = 0; i < 50; ++i)
	{
		objectsA[i].process();
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsB[i].process();
	}

	for (int i = 0; i < 50; ++i)
	{
		objectsC[i].process();
	}
}
