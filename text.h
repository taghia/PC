//1401-02-28

//---------------------------------------------------------------------------
#ifndef _textH_
#define _textH_

#include <cstdio>
#if __cplusplus > 201100L
#include <initializer_list>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>

#if !defined(TXT_LIGHT) && defined(__BORLANDC__)
#include <Classes.hpp>
#endif

#if !defined (QT_NO_DEBUG) && defined (QT_CORE_LIB)
#define QT_DEBUG
#endif

#ifdef QT_CORE_LIB
#include <QString>
#endif
#if defined(Q_OS_WINDOWS)
#define _Windows 1
#include <debugapi.h>
#endif
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option push
#pragma option -vi-  // prevent inline expansion
#define Is(x) InheritsFrom(__classid(x))
#endif
//---------------------------------------------------------------------------
#ifdef _MSC_VER //VC++ extra warnings
#pragma warning(disable : 4996)
#pragma warning(disable : 4267)
#pragma warning(disable : 4244)
#include <yvals.h>
#define wcstoll _wcstoi64
#define vsnwprintf vswprintf
#endif

#if defined(__GNUC__) && !(defined(__MINGW64__) || defined(__MINGW32__))
#define __int64 int64_t
//typedef uint16_t char16_t;
#endif

#if defined(__APPLE__) || defined(__ANDROID__)
#define vsprintf_s vsnprintf
#define vswprintf_s vswprintf
#define vsnwprintf vswprintf
#define swprintf_s swprintf
#include <string.h>
#endif

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif

#if defined(__LP64__) || defined (_M_X64)
#define _X64_
#define _int int64_t
#else
#define _int int
#endif

//#define Method(X) class Method {public: static X}

#define UNUSED(x) (void)(x);

#ifndef __log
#define __log
//static void log(char *fmt, void *value)
//{
//	char buf[100];
//	sprintf_s(buf, 100, fmt, value);
//	OutputDebugStringA(buf);
//}
#endif

namespace txt
{

	class array;
	class data_t;
	class text;
	typedef bool (*TFilterProc) (int);
	enum encoding_t {enAnsi, enUnicode, enUtf8, enUtf16, enUtf16LE};
	uint64_t hash64(unsigned char *pData, int len);
	template <class T> class arrayIt;
	//---------------------------------------------------------------------------
	class Bool
	{
	private:
		bool mValue;
	public:
		Bool()
		{
			mValue = false;
		}
		operator bool& ()
		{
			return mValue;
		}
		bool operator = (bool value)
		{
			return mValue = value;
		}
	};
	//---------------------------------------------------------------------------
	template <class T>
	class rangeof
	{
		public:
		T start;
		T end;
		rangeof(T start = 0, T end = 0)
		{
			this->start = start;
			this->end = end;
		}
		T length()
		{
			return end - start;
		}
		void operator += (T offset)
		{
			start += offset;
			end += offset;
		}
		void expandStart(T value)
		{
			if (value < start)
				start = value;
		}
		void expandEnd(T value)
		{
			if (value > end)
				end = value;
		}
		void operator -= (T offset)
		{
			start -= offset;
			end -= offset;
		}
		rangeof <T> operator + (int value)
		{
            return rangeof<T> (start + value, end + value);
		}
		bool in(rangeof <T> &rng)
		{
			return start >= rng.start && end <= rng.end;
		}
		bool operator == (const rangeof <T> &rng)
		{
			return rng.start == start && rng.end == end;
		}
		int length() const
		{
			return end - start;
		}
	};
	typedef rangeof<int> range;
	//---------------------------------------------------------------------------
	class ref_counter
	{
	private:
		int m_refCount;
	protected:
	public:
		ref_counter()
		{
			m_refCount = 0;
			tag = 0;
			data = NULL;
			//log("%x created", this);
		}
		~ref_counter() {}
		void addRef()
		{
			m_refCount++;
		}
		void release()
		{
			m_refCount--;
			if(m_refCount == 0)
			{

				//log("%x freed", this);
				delete this;
			}
		}
		int refCount()
		{
			return m_refCount;
		}
		void *data;
		int tag;
	};
	//---------------------------------------------------------------------------
	template <class T>
	class base_obj
	{
	protected:
		ref_counter *rc;
		ref_counter* get_rc() const
		{
			rc->addRef();
			//log("%x accessed", rc);
			return rc;
		}
		void clean() {}
		T& data() const
		{
			return (T&)rc->data;
		}
		int& tag() const
		{
			return rc->tag;
		}
		void free()
		{
			if(refCount() == 1)
			{
				clean();
				data() = NULL;
			}
			rc->release();
		}
	public:
		base_obj()
		{
			rc = new ref_counter;
			rc->addRef();
		}
		base_obj(const base_obj &inst)
		{
			rc = inst.get_rc();
		}
		base_obj& operator = (const base_obj &inst)
		{
			free();
			rc = inst.get_rc();
			return *this;
		}
		virtual ~base_obj()
		{
			free();
		}
		int refCount()
		{
			return rc->refCount();
		}
//		void *dataPtr()
//		{
//			return data();
//		}
	};
	//---------------------------------------------------------------------------
	template <class T>
	class buffer_t : public base_obj<T*>
	{
	protected:
		void clean()
		{
			if(base_obj<T*>::refCount() == 1 && base_obj<T*>::data() != NULL)
				::free(base_obj<T*>::data());
		}

