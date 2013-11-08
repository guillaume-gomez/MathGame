#ifndef PTRLIST_H_INCLUDED
#define PTRLIST_H_INCLUDED

#include <list>

template<typename V>
class PtrList
{
		std::list<V *> m_list;

	public:
		typedef typename std::list<V *>::iterator iterator;
		typedef typename std::list<V *>::const_iterator const_iterator;

		PtrList(){}

		~PtrList()
		{
			for(iterator it = m_list.begin(); it != m_list.end(); ++it)
				delete *it;
		}

		void push_back(V * value) { m_list.push_back(value); }
		void push_front(V * value) { m_list.push_front(value); }

		void remove(V * value)
		{
			delete value;
			m_list.remove(value);
		}

		void erase(iterator it)
		{
			delete *it;
			m_list.erase(it);
		}

		size_t size()			{ return m_list.size(); }
		bool empty()			{ return m_list.empty(); }
        iterator begin()	{ return m_list.begin(); }
        iterator end()		{ return m_list.end(); }
};

#endif // PTRLIST_H_INCLUDED
