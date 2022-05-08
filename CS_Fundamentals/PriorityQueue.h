#pragma once

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>

namespace priority_queue
{
	struct Document
	{
		Document(std::string s)
			: s(std::move(s))
		{}

		friend bool operator<(Document& lhs, Document& rhs)
		{
			return lhs.s < rhs.s;
		}

		std::string s{};
	};

	struct Hit
	{
		float rank{};
		Document* d{};
	};

	void run()
	{
		std::vector<int> numbers{ 2, 7, 4, 6, 8, 1, 10 };
		std::make_heap(numbers.begin(), numbers.end());
		int i = 0;
		
		//std::set<Document> m;
		//for (size_t i = 0; i < length; i++)
		//{

		//}

		//std::priority_queue<int> q;


	}
}