		typedef void (*applier_proc_t)(T &data);

	public:
		buffer_t(int size = 0)
		{
			if(size)
				setSize(size);
		}
		buffer_t(const T *data, uint32_t len)
		{
			setSize(len);
			memcpy(this->data(), data, len * sizeOf());
		}
		int sizeOf() const
		{
			return sizeof(T);
		}
		operator T* ()
		{
			return base_obj<T*>::data();
		}
		T *dataPtr() const
		{
			return (T*) base_obj<T*>::data();
		}
		T& operator[] (int index)
		{
#ifdef _DEBUG
			assert(index < high());
#endif
			return base_obj<T*>::data()[index];
		}
		T operator() (int index) const
		{
#ifdef _DEBUG
			assert(index < high());
#endif
			return base_obj<T*>::data()[index];
		}
		void setSize(int size)
		{
			base_obj<T*>::data() = (T*) realloc(base_obj<T*>::data(), size * sizeOf());
			base_obj<T*>::tag() = size;
		}
		virtual ~buffer_t()
		{
			clean();
		}
		int size() const
		{
			return base_obj<T*>::tag();
		}
		virtual int high() const
		{
			return size();
		}
		void assign(const buffer_t &buf)
		{
			setSize(buf.size());
			memcpy(base_obj<T*>::data(), buf.dataPtr(), buf.size() * sizeOf());
		}
		void write(const buffer_t &buf)
		{
			int offset = size();
			setSize(offset + buf.size());
			memcpy(base_obj<T*>::data() + offset, buf.dataPtr(), buf.size() * sizeOf());
		}
		buffer_t subdata(int start, int len)
		{
			buffer_t retv(len);
			T *pSrcData = base_obj<T*>::data();
			T *pDstData = retv;
			for (int i = start; i < start + len; i++) {
				pDstData[i - start] = pSrcData[i];
			}
			return retv;
		}
		void insert(const buffer_t &buf, int pos)
		{
			int len = size();
			int insert_size = buf.size();
			setSize(len + insert_size);
			T *pData = base_obj<T*>::data();
			T *pInsData = buf.dataPtr();
			for(int i = 0; i < len - pos; i++)
				pData[len + insert_size - i - 1] = pData[len - i - 1];
			for(int i = 0; i < insert_size; i++)
				pData[pos + i] = pInsData[i];
		}
		void insert(const T *data, int pos, int n)
		{
			int len = size();
			setSize(len + n);
			T *pData = base_obj<T*>::data();
			for(int i = 0; i < len - pos; i++)
				pData[len + n - i - 1] = pData[len - i - 1];
			for(int i = 0; i < n; i++)
				pData[pos + i] = data[i];
		}
		void remove(int pos, int n)
		{
			int len = size();
			T *pData = base_obj<T*>::data();
			for(int i = 0; i < len - n; i++)
				pData[pos + i] = pData[pos + i + n];
			setSize(len - n);
		}

#if __cplusplus > 201100L
		buffer_t(const std::initializer_list<T> &data)
		{
			write(data);
		}

		void set(T value)
		{
			int len = size();
			T *pData = base_obj<T*>::data();
			for(int i = 0; i < len; i++)
				pData[i] = value;
		}

		void write(const std::initializer_list<T> &data)
		{
			int offset = size();
			setSize(offset + data.size());
			auto it = data.begin();
			int size = data.size();
			T *pData = base_obj<T*>::data();
			for(int i = 0; i < size; i++)
				pData[i + offset] = T(it[i]);
		}
#endif
		void write(const void *pData, uint32_t size)
		{
			int offset = this->size();
			setSize(offset + size);
			memcpy(base_obj<T*>::data() + offset, pData, size);
		}
		int find(const buffer_t &buf, int offset = 0)
		{
			bool result;
			int buf_size = buf.size();
			T *pBuf = base_obj<T*>::data();
			T *pSubBuf = buf.data();
			int size = this->size();
			for (int i = offset; i <= size - buf_size; i++) {
				result = true;
				for (int j = 0; result && j < buf_size; j++) {
					result = result && pBuf[i + j] == pSubBuf[j];
				}
				if (result)
					return i;
			}
			return -1;
		}
		void replace(const buffer_t &from, const buffer_t &to)
		{
			int index, offset = 0;
			T *pData = base_obj<T*>::data();
			buffer_t result;
			do
			{
				index = find(from, offset);
				if(index >= 0)
				{
					result.write(pData + offset, index - offset);
					result.write(to);
					offset = index + from.size();
				}
				else
					result.write(pData + offset, size() - offset);
			}
			while(index >= 0);
			assign(result);
		}
		void apply(applier_proc_t applier_proc)
		{
			T *pData = base_obj<T*>::data();
			int count = size();
			for (int i = 0; i < count; i++) {
				applier_proc(pData[i]);
			}
		}
		uint64_t hash64()
		{
			return txt::hash64((unsigned char*)base_obj<T*>::data(), size());
		}
	};
	//---------------------------------------------------------------------------
	class data_t : public buffer_t<char>
	{
	protected:

