#pragma once

namespace Tmpl8
{
	template<typename T>
	class vector
	{
	public:
		vector() :
			m_size(0),
			m_capacity(1),
			m_elements((T*)malloc(sizeof(T)))
		{
		}

		~vector()
		{
			free((void*)m_elements);
		}

		unsigned int Size()
		{
			return m_size;
		}

		void Clear()
		{
			m_size = 0;
			m_capacity = 1;
			free((void*)m_elements);
			m_elements = (T*)malloc(sizeof(T));
		}

		void PushBack(const T& el)
		{
			if (m_size < m_capacity)
			{
				m_elements[m_size] = el;
			}
			else
			{
				m_capacity = m_size * 2;

				T* elements = (T*)malloc(m_capacity * sizeof(T));

				memcpy(elements, m_elements, sizeof(T) * m_size);

				elements[m_size] = el;

				free(m_elements);

				m_elements = elements;
			}

			m_size++;
		}

		void Remove(unsigned int index)
		{
			const unsigned int newSize = m_size - 1;

			if (newSize == 0)
			{
				Clear();
				return;
			}

			char* elements = (char*)malloc(sizeof(T) * newSize);

			const unsigned int firstHalf = sizeof(T) * (index + 1) - sizeof(T);
			const unsigned int secondHalf = (m_size * sizeof(T)) - firstHalf - sizeof(T);

			auto offset = firstHalf + sizeof(T);

			memcpy(elements, m_elements, firstHalf);
			memcpy(elements + firstHalf, m_elements + offset, secondHalf);

			free((void*)m_elements);

			m_size--;
			m_elements = (T*)elements;
		}

		/*
		void Remove(const Vector<int>& clearIds)
		{
			for (unsigned int i = 0; i < clearIds.m_size; i++)
				Remove((*clearIds[i]) - i);
		}
		*/

		T* At(unsigned int index) const
		{
			return &m_elements[index];
		}

		T* operator [] (unsigned int index) const
		{
			return &m_elements[index];
		}

	public:
		T* m_elements;
		unsigned int m_capacity;
		unsigned int m_size;
	};
}