#ifndef SCOPEDPTR_H_INCLUDED
#define SCOPEDPTR_H_INCLUDED

template <class T>
class ScopedPtr
{
		T*   m_ptr;

		ScopedPtr(const ScopedPtr &);
		ScopedPtr & operator=(const ScopedPtr &);
	public:
		ScopedPtr() : m_ptr(0) {}
		ScopedPtr(T* ptr) : m_ptr(ptr) {}

		~ScopedPtr() { delete m_ptr; }

		T & operator * () { return *m_ptr; }
		T * operator ->() { return m_ptr; }
		operator T*() const { return m_ptr; }

		void reset(T * ptr)
		{
			if(m_ptr != 0)
				delete m_ptr;
			m_ptr = ptr;
		}

		T * get() const { return m_ptr; }
};


#endif // SCOPEDPTR_H_INCLUDED