	public:
		data_t(int size = 0);
		data_t(const char *data, uint32_t len);
#if __cplusplus > 201100L
		//data_t(const std::initializer_list<char> &data);
		data_t(const std::initializer_list<uint8_t> &data);
#endif
#ifdef QBYTEARRAY_H
		data_t(QByteArray *ba)
		{
			buffer_t<char>::write(ba->data(), uint(ba->length()));
		}
#endif
		virtual int high() const // it should be defined in header otherwise gcc error be occured (Undefined symbols)
		{
			return size() + 1;
		}

//		char& operator[] (int index);
//		char operator() (int index) const;
		uint8_t* toUInt8Ptr() const;
		void operator << (unsigned char byte);
		void setLength(int len);
		int length() const;
		data_t subdata(int start, int end);
		void insert(const char *bytes, int pos);
		int find(const char *subStr, int offset = 0, bool matchCase = true, bool unicode = false);
		bool saveToFile(const text &fileName);
		data_t& loadFromFile(const text &fileName, uint32_t offset = 0, uint32_t count = 0);
		text toString(encoding_t encoding);
		void invertBytes();
		void reverseBytes();
		#if defined(System_ClassesHPP) || defined(ClassesHPP)
		TMemoryStream *createMemoryStream();
		#endif
		text getDebugString();
		void setData(const data_t &data);
		void write(const data_t &data);
		void write(const void *pData, uint32_t size);
		void write(uint32_t value);
        bool contains(const char *subStr, bool matchCase = false, bool unicode = false);
#ifdef QBYTEARRAY_H
		void writeByteArray(const QByteArray &data);
		QByteArray byteArray() const;
#endif
	};
	//---------------------------------------------------------------------------
	class text_t : public buffer_t<wchar_t>
	{
	private:
		void assign(const char *value);
		void assign(const wchar_t *value);

