#pragma once
#include <assert.h>

//https://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi

template <class T>
class VectorContainer
{
public:
	VectorContainer()
		: m_size(0),
		m_capacity(0),
		m_buffer(nullptr)
	{}
	VectorContainer(size_t initialSize, const T& object)
		: m_size(initialSize),
		m_capacity(initialSize),
		m_buffer(nullptr)
	{
		init(initialSize, object);
	}
	VectorContainer(const VectorContainer& orig)
		: m_size(orig.m_size),
		m_capacity(orig.m_capacity)
	{
		if (m_buffer)
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		if (orig.m_buffer)
		{
			reset(orig.m_buffer, orig.m_size);
		}
	}
	VectorContainer& operator=(const VectorContainer& orig)
	{
		m_size = orig.m_size;
		m_capacity = orig.m_capacity;

		if (m_buffer)
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		if (orig.m_buffer)
		{
			reset(orig.m_buffer, orig.m_size);
		}

		return *this;
	}
	VectorContainer(VectorContainer&& orig) noexcept
		: m_size(orig.m_size),
		m_capacity(orig.m_capacity)
	{
		if (m_buffer)
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		if (orig.m_buffer)
		{
			m_buffer = orig.m_buffer;
			orig.m_buffer = nullptr;
			orig.m_size = 0;
			orig.m_capacity = 0;
		}
	}
	VectorContainer& operator=(VectorContainer&& orig) noexcept
	{
		m_size = orig.m_size;
		m_capacity = orig.m_capacity;

		if (m_buffer)
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		if (orig.m_buffer)
		{
			m_buffer = orig.m_buffer;
			orig.m_buffer = nullptr;
			orig.m_size = 0;
			orig.m_capacity = 0;
		}

		return *this;
	}
	~VectorContainer()
	{
		if (m_buffer)
		{
			delete[] m_buffer;
		}
	}

	size_t getSize() const
	{
		return m_size;
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	void popBack()
	{
		assert(m_size > 0);
		--m_size;
	}

	void erase()
	{
		m_size = 0;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity > m_capacity)
		{
			m_capacity = newCapacity * 2;
			if (!m_buffer)
			{
				m_buffer = new T[m_capacity];
			}
			else
			{
				T* newBuffer = new T[m_capacity];
				for (int i = 0; i < m_size; ++i)
				{
					newBuffer[i] = m_buffer[i];
				}
				delete m_buffer;
				m_buffer = newBuffer;
			}
		}
	}

	void pushBack(const T& object)
	{
		if (!m_buffer)
		{
			init(1, object);
		}
		else
		{
			assert(m_size <= m_capacity);
			if (m_size == m_capacity)
			{
				size_t oldCapacity = m_capacity;
				m_capacity = m_capacity * 2;
				T* newBuffer = new T[m_capacity];
				for (int i = 0; i < oldCapacity; ++i)
				{
					newBuffer[i] = m_buffer[i];
				}

				delete m_buffer;
				m_buffer = newBuffer;
			}

			m_buffer[m_size] = object;
			++m_size;
		}
	}

	void removeAtPosition(size_t i)
	{
		assert(i < m_size);

		m_buffer[i].~T();
		if (i < m_size - 1)
		{
			for (int j = i + 1; j < m_size; ++j)
			{
				m_buffer[j - 1] = m_buffer[j];
			}
		}
	}

	void addItem(const T& item, int i)
	{
		assert(i < m_size);

		if (i == m_size - 1)
		{
			pushBack(item);
		}
		else
		{
			T lastValue = m_buffer[m_size - 1];
			for (int j = i + 1; j < m_size - 1; ++j)
			{
				m_buffer[j] = m_buffer[j - 1];
			}

			m_buffer[i] = item;
			pushBack(lastValue);
		}
	}

	void removeItem(const T& item)
	{
		for (int i = 0; i < m_size; ++i)
		{
			if (m_buffer[i] == item)
			{
				removeAtPosition(i);
			}
		}
	}

	T& get(size_t i)
	{
		assert(i < m_size);
		return m_buffer[i];
	}

private:
	size_t m_size;
	size_t m_capacity;
	T* m_buffer;

	void init(size_t initialSize, const T& object)
	{
		assert(!m_buffer);

		m_buffer = new T[initialSize];
		m_size = initialSize;
		m_capacity = m_size;

		for (int i = 0; i < initialSize; ++i)
		{
			m_buffer[i] = object;
		}
	}

	void reset(const T* otherBuffer, size_t otherSize)
	{
		assert(otherBuffer && !m_buffer);
		m_buffer = new T[otherSize];

		for (int i = 0; i < otherSize; ++i)
		{
			m_buffer[i] = otherBuffer[i];
		}
	}
};