#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include <exception>

template <typename iT>
class ContainerIterator
{
	iT* ptr;
	template <typename T> friend class Container;
	ContainerIterator<iT>(iT*);
public:
	ContainerIterator<iT>(const ContainerIterator<iT>&);
	bool operator==(const ContainerIterator<iT>&) const;
	bool operator!=(const ContainerIterator<iT>&) const;
	iT& operator*() const;
	ContainerIterator<iT>& operator++();
};

template <typename iT>
ContainerIterator<iT>::ContainerIterator(iT* ptr) : ptr(ptr) {}

template <typename iT>
ContainerIterator<iT>::ContainerIterator(const ContainerIterator<iT>& it) : ptr(it.ptr) {}

template <typename iT>
bool ContainerIterator<iT>::operator==(const ContainerIterator<iT>& it) const
{
	return ptr == it.ptr;
}

template <typename iT>
bool ContainerIterator<iT>::operator!=(const ContainerIterator<iT>& it) const
{
	return ptr != it.ptr;
}

template <typename iT>
iT& ContainerIterator<iT>::operator*() const
{
	return *ptr;
}

template <typename iT>
ContainerIterator<iT>& ContainerIterator<iT>::operator++()
{
	++ptr;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class Container
{
	T* set;
	int csize, buffer;
	static const int delta = 10;

	void alloc_for(int);
	void shrink_to_fit();
	int  calc_buffer(int);
public:
	Container();
	explicit Container(int);
	Container(const Container<T>&);
	~Container();

	int size() const;
	bool empty() const;
	int find(const T) const;

	Container<T>& add(const T);
	Container<T>& remove(const T);
	Container<T>& iremove(int);
	Container<T>& remove_all();

	const Container<T>& operator=(const Container<T>&);
	T& operator[](int);
	const T& operator[](int) const;

	ContainerIterator<T> begin() const;
	ContainerIterator<T> end() const;
};

template<typename T>
void Container<T>::alloc_for(int n)
{
	if (csize + n <= buffer)
		return;
	buffer = calc_buffer(csize + n);
	T* new_set = new T[buffer];
	for (int i = 0; i < csize; i++)
		new_set[i] = set[i];
	if (set)
		delete[] set;
	set = new_set;
};

template<typename T>
void Container<T>::shrink_to_fit()
{
	int empty = buffer - csize;
	if (empty >= delta)
	{
		int d = calc_buffer(csize);
		delete[](set + d);
		buffer = d;
	}
};

template<typename T>
int Container<T>::calc_buffer(int new_size)
{
	return new_size / delta * delta + delta;
};

template<typename T>
Container<T>::Container()
{
	csize = buffer = 0;
	set = nullptr;
};

template<typename T>
Container<T>::Container(int new_size)
{
	csize = 0;
	buffer = calc_buffer(new_size);
	set = new T[buffer];
};

template<typename T>
Container<T>::Container(const Container<T> & c)
{
	csize = buffer = 0;
	set = nullptr;
	alloc_for(c.csize);
	for (int i = 0; i < c.csize; i++)
		set[i] = c.set[i];
	csize = c.csize;
};

template<typename T>
Container<T>::~Container()
{
	remove_all();
};

template<typename T>
int Container<T>::size() const
{
	return csize;
};

template<typename T>
bool Container<T>::empty() const
{
	return csize == 0;
};

template<typename T>
int Container<T>::find(const T elem) const
{
	for (int i = 0; i < csize; i++)
		if (set[i] == elem)
			return i;
	return -1;
};

template<typename T>
Container<T> & Container<T>::add(const T elem)
{
	alloc_for(1);
	set[csize] = elem;
	csize += 1;
	return *this;
};

template<typename T>
Container<T>& Container<T>::remove(const T object)
{
	bool flag = false;
	for (int i = 0; i < csize; i++)
		if (set[i] == object)
		{
			iremove(i);
			flag |= true;
		}
	if (!flag)
		throw std::range_error("Container does not contain element with that"
			"value");
	return *this;
};

template<typename T>
Container<T> & Container<T>::iremove(int index)
{
	if (index >= csize)
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	if (index == csize - 1)
	{
		csize -= 1;
		return *this;
	}
	csize -= 1;
	set[index] = set[csize];
	return *this;
};

template<typename T>
Container<T>& Container<T>::remove_all()
{
	if (!csize || !set)
		return *this;
	delete[] set;
	set = nullptr;
	csize = buffer = 0;
	return *this;
};

template<typename T>
const Container<T> & Container<T>::operator=(const Container<T> & c)
{
	remove_all();
	alloc_for(c.csize);
	for (int i = 0; i < c.csize; i++)
		set[i] = c.set[i];
	csize = c.csize;
	return *this;
};

template<typename T>
T & Container<T>::operator[](int index)
{
	if ((index >= csize) || (index < 0))
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	return set[index];
};

template<typename T>
const T & Container<T>::operator[](int index) const
{
	if ((index >= csize) || (index < 0))
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	return set[index];
};

template<typename T>
ContainerIterator<T> Container<T>::begin() const
{
	return ContainerIterator<T>(set);
};

template<typename T>
ContainerIterator<T> Container<T>::end() const
{
	return ContainerIterator<T>(set + ñsize);
};

///////////////////////////////////////////////////////////////////////////////

template <typename iT>
class ContainerIterator<iT*>
{
	iT** ptr;
	template <typename T> friend class Container;
	ContainerIterator<iT*>(iT**);
public:
	ContainerIterator<iT*>(const ContainerIterator<iT*>&);
	bool operator==(const ContainerIterator<iT*>&) const;
	bool operator!=(const ContainerIterator<iT*>&) const;
	iT*& operator*() const;
	ContainerIterator<iT*>& operator++();
};

template <typename iT>
ContainerIterator<iT*>::ContainerIterator(iT** ptr) : ptr(ptr) {}

template <typename iT>
ContainerIterator<iT*>::ContainerIterator(const ContainerIterator<iT*>& it) : ptr(it.ptr) {}

template <typename iT>
bool ContainerIterator<iT*>::operator==(const ContainerIterator<iT*>& it) const
{
	return ptr == it.ptr;
}

template <typename iT>
bool ContainerIterator<iT*>::operator!=(const ContainerIterator<iT*>& it) const
{
	return ptr != it.ptr;
}

template <typename iT>
iT*& ContainerIterator<iT*>::operator*() const
{
	return *ptr;
}

template <typename iT>
ContainerIterator<iT*>& ContainerIterator<iT*>::operator++()
{
	++ptr;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class Container<T*>
{
	T** set;
	int csize, buffer;
	static const int delta = 10;

	void alloc_for(int);
	void shrink_to_fit();
	int  calc_buffer(int);
public:
	Container();
	explicit Container(int);
	Container(const Container<T*>&);
	~Container();

	int size() const;
	bool empty() const;
	int find(const T) const;

	Container<T*>& add(const T*);
	Container<T*>& remove(const T);
	Container<T*>& iremove(int);
	Container<T*>& remove_all();

	const Container<T*>& operator=(const Container<T*>&);
	T*& operator[](int);
	const T*& operator[](int) const;

	ContainerIterator<T*> begin() const;
	ContainerIterator<T*> end() const;
};

template<typename T>
void Container<T*>::alloc_for(int n)
{
	if (csize + n <= buffer)
		return;
	buffer = calc_buffer(csize + n);
	T** new_set = new T*[buffer];
	for (int i = 0; i < csize; i++)
		new_set[i] = set[i];
	if (set)
		delete[] set;
	set = new_set;
};

template<typename T>
void Container<T*>::shrink_to_fit()
{
	int empty = buffer - csize;
	if (empty >= delta)
	{
		int d = calc_buffer(csize);
		delete[](set + d);
		buffer = d;
	}
};

template<typename T>
int Container<T*>::calc_buffer(int new_size)
{
	return new_size / delta * delta + delta;
};

template<typename T>
Container<T*>::Container()
{
	csize = buffer = 0;
	set = nullptr;
};

template<typename T>
Container<T*>::Container(int new_size)
{
	csize = 0;
	buffer = calc_buffer(new_size);
	set = new T[buffer];
};

template<typename T>
Container<T*>::Container(const Container<T*> & c)
{
	csize = buffer = 0;
	set = nullptr;
	alloc_for(c.csize);
	for (int i = 0; i < c.csize; i++)
	{
		set[i] = new T(*(c.set[i]));
	}
	csize = c.csize;
};

template<typename T>
Container<T*>::~Container()
{
	remove_all();
};

template<typename T>
int Container<T*>::size() const
{
	return csize;
};

template<typename T>
bool Container<T*>::empty() const
{
	return csize == 0;
};

template<typename T>
int Container<T*>::find(const T elem) const
{
	for (int i = 0; i < csize; i++)
		if (*(set[i]) == elem)
			return i;
	return -1;
};

template<typename T>
Container<T*>& Container<T*>::add(const T* ptr)
{
	alloc_for(1);
	set[csize] = new T(*ptr);
	csize += 1;
	return *this;
}

template<typename T>
Container<T*>& Container<T*>::remove(const T elem)
{
	bool flag = false;
	for (int i = 0; i < csize; i++)
		if (**(set + i) == elem)
		{
			iremove(i);
			flag |= true;
		}
	if (!flag)
		throw std::range_error("Container does not contain element with that"
			"value");
	return *this;
};

template<typename T>
Container<T*>& Container<T*>::iremove(int index)
{
	if (index >= csize)
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	if (index == csize - 1)
	{
		delete set[index];
		csize -= 1;
		return *this;
	}
	delete set[index];
	csize -= 1;
	set[index] = set[csize];
	return *this;
};

template<typename T>
Container<T*>& Container<T*>::remove_all()
{
	if (!csize || !set)
		return *this;
	for (int i = 0; i < csize; i++)
		delete set[i];
	delete[] set;
	set = nullptr;
	csize = buffer = 0;
	return *this;
};

template<typename T>
const Container<T*>& Container<T*>::operator=(const Container<T*>& c)
{
	remove_all();
	alloc_for(c.csize);
	for (int i = 0; i < c.csize; i++)
	{
		set[i] = new T(*(c.set[i]));
	}
	csize = c.csize;
	return *this;
};

template<typename T>
T*& Container<T*>::operator[](int index)
{
	if ((index >= csize) || (index < 0))
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	return set[index];
};

template<typename T>
const T*& Container<T*>::operator[](int index) const
{
	if ((index >= csize) || (index < 0))
		throw std::out_of_range("Container does not contain element with that"
			"index.");
	return set[index];
};

template<typename T>
ContainerIterator<T*> Container<T*>::begin() const
{
	return ContainerIterator<T*>(set);
};

template<typename T>
ContainerIterator<T*> Container<T*>::end() const
{
	return ContainerIterator<T*>(set + ñsize);
};

#endif