	public:
		text_t(const char *value);
		text_t(const wchar_t *value);
		void setLength(int len);
		int length() const;
		text_t& operator =(const char *value);
		text_t& operator =(const wchar_t *value);
		buffer_t<char16_t> getChar16Ptr() const;
		operator wchar_t* () const;
		data_t c_str() const;
	};
	//---------------------------------------------------------------------------
	class stream_t : public base_obj<void*>
	{
	private:
		int m_position;
	public:
		stream_t();
		virtual void write(void *data, int dataSize) = 0;
		virtual void write(int value) = 0;
		virtual void write(short value) = 0;
		virtual void write(char value) = 0;
		virtual void write(const data_t &data) = 0;
		virtual void setPosition(int position) = 0;
		virtual int position() = 0;
		virtual int read(void *data, int dataSize) = 0;
		virtual int readInt() = 0;
		virtual unsigned char readByte() = 0;
		virtual void clear();
	};
	//---------------------------------------------------------------------------
	class memory_stream_t : public stream_t, public data_t
	{
	private:
		int m_position;
	public:
		memory_stream_t(int size = 0);
		void write(void *data, int dataSize);
		void write(int value);
		void write(short value);
		void write(char value);
		void write(const data_t &data);
		void setPosition(int position);
		int position();
		int read(void *data, int dataSize);
		int readInt();
		uint16_t readUInt16();
		uint32_t readUInt32();
		unsigned char readByte();
		virtual void clear();
	};
	//---------------------------------------------------------------------------
	class ptr_list
	{
	private:
	protected:
		void *pointers;
        int m_capacity, m_count, m_refCount;
	public:
        ptr_list(int count = 0);
		void setCapacity(int value);
		void setLength(int value);
		int getCapacity();
		int add(void *item);
		void insert(void *item, int pos);
		void remove(int index, int count = 1);
		~ptr_list();
        int count() const;
        void *item(int index);
		void addRef();
		void release();
		int refCount();
		void clear();
		void** ptrList();
		void exchange(int index1, int index2);
		void *operator [] (int index);
		void zero();
	};
	//---------------------------------------------------------------------------
	template <class T>
	class arrayof : public base_obj<ptr_list*>
	{
    public:
		typedef void (*applier_proc_t)(T &item);
	private:
		void clean()
		{
			if(refCount() == 1)
			{
                for (int i=0; i < (int)data()->count(); i++) {
					freeItem(i);
				}
				delete data();
			}
		}
		void freeItem(int index)
		{
            delete (T*) data()->item(index);
		}
	protected:
        virtual T& get_item(int index) const
		{
			#ifdef _DEBUG
			//if(index < 0 || index >= count()) throw ((text)"list index ([]) out of range." << index);
			#endif
            return *(T*) data()->item(index);
		}
		virtual void set_item(int index, T value)
		{
            *(T*) data()->item(index) = value;
		}
		void copy(arrayof<T> &inst)
		{
			for (int i = 0; i < count(); i++) {
				inst.add(item(i));
			}
		}
		//----------------------------------------------------------------------
		void swap(void *v[], int i, int j)
		{
			void *temp;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}
		//----------------------------------------------------------------------
		void quickSort(void *v[], int left, int right, bool descending)
		{
			int i, last;
			if(left >= right)
				return;
			swap(v, left, (left + right) / 2);
			last = left;
			for(i=left+1; i<=right; i++)
 			if(compareProc(*(T*)v[i], *(T*)v[left]) * (descending ? 1 : -1) < 0)
				swap(v, ++last, i);
			swap(v, left, last);
			quickSort(v, left, last - 1, descending);
			quickSort(v, last+1, right, descending);
		}
		//----------------------------------------------------------------------
	public:
        virtual int compareProc(T &item1, T &item2)
        {
			UNUSED(item1)
			UNUSED(item2)
            throw; //"Undefined compare proc."
            return 0;
        }
		void sort(bool descending = true)
		{
			quickSort(data()->ptrList(), 0, count() - 1, descending);
		}
		void apply(applier_proc_t applier_proc)
		{
			for (int i = 0; i < count(); i++) {
				applier_proc(item(i));
			}
		}
		arrayof(int count = 0)
		{
			data() = new ptr_list;
			for (int i = 0; i < count; i++)
				add();

// its ok but how to free?
//			data()->setLength(count);
//			T* temp = new T[count];
//			void **pItems = data()->ptrList();
//			for (int i = 0; i < count; i++) {
//				pItems[i] = &temp[i];
//			}

		}
#if __cplusplus > 201100L
		arrayof(const std::initializer_list<T> &data)
		{
			this->data() = new ptr_list;
			add(data);
		}
		void add(const std::initializer_list<T> &data)
		{
			auto *pData = data.begin();
			for(uint32_t i = 0; i < data.size(); i++)
				add(pData[i]);
		}
#endif
		~arrayof<T>()
		{
			clean();
		}
		int add(const T& _item)
		{
			T *item = new T;
			*item = _item;
			return data()->add(item);
		}
		void insert(T _item, int pos)
		{
        	#ifdef _DEBUG
			assert(pos <= count());
            #endif
			T *item = new T;
			*item = _item;
			data()->insert(item, pos);
		}
		T &add()
		{
			T *item = new T;
			data()->add(item);
			return *item;
		}
        arrayof<T>& add(const arrayof<T> &array)
		{
			for (int i = 0; i < array.count(); i++) {
                add(array.item(i));
			}
            return *this;
		}
        arrayof<T>& operator += (const arrayof<T> &array)
        {
            return add(array);
        }
		void remove(int index, int count = 1)
		{
			#ifdef _DEBUG
			assert(index >= 0);
			#endif

			for (int i = 0; i < count; i++)
				freeItem(index + i);

			data()->remove(index, count);
		}
        T& operator [] (int index)
        {
            return item(index);
        }
        T& operator () (int index) const
        {
            return item(index);
        }
        arrayof<T>& operator << (const T &item)
		{
			add(item);
			return *this;
		}
		arrayof<T>& operator >> (T item)
		{
			int index = indexOf(item);
			if(index > -1)
				remove(index);
			return *this;
		}
        T& item(int index) const
		{
			return get_item(index);
		}
		T& lastItem() const
		{
			return get_item(count() - 1);
		}
        virtual int count() const
		{
            return data()->count();
		}
		int getCapacity()
		{
			return data()->getCapacity();
		}
		void setCapacity(int value)
		{
			data()->setCapacity(value);
		}
		virtual int indexOf(T inst)
		{
            UNUSED(inst);
			throw "not defined";
            return 0;
		}
		void exchange(int index1, int index2)
		{
			data()->exchange(index1, index2);
		}
		void clear()
		{
			for (int i=0; i<data()->count(); i++) {
				freeItem(i);
			}
			data()->clear();
			setCapacity(5);
		}

		typedef arrayIt <T> it;
		typedef T of;

		it getIterator() const
		{
			it it(*this);
			return it;
		}

