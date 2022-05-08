#pragma once

//https://docs.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-160

#include <iostream>

namespace StructPadding
{
	struct Data
	{
		char a = 'a';
		char b = 'b';
		int x = 1;
		int y = 2;
		short s = 2;
		char c = 'c';
	};

	void padding_example()
	{
		Data d;
		std::cout << sizeof(d) << "\n";
		char* c = reinterpret_cast<char*>(&d);
		std::cout << *c << "\n";

		std::cout << &d.a - c << "\n";
		std::cout << &d.b - c << "\n";
		std::cout << reinterpret_cast<char*>(&d.x) - c << "\n";
		std::cout << reinterpret_cast<char*>(&d.y) - c << "\n";
		std::cout << reinterpret_cast<char*>(&d.s) - c << "\n";
		std::cout << reinterpret_cast<char*>(&d.c) - c << "\n";
	}

	void pointer_offset_example()
	{
		struct Object
		{
			int number = {};
		};

		struct DerivedObject : public Object
		{
			int number2 = {};
		};

		DerivedObject d;

		Object& o = d;
	}

	void run()
	{
		Data d;
		std::cout << sizeof(d) << "\n";
		char* c = reinterpret_cast<char*>(&d);
		std::cout << "a: " << * c << "\n";
		++c;
		std::cout << "b: " <<  * c << "\n";
		++c;
		++c;
		++c;

		int* i = reinterpret_cast<int*>(c);
		std::cout << "x: " <<  * i << "\n";
		++i;
		std::cout << "y: " << * i << "\n";
		++i;

		short* s = reinterpret_cast<short*>(i);
		std::cout << "s: " << * s << "\n";
		++s;

		c = reinterpret_cast<char*>(s);
		std::cout << "c: " << *c << "\n";
	}
};