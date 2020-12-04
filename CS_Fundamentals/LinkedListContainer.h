#pragma once
#include <assert.h>
#include <iostream>

template <class T>
struct LinkedListNode
{
	LinkedListNode(const T& data, LinkedListNode* next)
		: data(data),
		next(next)
	{}

	T data;
	LinkedListNode* next;
};

template <class T>
class LinkedListContainer
{
public:
	LinkedListContainer()
		: m_head(nullptr),
		m_tail(nullptr),
		m_size(0)
	{}
	LinkedListContainer(const LinkedListContainer&) = delete;
	LinkedListContainer& operator=(const LinkedListContainer&) = delete;
	LinkedListContainer(LinkedListContainer&&) = delete;
	LinkedListContainer& operator=(LinkedListContainer&&) = delete;
	~LinkedListContainer()
	{
		clear();
	}

	void pushBack(const T& data)
	{
		if (m_size == 0)
		{
			assert(!m_head && !m_tail);
			
			LinkedListNode<T>* node = new LinkedListNode<T>(data, nullptr);
			m_head = node;
			m_tail = node;
		}
		else if(m_size == 1)
		{
			assert(m_head && m_tail && m_head == m_tail);

			LinkedListNode<T>* node = new LinkedListNode<T>(data, nullptr);
			m_head->next = node;
			m_tail = node;
		}
		else
		{
			assert(m_head && m_tail && m_head != m_tail);
			assert(!m_tail->next);

			LinkedListNode<T>* node = new LinkedListNode<T>(data, nullptr);
			m_tail->next = node;
			m_tail = node;
		}

		++m_size;
	}

	void pushFront(const T& data)
	{
		if (m_size == 0)
		{
			assert(!m_head && !m_tail);

			LinkedListNode<T>* node = new LinkedListNode<T>(data, nullptr);
			m_head = node;
			m_tail = node;
		}
		else
		{
			assert(m_head && m_tail);
			
			LinkedListNode<T>* node = new LinkedListNode<T>(data, nullptr);
			LinkedListNode<T>* oldHead = m_head;
			m_head = node;
			m_head->next = oldHead;
		}

		++m_size;
	}

	void clear()
	{
		if (!isEmpty())
		{
			LinkedListNode<T>* node = &getHead();
			while (node)
			{
				LinkedListNode<T>* next = node->next;
				delete node;
				node = next;
			}

			m_size = 0;
		}
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	size_t getSize() const
	{
		return m_size;
	}

	LinkedListNode<T>& getHead()
	{
		assert(m_head && m_size > 0);
		return *m_head;
	}

	LinkedListContainer<T>& getTail()
	{
		assert(m_tail && m_size > 0);
		return *m_tail;
	}

private:
	LinkedListNode<T>* m_head;
	LinkedListNode<T>* m_tail;
	size_t m_size;
};