		it getIteratorReverse() const
		{
			it it(*this, true /*reverse*/);
			return it;
		}
		//--------------------------------------------------------
		it begin() const
		{
			it it(*this, false, 0);
			return it;
		}
		it end() const
		{
			it it(*this, false, count());
			return it;
		}
		//--------------------------------------------------------
		typedef bool (*FilterCallback)(const T &item);
		arrayof<T>& filter(FilterCallback callback)
		{
			arrayof<T> temp;
			int count = this->count();
			for(int i = 0; i < count; i++)
			{
				if(callback(item(i)))
					temp << item(i);
			}
			*this = temp;

			return *this;
		}
	};
	//---------------------------------------------------------------------------
	template <class T>
	class arrayIt
	{
	private:
		const arrayof<T> *mArrayPtr;
		int mPos;
		int mStep;
		bool mReverseOrder;
	public:
		arrayIt(const arrayof<T> &arrayPtr, bool reverseOrder = false, int pos = 0)
		{
			mReverseOrder = reverseOrder;
			mArrayPtr = &arrayPtr;
			mStep = mReverseOrder ? -1 : 1;
			mPos = mReverseOrder ? arrayPtr.count() - 1 : pos;
		}
		bool atEnd()
		{
			return mReverseOrder ? mPos < 0 : mPos >= mArrayPtr->count();
		}
		bool notAtEnd()
		{
			return !atEnd();
		}
		operator bool() {
			return !atEnd();
		}
		T &next()
		{
			T &retv = mArrayPtr->item(mPos);
			mPos += mStep;
			return retv;
		}
		T &futureValue()
		{
			T &retv = mArrayPtr->item(mPos);
			return retv;
		}
		T &prevValue()
		{
			T &retv = mArrayPtr->item(mPos - mStep * 2);
			return retv;
		}
		T &value()
		{
			#ifdef _DEBUG
			assert(mPos - mStep >= 0);
			assert(mPos - mStep < mArrayPtr->count());
			#endif
			return mArrayPtr->item(mPos - mStep);
		}

		void first()
		{
			mPos = mReverseOrder ? mArrayPtr->count() - 1 : 0;
		}
		void seek(int pos)
		{
			mPos = pos;
		}
		int pos() const
		{
			return mPos - mStep;
		}
		bool operator != (const arrayIt<T> &other) const
		{
			return mPos != other.mPos;
		}
		arrayIt<T>& operator ++ ()
		{
			mPos ++;
			return *this;
		}
		T& operator * () const
		{
			return mArrayPtr->item(mPos);
		}
	};
	//---------------------------------------------------------------------------
	#ifdef __COREFOUNDATION_CFSTRING__
	class AutoReleaseStringRef
	{
	private:
		CFStringRef mValue;
	public:
		AutoReleaseStringRef(const text &value);
		~AutoReleaseStringRef();
		operator CFStringRef();
	};
	#endif

	class text
	{
	private:
		void free();
		//----------------------------------------------------------------------
		#ifdef __BORLANDC__
		int tolower_fixed(int ch) const;
		int toupper_fixed(int ch) const;
		#else
		#define tolower_fixed tolower
		#define toupper_fixed toupper
		#endif
		//----------------------------------------------------------------------
		wchar_t *assign(const char *value);
		wchar_t *assign(const wchar_t *value);
		wchar_t *assign(const char16_t *value);
		wchar_t *append_char(const char value);
		wchar_t *append_char(const wchar_t value);
		wchar_t *append_char(const char16_t value);
		//----------------------------------------------------------------------
		wchar_t *append(const wchar_t *value);
		wchar_t *append(const char16_t *value);
		wchar_t *append(const char *value);
		//----------------------------------------------------------------------
		text replace_once_ex(const wchar_t *from, const wchar_t *to, int *start, bool matchCase);
		wchar_t *wcsstr(const wchar_t *s1, const wchar_t *s2) const;
		wchar_t *iwcsstr(const wchar_t *str, const wchar_t *substr) const;
		int wcsicmp(const wchar_t *s1, const wchar_t *s2) const;
		wchar_t *wcslwr(wchar_t *str) const;
		wchar_t *wcsupr(wchar_t *str) const;
		//wchar_t *wcstok(wchar_t *s1, const wchar_t *s2) const;
		text replace_ex(wchar_t *from, wchar_t *to, bool matchCase) const;
		text replace_ex(wchar_t *startTag, wchar_t *endTag, wchar_t *repl, bool replaceTags = true, int start = 0, bool matchCase = true);
		text wcSubstr_ex(wchar_t *pattern, int start, bool matchCase);
		bool wcCompare_ex(const wchar_t *pattern, int start, bool matchCase, bool whole_word, int *end) const;
		int wcFind_ex(const wchar_t *pattern, int start, bool matchCase, int *end);
		text wcReplace_ex(text pattern, text repl, bool matchCase, bool replaceOnce);
		int find_ex(const wchar_t *str, int start, bool matchCase) const;
		int rfind_ex(wchar_t *str, int rOff, bool matchCase) const;
		void substr_ex(text &result, const wchar_t *startStr, const wchar_t *endStr, int start, int end, bool matchCase) const;
		void read_ex(text &substr, int &start, const wchar_t *stopChars) const;
		void rread_ex(text &substr, int &start, const wchar_t *stopChars);
		void read_ex(text &substr, wchar_t *startStr, const wchar_t *stopChars, bool matchCase) const;
		bool isBase64(unsigned char c);
#if defined (QT_DEBUG)
		//int mLength = 0;
#endif

	public:
		wchar_t *data;

