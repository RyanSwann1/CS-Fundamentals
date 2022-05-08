#pragma once

namespace constexpr_tutorials
{
	constexpr int getSum()
	{
		return 1 + 2 + 3 + 4 + 5;
	}

	constexpr int maybe_allocate(int i)
	{
		if (i < 3) { return -1; }

		int* p = new int(5);
		int value = *p;
		delete p;
		return value;
	}
}