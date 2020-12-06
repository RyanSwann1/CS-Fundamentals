#pragma once

#include <assert.h>
#include <array>

template <class Value>
struct UnorderedMapNode
{
	UnorderedMapNode(const Value& data)
		: data(data),
		next(nullptr)
	{}
	UnorderedMapNode(const UnorderedMapNode&) = delete;
	UnorderedMapNode& operator=(const UnorderedMapNode&) = delete;
	UnorderedMapNode(UnorderedMapNode&& orig) noexcept
		: data(std::move(orig.data)),
		next(orig.next)
	{
		orig.next = nullptr;
	}
	UnorderedMapNode& operator=(UnorderedMapNode&& orig) noexcept
	{
		data = std::move(orig.data);
		next = orig.next;

		orig.next = nullptr;
	}
	
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
				while(node)
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
			m_buckets[hashKey] = new UnorderedMapNode<Value>(data);
		}
		else
		{
			UnorderedMapNode<Value>* node = m_buckets[hashKey];
			while (node->next)
			{
				node = node->next;
			}

			node->next = new UnorderedMapNode<Value>(data);
		}
	}

	size_t remove(int key)
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