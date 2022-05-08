#pragma once

#include <functional>
#include <iostream>
#include <chrono>

namespace std_function
{
	//Unable to inline std function call
	void run_1()
	{
		const auto print = [](const auto i)
		{
			std::cout << i << "\n";
		};

		std::function<void(int)> f = { print };
		f(5);
	}

	//Captured variables can cause heap allocation for std function if exceed certain size
	void run_2()
	{
		std::string name = "Bert";
		const auto print = [name]()
		{
			std::cout << name << "\n";
		};

		std::function<void()> f = { print };
		f();
	}



	void run()
	{

	}
}