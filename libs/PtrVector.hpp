#ifndef PTRVECTOR_H_INCLUDED
#define PTRVECTOR_H_INCLUDED

#include <cstdlib>
#include <vector>

template<typename V>
class PtrVector
{
		std::vector<V *> m_vector;

	public:
		typedef typename std::vector<V *>::iterator iterator;
		typedef typename std::vector<V *>::const_iterator const_iterator;

		PtrVector(){}

		~PtrVector()
		{
			for(iterator it = m_vector.begin(); it != m_vector.end(); ++it)
				delete *it;
		}

		void push_back(V * value)	{ m_vector.push_back(value); }
		V & operator [](size_t id)	{ return *m_vector[id]; }
		size_t size()				{ return m_vector.size(); }
		bool empty()				{ return m_vector.empty(); }
		 iterator begin()	{ return m_vector.begin(); }
		 iterator end()		{ return m_vector.end(); }
};


#endif // PTRVECTOR_H_INCLUDED
