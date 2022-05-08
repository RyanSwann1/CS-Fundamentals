#pragma once

#include <vector>
#include <string>

namespace explicit_keyword
{
	struct Object
	{
		Object(int i)
			: number(i)
		{}
		Object(std::string s) {}

		int number = { 0 };
	};

	void foo(Object o)
	{

	}

	struct ExplicitObject
	{
		explicit ExplicitObject(int i)
		{

		}
		explicit ExplicitObject(std::string s)
		{

		}
	};

	void explicit_foo(ExplicitObject o)
	{

	}

	void run()
	{
		foo(42);
		foo({ "asds" });

		Object o = { 42 };

		ExplicitObject o = { "asda" };
		explicit_foo({ "sdsd" });

	}
}