		text();
		text(const wchar_t *value);
		text(const char16_t *value);
		text(const char *value);
		text(const text &value);
		text(double value);
		text(int value);
		text(unsigned int value);
		text(long value);
		text(int64_t value);
		text(uint64_t value);
		text(char value);
		text(char16_t value);
		text(wchar_t value);
		text(const data_t &data, encoding_t encoding);
		~text();

		#ifdef __COREFOUNDATION_CFSTRING__
		text(const CFStringRef value);
		void operator = (const CFStringRef value);
		CFStringRef createStringRef() const;
		AutoReleaseStringRef getStringRef() const;
		#endif

#ifdef QSTRING_H
		void assign(const QString &value);
		void assign(const QByteArray &value);
		text(const QString &value);
		text(const QByteArray &value);
		text& operator = (const QString &value);
		text& operator = (const QByteArray &value);
		operator QString() const;
		QByteArray byteArray() const;
#endif

		static text link(int chr1, ...);

		text& operator = (const char *value);
		text& operator = (const wchar_t *value);
		text& operator = (const char16_t *value);
		text& operator = (const char value);
		text& operator = (const wchar_t value);
		text& operator = (const char16_t value);
		text& operator = (const text &value);
		text& operator = (bool value);
		text& operator = (int value);
		text& operator = (unsigned int value);
		text& operator = (int64_t value);
		text& operator = (uint64_t value);
		text& operator = (double value);
		void operator += (text value);
		void operator += (const char value);
		void operator += (const wchar_t value);
		void operator += (const char16_t value);

		void set(wchar_t chr, int count = 0);

		void display();

		#if !defined(TXT_LIGHT) && defined(__BORLANDC__)
		text(const UnicodeString &value);
		text(const AnsiString &value);
		text(const WideString &value);
		text& operator = (const UnicodeString &value);
		text& operator = (const WideString &value);
		text& operator = (const AnsiString &value);
		void operator += (const String &value);
		void operator += (const AnsiString &value);
		operator UnicodeString() const;
		operator AnsiString() const;
		operator WideString() const;
		text operator + (const UnicodeString &value) const;
		text operator + (const AnsiString &value) const;
		text operator + (const WideString &value) const;
		text(DWORD value);
		void operator = (DWORD value);
		//----------------------------------------------------------------------
		#endif

