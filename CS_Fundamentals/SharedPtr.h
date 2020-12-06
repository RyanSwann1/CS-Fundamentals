#pragma once

#include <assert.h>

template <class T>
struct SharedPtrResource
{
	SharedPtrResource(const T& data)
		: data(data),
		owners(1)
	{}
	SharedPtrResource(const SharedPtrResource&) = delete;
	SharedPtrResource& operator=(const SharedPtrResource&) = delete;
	SharedPtrResource(SharedPtrResource&&) = delete;
	SharedPtrResource& operator=(SharedPtrResource&&) = delete;
	~SharedPtrResource()
	{
		assert(owners == 0);
	}

	T data;
	int owners;
};

template <class T>
class SharedPtr
{
public:
	SharedPtr()
		: m_resource(nullptr)
	{}
	SharedPtr(const T& resource)
		: m_resource(new SharedPtrResource<T>(resource))
	{}
	SharedPtr(const SharedPtr& orig)
		: m_resource(nullptr)
	{
		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			++m_resource->owners;
		}
	}
	SharedPtr& operator=(const SharedPtr& orig)
	{
		if (m_resource)
		{
			--m_resource->owners;
			if (m_resource->owners == 0)
			{
				delete m_resource;
			}
		}

		m_resource = nullptr;
		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			++m_resource->owners;
		}

		return *this;
	}
	SharedPtr(SharedPtr&& orig) noexcept
		: m_resource(nullptr)
	{
		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			orig.m_resource = nullptr;
		}
	}
	SharedPtr& operator=(SharedPtr&& orig) noexcept
	{
		if (m_resource)
		{
			--m_resource->owners;
			if (m_resource->owners == 0)
			{
				delete m_resource;
			}
		}

		m_resource = nullptr;
		if (orig.m_resource)
		{
			m_resource = orig.m_resource;
			orig.m_resource = nullptr;
		}

		return *this;
	}
	~SharedPtr()
	{
		clear();
	}

	void reset()
	{
		clear();
	}

	const T& getResource() const
	{
		assert(m_resource);
		return m_resource->data;
	}

	T& getResource() 
	{
		assert(m_resource);
		return m_resource->data;
	}

private:
	SharedPtrResource<T>* m_resource;

	void clear()
	{
		if (m_resource)
		{
			assert(m_resource->owners >= 1);
			--m_resource->owners;
			if (m_resource->owners == 0)
			{
				delete m_resource;
			}

			m_resource = nullptr;
		}
	}
};