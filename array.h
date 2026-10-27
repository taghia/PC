#ifndef arrayH
#define arrayH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
template <class T>
class TPcArray
{
protected:
	//TSortProc m_compare;
	int get_count()
	{
		return m_items->Count;
	}
	T& get_items(int index)
	{
		return *(T*)m_items->Items[index];
	}
	void set_capacity(int value)
	{
		m_items->Capacity = value;
	}
	int get_capacity()
	{
		return m_items->Capacity;
	}
protected:
	TList *m_items;
	virtual void freeItem(int index)
	{
		T *item = (T*)m_items->Items[index];
		delete item;
	}

public:
	TPcArray(bool ptr = false)
	{
		m_items = new TList;
	}
	~TPcArray()
	{
		clear();
		delete m_items;
	}
	virtual void clear()
	{
		for(int t=0; t<m_items->Count; t++)
			freeItem(t);
		m_items->Clear();
	}

	void remove(int index)
	{
		freeItem(index);
		m_items->Delete(index);
	}

	void remove(T& item)
	{
		int index = indexOf(item);
		remove(index);
	}

	void remove(T* item)
	{
		int index = indexOf(item);
		remove(index);
	}

	virtual T& add()
	{
		T &instance = *new T;
		add(instance);
		return instance;
	}

	virtual void add(T& item)
	{
		m_items->Add(&item);
	}

	virtual void add(T* item)
	{
		m_items->Add(item);
	}

	void add(TPcArray<T> *items)
	{
		for (int i=0; i<items->count; i++) {
			add(items->items[i]);
		}
	}

	void add(TPcArray<T> &items)
	{
		for (int i=0; i<items.count; i++) {
			add(items.items[i]);
		}
	}

	int indexOf(T& item)
	{
		return m_items->IndexOf(&item);
	}

	int indexOf(T* item)
	{
		return m_items->IndexOf(item);
	}

	void exchange(int index1, int index2)
	{
		m_items->Exchange(index1, index2);
	}

	void insert(int index, T& item)
	{
		m_items->Insert(index, &item);
	}
	T& operator [] (int index)
	{
		return items[index];
	}

	__property int count = {read=get_count};
	__property T& items[int index] = {read=get_items};
	__property int capacity = {read=get_capacity, write=set_capacity};
};
//---------------------------------------------------------------------------
#endif