		void operator += (const wchar_t *value);
		void operator += (const char16_t *value);
		void operator += (const char *value);
		text operator + (const wchar_t *value) const;
		text operator + (const char16_t *value) const;
		text operator + (const char *value) const;
		text operator + (const wchar_t value) const;
		text operator + (const char16_t value) const;
		text operator + (const char value) const;
		text operator + (const text &value) const;
		bool operator == (const text &value) const;
		bool operator == (const wchar_t *value) const;
		bool operator == (const char *value) const;
        bool operator != (const text &value) const;
        bool operator != (const wchar_t *value) const;
        bool operator != (const char *value) const;
		bool operator / (const text &value) const;
		bool operator ^ (const text &value) const;
		operator wchar_t* () const;
		data_t getChar16Ptr() const;
		char16_t* createChar16Ptr() const;
		text operator << (const text &value);
		text operator >> (text value);
		text operator | (void *value);
		text operator | (bool value);
		text operator | (int value);
		text operator | (char value);
		text operator | (long value);
		text operator | (wchar_t *value);
		text operator | (char *value);
		text operator | (unsigned long value);
		text operator | (double value);
		text operator | (text value);
		wchar_t & operator[](int index);
		wchar_t & operator()(int index) const;
		int length() const;
		int byteSize() const;
		void setLength(int value);
		void resize(int value);
		wchar_t &lastChar() const;
		wchar_t &firstChar();
		text& decreaseLen(int count = 1);
        //text& replaceChar(wchar_t from, wchar_t to, bool all = true, int skip = 0);
        text& replaceChar(wchar_t from, wchar_t to, int skip = -1 /*all*/);
		text replaceOnce(const text &from, const text &to, int *start = NULL);
		text ireplaceOnce(const text &from, const text &to, int *start = NULL);
		text replace(const text &from, const text &to) const;
		text ireplace(const text &from, const text &to) const;
		text replace(const text &startTag, const text &endTag, const text &repl,
			bool replaceTags = true, int start = 0);
		text ireplace(const text &startTag, const text &endTag, const text &repl,
			bool replaceTags = true, int start = 0);
		text replace(const range &range, text to);
		int icompare(const text &str) const;
        int compare(const text &that) const;
        bool wcCompare(const text &pattern) const;
        bool wciCompare(text pattern);
		text uppercase() const;
		text lowercase() const;
		bool empty() const;
		void substr(text &substr, int start, int len) const;
		text subrange(const range &range) const;
		text substr(int start, int len = -1) const;
		text subto(int start, const text &stopStr) const;
		text subfind(const text &startStr, const text &endStr = "", int start = 0, int end = 0) const;
		text isubstr(text startStr, text endStr = L"", int start = 0, int end = 0) const;
		int read(int start, const wchar_t *stopChars) const;
        text read(text startStr, const wchar_t *stopChars, bool includeTag) const;
		int rread(int start, const wchar_t *stopChars) const;
		text read(int start, const wchar_t *stopChars, int *offset) const;
		text rread(int start, const wchar_t *stopChars, int *offset);
		int pass(int start, const wchar_t *stopChars) const;
		int rpass(int start, const wchar_t *stopChars);
		text left(int count) const;
		text right(int count) const;
		bool leftIs(text str, bool matchCase = false);
		bool rightIs(text str, bool matchCase = false);
		bool startsWith(const text &str, bool matchCase = false) const;
		bool endsWith(const text &str, bool matchCase = false) const;
		float floatValue() const;
		double doubleValue() const;
		int find(const text &substr, int start = 0) const;
		int ifind(const text &substr, int start = 0);
		range wcFind(text pattern, int start = 0);
		range wciFind(text pattern, int start = 0);
		int rfind(text str, int rOff = 0) const;
		int irfind(text str, int rOff = 0) const;
		int findByIndex(text str, int index);
		bool contains(const text &substr, bool matchCase = false) const;
		bool contains(const array &substrs, bool matchCase = false) const;
		bool include(text chars);
        int intValue(int base = 10) const;
        int64_t int64Value(int base = 10) const;
        wchar_t *firstToken(const wchar_t *delimiters) const; // thread unsafe
        wchar_t *nextToken(const wchar_t *delimiters) const; // thread unsafe
		wchar_t *firstToken(const wchar_t *delimiters, wchar_t **save) const; // thread safe
		wchar_t *nextToken(const wchar_t *delimiters, wchar_t **save) const; // thread safe
        data_t t_str() const;
		data_t c_str() const;
		#if defined (_Windows) && defined (__BORLANDC__)
		wchar_t* getOleStr();
		#endif
        text toHex(int digits = 0);
        text toHexString();
        text& fromHexString(text hexStr);
		text trim() const;
		text reverse();
		text quoted(char quote = '"') const;
		text unQuoted(wchar_t quote = L'"') const;
		bool isAnsiString() const;
		bool hasAnsiChar() const;
		array split(const wchar_t *delim) const;
		array split(const wchar_t *startTag, const wchar_t *endTag) const;
		typedef void (*splitCallback)(const wchar_t* substr, int index, void *user_data);
		void split(const wchar_t *delim, splitCallback callback, void *user_data = NULL) const;
		//int scan(text charSet, int start = 0);
		text wcSubstr(text pattern, int start = 0);
		text wciSubstr(text pattern, int start = 0);
		text wcReplace(text pattern, text repl);
		text wciReplace(text pattern, text repl);
		data_t toUtf8() const;
		text toRot13(bool numbers = false) const;
        text toBase64() const;
		text fromBase64();
        text toUnicode();
		uint8_t utf8ByteCount(int index);
		uint8_t utf16ByteCount(int index);
		array splitByCodepoint(); // data is utf16

#if defined(_Windows)
		static int vasprintf(char **retv, const char *format, va_list args);
		text& print(const wchar_t* format, ...);
#endif
		text& print(const char* format, ...);
		text& write(const char* format, ...);
		//----------------------------------------------------------------------
//		static wchar_t *wcstok(wchar_t *s1, const wchar_t *s2, wchar_t **ps,
//			wchar_t *delim = NULL);
		//----------------------------------------------------------------------
		text &remove(int pos, int count = 1);
		text &insert(int pos, wchar_t chr);
		text &insert(int pos, const text &text);
		uint64_t hash64() const;
		text filter(TFilterProc proc) const;
		text& itoa64(uint64_t value, int radix);
        int countOf(wchar_t chr, int max = 0) const;
		text random(int len);
		text &copy(const char *buffer, int count);
		text &copy(const wchar_t *buffer, int count);
		text &copy(const char16_t *buffer, int count);
		text exchangeBy(const text &delim);
		bool in(const text &container, bool matchCase = false) const;

