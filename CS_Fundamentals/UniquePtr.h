#pragma once

#include <assert.h>

template <class T>
class UniquePtr
{
public:
	UniquePtr()
		: m_resource(nullptr)
	{}
	UniquePtr(T* resource)
		: m_resource(resource)
	{
		assert(m_resource);
	}
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;
	UniquePtr(UniquePtr&& orig) noexcept
		: m_resource(nullptr)
	{
		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			orig.m_resource = nullptr;
		}
	}
	UniquePtr& operator=(UniquePtr&& orig) noexcept
	{
		if (m_resource)
		{
			delete m_resource;
		}

		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			orig.m_resource = nullptr;
		}

		return *this;
	}
	~UniquePtr()
	{
		if (m_resource)
		{
			delete m_resource;
		}
	}

	T& getResource()
	{
		assert(m_resource);
		return *m_resource;
	}

private:
	T* m_resource;
};