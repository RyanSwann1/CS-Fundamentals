#pragma once
#include <assert.h>

template <class T>
struct SingleLinkedListNode
{
	SingleLinkedListNode(const T& data, SingleLinkedListNode* next)
		: data(data),
		next(next)
	{}

	T data;
	SingleLinkedListNode* next;
};

template <class T>
class SingleLinkedList
{
public:
	SingleLinkedList()
		: m_head(nullptr),
		m_size(0)
	{}
	SingleLinkedList(const SingleLinkedList&) = delete;
	SingleLinkedList& operator=(const SingleLinkedList&) = delete;
	SingleLinkedList(SingleLinkedList&& orig) noexcept
	{
		m_head = orig.m_head;
		m_size = orig.m_size;
	
		orig.m_head = nullptr;
		orig.m_size = 0;
	}
	SingleLinkedList& operator=(SingleLinkedList&& orig) noexcept
	{
		if (!isEmpty())
		{
			clear();
		}

		m_head = orig.m_head;
		m_size = orig.m_size;

		orig.m_head = nullptr;
		orig.m_size = 0;

		return *this;
	}
	~SingleLinkedList()
	{
		if (!isEmpty())
		{
			clear();
		}
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	void pushFront(const T& data)
	{
		if (!isEmpty())
		{
			assert(m_head);

			SingleLinkedListNode<T>* node = new SingleLinkedListNode<T>(data, m_head);
			m_head = node;
		}
		else
		{
			assert(!m_head);
			m_head = new SingleLinkedListNode<T>(data, nullptr);
		}

		++m_size;
	}

	void remove(const T& data)
	{
		assert(!isEmpty() && m_head);

		SingleLinkedListNode<T>* node = m_head;
		SingleLinkedListNode<T>* previousNode = nullptr;
		size_t nodesDeleted = 0;
		for (int i = 0; i < m_size; ++i)
		{
			assert(node);
			if (node->data == data)
			{
				if (node == m_head)
				{
					SingleLinkedListNode<T>* nextNode = node->next;
					m_head = nextNode;
					delete node;
					node = nextNode;
				}
				else
				{
					if (previousNode)
					{
						previousNode->next = node->next;
					}

					SingleLinkedListNode<T>* nextNode = node->next;
					delete node;
					node = nextNode;
				}

				++nodesDeleted;
			}
			else
			{
				previousNode = node;
				node = node->next;
			}
		}

		m_size -= nodesDeleted;
	}

	void clear()
	{
		assert(!isEmpty());

		SingleLinkedListNode<T>* node = m_head;
		while (node)
		{
			SingleLinkedListNode<T>* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}

	SingleLinkedListNode<T>& getHead()
	{
		assert(!isEmpty() && m_head);
		return *m_head;
	}

	const SingleLinkedListNode<T>& getHead() const
	{
		assert(!isEmpty() && m_head);
		return *m_head;
	}

private:
	SingleLinkedListNode<T>* m_head;
	size_t m_size;
};