		// scan:
		// %i->int %c->char %lc->wchar_t %s->char* %ls->wchar_t* %f->float %lf->double
		// %x->hex to int %lx->hex to long %llx hex to int64
		// %% -> %
		// %* -> *
		bool scan(const char *fmt, ...);
		//----------------------------------------------------------------------
		//#ifdef _DEBUG
		text getDebugString();
		//#endif
		//----------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------
	class array : public arrayof<text>
	{
	private:
		bool left_cmp(const wchar_t *str1, const wchar_t *str2);
		virtual int find_ex(const text &text, bool matchCase) const;
		virtual int compareProc(text &item1, text &item2);
	protected:
		text &addBuffer(wchar_t *buffer, int offset, int len);
	public:
		array()	{}
		~array() {}
		array &load(text fileName);
		bool save(text fileName);
		array &loadFromFile(const text &fileName);
		bool saveToFile(const text &fileName);
		text implode(const wchar_t *glue) const; // not safe
		text toString(const wchar_t glue = ',', bool ignore_empty_items = false) const; // safe
		text toString(const wchar_t *glue) const; // not safe
		void addArray(array anArr);
		void explode(const wchar_t *delimiter, const text &input); // depricated
		void fromString(const text &rawData, const wchar_t glue = ',');
//		void tokenize(const wchar_t *delimiters, wchar_t *input,
//			void(*callback)(array&, wchar_t*, wchar_t) = NULL);
		int find(const wchar_t *text) const;
		int ifind(const wchar_t *text);
		bool contains(const wchar_t *text, bool matchCase = false);
		int search(const text &substr, bool matchCase = false);
		int include(const text &str);
		array &operator << (text inst);
		array &operator << (array arr);
		int sortAndRemoveDuplicates();
		text getDelimitedText(wchar_t delimiter);
		text briefStr();
        array &operator += (const array &arr);
		//#ifdef _DEBUG
		text getDebugString();
		//#endif
#if __cplusplus > 201100L
		array(const std::initializer_list<text> &data) : arrayof<text>(data)
		{
		}
#endif
	};
	//--------------------------------------------------------------------------
	template <class T1, class T2>
	class key_value_t
	{
	public:
		T1 key;
		T2 value;
		void operator = (T2 value)
		{
			this->value = value;
		}
		bool operator == (T2 value) const
		{
			return this->value == value;
		}
		bool operator != (T2 value) const
		{
			return this->value != value;
		}
		operator T2 ()
		{
			return value;
		}
	};

	//--------------------------------------------------------------------------
	//#if !defined(__GNUC__)
	template <class T>
	class InitializedType
	{
	private:
		T mValue;
	public:
		InitializedType(T value = NULL)
		{
			mValue = value;
		}
		operator T& ()
		{
			return mValue;
		}
		T& operator = (const T &value)
		{
			mValue = value;
			return mValue;
		}
	};
	typedef InitializedType <int> int_t;
	typedef InitializedType <bool> bool_t;
	typedef InitializedType <float> float_t;
	typedef InitializedType <char> Char;
	typedef InitializedType <wchar_t> Wchar;
	template <class T1, class T2>
	class dic_t : public arrayof< key_value_t<T1, T2> >
	{
	public:
		int find(const T1 &key)
		{
			int count = this->count();
			for (int i=0; i<count; i++) {
				key_value_t<T1, T2> &item = this->item(i);
				if(item.key == key)
					return i;
			}
			return -1;
		}
		T2 &operator[] (const T1 &key)
		{
			int index = find(key);
			if(index >= 0)
				return this->item(index).value;
			key_value_t<T1, T2> &item = this->add();
			item.key = key;
//			item.value = NULL;
			return item.value;
		}
	};
	//#endif
	//--------------------------------------------------------------------------
	class dictionary_t : public arrayof< key_value_t<text, text> >
	{
		private:
		typedef int (*TCompareProc)(key_value_t<text, text> &, key_value_t<text, text> &);
		TCompareProc mCompareProc;
	public:
        dictionary_t();
//#if __cplusplus > 201100L
//		dictionary_t(const std::initializer_list<text> &data) : arrayof< key_value_t<text, text> >(data)
//		{
//		}
//#endif
		void loadFromFile(const text &fileName);
		void saveToFile(const text &fileName);
		text toString(const wchar_t glue = '&') const;
		void fromString(const text &rawData, const wchar_t glue = '&');
		int findKey(const text &key, bool matchCase = false) const;
		bool hasKey(const text &key, bool matchCase = false) const;
		key_value_t<text, text> &operator[] (text key);
		//key_value_t<text, text> &operator() (text key) const;
		text keyValue(int index);
		void addKeyValue(text keyValue);
		int getInt(const text &key, int defVal);
		text getDebugString();
		virtual int compareProc(key_value_t<text, text> &item1, key_value_t<text, text> &item2);
		void sort(TCompareProc compareProc);
	};
	//--------------------------------------------------------------------------
	#if !defined(__GNUC__) && !defined(_MSC_VER) && !defined(_WIN64)   // causes duplicate symbole error
	#endif
	//---------------------------------------------------------------------------
	#if defined(__BORLANDC__)
	//text __fastcall operator << (char *left, const text& right);
	//text __fastcall operator << (wchar_t *left, const text& right);
	#endif
	//---------------------------------------------------------------------------
	//typedef text string;
	//---------------------------------------------------------------------------
}; // txt
#ifdef __BORLANDC__
#pragma option pop
#endif

using namespace txt;

#ifdef _MSC_VER
#pragma warning( default : 4996)
#pragma warning( default : 4267)
#pragma warning( default : 4244)
#endif

#endif


/* read and rread example:

	text retv = "x.abc.y.c";
	int off = 3, start;
	text x;
	while(retv[off])
	{
		off = retv.pass(off, L".");
		start = off;
		off = retv.read(off, L".");
		x = retv.substr(start, off - start);
	}
	off = 3;
	while(off >= 0)
	{
		off = retv.rpass(off, L".");
		start = off;
		off = retv.rread(off, L".");
		x = retv.substr(off + 1, start - off);
	}
*/

