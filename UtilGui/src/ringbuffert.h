#ifndef RINGBUFFERT_H
#define RINGBUFFERT_H

#include <iostream>

using namespace std;

template <class T>
class RingBuffer
{
    private:
        unsigned int m_size;//队列大小
        int m_front;//队列头
        int m_rear;//队列尾
        T*  m_data;//队列数组
    public:
        RingBuffer(unsigned size)
            :m_size(size),
            m_front(0),
            m_rear(0)
        {
            m_data = new T[size];
        }

        ~RingBuffer()
        {
            delete [] m_data;
        }

        bool isEmpty()
        {
            return m_front == m_rear;
        }

        bool isFull()
        {
            return m_front == (m_rear + 1)%m_size;
        }

		void push_front(T ele)
		{
			if (m_data == NULL)
			{
				return false;
			}

			if ( (m_front-1+m_size)%m_size == m_rear)
			{
				return false;
			}

			m_front = (m_front - 1 + m_size) % m_size;
			m_data[m_front] = ele;
			return true;
		}

        void push_back(T ele)throw(bad_exception)
        {
            if(isFull())
            {
                throw bad_exception();
            }
            m_data[m_rear] = ele;
            m_rear = (m_rear + 1)%m_size;
        }

		T front()
		{
			T ret = m_data[m_front];
			return ret;
		}

        T pop_front() throw(bad_exception)
        {
            if(isEmpty())
            {
                throw bad_exception();
            }
            T tmp = m_data[m_front];
            m_front = (m_front + 1)%m_size;
            return tmp;
        }

		int total_size() const
		{
			return m_size;
		}

		bool resize(int size)
		{
			if (size < 0 )
			{
				return false;
			}

			int iLen = sizeof(T);
			if (m_data == NULL)
			{
				m_data = (T*)malloc(sizeof(T)*size);
				if (m_data == NULL)
				{
					return false;
				}
				m_size = size;
				return true;
			}

			T* pNewArray = (T*)realloc(m_data, sizeof(T)*size);
			if (pNewArray == NULL)
			{
				return false;
			}
			m_data = pNewArray;
			m_size = size;
			return true;
		}
};
#endif // RINGBUFFERT_H
