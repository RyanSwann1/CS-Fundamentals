#pragma once

#include <iostream>

namespace RValueReferences
{
	template <typename T>
	void foo(T&& _t)
	{
		T t = _t;
	}

	template <typename T>
	void foo(T& _t)
	{
		T t = _t;
	}

	template <typename T>
	void expensiveSwap(T& param1, T& param2)
	{
		T tempCopy = param1;
		param1 = param2;
		param2 = tempCopy;
	}

	template <typename T>
	void cheapSwap(T& param1, T& param2)
	{
		T tempCopy = std::move(param1);
		param1 = std::move(param2);
		param2 = std::move(tempCopy);
	}

	struct Person1
	{
		Person1() {}
		Person1(const Person1& rhs) { std::cout << "Person1 Copy Constructor\n"; }
		Person1(Person1&& rhs) { std::cout << "Person1 Move Constructor\n"; }
	};

	struct Person2 : public Person1
	{
		Person2() {}
		Person2(const Person2& rhs) : Person1(rhs) { std::cout << "Person2 Copy Constructor\n"; }
		Person2(Person2&& rhs) : Person1(rhs) { std::cout << "Person2 Move Constructor\n"; }
	};
}