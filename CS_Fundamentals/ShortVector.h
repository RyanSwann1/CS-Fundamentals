#pragma once

#include <array>
#include <assert.h>
#include <iostream>

//template <typename T>
//class ShortVectorIter
//{
//public:
//	using iterator_category = std::forward_iterator_tag;
//	using difference_type = std::ptrdiff_t;
//	using value_type = T;
//	using pointer = T*;  // or also value_type*
//	using reference = T&;  // or also value_type&
//	
//	ShortVectorIter(T* ptr)
//		: m_ptr(ptr)
//	{}
//
//
//
//private:
//	T* m_ptr;
//};

//using iterator_category = std::forward_iterator_tag;
//using difference_type = std::ptrdiff_t;
//using value_type = int;
//using pointer = int*;  // or also value_type*
//using reference = int&;  // or also value_type&



template <typename T, size_t MaxSize = 1>
class ShortVector
{
public:
	struct ShortVectorIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		ShortVectorIterator(pointer ptr)
			: m_ptr(ptr)
		{}

		reference operator*() { return *m_ptr; };
		pointer operator->() { return m_ptr; };

		ShortVectorIterator& operator++() { m_ptr++; return *this; }
		ShortVectorIterator operator++(int) { ShortVectorConstIterator tmp = *this; ++(*this); return tmp; }

		friend bool operator==(const ShortVectorIterator& a, const ShortVectorIterator& b)
		{
			return a.m_ptr == b.m_ptr;
		}

		friend bool operator!=(const ShortVectorIterator& a, const ShortVectorIterator& b)
		{
			return a.m_ptr != b.m_ptr;
		}

	private:
		pointer m_ptr;
	};

	struct ShortVectorConstIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;

		ShortVectorConstIterator(pointer ptr)
			: m_ptr(ptr)
		{}

		reference operator*() { return *m_ptr; };
		pointer operator->() { return m_ptr; };

		ShortVectorConstIterator& operator++() { m_ptr++; return *this; }
		ShortVectorConstIterator operator++(int) { auto p = m_ptr; m_ptr++; return p; }

		friend bool operator==(const ShortVectorConstIterator& a, const ShortVectorConstIterator& b)
		{
			return a.m_ptr == b.m_ptr;
		}

		friend bool operator!=(const ShortVectorConstIterator& a, const ShortVectorConstIterator& b)
		{
			return a.m_ptr != b.m_ptr;
		}

	private:
		pointer m_ptr;
	};


	ShortVector()
		: m_container(),
		m_currentSize(0)
	{}

	ShortVectorIterator begin()
	{
		return ShortVectorIterator(&m_container[0]);
	}

	ShortVectorConstIterator cbegin() const
	{
		return ShortVectorConstIterator(&m_container[0]);
	}

	ShortVectorIterator end() 
	{
		return ShortVectorIterator(&m_container[m_currentSize]);// m_currentSize]);
	}

	ShortVectorConstIterator cend() const
	{
		return ShortVectorConstIterator(&m_container[m_currentSize]);
	}

	size_t getSize() const
	{
		return m_currentSize;
	}

	void pushBack(T object)
	{
		assert(m_currentSize < MaxSize);
		T* element = &m_container[m_currentSize];
		element = new(element)T(object);
		++m_currentSize;
	}

	void popBack()
	{
		assert(getSize() > 0);
		--m_currentSize;
	}
	
	void clear()
	{
		m_currentSize = 0;
	}

private:
	std::array<T, MaxSize> m_container;
	size_t m_currentSize;
};