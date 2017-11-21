#pragma once

#include "stddef.h"

template <class T>
class Singleton
{
protected:
	Singleton() {};
	virtual ~Singleton() {};

public:
	static T * GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new T;

		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	static T * m_pInstance;
};

template <class T>
T * Singleton<T>::m_pInstance = NULL;
