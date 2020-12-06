#pragma once
#include <assert.h>

template <class T>
struct SingleLinkedListNode
{
	SingleLinkedListNode(const T& data, SingleLinkedListNode* next = nullptr)
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
		m_tail(nullptr),
		m_size(0)
	{}
	SingleLinkedList(const SingleLinkedList& orig)
		: m_head(nullptr),
		m_tail(nullptr),
		m_size(0)
	{
		const SingleLinkedListNode<T>* node = orig.m_head;
		while (node)
		{
			pushBack(node->data);
			node = node->next;
		}
	}
	SingleLinkedList& operator=(const SingleLinkedList& orig)
	{
		clear();
		const SingleLinkedListNode<T>* node = orig.m_head;
		while (node)
		{
			pushBack(node->data);
			node = node->next;
		}

		return *this;
	}
	SingleLinkedList(SingleLinkedList&& orig) noexcept
	{
		m_head = orig.m_head;
		m_tail = orig.m_tail;
		m_size = orig.m_size;
	
		orig.m_head = nullptr;
		orig.m_tail = nullptr;
		orig.m_size = 0;
	}
	SingleLinkedList& operator=(SingleLinkedList&& orig) noexcept
	{
		clear();

		m_head = orig.m_head;
		m_tail = orig.m_tail;
		m_size = orig.m_size;

		orig.m_head = nullptr;
		orig.m_tail = nullptr;
		orig.m_size = 0;

		return *this;
	}
	~SingleLinkedList()
	{
		clear();
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	void pushFront(const T& data)
	{
		if (m_size == 0)
		{
			assert(!m_head && !m_tail);
			SingleLinkedListNode<T>* node = new SingleLinkedListNode<T>(data, nullptr);
			m_head = node;
			m_tail = node;
		}
		else if (m_size == 1)
		{
			assert(m_head && m_tail);
			SingleLinkedListNode<T>* node = new SingleLinkedListNode<T>(data, m_head);
			m_head = node;
			m_head->next = m_tail;
		}
		else
		{
			assert(m_head && m_tail);
			SingleLinkedListNode<T>* node = new SingleLinkedListNode<T>(data, m_head);
			m_head = node;
		}

		++m_size;
	}

	void remove(const T& data)
	{
		assert(!isEmpty() && m_head && m_tail);

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

		m_tail = previousNode;
		m_size -= nodesDeleted;
	}

	void clear()
	{
		if (!isEmpty())
		{
			assert(m_head && m_tail);

			SingleLinkedListNode<T>* node = m_head;
			while (node)
			{
				SingleLinkedListNode<T>* nextNode = node->next;
				delete node;
				node = nextNode;
			}

			m_head = nullptr;
			m_tail = nullptr;
			m_size = 0;
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
	SingleLinkedListNode<T>* m_tail;
	size_t m_size;

	void pushBack(const T& data)
	{
		SingleLinkedListNode<T>* node = new SingleLinkedListNode<T>(data);
		
		if (m_size == 0)
		{
			assert(!m_head && !m_tail);
			m_head = node;
			m_tail = node;
		}
		else if (m_size == 1)
		{
			assert(m_head && m_tail);
			m_head->next = node;
			m_tail = node;
		}
		else
		{
			assert(m_head && m_tail);
			m_tail->next = node;
			m_tail = node;
		}

		++m_size;
	}
};