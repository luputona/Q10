#pragma once
#include<vector>

template<class T>
class Object
{
private:
	bool m_isActive;
	T *m_pObject;

public:
	Object()
	{
		m_isActive = false;
		m_pObject = NULL;
	}
	~Object()
	{
		if (m_pObject != NULL)
		{
			delete m_pObject;
		}
	}

	void SetActive(bool b)
	{
		m_isActive = b;
	}
	void SetObject(T *pObj)
	{
		m_pObject = pObj;
	}
	
	bool GetActive()
	{
		return m_isActive;
	}
	T *GetObjects()
	{
		return m_pObject;
	}
};

template <class T>
class ObjectPool
{
private:
	std::vector<Object<T> *> m_pooledObjects;
	int m_amountPool;

public:
	ObjectPool(int size)
	{
		m_amountPool = size;

		for (int i = 0; i < m_amountPool; i++)
		{
			Object<T> *pObj = new Object<T>;
			pObj->SetActive(false);
			pObj->SetObject(new T);
			m_pooledObjects.push_back(pObj);
		}
	}
	~ObjectPool()
	{
		for (int i = 0; i < m_amountPool; i++)
		{
			delete m_pooledObjects[i];
		}
	}

	Object<T> *GetPooledObject()
	{
		for (int i = 0; i < m_amountPool; i++)
		{
			if (!m_pooledObjects[i]->GetActive())
			{
				return m_pooledObjects[i];
			}
		}
		return NULL;
	}

	Object<T> *GetPooledObject(int index)
	{
		if (index < 0 || index >= m_amountPool) 
		{
			return NULL;
		}

		return m_pooledObjects[index];
	}

	int GetAmountPool()
	{
		return m_amountPool;
	}

};