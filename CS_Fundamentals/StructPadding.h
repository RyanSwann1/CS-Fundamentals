#pragma once

//https://docs.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-160

namespace StructPadding
{
	struct StructA // sizeof == 8
	{
		char c;
		int i;
	};

	struct StructB //size of == 12
	{
		char c;
		int i;
		char c1;
	};

	struct StructC //sizeof == 8
	{
		char c;
		char c1;
		short s;
		int i;
	};

	struct StructD //sizeof == 24
	{
		char c;
		int i;
		double d;
		float f;
		short s;
		char c1;
	};
};