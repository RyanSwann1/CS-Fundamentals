#pragma once

#include <assert.h>
#include <unordered_map>
#include <string>

//https://www.youtube.com/watch?v=LsjFAx-dG5I
//https://www.cs.usfca.edu/~galles/visualization/OpenHash.html

//https://stackoverflow.com/questions/50073376/how-does-stdunordered-map-store-and-compare-its-keys-to-achieve-fast-access-to

namespace manual
{
	template <class Value>
	struct UnorderedMapNode
	{
		UnorderedMapNode(int key, const Value& data)
			: key(key),
			data(data),
			next(nullptr)
		{}
		UnorderedMapNode(const UnorderedMapNode&) = delete;
		UnorderedMapNode& operator=(const UnorderedMapNode&) = delete;
		UnorderedMapNode(UnorderedMapNode&& orig) noexcept
			: key(orig.key),
			data(std::move(orig.data)),
			next(orig.next)
		{
			orig.next = nullptr;
		}
		UnorderedMapNode& operator=(UnorderedMapNode&& orig) noexcept
		{
			key = orig.key;
			data = std::move(orig.data);
			next = orig.next;

			orig.next = nullptr;
		}

		int key;
		Value data;
		UnorderedMapNode* next;
	};

	template <class Value>
	class UnorderedMap
	{
	public:
		UnorderedMap()
			: m_buckets()
		{}
		UnorderedMap(const UnorderedMap& orig)
			: m_buckets()
		{
			for (int i = 0; i < orig.m_buckets.size(); ++i)
			{
				if (orig.m_buckets[i])
				{
					UnorderedMapNode<Value>* node = orig.m_buckets[i];
					int hashKey = getHashKey(i);
					while (node)
					{
						insert(hashKey, node->data);
						node = node->next;
					}
				}
			}
		}
		UnorderedMap& operator=(const UnorderedMap& orig)
		{
			clear();

			for (int i = 0; i < orig.m_buckets.size(); ++i)
			{
				if (orig.m_buckets[i])
				{
					UnorderedMapNode<Value>* node = orig.m_buckets[i];
					int hashKey = getHashKey(i);
					while (node)
					{
						insert(hashKey, node->data);
						node = node->next;
					}
				}
			}
		}
		UnorderedMap(UnorderedMap&& orig) noexcept
		{
			m_buckets = std::move(orig.m_buckets);

			for (auto& bucket : orig.m_buckets)
			{
				bucket = nullptr;
			}
		}
		UnorderedMap& operator=(UnorderedMap&& orig) noexcept
		{
			clear();

			m_buckets = std::move(orig.m_buckets);

			for (auto& bucket : orig.m_buckets)
			{
				bucket = nullptr;
			}

			return *this;
		}
		~UnorderedMap()
		{
			clear();
		}

		void insert(int key, const Value& data)
		{
			int hashKey = getHashKey(key);
			if (!m_buckets[hashKey])
			{
				m_buckets[hashKey] = new UnorderedMapNode<Value>(key, data);
			}
			else
			{
				UnorderedMapNode<Value>* previousNode = m_buckets[hashKey];
				UnorderedMapNode<Value>* node = m_buckets[hashKey];
				bool addElement = true;
				while (node)
				{
					if (node->key == key)
					{
						addElement = false;
						break;
					}

					previousNode = node;
					node = node->next;
				}

				if (addElement)
				{
					previousNode->next = new UnorderedMapNode<Value>(key, data);
				}
			}
		}

		UnorderedMapNode<Value>* find(int key)
		{
			int hashKey = getHashKey(key);
			if (m_buckets[hashKey])
			{
				UnorderedMapNode<Value>* node = m_buckets[hashKey];
				while (node)
				{
					if (node->key == key)
					{
						return node;
					}
				}
			}

			return nullptr;
		}

		size_t emptyBucket(int key)
		{
			size_t nodesDeleted = 0;
			int hashKey = getHashKey(key);

			UnorderedMapNode<Value>* node = m_buckets[hashKey];
			while (node)
			{
				UnorderedMapNode<Value>* nextNode = node->next;
				delete node;
				++nodesDeleted;
				node = nextNode;
			}

			m_buckets[hashKey] = nullptr;
			return nodesDeleted;
		}

		void remove(int key)
		{
			int hashKey = getHashKey(key);
			assert(m_buckets[hashKey]);

			UnorderedMapNode<Value>* previousNode = m_buckets[hashKey];
			UnorderedMapNode<Value>* node = m_buckets[hashKey];
			bool elementDeleted = false;
			while (!elementDeleted && node)
			{
				if (node == m_buckets[hashKey])
				{
					UnorderedMapNode<Value>* nextNode = node->next;
					delete node;
					if (nextNode)
					{
						m_buckets[hashKey] = nextNode;
						elementDeleted = true;
					}
				}
				else
				{
					UnorderedMapNode<Value>* nextNode = node->next;
					if (node->key == key)
					{
						delete node;
						elementDeleted = true;
					}

					previousNode->next = nextNode;
				}

				node = node->next;
			}
		}

		void clear()
		{
			for (auto& bucket : m_buckets)
			{
				if (bucket)
				{
					UnorderedMapNode<Value>* node = bucket;
					while (node)
					{
						UnorderedMapNode<Value>* nextNode = node->next;
						delete node;
						node = nextNode;
					}

					bucket = nullptr;
				}
			}
		}

	private:
		std::array<UnorderedMapNode<Value>*, 8> m_buckets;

		int getHashKey(int key) const
		{
			return key % static_cast<int>(m_buckets.size());
		}
	};
}

namespace unordered_map_lesson
{
	void rehash()
	{
		std::unordered_map<std::string, int> m;
		for (int i = 0; i < 100; ++i)
		{
			m.emplace(std::piecewise_construct,
				std::forward_as_tuple("Hello" + std::to_string(i)),
				std::forward_as_tuple(1));
		}

 		const size_t oldSize =  m.bucket_count();
		const float oldLoadFactor = m.load_factor();
		m.rehash(1000);
		const size_t newSize = m.bucket_count();
		const float newLoadFactor = m.load_factor();
		int i = 0;
	}

	void reserve()
	{
		std::unordered_map<std::string, int> m;
		m.reserve(64);
		for (int i = 0; i < 64; ++i)
		{
			m.emplace(std::piecewise_construct,
				std::forward_as_tuple("Hello" + std::to_string(i)),
				std::forward_as_tuple(1));
		}

		const size_t bucketCount = m.bucket_count();
		int i = 0;
	}

	void run()
	{
		rehash();
		reserve();
		//auto hash = [](const std::string& s)
		//{
		//	return 0;
		//};

		//std::unordered_map<std::string, int, decltype(hash)> m{ 0, hash }; 
		//for (int i = 0; i < 100; ++i)
		//{
		//	m.emplace(std::piecewise_construct,
		//		std::forward_as_tuple("Hello" + std::to_string(i)),
		//		std::forward_as_tuple(1));
		//}

		//const size_t bucketSize = m.bucket_size(0);
		//const size_t bucketCount = m.bucket_count();
		//
		//const float loadFactor = m.load_factor();
		//const float maxLoadFactor = m.max_load_factor();
		//const size_t maxBucketCount = m.max_bucket_count();

		//int i = 0;
		//m.rehash(1000);
	}
}