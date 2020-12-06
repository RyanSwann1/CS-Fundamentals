#pragma once
#include <assert.h>
#include <iostream>

template <class T>
struct DoublyLinkedListNode
{
	DoublyLinkedListNode(const T& data, DoublyLinkedListNode<T>* previous = nullptr, 
		DoublyLinkedListNode<T>* next = nullptr)
		: data(data),
		previous(previous),
		next(next)
	{}

	T data;
	DoublyLinkedListNode<T>* previous;
	DoublyLinkedListNode<T>* next;
};

template <class T>
class DoublyLinkedList
{
public:
	DoublyLinkedList()
		: m_head(nullptr),
		m_tail(nullptr),
		m_size(0)
	{}
	DoublyLinkedList(const DoublyLinkedList& orig)
		: m_head(nullptr),
		m_tail(nullptr),
		m_size(0)
	{
		if (!orig.isEmpty())
		{
			DoublyLinkedListNode<T>* node = orig.m_head;
			while (node)
			{
				pushBack(node->data);
				node = node->next;
			}
		}
	}
	DoublyLinkedList& operator=(const DoublyLinkedList& orig)
	{
		if (!isEmpty())
		{
			clear();
		}

		if (!orig.isEmpty())
		{
			DoublyLinkedListNode<T>* node = orig.m_head;
			while (node)
			{
				pushBack(node->data);
				node = node->next;
			}
		}

		return *this;
	}
	DoublyLinkedList(DoublyLinkedList&& orig) noexcept
		: m_head(orig.m_head),
		m_tail(orig.m_tail),
		m_size(orig.m_size)
	{
		orig.m_head = nullptr;
		orig.m_tail = nullptr;
		orig.m_size = 0;
	}
	DoublyLinkedList& operator=(DoublyLinkedList&& orig) noexcept
	{
		if (!isEmpty())
		{
			clear();
		}

		m_head = orig.m_head;
		m_tail = orig.m_tail;
		m_size = orig.m_size;

		orig.m_head = nullptr;
		orig.m_tail = nullptr;
		orig.m_size = 0;

		return *this;
	}
	~DoublyLinkedList()
	{
		if (!isEmpty())
		{
			clear();
		}
	}

	void pushBack(const T& data)
	{
		if (m_size == 0)
		{
			assert(!m_head && !m_tail);
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(data);
			m_head = node;
			m_tail = node;
		}
		else 
		{
			assert(m_head && m_tail);

			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(data, m_tail);
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
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(data);
			m_head = node;
			m_tail = node;
		}
		else
		{
			assert(m_head && m_tail);

			DoublyLinkedListNode<T> node = new DoublyLinkedListNode<T>(data, nullptr, m_head);
			m_head = node;
		}
	}

	void remove(DoublyLinkedListNode<T>& node)
	{
		assert(!isEmpty() && m_head && m_tail);
		
		if (m_head == &node)
		{
			DoublyLinkedListNode<T>* nextNode = node.next;
			delete m_head;
			if (nextNode)
			{
				m_head = nextNode;
			}
			else
			{
				m_head = nullptr;
			}
		}
		else if(m_tail == &node)
		{
			DoublyLinkedListNode<T>* previousNode = node.previous;
			delete m_tail;
			if (m_tail)
			{
				m_tail = previousNode;
			}
			else
			{
				m_tail = nullptr;
			}
		}
		else
		{
			DoublyLinkedListNode<T>* previousNode = node.previous;
			DoublyLinkedListNode<T>* nextNode = node.next;

			delete &node;
			previousNode->next = nextNode;
			nextNode->previous = previousNode;
		}

		--m_size;
	}

	DoublyLinkedListNode<T>* get(const T& data)
	{
		assert(!isEmpty() && m_head && m_tail);
		DoublyLinkedListNode<T>* node = m_head;
		while (node)
		{
			if (node->data == data)
			{
				return node;
			}
			
			node = node->next;
		}

		return nullptr;
	}

	void clear()
	{
		assert(!isEmpty() && m_head && m_tail);

		DoublyLinkedListNode<T>* node = m_head;
		while (node)
		{
			DoublyLinkedListNode<T>* nextNode = node->next;
			delete node;
			node = nextNode;
		}

		m_size = 0;
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	const DoublyLinkedListNode<T>& getHead() const
	{
		return *m_head;
	}

	const DoublyLinkedListNode<T>& getTail() const
	{
		return *m_tail;
	}

private:
	DoublyLinkedListNode<T>* m_head;
	DoublyLinkedListNode<T>* m_tail;
	size_t m_size;
};