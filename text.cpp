//1401-02-28

//---------------------------------------------------------------------------
#include <cstdlib>
#include <cwchar>
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "text.h"
#ifdef __BORLANDC__
#define nullptr NULL
#endif
//---------------------------------------------------------------------------
#ifdef __GNUC__
char *strrev(char *str)
{
	char *p1, *p2;

	if (!str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}
#endif
//---------------------------------------------------------------------------
namespace txt
{
uint64_t hash64(unsigned char *pData, int len)
{
	int index = 0;
	uint64_t retVal = 0;
	while (index < len)
	{
		uint64_t constant = 0x27d4eb2d;
		uint64_t value = pData[index] & 0xFF;
		value = (value ^ 61) ^ (value >> 16);
		value = value + (value << 3);
		value = value ^ (value >> 4);
		value = value * constant;
		value = value ^ (value >> 15);
		retVal += value * value;
		index ++;
	}
	return retVal;
}

stream_t::stream_t()
{
	m_position = 0;
}

void stream_t::setPosition(int position)
{
	m_position = position;
}

int stream_t::position()
{
	return m_position;
}

void stream_t::clear()
{
	setPosition(0);
}

void text_t::assign(const char *value)
{
	int len = strlen(value), index = 0;
	setLength(len);
	wchar_t *pData = data();
	while(value[index])
	{
		pData[index] = value[index];
		index ++;
	}
}

void text_t::assign(const wchar_t *value)
{
	int len = wcslen(value);
	setLength(len);
	memcpy(data(), value, sizeof(wchar_t) * (len + 1));
}

text_t::text_t(const char *value)
{
	assign(value);
}

text_t::text_t(const wchar_t *value)
{
	assign(value);
}

void text_t::setLength(int len)
{
	base_obj<wchar_t*>::data() = (wchar_t*) realloc(base_obj<wchar_t*>::data(), (len + 1) * sizeOf());
	base_obj<wchar_t*>::tag() = len;
	operator[](len) = 0;
}

int text_t::length() const
{
	return size();
}

text_t& text_t::operator =(const wchar_t *value)
{
	assign(value);
	return *this;
}

buffer_t<char16_t> text_t::getChar16Ptr() const
{
	buffer_t<char16_t> retv;
	int len = length();
	retv.setSize((len + 1) * 2);
	char16_t *pChr16 = (char16_t*) retv;
	wchar_t *pData = data();
	int index = 0;
	while(pData[index])
	{
		pChr16[index] = (char16_t) pData[index];
		index++;
	}
	pChr16[index] = 0;
	return retv;
}

text_t::operator wchar_t *() const
{
	return data();
}

data_t text_t::c_str() const
{
	data_t retv;
	int len = length();
	retv.setSize((len + 1) * 2);
	char *pChar = (char*) retv;
	wchar_t *pData = data();
	int index = 0;
	while(pData[index])
	{
		pChar[index] = (char16_t) pData[index];
		index++;
	}
	pChar[index] = 0;
	return retv;
}

text_t& text_t::operator =(const char *value)
{
	assign(value);
	return *this;
}

}
//---------------------------------------------------------------------------
//void data_t::clean()
//{
//	if(refCount() == 1 && data() != NULL)
//		::free(data());
//}
//---------------------------------------------------------------------------
data_t::data_t(int size) : buffer_t<char> (size)
{
}

data_t::data_t(const char *data, uint32_t len) : buffer_t<char> (data, len)
{
}

uint8_t* data_t::toUInt8Ptr() const
{
	return (uint8_t*) data();
}
//---------------------------------------------------------------------------
void data_t::operator <<(unsigned char byte)
{
	int size = length();
	setSize(size + 1);
	data()[size] = byte;
}
//---------------------------------------------------------------------------
void data_t::setLength(int len)
{
	//setSize(len + 1);
	base_obj<char*>::data() = (char*) realloc(base_obj<char*>::data(), (len + 1) * sizeOf());
	base_obj<char*>::tag() = len;
}
//---------------------------------------------------------------------------
int data_t::length() const
{
	return tag();
}
//---------------------------------------------------------------------------
#if __cplusplus > 201100L
//data_t::data_t(const std::initializer_list<char> &data) : buffer_t<char>(data)
//{
//}

data_t::data_t(const std::initializer_list<uint8_t> &data)
{
	setLength(data.size());
	auto it = data.begin();
	for (int i = 0; i < length(); i++)
		this->data()[i] = it[i];
}

#endif

//char &data_t::operator[](int index)
//{
//#ifdef _DEBUG
//	assert(index < size() + 1);
//#endif
//	return base_obj<char*>::data()[index];
//}

//char data_t::operator()(int index) const
//{
//#ifdef _DEBUG
//	assert(index < size() + 1);
//#endif
//	return base_obj<char*>::data()[index];
//}
//---------------------------------------------------------------------------
int data_t::find(const char *subStr, int offset, bool matchCase, bool unicode)
{
	bool result;
	int subStrLen = strlen(subStr);
	char *pData = data();
	int size = length();
	for (int i = offset; i <= size - subStrLen; i++)
	{
		result = true;
		int unicode_offset = 0;
		for (int j = 0; result && j < subStrLen; j++)
		{
			wchar_t ch1 = pData[i + j + unicode_offset], ch2 = subStr[j];
			if (!matchCase)
			{
				ch1 = tolower(ch1);
				ch2 = tolower(ch2);
			}
			result = result && ch1 == ch2;
			if (unicode && result)
			{
				unicode_offset++;
				result = result && pData[i + j + unicode_offset] == 0;
			}
		}
		if (result)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
bool data_t::saveToFile(const text &fileName)
{
	#if defined(__APPLE__) || defined(__ANDROID__)
	FILE *output = fopen(fileName.toUtf8(), "wb");
	#else
	FILE *output = _wfopen(fileName, L"wb");
	#endif
	if (output != NULL)
	{
		fwrite(data(), 1, length(), output);
		fclose(output);
	}
	return output != NULL;
}
//---------------------------------------------------------------------------
text data_t::toString(encoding_t encoding)
{
	text retv;
	switch (encoding) {
		case enAnsi:
			retv.copy(data(), length());
			break;
		case enUnicode:
		{
			int len = length() / 2;
			char16_t *pData = (char16_t*) (char*) data();
			if(len > 0 && pData[0] == 0xFEFF)
			{
				pData ++;
				len --;
			}
			retv.setLength(len);
			for (int i = 0; i < len; i++) {
				retv[i] = pData[i];
			}
			pData[len] = 0;
			break;
		}
		case enUtf8:
			retv.copy(data(), length());
			retv = retv.toUnicode();
			break;
		case enUtf16:
		{
			int len = length() / 2;
			retv.setLength(len);
			char16_t *pData = (char16_t*) data();
			for (int i = 0; i < len; i++) {
				retv[i] = pData[i];
			}
			break;
		}
		case enUtf16LE:
		{
			int len = length() / 2;
			retv.setLength(len);
			unsigned char *pData = (unsigned char *) data();
			for (int i = 0; i < len; i++) {
				retv[i] = (pData[i * 2] << 8) + pData[i * 2 + 1];
			}
			retv[len] = 0;
			break;
		}
	}
	return retv;
}
//---------------------------------------------------------------------------
ptr_list::ptr_list(int count)
{
	pointers = NULL;
	m_count = 0;
	m_refCount = 0;
	addRef();
	if(count)
		setLength(count);
	else
		setCapacity(5);
}
//---------------------------------------------------------------------------
void ptr_list::setCapacity(int value)
{
	m_capacity = value;
	pointers = realloc(pointers, value * sizeof(_int));
}
//---------------------------------------------------------------------------
void ptr_list::setLength(int value)
{
	setCapacity(value);
	m_count = value;
}
//---------------------------------------------------------------------------
int ptr_list::getCapacity()
{
	return m_capacity;
}
//---------------------------------------------------------------------------
int ptr_list::add(void *item)
{
	if(m_count >= m_capacity)
		setCapacity(m_capacity + 10);
	((_int*)pointers)[m_count] = (_int)item;
	return m_count++;
}
//---------------------------------------------------------------------------
void ptr_list::insert(void *item, int pos)
{
	if(m_count >= m_capacity)
		setCapacity(m_capacity + 10);
    for (int index = m_count; index > pos; index--) {
		((_int*)pointers)[index] = ((_int*)pointers)[index - 1];
	}
	((_int*)pointers)[pos] = (_int)item;
	m_count++;
}
//---------------------------------------------------------------------------
void ptr_list::remove(int index, int count)
{
	m_count -= count;
    for (int i = index; i < m_count; i++) {
		((_int*)pointers)[i] = ((_int*)pointers)[i + count];
	}
}
//---------------------------------------------------------------------------
ptr_list::~ptr_list()
{
	if(pointers)
		free(pointers);
}
//---------------------------------------------------------------------------
int ptr_list::count() const
{
	return m_count;
}
//---------------------------------------------------------------------------
#ifdef _Windows
#ifndef MessageBox
extern "C" int __stdcall MessageBoxW(void* hWnd, const wchar_t* lpText, const wchar_t* lpCaption, uint32_t uType);
#endif
#endif
void *ptr_list::item(int index)
{
	//assert(index >= 0);
	//assert(index < count());
	#ifdef _DEBUG
    if(index >= m_capacity)
	{
		text msg = text(L"File:'[]' Function:'[]' Line:'[]'\nInvalid index requested: index=[] count=[]") <<
			__FILE__ <<__FUNCTION__ << __LINE__ <<
			index <<
			count();
		#ifdef _Windows
		MessageBoxW(NULL, msg, L"Error", 0x00000000L /*ok*/);
		#else
        printf("%ls", msg.data);
		#endif
	}
	#endif
	return (void *)((_int*)pointers)[index];
}
//---------------------------------------------------------------------------
void ptr_list::addRef()
{
	m_refCount++;
}
//---------------------------------------------------------------------------
void ptr_list::release()
{
	m_refCount--;
	if(m_refCount == 0)
	{
		free(pointers);
		pointers = NULL;
		delete this;
	}
}
//---------------------------------------------------------------------------
int ptr_list::refCount()
{
	return m_refCount;
}
//---------------------------------------------------------------------------
void ptr_list::clear()
{
	m_count = 0;
}
//---------------------------------------------------------------------------
void** ptr_list::ptrList()
{
	return (void **)pointers;
}
//---------------------------------------------------------------------------
void ptr_list::exchange(int index1, int index2)
{
	_int *pData = (_int*)pointers;
	_int temp = (_int)pData[index1];
	pData[index1] = pData[index2];
	pData[index2] = temp;
}
//---------------------------------------------------------------------------
void *ptr_list::operator [] (int index)
{
	return item(index);
}
//---------------------------------------------------------------------------
void ptr_list::zero()
{
	memset(ptrList(), 0, count());
}
//---------------------------------------------------------------------------
void text::free()
{
	::free(data);
}
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
int text::tolower_fixed(int ch) const
{
	if(ch < 256)
		return tolower(ch);
	return ch;
}
//---------------------------------------------------------------------------
int text::toupper_fixed(int ch) const
{
	if(ch < 256)
		return toupper(ch);
	return ch;
}
#endif
//---------------------------------------------------------------------------
wchar_t *text::assign(const char *value)
{
	if(!value)
	{
		assign(L"");
		return data;
	}
	int index = strlen(value);
	resize(index);
	while(index >= 0) {
		data[index] = value[index] & 0xFF;
		index--;
	}
	return data;
}
//----------------------------------------------------------------------
wchar_t *text::assign(const wchar_t *value)
{
	if(!value)
	{
		assign(L"");
		return data;
	}
	if(value == data) // prevents assign to self
		return data;
	int index = int(wcslen(value));
	resize(index);
	while(index >= 0) {
#ifdef _Windows
		data[index] = value[index] & 0xFFFF;
#else
		data[index] = value[index];
#endif
		//fflush(stdout);
		index--;
	}
	return data;
}
//----------------------------------------------------------------------
wchar_t *text::assign(const char16_t *value)
{
	int index = 0;
	if(!value)
	{
		assign(L"");
		return data;
	}
	while(value[index])
		index++;
	resize(index);
	while(index >= 0) {
		data[index] = value[index] & 0xFFFF;
		index--;
	}
	return data;
}
//----------------------------------------------------------------------
text text::replace_once_ex(const wchar_t *from, const wchar_t *to, int *start, bool matchCase)
{
	int begin = 0;
	if(start) begin = *start;
	int pos = find_ex(from, begin, matchCase);
	if (pos == -1)
	{
		if (start)
			*start = -1;
		return data;
	}
	if (start)
		*start = pos + wcslen(to);
	text retv = substr(0, pos);
	retv += to;
	retv += substr(pos + wcslen(from));
	return retv;
}
//----------------------------------------------------------------------
wchar_t *text::wcsstr(const wchar_t *s1, const wchar_t *s2) const
{
	if (*s2 == L'\0')
		return ((wchar_t *)s1);
	for (; (s1 = wcschr(s1, *s2)) != 0; ++s1)
	{
		const wchar_t *sc1, *sc2;
		for (sc1 = s1, sc2 = s2; ; )
			if (*++sc2 == L'\0')
				return ((wchar_t *)s1);
			else if (*++sc1 != *sc2)
				break;
	}
	return 0;
}
//----------------------------------------------------------------------
bool compareCharIC(wchar_t ch1, wchar_t ch2)
{
	if(ch1 >= 'A' && ch1 <= 'Z')
		ch1 = ch1 | 32;
	if(ch2 >= 'A' && ch2 <= 'Z')
		ch2 = ch2 | 32;
	return ch1 == ch2;
}
//----------------------------------------------------------------------
wchar_t *text::iwcsstr(const wchar_t *str, const wchar_t *substr) const
{
	const wchar_t *tmp1, *tmp2;
	while(*str)
	{
		if(compareCharIC(*str, *substr))
		{
			tmp1 = str;
			tmp2 = substr;
			while(*tmp1 && *tmp2 && compareCharIC(*tmp1, *tmp2)) {
				tmp1++;
				tmp2++;
			}
			if(*tmp2 == 0) return (wchar_t *)str;
		}
		str++;
	}
	return NULL;
}
//----------------------------------------------------------------------
int text::wcsicmp(const wchar_t *s1, const wchar_t *s2) const
{
#ifdef _Windows
	return ::_wcsicmp(s1, s2);
#elif __APPLE__
	return wcscasecmp(s1, s2);
#endif
}
//----------------------------------------------------------------------
wchar_t *text::wcslwr(wchar_t *str) const
{
	wchar_t *p = (wchar_t *) str;

	while ( (*p = (wchar_t) tolower_fixed( *p ) ) != L'\0')
		p++;

	return str;
}
//----------------------------------------------------------------------
wchar_t *text::wcsupr(wchar_t *str) const
{
	wchar_t *p = (wchar_t *) str;

	while ( (*p = (wchar_t) toupper_fixed( *p ) ) != L'\0')
		p++;

	return str;
}
//----------------------------------------------------------------------
//wchar_t *text::wcstok(wchar_t *s1, const wchar_t *s2) const
//{
//    const wchar_t *sp;
//    wchar_t sc1, spc;
//    wchar_t *tok;
//    wchar_t **save;
//    static wchar_t *token;

//    save = &token;

//    if (s1 == NULL)
//        s1 = *save;

//    while ((sc1 = *s1) != 0)
//    {
//        for (sp = s2; (spc = *sp) != 0; sp++)
//            if (spc == sc1)
//                break;
//        if (spc == 0)
//            break;
//        s1++;
//    }
//    if (sc1 == 0)
//    {
//        *save = s1;
//        return (0);
//    }
//    tok = s1;
//    while ((sc1 = *s1) != 0)
//    {
//        for (sp = s2; (spc = *sp) != 0; sp++)
//            if (spc == sc1)
//                goto Found;
//        s1++;
//    }
//    *save = s1;
//    return (tok);
//    Found:
//    *s1++ = 0;
//    *save = s1;
//    return (tok);
//}
//----------------------------------------------------------------------
#ifdef _Windows
//#include "windows.h"
//extern "C" {
//	//NTSYSAPI WORD NTAPI RtlCaptureStackBackTrace (DWORD FramesToSkip, DWORD FramesToCapture, PVOID *BackTrace, PDWORD BackTraceHash);
//	uint16_t RtlCaptureStackBackTrace (uint32_t FramesToSkip, uint32_t FramesToCapture, void **BackTrace, uint32_t *BackTraceHash);
//	uint32_t GetModuleFileNameW (void* hModule, wchar_t *lpFilename, int32_t nSize);
//	bool GetModuleHandleExW (uint32_t dwFlags, wchar_t *lpModuleName, void **phModule);
//}
//text getCallerName(int stackIndex)
//{

//	void *frame;
//	text retv;
//	if(RtlCaptureStackBackTrace(stackIndex, 1, &frame, NULL) > 0)
//	{
//		unsigned char* pMem = (unsigned char*)frame;

//		void *hModule;
//		wchar_t moduleName[0xFF] = {};

//		GetModuleHandleExW(0x4 /*GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS*/, (wchar_t*)pMem,
//			&hModule);
//		GetModuleFileNameW(hModule, moduleName, 0xFF);
//		retv = moduleName;
//		retv = retv.substr(retv.rfind("\\") + 1);
//	}
//	return retv;
//}
#endif
text text::replace_ex(wchar_t *from, wchar_t *to, bool matchCase) const
{
	text result;
	int from_len = wcslen(from), to_len = wcslen(to);
	//const int max_offset = 1000;
	//int offsets[max_offset];
	buffer_t<int> offsets(500);
	int offset = 0, offset_count = 0, offset_src = 0, offset_dst = 0;
	//debug("from=%ls to=%ls", from, to)
	do {
		offset = find_ex(from, offset, matchCase);
		if(offset == -1)
			break;
#ifdef _Windows
		if(offset_count >= offsets.size())
			offsets.setSize(offsets.size() + 100);
//		{
//			text txt = data;
//			int len = length();
//			if(len > 100)
//			{
//				txt = txt.substr(0, 100);
//				txt += text("... (len=[])") << len;
//			}
//			MessageBoxW(NULL, text("text='[]' from='[]' to='[]'") << txt << from << to, L"Alert", 0);
//		}
#endif
//		assert(offset_count < max_offset);
		offsets[offset_count] = offset;
		offset += from_len;
		offset_count ++;
	} while(true);
	int d_len = to_len - from_len;
	int len = length();
	result.setLength(len + d_len * offset_count);
	for (int oi = 0; oi < offset_count; oi ++) {
		wmemmove(result.data + offset_dst, data + offset_src, offsets[oi] - offset_src);
		offset_dst += offsets[oi] - offset_src;
		wmemmove(result.data + offset_dst, to, to_len);
		offset_src = offsets[oi] + from_len;
		offset_dst += to_len;
	}
	wmemmove(result.data + offset_dst, data + offset_src, len - offset_src);
	return result;
}
//----------------------------------------------------------------------
text text::replace_ex(wchar_t *startTag, wchar_t *endTag, wchar_t *repl,
	bool replaceTags, int start, bool matchCase)
{
	int pos0 = find_ex(startTag, start, matchCase);
	if (pos0 == -1)
		return data;
	int startTagLen = wcslen(startTag);
	if (!replaceTags)
		pos0 += startTagLen;
	int pos1;
	if (!endTag[0])
		pos1 = length();
	else
		pos1 = find_ex(endTag, pos0 + startTagLen, matchCase);
	if (pos1 == -1)
		return data;
	if (replaceTags)
		pos1 += wcslen(endTag);
	text ret = substr(0, pos0);
	ret += repl;
	ret += substr(pos1, length());
	return ret;
}
//----------------------------------------------------------------------
text text::wcSubstr_ex(wchar_t *pattern, int start, bool matchCase)
{
	int len;
	int pos = wcFind_ex(pattern, start, matchCase, &len);
	if (pos == -1)
		return (const wchar_t *)L"";
	return substr(pos, len);
}
//----------------------------------------------------------------------
bool text::wcCompare_ex(const wchar_t *pattern, int start, bool matchCase, bool whole_word, int *end) const
{
	wchar_t *cp = NULL, *mp = NULL, *pData = data + start, chr1, chr2;
	bool retv = false;
	if (end)
		*end = 0;
	while ((*pData) && (*pattern != '*'))
	{
		chr1 = *pattern;
		chr2 = *pData;
		if (!matchCase)
		{
			chr1 = tolower_fixed(chr1);
			chr2 = tolower_fixed(chr2);
		}
		if ((chr1 != chr2) && (*pattern != '?'))
		{
			retv = false;
			goto final;
		}
		pattern++;
		pData++;
		if (*pattern == 0 && !whole_word)
		{
			retv = true;
			goto final;
		}
	}

	while (*pData)
	{
		chr1 = *pattern;
		chr2 = *pData;
		if (!matchCase)
		{
			chr1 = tolower_fixed(chr1);
			chr2 = tolower_fixed(chr2);
		}
		if (chr1 == '*')
		{
			if (!*++pattern)
			{
				while (*pData)
					pData++;
				retv = true;
				goto final;
			}
			mp = (wchar_t *)pattern;
			cp = pData + 1;
		}
		else if ((chr1 == chr2) || (chr1 == '?'))
		{
			pattern++;
			pData++;
			if (*pattern == 0 && !whole_word)
			{
				retv = true;
				goto final;
			}
		}
		else
		{
			pattern = mp;
			pData = cp++;
			if (!pData)
				goto final;
		}
	}

	while (*pattern == '*')
	{
		pattern++;
	}

	retv = !*pattern;
final:
	if (end)
		*end = pData - data;
	return retv;

}
//----------------------------------------------------------------------
int text::wcFind_ex(const wchar_t *pattern, int start, bool matchCase, int *end)
{
	if (end)
		*end = 0;
	for (int pos = start; data[pos]; pos++)
	{
		bool match = wcCompare_ex(pattern, pos, matchCase, false, end);
		if (match)
		{
			*end = *end - pos;
			return pos;
		}
	}
	return -1;
}
//----------------------------------------------------------------------
text text::wcReplace_ex(text pattern, text repl, bool matchCase, bool replaceOnce)
{
	text retv = data;
	int start = 0;
	do {
		range range = matchCase ? retv.wcFind(pattern, start) : retv.wciFind(pattern, start);
		if(range.start == -1) break;
		else if(range.start == 0)
			retv = repl + retv.substr(range.length());
		else
			retv = retv.substr(0, range.start) + repl + retv.substr(range.start + range.length());
		start = range.start + repl.length();
	} while(!replaceOnce);
	return retv;
}
//----------------------------------------------------------------------
int text::find_ex(const wchar_t *str, int start, bool matchCase) const
{
	if(matchCase)
	{
		wchar_t *pos = wcsstr(data + start, str);
		if (!pos)
			return -1;
		return pos - data;
	}
	else
	{
		wchar_t *pos = iwcsstr(data + start, str);
		if (!pos)
			return -1;
		return pos - data;
	}
}
//----------------------------------------------------------------------
int text::rfind_ex(wchar_t *str, int rOff, bool matchCase) const
{
	int len = length();
	int start = len - wcslen(str) - rOff;
	int max = len - rOff;
	wchar_t *pos = NULL;
	while (start >= 0)
	{
		wchar_t *pos = matchCase ? wcsstr(data + start - rOff, str) :
			iwcsstr(data + start - rOff, str);
		if (pos && pos - data < max)
			return pos - data;
		start--;
	}
	if (!pos)
		return -1;
	return pos - data;
}
//----------------------------------------------------------------------
void text::substr_ex(text &result, const wchar_t *startStr, const wchar_t *endStr,
	int start, int end, bool matchCase) const
{
	int startPos, startLen = 0;
	if (!startStr[0])
		startPos = 0;
	else
	{
		startPos = find_ex(startStr, start, matchCase);
		startLen = wcslen(startStr);
	}

	if (startPos == -1 || (end && (startPos > end)))
		return;
	int endPos;
	if (!endStr[0])
		endPos = length();
	else
		endPos = find_ex(endStr, startPos + startLen, matchCase);
	if (endPos == -1)
		return;
	int begin = startPos + startLen;
	result = substr(begin, endPos - begin);
}
//----------------------------------------------------------------------
void text::read_ex(text &substr, int &start, const wchar_t *stopChars) const
{
	int end = start;
	while (data[end] && !wcschr(stopChars, data[end]))
		end++;
	int len = end - start;
	substr.setLength(len);
	wmemmove(substr.data, data + start, len);
	start = start + len;
}
//----------------------------------------------------------------------
void text::rread_ex(text &substr, int &start, const wchar_t *stopChars)
{
	int end = start;
	while (end >= 0 && !wcschr(stopChars, data[end]))
		end--;
	int len = end - start;
	substr.setLength(-len);
	wmemmove(substr.data, data + start + len + 1, -len);
	start = start + len;
}
//----------------------------------------------------------------------
void text::read_ex(text &substr, wchar_t *startStr, const wchar_t *stopChars, bool matchCase) const
{
	int start = find_ex(startStr, 0, matchCase);
	if(start > -1)
		read_ex(substr, start, stopChars);
}
//----------------------------------------------------------------------
bool text::isBase64(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}
//----------------------------------------------------------------------
array text::split(const wchar_t *delim) const
{
	array retV;
	if(!data[0])
		return retV;
	int begin = 0, end, len;
	int delim_len = wcslen(delim);
	start :
	end = find_ex(delim, begin, true);
	if(end != -1)
		len = end - begin;
	else
		len = -1;
	substr(retV.add(), begin, len);
	begin = end + delim_len;
	if(len != -1)
	{
		if(data[begin])
			goto start;
		else
			retV.add();
	}
	return retV;
}
//---------------------------------------------------------------------------
array text::split(const wchar_t *startTag, const wchar_t *endTag) const
{
	array retv;
	int len1 = wcslen(startTag);
	int len2 = wcslen(endTag);
	int pos1 = 0, pos2;
	while((pos1 = find_ex(startTag, pos1, true)) != -1)
	{
		pos1 += len1;
		pos2 = find_ex(endTag, pos1, true);
		if (pos2 < 0) {
			break;
		}
		retv << substr(pos1, pos2 - pos1);
		pos1 = pos2 + len2;
	}
	return retv;
}

void text::split(const wchar_t *delim, splitCallback callback, void *user_data) const
{
	int delim_len = wcslen(delim);
	wchar_t *find = data;
	int offset = 0, offset_prev = 0;
	int index = 0;
	while(find)
	{
		find = wcsstr(data + offset, delim);
		if(find)
		{
			offset = ((__int64)find - (__int64)data) / sizeof(wchar_t);
			wchar_t save = data[offset];
			data[offset] = 0;
			callback(data + offset_prev, index, user_data);
			data[offset] = save;
		}
		else
		{
			callback(data + offset_prev, index, user_data);
			return;
		}
		offset += delim_len;
		offset_prev = offset;
		index ++;
	}
}
//---------------------------------------------------------------------------
data_t& data_t::loadFromFile(const text &fileName, uint32_t offset, uint32_t count)
{
	#if defined(__APPLE__) || defined(__ANDROID__)
	FILE *input = fopen(fileName.toUtf8(), "rb");
	#else
	FILE *input = _wfopen(fileName, L"rb");
	#endif
	if (input != NULL)
	{
		fseek(input, 0, SEEK_END);
		unsigned long size = ftell(input);
		fseek(input, 0, SEEK_SET);
		if(count)
		{
			fseek(input, offset, SEEK_SET);
			if(offset + count > size)
				size = size - offset;
			else
				size = count;
		}
		setLength(size); // allocates size + 1, because data_t sometimes uses for c strings (c_str())
		fread(data(), 1, size, input);
		fclose(input);
	}
	return *this;
}
//---------------------------------------------------------------------------
data_t text::toUtf8() const
{
	data_t retv;
	uint32_t ch, len = 0;

    //uint8_t bt1, bt2, bt3, bt4, bt5, bt6;
	retv.setLength(length() * 2 + 6);
	for (int n = 0; data[n]; ++n)
	{
		if(len >= (uint32_t) retv.length())
		{
			retv.setLength(retv.length() + 100);
		}
		ch = data[n];
		if (ch < 128) {
			retv[len++] = ch;
		}
		else if (ch <= 2047) {
			retv[len++] = (uint8_t)(192 + (ch / 64));
			retv[len++] = (uint8_t)(128 + (ch % 64));
		}
		else if (ch <= 65535) {
			retv[len++] = (uint8_t)(224 + (ch / 4096));
			retv[len++] = (uint8_t)(128 + ((ch / 64) % 64));
			retv[len++] = (uint8_t)(128 + (ch % 64));
		}
		else if (ch <= 2097151) {
			retv[len++] = (uint8_t)(240 + (ch / 262144));
			retv[len++] = (uint8_t)(128 + ((ch / 4096) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 64) % 64));
			retv[len++] = (uint8_t)(128 + (ch % 64));
		}
		else if (ch <= 67108863) {
			retv[len++] = (uint8_t)(248 + (ch / 16777216));
			retv[len++] = (uint8_t)(128 + ((ch / 262144) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 4096) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 64) % 64));
			retv[len++] = (uint8_t)(128 + (ch % 64));
		}
		else if (ch <= 2147483647) {
			retv[len++] = (uint8_t)(252 + (ch / 1073741824));
			retv[len++] = (uint8_t)(128 + ((ch / 16777216) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 262144) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 4096) % 64));
			retv[len++] = (uint8_t)(128 + ((ch / 64) % 64));
			retv[len++] = (uint8_t)(128 + (ch % 64));
		}
	}
	retv[len] = 0;
	retv.setLength(len);
	return retv;
}
//---------------------------------------------------------------------------
text text::toUnicode()
{
	text retv;
	retv.setLength(length());
	int index = 0;
	uint32_t ch1, ch2, ch3;

	int len = 0;
	while (data[index]) {
		ch1 = data[index];
		if (ch1 < 128) {
			retv[len] = wchar_t(ch1);
			index++;
		}
		else if ((ch1 > 191) && (ch1 < 224)) {
			ch2 = data[index + 1];
			retv[len] = wchar_t(((ch1 & 31) << 6) | (ch2 & 63));
			index += 2;
		}
		else {
			ch2 = data[index + 1];
			ch3 = data[index + 2];
			retv[len] =
				wchar_t(((ch1 & 15) << 12) | ((ch2 & 63) << 6) | (ch3 & 63));
			index += 3;
		}
		len++;
	}
	retv[len] = 0;
	return retv;
}
//---------------------------------------------------------------------------
uint8_t text::utf8ByteCount(int index)
{
	wchar_t ch = data[index];
	uint8_t mask = 0x80u;
	unsigned result = 0;
	while(ch & mask)
	{
		++result;
		mask >>= 1;
	}
	return (result == 0) ? 1 : ((result > 4) ? 4 : result);
}
//---------------------------------------------------------------------------
uint8_t text::utf16ByteCount(int index)
{
	wchar_t ch = data[index];
	if (ch >= 0xd800 && ch <= 0xdbff)
		return 4;
	else
		return 2;
}
//---------------------------------------------------------------------------
array text::splitByCodepoint()
{
	array ret;
	int index = 0;
	while (data[index]) {
		uint8_t count = utf16ByteCount(index) / sizeof(wchar_t);
		text &item = ret.add();
		item.copy(data + index, count);
		index += count;
	}
	return ret;
}
//---------------------------------------------------------------------------
text::text()
{
	data = NULL;
	assign(L"");
}
//---------------------------------------------------------------------------
text::text(const text &value)
{
	data = NULL;
	assign(value.data);
}
//---------------------------------------------------------------------------
text::text(double value)
{
	data = NULL;
	setLength(0);
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(int value)
{
	data = NULL;
	setLength(0);
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(unsigned int value)
{
	data = NULL;
	setLength(0);
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(long value)
{
	data = NULL;
	setLength(0);
	operator = ((int)value);
}
//---------------------------------------------------------------------------
text::text(int64_t value)
{
	data = NULL;
	setLength(0);
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(uint64_t value)
{
	data = NULL;
	setLength(0);
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(char value)
{
	data = NULL;
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(char16_t value)
{
	data = NULL;
	operator = ((wchar_t)value);
}
//---------------------------------------------------------------------------
text::text(wchar_t value)
{
	data = NULL;
	operator = (value);
}
//---------------------------------------------------------------------------
text::text(const data_t &data, encoding_t encoding)
{
	this->data = NULL;
	char *pData = reinterpret_cast<char*>(data.dataPtr());
	switch (encoding) {
		case enAnsi:
		{
			int len = data.length();
			setLength(len);
			for (int i = 0; i < len; i++) {
				this->data[i] = pData[i] & 0xFF;
			}
			break;
		}
		case enUnicode:
		{
			int len = data.length() / 2;
			setLength(len);
			for (int i = 0; i < len; i++) {
				this->data[i] = ((wchar_t*)pData)[i];
			}
			break;
		}

		case enUtf8: break;
	default:
		;
	}
}
//---------------------------------------------------------------------------
text::~text()
{
	free();
}

#ifdef QSTRING_H
void text::assign(const QString &value)
{
	int len = value.length();
	setLength(len);
	int offset = 0;
	foreach(QChar ch, value)
		data[offset++] = ch.unicode();
}

void text::assign(const QByteArray &value)
{
	setLength(value.size());
	copy(value.constData(), value.size());
}

text::text(const QString &value)
{
	data = NULL;
	assign(value);
}

text::text(const QByteArray &value)
{
	data = NULL;
	assign(value);
}

text &text::operator =(const QString &value)
{
	data = NULL;
	assign(value);
	return *this;
}

text::operator QString() const
{
	return QString::fromWCharArray(data);
}

QByteArray text::byteArray() const
{
	return QByteArray(c_str(), length());
}

text &text::operator =(const QByteArray &value)
{
	data = NULL;
	assign(value);
	return *this;
}

void data_t::writeByteArray(const QByteArray &data)
{
	write(data.data(), data.size());
}

QByteArray data_t::byteArray() const
{
	return QByteArray(data(), size());
}
#endif
//---------------------------------------------------------------------------
#ifdef __COREFOUNDATION_CFSTRING__
//---------------------------------------------------------------------------
text::text(const CFStringRef value)
{
	data = NULL;
	operator = (value);
}
//---------------------------------------------------------------------------
void text::operator = (const CFStringRef value)
{
	if(value == NULL)
	{
		assign("");
		return;
	}
	int len = CFStringGetLength(value);
	resize(len);
	for (int i=0; i<len; i++) {
		data[i] = CFStringGetCharacterAtIndex(value, i);
	}
	data[len] = 0;
}
//---------------------------------------------------------------------------
//text::operator CFStringRef () const
AutoReleaseStringRef::AutoReleaseStringRef(const text &value)
{
	mValue = value.createStringRef();
}
//---------------------------------------------------------------------------
AutoReleaseStringRef::~AutoReleaseStringRef()
{
	if (mValue) {
		CFRelease(mValue);
	}
}
//---------------------------------------------------------------------------
AutoReleaseStringRef::operator CFStringRef()
{
	return mValue;
}
//---------------------------------------------------------------------------
CFStringRef text::createStringRef() const
{
//	return CFStringCreateWithBytes(kCFAllocatorDefault, reinterpret_cast<const UInt8 *>(data),
//		uint(length()) * sizeof(wchar_t), kCFStringEncodingUTF32, false);
	return  CFStringCreateWithCharacters(kCFAllocatorDefault,
										 reinterpret_cast< ::UniCharPtr >(getChar16Ptr().operator char *()),
										 length());
}
//---------------------------------------------------------------------------
AutoReleaseStringRef text::getStringRef() const
{
	return AutoReleaseStringRef(*this);
}
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
text text::link(int chr1, ...)
{
	const int maxParams = 255;
	wchar_t buffer[maxParams];
	int index = 0;
	va_list args;
	va_start(args, chr1);
	wchar_t chr = chr1;
	while (chr && index + 1 < maxParams)
	{
		buffer[index++] = chr;
		chr = va_arg(args, int);
	}
	buffer[index] = 0;
	va_end(args);
	return text(buffer);
}
//---------------------------------------------------------------------------
text& text::operator = (const char value)
{
	char str[] = {value, 0};
	assign(str);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const wchar_t value)
{
	wchar_t str[] = {value, 0};
	assign(str);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const char16_t value)
{
	char16_t str[] = {value, 0};
	assign(str);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const text &value)
{
	assign(value.data);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (bool value)
{
	assign(value ? "1" : "0");
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (int value)
{
	print("%i", value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (unsigned int value)
{
	print("%u", value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (int64_t value)
{
	print("%lli", value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (uint64_t value)
{
	print("%llu", value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (double value)
{
	print("%f", value);
	int trim = 0;
	int len = length();
	while (data[len - trim - 1] == L'0')
		trim++;
	len -= trim;
	if(data[len - 1] == L'.')
		len --;
	setLength(len);
	return *this;
}
//---------------------------------------------------------------------------
void text::operator += (text value)
{
	append(value.data);
}
//---------------------------------------------------------------------------
void text::set(wchar_t chr, int count)
{
	int index = 0;
	if (count) {
		setLength(count);
		while(count != index)
			data[index++] = chr;
	}
	else {
		while(data[index])
			data[index++] = chr;
	}
}
//---------------------------------------------------------------------------
void text::display()
{
	#ifdef _WINBASE_
	OutputDebugStringW(data);
	#elif __APPLE__
	printf("%ls\n", data);
	#endif
}
//---------------------------------------------------------------------------
wchar_t *text::append_char(const char value)
{
	wchar_t str[] = {(wchar_t) value, 0};
	return append(str);
}
//---------------------------------------------------------------------------
wchar_t *text::append_char(const wchar_t value)
{
	wchar_t str[] = {value, 0};
	return append(str);
}
//---------------------------------------------------------------------------
wchar_t *text::append_char(const char16_t value)
{
	wchar_t str[] = {value, 0};
	return append(str);
}
//---------------------------------------------------------------------------
text &text::copy(const char *buffer, int count)
{
	setLength(count);
	for (int i = 0; i < count; i++) {
		data[i] = buffer[i] & 0xFF;
	}
	return *this;
}
//---------------------------------------------------------------------------
text &text::copy(const wchar_t *buffer, int count)
{
	setLength(count);
	for (int i = 0; i < count; i++) {
		#ifdef __APPLE__
		data[i] = buffer[i];
		#elif _Windows
		data[i] = buffer[i] & 0xFFFF;
		#endif
	}
	return *this;
}
//---------------------------------------------------------------------------
text &text::copy(const char16_t *buffer, int count)
{
	setLength(count);
	for (int i = 0; i < count; i++) {
		data[i] = buffer[i] & 0xFFFF;
	}
	return *this;
}

//---------------------------------------------------------------------------
void text::operator += (const char value)
{
	append_char(value);
}
//---------------------------------------------------------------------------
void text::operator += (const wchar_t value)
{
	append_char(value);
}
//---------------------------------------------------------------------------
void text::operator += (const char16_t value)
{
	append_char(value);
}
//---------------------------------------------------------------------------
wchar_t *text::append(const wchar_t *value)
{
	if (!value)
		return data;
	int appendLen = wcslen(value);
	int currentLen = wcslen(data);
	setLength(appendLen + currentLen);
	memcpy(data + currentLen, value, appendLen * sizeof(wchar_t));
	return data;
}
//---------------------------------------------------------------------------
wchar_t *text::append(const char16_t *value)
{
	if (!value)
		return data;
	int appendLen = 0;
	while (value[++appendLen]);
	int currentLen = wcslen(data);
	setLength(appendLen + currentLen);
	for (int i = 0; i <= appendLen; i++) {
		data[currentLen + i] = value[i];
	}
	return data;
}
//---------------------------------------------------------------------------
wchar_t *text::append(const char *value)
{
	if (!value)
		return data;
	int appendLen = strlen(value);
	int currentLen = wcslen(data);
	setLength(appendLen + currentLen);
	for (int i = 0; i <= appendLen; i++) {
		data[currentLen + i] = value[i];
	}
	return data;
}
//---------------------------------------------------------------------------
text text::operator + (const wchar_t *value) const
{
	return text(data).append(value);
}
//----------------------------------------------------------------------
text text::operator + (const char16_t *value) const
{
	return text(data).append(value);
}
//---------------------------------------------------------------------------
text text::operator + (const char *value) const
{
	return text(data).append(value);
}
//---------------------------------------------------------------------------
void text::operator += (const wchar_t *value)
{
	append(value);
}
//---------------------------------------------------------------------------
void text::operator += (const char16_t *value)
{
	append(value);
}
//---------------------------------------------------------------------------
void text::operator += (const char *value)
{
	append(value);
}
//---------------------------------------------------------------------------
text text::operator + (const wchar_t value) const
{
	int len = length();
	text retv = data;
	retv.setLength(len + 1);
	retv[len] = value;
	return retv;
}
//---------------------------------------------------------------------------
text text::operator + (const char16_t value) const
{
	int len = length();
	text retv = data;
	retv.setLength(len + 1);
	retv[len] = value;
	return retv;
}
//---------------------------------------------------------------------------
text text::operator + (const char value) const
{
	int len = length();
	text retv = data;
	retv.setLength(len + 1);
	retv[len] = value;
	return retv;
}
//---------------------------------------------------------------------------
text text::operator + (const text &value) const
{
	return text(data).append(value.data);
}
//---------------------------------------------------------------------------
bool text::operator == (const text &value) const
{
    return !compare(value);
}
//---------------------------------------------------------------------------
bool text::operator == (const wchar_t *value) const
{
	return !compare(value);
}

bool text::operator == (const char *value) const
{
	return !compare(text(value));
}

bool text::operator !=(const text &value) const
{
	return compare(value);
}
//---------------------------------------------------------------------------
bool text::operator != (const wchar_t *value) const
{
	return !operator == (value);
}
//---------------------------------------------------------------------------
bool text::operator != (const char *value) const
{
	return !operator == (value);
}
//---------------------------------------------------------------------------
bool text::operator / (const text &value) const
{
	return icompare(value) == 0;
}

bool text::operator ^(const text &value) const
{
	return contains(value);
}
//---------------------------------------------------------------------------
text::operator wchar_t* () const
{
	return data;
}
//---------------------------------------------------------------------------
text& text::operator = (const char *value)
{
	assign(value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const wchar_t *value)
{
	assign(value);
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const char16_t *value)
{
	assign(value);
	return *this;
}
//---------------------------------------------------------------------------
text::text(const wchar_t *value)
{
	data = NULL;
	assign(value);
}
//---------------------------------------------------------------------------
text::text(const char16_t *value)
{
	data = NULL;
	assign(value);
}
//---------------------------------------------------------------------------
text::text(const char *value)
{
	data = NULL;
	assign(value);
}
//---------------------------------------------------------------------------
#if !defined(TXT_LIGHT) && defined(__BORLANDC__)
//---------------------------------------------------------------------------
text::text(const UnicodeString &value)
{
	data = NULL;
	assign(value.c_str());
}
//---------------------------------------------------------------------------
text::text(const AnsiString &value)
{
	data = NULL;
	assign(value.c_str());
}
//---------------------------------------------------------------------------
text::text(const WideString &value)
{
	data = NULL;
	assign(value.c_bstr());
}
//---------------------------------------------------------------------------
text& text::operator = (const String &value)
{
	assign(value.c_str());
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const WideString &value)
{
	assign(value.c_bstr());
	return *this;
}
//---------------------------------------------------------------------------
text& text::operator = (const AnsiString &value)
{
	assign(value.c_str());
	return *this;
}
//---------------------------------------------------------------------------
void text::operator += (const String &value)
{
	append(value.c_str());
}
//---------------------------------------------------------------------------
void text::operator += (const AnsiString &value)
{
	operator += (value.c_str());
}
//---------------------------------------------------------------------------
text::operator UnicodeString() const
{
	return WideString(data); // uses WideString because UnicodeString constructor [Mac] is buggy
}
//---------------------------------------------------------------------------
text::operator AnsiString() const
{
	return AnsiString(data);
}
//---------------------------------------------------------------------------
text::operator WideString() const
{
	return WideString(data);
}
//---------------------------------------------------------------------------
text text::operator + (const UnicodeString &value) const
{
	return text(data).append(value.c_str());
}
//---------------------------------------------------------------------------
text text::operator + (const AnsiString &value) const
{
	return text(data).append(value.c_str());
}
//---------------------------------------------------------------------------
text text::operator + (const WideString &value) const
{
	return text(data).append(value.c_bstr());
}
//---------------------------------------------------------------------------
text::text(DWORD value)
{
	data = NULL;
	operator = (value);
}
//---------------------------------------------------------------------------
void text::operator = (DWORD value)
{
	#ifdef _Windows
	char buf[20];
	ultoa(value, buf, 10);
	assign(buf);
	#elif __APPLE_
	print("%u", value);
	#endif
}
//---------------------------------------------------------------------------
TMemoryStream *data_t::createMemoryStream()
{
	TMemoryStream *retv = new TMemoryStream;
	retv->Write(data(), length());
	return retv;
}
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
text text::toHex(int digits)
{
	char fmt[10];
	sprintf(fmt, "%%.%iX", digits);
	return text().print(fmt, intValue());
}
//---------------------------------------------------------------------------
text text::toHexString()
{
	char *pData = (char*)data;
	int len = length();
	int size = (len + 1) * sizeof(wchar_t) * 2;
	text retv;
	retv.setLength(size);
	for (int i = 0; i < len * 2; i++) {
		swprintf_s(retv.data + i * 2, size, L"%.2X", pData[i] & 255);
	}
	return retv;
}
//---------------------------------------------------------------------------
text& text::fromHexString(text hexStr)
{
	setLength(hexStr.length() / sizeof(wchar_t) / 2);
	int pos = 0;
	for (int i = 0; hexStr[i]; i += 4) {
		text hex = hexStr.substr(i + 2, 2) + hexStr.substr(i, 2);
		data[pos++] = hex.intValue(16);
	}
	return *this;
}
//---------------------------------------------------------------------------
text& text::remove(int pos, int count)
{
	int index;
	#ifdef _DEBUG
	if(pos + count > length())
		throw "txt::remove: invalid params.";
	#endif
	for (index = pos; data[index + count - 1]; index++) {
		data[index] = data[index + count];
	}
	return *this;
}
//---------------------------------------------------------------------------
text& text::insert(int pos, wchar_t chr)
{
	int index;
	int len = length();
	resize(len + 1);
	for (index = len; index > pos; index--) {
		data[index] = data[index - 1];
	}
	data[pos] = chr;
	data[len + 1] = 0;
	return *this;
}
//---------------------------------------------------------------------------
text& text::insert(int pos, const text &text)
{
	*this = substr(0, pos) + text + substr(pos);
	return *this;
}
//---------------------------------------------------------------------------
uint64_t text::hash64() const
{
	int index = 0;
	uint64_t retVal = 0;
	while (data[index++])
	{
		uint64_t constant = 0x27d4eb2d;
		uint64_t value = data[index] & 0xFF;
		value = (value ^ 61) ^ (value >> 16);
		value = value + (value << 3);
		value = value ^ (value >> 4);
		value = value * constant;
		value = value ^ (value >> 15);
		retVal += value * value;
	}
	return retVal;
}
//---------------------------------------------------------------------------
text text::filter(TFilterProc proc) const
{
	text retv;
	retv.setLength(length());
	int pos = 0, retv_pos = 0;
	while(data[pos])
	{
		if(proc(data[pos]))
			retv[retv_pos++] = data[pos];
		pos++;
	}
	retv[retv_pos] = data[pos];
	return retv;
}
//---------------------------------------------------------------------------
text& text::itoa64(uint64_t value, int radix)
{
	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", buf[20];
	int pos = 0;
	__int64 count;
	int remain;
	do {
		count = value / radix;
		remain = value % radix;
		buf[pos++] = digits[remain];
		value = count;
	}
	while (count);
	buf[pos] = 0;
	strrev(buf);
	assign(buf);
	return *this;
}
//---------------------------------------------------------------------------
int text::countOf(wchar_t chr, int max) const
{
	int retv = 0, index = 0;
	while(data[index] && (max == 0 || index <= max))
	{
		retv += data[index++] == chr;
	}
	return retv;
}
//---------------------------------------------------------------------------
data_t text::getChar16Ptr() const
{
	data_t retv;
	int len = length();
	retv.setSize((len + 1) * 2);
	char16_t *chr16 = (char16_t*)(char*)retv;
	int index = 0;
	while(data[index])
	{
		chr16[index] = (char16_t)data[index];
		index++;
	}
	chr16[index] = 0;
	return retv;
}
//---------------------------------------------------------------------------
char16_t* text::createChar16Ptr() const
{
	data_t data = getChar16Ptr();
	char16_t *retv = new char16_t[data.length() / sizeof(char16_t) + 1];
	memcpy(retv, data, data.length());
	return retv;
}
//---------------------------------------------------------------------------
text text::operator << (const text &value)
{
	return replaceOnce("[]", value);
}
//---------------------------------------------------------------------------
text text::operator >> (text value)
{
	return replace(value, "");
}
//---------------------------------------------------------------------------
text text::operator | (void *value)
{
	text temp;
	temp.print("%X", value);
	return operator << (temp);
}
//---------------------------------------------------------------------------
text text::operator | (bool value)
{
	return operator << ((text)(value ? L"true" : L"false"));
}
//---------------------------------------------------------------------------
text text::operator | (int value)
{
	return operator << (value);
}
//---------------------------------------------------------------------------
text text::operator | (char value)
{
	return operator << (value);
}
//---------------------------------------------------------------------------
text text::operator | (long value)
{
	return operator << (value);
}
//---------------------------------------------------------------------------
text text::operator | (wchar_t *value)
{
	return operator << (text(value));
}
//---------------------------------------------------------------------------
text text::operator | (char *value)
{
	return operator << (text(value));
}
//---------------------------------------------------------------------------
text text::operator | (unsigned long value)
{
	return operator << ((int)value);
}
//---------------------------------------------------------------------------
text text::operator | (double value)
{
	return operator << (value);
}
//---------------------------------------------------------------------------
text text::operator | (text value)
{
	return operator << (value);
}
//---------------------------------------------------------------------------
wchar_t& text::operator[](int index)
{
//#ifdef _DEBUG
//	assert(index <= length());
//#endif
	return data[index];
}
//---------------------------------------------------------------------------
wchar_t& text::operator()(int index) const
{
//#ifdef _DEBUG
//	assert(index <= length());
//#endif
	return data[index];
}
//---------------------------------------------------------------------------
int text::length() const
{
	return int(wcslen(data));
}

int text::byteSize() const
{
	return (length() + 1) * int(sizeof (wchar_t));
}
//---------------------------------------------------------------------------
void text::setLength(int value)
{
	resize(value);
    data[value] = 0; // what happen if exists a zero before value?
}
//---------------------------------------------------------------------------
void text::resize(int value)
{
	int size = sizeof(wchar_t) * (value + 1);
	data = (wchar_t*) realloc(data, size);

#if defined (_DEBUG)
	assert(data != NULL);
#endif
}
//---------------------------------------------------------------------------
wchar_t& text::lastChar() const
{
	int len = length();
	if(len == 0)
		return data[0];
	return data[len - 1];
}
//---------------------------------------------------------------------------
wchar_t& text::firstChar()
{
	return data[0];
}
//---------------------------------------------------------------------------
text& text::decreaseLen(int count)
{
	if(data[0])
		setLength(length() - count);
	return *this;
}
//---------------------------------------------------------------------------
text text::replaceOnce(const text &from, const text &to, int *start)
{
	return replace_once_ex(from.data, to.data, start, true);
}
//---------------------------------------------------------------------------
text text::ireplaceOnce(const text &from, const text &to, int *start)
{
	return replace_once_ex(from.data, to.data, start, false);
}
//---------------------------------------------------------------------------
text& text::replaceChar(wchar_t from, wchar_t to, int skip)
{
    int index = 0, chi, match = 0;
	for (chi = 0; data[chi]; chi ++) {
		if (data[chi] == from)
		{
            match++;
            if (skip == -1 || match - 1 == skip) {
                data[index] = to;
                index += to != 0;
                continue;
            }
        }
		data[index] = data[chi];
		index ++;
	}
	if (index != chi) {
		setLength(index);
	}
	return *this;
}
//---------------------------------------------------------------------------
// text& text::replaceChar(wchar_t from, wchar_t to, bool all, int skip)
// {
// 	int index = 0, chi, occur = 0;
// 	bool done = false;
// 	for (chi = 0; data[chi]; chi ++) {
// 		if (data[chi] == from && (!done || all))
// 		{
// 			occur++;
// 			if (skip == 0 || occur > skip)
// 			{
// 				data[index] = to;
// 				index += to != 0;
// 				done = true;
// 				continue;
// 			}
// 		}
// 		data[index] = data[chi];
// 		index ++;
// 	}
// 	if (index != chi) {
// 		setLength(index);
// 	}
// 	return *this;
// }
//---------------------------------------------------------------------------
text text::replace(const text &from, const text &to) const
{
	return replace_ex(from.data, to.data, true);
}
//---------------------------------------------------------------------------
text text::ireplace(const text &from, const text &to) const
{
	return replace_ex(from.data, to.data, false);
}
//---------------------------------------------------------------------------
text text::replace(const text &startTag, const text &endTag, const text &repl,
	bool replaceTags, int start)
{
	return replace_ex(startTag, endTag, repl, replaceTags, start, true);
}
//---------------------------------------------------------------------------
text text::ireplace(const text &startTag, const text &endTag, const text &repl,
	bool replaceTags, int start)
{
	return replace_ex(startTag, endTag, repl, replaceTags, start, false);
}
//---------------------------------------------------------------------------
text text::replace(const range &range, text to)
{
	return substr(0, range.start) + to + substr(range.end);
}
//---------------------------------------------------------------------------
int text::icompare(const text &str) const
{
	return wcsicmp(data, str);
}
//---------------------------------------------------------------------------
int text::compare(const text &that) const
{
	return wcscmp(data, that);
}
//---------------------------------------------------------------------------
bool text::wcCompare(const text &pattern) const
{
    return wcCompare_ex(pattern, 0, true, true, NULL);
}
//---------------------------------------------------------------------------
bool text::wciCompare(text pattern)
{
    return wcCompare_ex(pattern, 0, false, true, NULL);
}
//---------------------------------------------------------------------------
text text::uppercase() const
{
    text result = *this;
    wcsupr(result.data);
    return result;
}
//---------------------------------------------------------------------------
text text::lowercase() const
{
	text result = *this;
    wcslwr(result.data);
	return result;
}
//---------------------------------------------------------------------------
bool text::empty() const
{
	return data[0] == 0;
}
//---------------------------------------------------------------------------
void text::substr(text &substr, int start, int len) const
{
	int offset = 0;
	while(data[start + offset] && offset != len)
		offset++;
	substr.setLength(offset);
	wmemmove(substr.data, data + start, size_t(offset));
}
//---------------------------------------------------------------------------
text text::subrange(const range &range) const
{
	if(range.length() <= 0)
		return "";
// #ifdef _DEBUG
// 	assert(range.length() >= 0);
// #endif
	return substr(range.start, range.length());
}
//---------------------------------------------------------------------------
text text::substr(int start, int len) const
{
	text retv;
	if (len == -1)
        len = (int) wcslen(data) - start;
#ifdef _DEBUG
	assert(start >= 0);
	assert(len <= length() && len >= 0);
#endif
	retv.setLength(len);
    memcpy(retv.data, data + start, size_t(len) * sizeof(wchar_t));
	return retv;
}
//---------------------------------------------------------------------------
text text::subto(int start, const text &stopStr) const
{
	int end = find(stopStr, start);
	if (end < 0)
		end = length();
	return substr(start, end - start);
}
//---------------------------------------------------------------------------
text text::subfind(const text &startStr, const text &endStr, int start, int end) const
{
	text retV;
	if(start < length())
		substr_ex(retV, startStr, endStr, start, end, true);
	return retV;
}
//---------------------------------------------------------------------------
text text::isubstr(text startStr, text endStr, int start, int end) const
{
	text retV;
	substr_ex(retV, startStr.data, endStr.data, start, end, false);
	return retV;
}
//---------------------------------------------------------------------------
int text::read(int start, const wchar_t *stopChars) const
{
	while (data[start] && !wcschr(stopChars, data[start]))
		start++;
	return start;
}
//---------------------------------------------------------------------------
text text::read(text startStr, const wchar_t *stopChars, bool includeTag) const
{
	text retVal;
	int start = find(startStr);
	if (start == -1)
		return "";
	if (includeTag)
		retVal = startStr;
	start += startStr.length();
	int index = start;
	while (data[index] && !wcschr(stopChars, data[index]))
		index++;
	retVal += substr(start, index - start);
	return retVal;
}
//---------------------------------------------------------------------------
int text::rread(int start, const wchar_t *stopChars) const
{
	while (start >= 0 && !wcschr(stopChars, data[start]))
		start--;
	return start;
}
//---------------------------------------------------------------------------
text text::read(int start, const wchar_t *stopChars, int *offset) const
{
	text retv;
	read_ex(retv, start, stopChars);
	if(offset)
		*offset = start;
	return retv;
}
//---------------------------------------------------------------------------
text text::rread(int start, const wchar_t *stopChars, int *offset)
{
	text retv;
	rread_ex(retv, start, stopChars);
	if(offset)
		*offset = start;
	return retv;
}
//---------------------------------------------------------------------------
int text::pass(int start, const wchar_t *stopChars) const
{
	while (data[start] && wcschr(stopChars, data[start]))
		start++;
	return start;
}
//---------------------------------------------------------------------------
int text::rpass(int start, const wchar_t *stopChars)
{
	while (data[start] && wcschr(stopChars, data[start]))
		start--;
	return start;
}
//---------------------------------------------------------------------------
text text::left(int count) const
{
	text retv;
	retv.setLength(count);
	memcpy(retv, data, count * sizeof(wchar_t));
	return retv;
}
//---------------------------------------------------------------------------
text text::right(int count) const
{
	int len = length();
	if (count >= len)
		return data;
	return data + len - count;
}
//---------------------------------------------------------------------------
bool text::startsWith(const text &str, bool matchCase) const
{
	text leftStr = left(str.length());
	if (matchCase)
		return leftStr.compare(str) == 0;
	return leftStr.icompare(str) == 0;
}
//---------------------------------------------------------------------------
bool text::endsWith(const text &str, bool matchCase) const
{
	text rightStr = right(str.length());
	if (matchCase)
		return rightStr.compare(str) == 0;
	return rightStr.icompare(str) == 0;
}
//---------------------------------------------------------------------------
bool text::leftIs(text str, bool matchCase)
{
	return startsWith(str, matchCase);
}
//---------------------------------------------------------------------------
bool text::rightIs(text str, bool matchCase)
{
	return endsWith(str, matchCase);
}
//---------------------------------------------------------------------------
float text::floatValue() const
{
	return (float) doubleValue();
}
//---------------------------------------------------------------------------
double text::doubleValue() const
{
	return wcstod(data, NULL);
}
//---------------------------------------------------------------------------
int text::find(const text &substr, int start) const
{
	return find_ex(substr.data, start, true);
}
//---------------------------------------------------------------------------
int text::ifind(const text &substr, int start)
{
	return find_ex(substr.data, start, false);
}
//---------------------------------------------------------------------------
range text::wcFind(text pattern, int start)
{
	int len;
	int pos = wcFind_ex(pattern, start, true, &len);
	return range(pos, pos + len);
}
//---------------------------------------------------------------------------
range text::wciFind(text pattern, int start)
{
	int len;
	int pos = wcFind_ex(pattern, start, false, &len);
	return range(pos, pos + len);
}
//---------------------------------------------------------------------------
int text::rfind(text str, int rOff) const
{
	return rfind_ex(str.data, rOff, true);
}
//---------------------------------------------------------------------------
int text::irfind(text str, int rOff) const
{
	return rfind_ex(str.data, rOff, false);
}
//---------------------------------------------------------------------------
int text::findByIndex(text str, int index)
{
	int pos = 0;
	do
	{
		pos = find(str, pos);
		if (pos == -1)
			return -1;
		pos++;
		index--;
	}
	while (index >= 0);
	return pos - 1;
}
//---------------------------------------------------------------------------
bool text::contains(const text &substr, bool matchCase) const
{
	return find_ex(substr.data, 0, matchCase) != -1;
}
//---------------------------------------------------------------------------
bool text::contains(const array &substrs, bool matchCase) const
{
	array::it it = substrs.getIterator();
	bool retv = false;
	while(!retv && it.notAtEnd())
	{
		retv |= contains(it.next(), matchCase);
	}
	return retv;
}
//---------------------------------------------------------------------------
bool text::include(text chars)
{
	for (int i = 0; i < chars.length(); i++)
	{
		if (wcschr(data, chars.data[i]))
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
int text::intValue(int base) const
{
	return (int)wcstoll(data, NULL, base);
}
//---------------------------------------------------------------------------
int64_t text::int64Value(int base) const
{
	return wcstoll(data, NULL, base);
}
//---------------------------------------------------------------------------
#ifdef __APPLE__
wchar_t *wcstok_save;
#endif

wchar_t *text::firstToken(const wchar_t *delimiters) const // thread unsafe
{
#ifdef _Windows
	return wcstok(data, delimiters);
#elif __APPLE__
	return wcstok(data, delimiters, &wcstok_save);
#endif
}
//---------------------------------------------------------------------------
wchar_t *text::nextToken(const wchar_t *delimiters) const // thread unsafe
{
#ifdef _Windows
	return wcstok(nullptr, delimiters);
#elif __APPLE__
	return wcstok(nullptr, delimiters, &wcstok_save);
#endif
}
//---------------------------------------------------------------------------
wchar_t *text::firstToken(const wchar_t *delimiters, wchar_t **save) const // thread safe
{
#ifdef _Windows
	if (!save)
		return nullptr;
	wchar_t *token = data + wcsspn(data, delimiters);
	if (!*token) {
		*save = nullptr;
		return nullptr;
	}
	wchar_t *end = token + wcscspn(token, delimiters);
	if (*end) {
		*end = 0;
		*save = end + 1;
	}
	else
		*save = nullptr;
	return token;
#elif __APPLE__
	return wcstok(nullptr, delimiters, save);
#endif
}
//---------------------------------------------------------------------------
wchar_t *text::nextToken(const wchar_t *delimiters, wchar_t **save) const // thread safe
{
#ifdef _Windows
	if (!save || !*save)
		return nullptr;
	wchar_t *token = *save + wcsspn(*save, delimiters);
	if (!*token) {
		*save = nullptr;
		return nullptr;
	}
	wchar_t *end = token + wcscspn(token, delimiters);
	if (*end) {
		*end = 0;
		*save = end + 1;
	}
	else
		*save = nullptr;
	return token;
#elif __APPLE__
	return wcstok(nullptr, delimiters, save);
#endif
}
//---------------------------------------------------------------------------
data_t text::t_str() const
{
	data_t retV;
	int len = length();
	retV.setLength(len);
	for (int ci = 0; ci < len; ci++)
	{
		retV[ci] = (char)data[ci];
	}
	retV[len] = 0;
	return retV;
}
//---------------------------------------------------------------------------
data_t text::c_str() const
{
	return t_str();
}
//---------------------------------------------------------------------------
text text::trim() const
{
	int left = 0;
	int len = length();
	if (!len)
		return "";
	int right = len - 1;
	while (left < len && wcschr(L" \t\r\n", data[left]))
		left++;
	while (right > left && wcschr(L" \t\r\n", data[right]))
		right--;
	return substr(left, right - left + 1);
}
//---------------------------------------------------------------------------
text text::reverse()
{
	text temp;
	int len = wcslen(data);
	temp.resize(len);
	for(int index=0; index<len; index++)
	{
		temp.data[index] = data[len - index - 1];
	}
	return temp;
}
//---------------------------------------------------------------------------
text text::quoted(char quote) const
{
	return text(quote) + *this + text(quote);
}
//---------------------------------------------------------------------------
text text::unQuoted(wchar_t quote) const
{
	if (data[0] == quote && lastChar() == quote)
		return substr(1, length() - 2);
	return *this;
}
//---------------------------------------------------------------------------
bool text::isAnsiString() const
{
	for (int i = 0; data[i]; i++)
	{
		if(data[i] > 0xFF)
			return false;
	}
	return true;
}

bool text::hasAnsiChar() const
{
	for (int i = 0; data[i]; i++)
	{
		if(data[i] <= 0xFF && data[i] != 32)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
//int text::scan(text charSet, int start)
//{
//	wchar_t *ptr = wcspbrk(data + start, charSet);
//	if(!ptr)
//		return -1;
//	start = ptr - data;
//	pass(start, charSet);
//	return start;
//}
//---------------------------------------------------------------------------
text text::wcSubstr(text pattern, int start)
{
	return wcSubstr_ex(pattern.data, start, true);
}
//---------------------------------------------------------------------------
text text::wciSubstr(text pattern, int start)
{
	return wcSubstr_ex(pattern.data, start, false);
}
//---------------------------------------------------------------------------
text text::wcReplace(text pattern, text repl)
{
	return wcReplace_ex(pattern, repl, true, false);
}
//---------------------------------------------------------------------------
text text::wciReplace(text pattern, text repl)
{
	return wcReplace_ex(pattern, repl, false, false);
}
//---------------------------------------------------------------------------
text text::toRot13(bool numbers) const
{
	text alpha1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text alpha2 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";;
	if(numbers)
	{
		alpha1 += "12345678";
		alpha2 += "56781234";
	}
	text newStr;
	wchar_t curLet;
	int curLetLoc;

	for (int i = 0; data[i]; i++)
	{
		curLet    = data[i];
		curLetLoc = alpha1.find(curLet);
		newStr += (curLetLoc < 0) ? curLet : alpha2[curLetLoc];
	 }

	return newStr;
}
//---------------------------------------------------------------------------
text text::toBase64() const
{
	static text base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	text ret;
	int i = 0;
	int j;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	int in_len = length();
	wchar_t *bytes_to_encode = data;

	while (in_len--) {
		char_array_3[i++] = (unsigned char)*(bytes_to_encode++);
		if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for(j = i; j < 3; j++)
		char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';
	}

	return ret;
}
//---------------------------------------------------------------------------
text text::fromBase64()
{
	static text base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	wchar_t *encoded_string = data;
	int in_len = length();
	int i = 0;
	int j;
	int in_ = 0;
	wchar_t char_array_4[4], char_array_3[3];
	text ret;

	while (in_len-- && ( (char)encoded_string[in_] != '=') && isBase64((char)encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
			char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
        for (j = i; j <4; j++)
        char_array_4[j] = 0;

        for (j = 0; j <4; j++)
        char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}
//---------------------------------------------------------------------------
data_t getAnsiString(const wchar_t* wstr)
{
	int len = wcslen(wstr);
	data_t retv(len);
	for(int i = 0; i <= len; i++)
		retv[i] = wstr[i];
	return retv;
}

#if defined(_Windows)
int text::vasprintf(char **retv, const char *format, va_list args)
{
	int len = vsnprintf(0, 0, format, args);
	if (len == -1)
		return -1;
	char *str = (char*) malloc((size_t) len + 1);
	if (!str)
		return -1;
	len = vsnprintf(str, len + 1, format, args); /* "secure" version of vsprintf */
	if (len == -1)
	{
		::free(str);
		return -1;
	}
	*retv = str;
	return len;
}
//---------------------------------------------------------------------------
text &text::print(const wchar_t *format, ...)
{
	va_list args;
	va_start(args, format);
#ifdef _Windows
	int size = vsnwprintf(nullptr, 0, format, args) + 1;
	setLength(size);
	vsnwprintf(data, size, format, args);
	va_end(args);
	return *this;
//#elif __APPLE__
//	int size = 1000;
//	do {
//		setLength(size);
//		int len = vsnwprintf(data, size, format, args);
//		if(len != -1)
//		{
//			va_end(args);
//			setLength(len);
//			return *this;
//		}
//		size += 100;
//	} while(true);
#endif
}
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
text& text::print(const char* format, ...)
{
	char *buffer;
	va_list args;
	va_start(args, format);
	int len = vasprintf(&buffer, format, args);
	if(len != -1)
	{
		assign(buffer);
		::free(buffer);
	}
	va_end(args);
	return *this;
}
//---------------------------------------------------------------------------
text &text::write(const char *format, ...)
{
	char *buffer;
	va_list args;
	va_start(args, format);
	int len = vasprintf(&buffer, format, args);
	if(len != -1)
	{
		append(buffer);
		::free(buffer);
	}
	va_end(args);
	return *this;
}
//---------------------------------------------------------------------------
//wchar_t* text::wcstok(wchar_t *s1, const wchar_t *s2, wchar_t **ps, wchar_t *delim)
//{
//	wchar_t *sbegin, *send;
//	static const wchar_t nullstr[1] = {L'\0'};

//	sbegin = s1 ? s1 : *ps;
//	sbegin += wcsspn(sbegin, s2);
//	if (*sbegin == L'\0')
//	{	/* end of scan */
//        *ps = (wchar_t *) nullstr;	/* for safety */
//		return (0);
//	}
//	uint32_t delimPos = wcscspn(sbegin, s2);
//	if(delim)
//		*delim = sbegin[delimPos];
//	send = sbegin + delimPos;
//	if (*send != L'\0')
//		*send++ = L'\0';
//	*ps = send;
//	return (sbegin);
//}
//---------------------------------------------------------------------------
text text::exchangeBy(const text &delim)
{
	text retv;
	array parts = split(delim);
	array::it it = parts.getIteratorReverse();
	while (it.notAtEnd())
	{
		text part = it.next();
		retv += part;
		if(it.notAtEnd())
			retv += delim;
	}
	return retv;
}

bool text::in(const text &container, bool matchCase) const
{
	return container.contains(*this, matchCase);
}

bool text::scan(const char *fmt, ...)
{
	bool retv = false;
	va_list args;
	va_start(args, fmt);

	class im //internal methods
	{
	public:
		static int search(wchar_t *data, int data_index, const char *fmt, int fmt_index, int fmt_slice_len)
		{
			bool search_result = false;
			int data_i;
			if(fmt_slice_len == 0)
			{
				data_i = data_index;
				while(data[data_i])
					data_i++;
				return data_i;
			}
			for(data_i = data_index; data[data_i]; data_i++)
			{
				search_result = true;
				for(int fmt_i = 0; search_result && fmt_i < fmt_slice_len; fmt_i ++)
				{
					char fmt_ch = fmt[fmt_index + fmt_i];
					wchar_t data_ch = data[data_i + fmt_i];
					if(fmt_ch == '%')
						fmt_ch = fmt[fmt_index + ++fmt_i];
					search_result &= data_ch == fmt_ch;
				}
				if(search_result)
					return data_i;
			}
			return -1;
		}
		static bool isCtrl(const char *fmt, int index, bool &step)
		{
			char ch = fmt[index];
			step = false;
			if(ch == 0)
				return true;
			if(ch == '%')
			{
				char ch_next = fmt[index + 1];
				if(ch_next == '%' || ch_next == '*')
				{
					step = true;
					return false;
				}

				return true;
			}
			if(ch == '*' && index > 0 && fmt[index - 1] != '%')
				return true;
			return false;
		}
		static int findFirstCtrl(const char *fmt, int index, int &duals)
		{
			int retv = 0;
			bool step;
			duals = 0;
			while(!im::isCtrl(fmt, index + retv + 1, step))
			{
				retv = retv + 1 + step;
				duals += step;
			}
			return retv;
		}
	};

	int fmt_index = 0, data_index = 0, fmt_slice_len;

	while(fmt[fmt_index])
	{
		wchar_t ch = fmt[fmt_index], type, sub_type = 0, sub_type2 = 0;
		switch (ch) {
		case '*':
		{
			int duals;
			fmt_slice_len = im::findFirstCtrl(fmt, fmt_index, duals);
			int data_i = im::search(data, data_index, fmt, fmt_index + 1 /* bypass'*' */, fmt_slice_len);
			if(data_i == -1)
				goto end;
			data_index = data_i + fmt_slice_len - duals;
			fmt_index += fmt_slice_len + 1;
			break;
		}
		case '%':
		{
			type = fmt[++fmt_index];
			if(type == '%' || type == '*')
			{
				if(type != data[data_index])
					goto end;
				fmt_index++;
				data_index++;
				continue;
			}
			if(type == 'l')
			{
				sub_type = type;
				type = fmt[++fmt_index];
				if(type == 'l')
				{
					sub_type2 = type;
					type = fmt[++fmt_index];
				}
			}
			int duals;
			fmt_slice_len = im::findFirstCtrl(fmt, fmt_index, duals);
			fmt_index++;
			int data_i = im::search(data, data_index, fmt, fmt_index, fmt_slice_len);
			if(data_i == -1)
				goto end;
			int data_slice_len = data_i - data_index;
			fmt_index += fmt_slice_len;
			if(type == 's' || type == 't')
			{
				if(sub_type == 'l')
				{
					wchar_t *arg = va_arg(args, wchar_t*);
					memcpy(arg, data + data_index, data_slice_len * sizeof(wchar_t));
					arg[data_slice_len] = 0;
				}
				else if(type == 't')
				{
					text *arg = va_arg(args, text*);
					arg->setLength(data_slice_len);
					arg->copy(data + data_index, data_slice_len);
				}
				else
				{
					char *arg = va_arg(args, char*);
					for (int i = 0; i < data_slice_len; i++)
						arg[i] = data[data_index + i];
					arg[data_slice_len] = 0;
				}
			}
			else if(type == 'i' || type == 'u')
			{
				wchar_t *endPtr;
				if(sub_type == 'l')
				{
					if(sub_type2 == 'l')
					{
						int64_t &arg = *va_arg(args, int64_t*);
						arg = wcstoll(data + data_index, &endPtr, 10);
					}
					else
					{
						long &arg = *va_arg(args, long*);
						arg = wcstol(data + data_index, &endPtr, 10);
					}
				}
				else
				{
					int &arg = *va_arg(args, int*);
					arg = wcstol(data + data_index, &endPtr, 10);
				}
			}
			else if(type == 'f')
			{
				wchar_t *endPtr;
				if(sub_type == 'l')
				{
					double &arg = *va_arg(args, double*);
					arg = wcstod(data + data_index, &endPtr);
				}
				else
				{
					float &arg = *va_arg(args, float*);
					arg = wcstod(data + data_index, &endPtr);
				}
			}
			else if(type == 'c')
			{
				if(sub_type == 'l')
				{
					wchar_t *arg = va_arg(args, wchar_t*);
					arg[0] = data[data_index];
				}
				else
				{
					char *arg = va_arg(args, char*);
					arg[0] = data[data_index];
				}
			}
			else if(type == 'x')
			{
				wchar_t *endPtr;
				if(data[data_index] == '0')
				{
					data_index++;
					if(data[data_index] == 'x')
						data_index++;
				}
				else if(data[data_index] == '#')
					data_index++;
				if(sub_type == 'l')
				{
					long &arg = *va_arg(args, long*);
					arg = wcstol(data + data_index, &endPtr, 16);
				}
				else if(sub_type2 == 'l')
				{
					int64_t &arg = *va_arg(args, int64_t*);
					arg = wcstoll(data + data_index, &endPtr, 16);
				}
				else
				{
					int &arg = *va_arg(args, int*);
					arg = wcstol(data + data_index, &endPtr, 16);
				}
				if(endPtr == data + data_index)
					goto end;
			}
			data_index = data_i + fmt_slice_len;
			break;
		}
		default:
			//fmt_index += ch == data[data_index++];
			if(ch != data[data_index])
				goto end;
			fmt_index ++;
			data_index++;
			break;
		}
	}
	retv = true;
	end:
	va_end(args);
	return retv;
}
//---------------------------------------------------------------------------
#if defined(__BORLANDC__)
text __fastcall operator << (char *left, const text& right)
{
	return text(left).operator << (right);
}
//---------------------------------------------------------------------------
text __fastcall operator << (wchar_t *left, const text& right)
{
	return text(left).operator << (right);
}
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
dictionary_t::dictionary_t() : mCompareProc(NULL)
{
}
//---------------------------------------------------------------------------
void dictionary_t::loadFromFile(const text &fileName)
{
	array file;
	clear();
	file.load(fileName);
	for (int i = 0; i < file.count(); i++) {
		key_value_t<text, text> &item = add();
		item.key = file[i].subto(0, L"=");
		item.value = file[i].subfind("=");
	}
}
//---------------------------------------------------------------------------
void dictionary_t::saveToFile(const text &fileName)
{
	array file;
	for (int i = 0; i < count(); i++) {
		text key = item(i).key;
		if(!key.empty())
			file << key + "=" + item(i).value;
	}
	file.save(fileName);
}
//---------------------------------------------------------------------------
void dictionary_t::fromString(const text &rawData, const wchar_t glue)
{
	int offset = 0, start;
	clear();
	wchar_t glue_str[] = {glue, 0};
	while(rawData(offset))
	{
		offset = rawData.pass(offset, glue_str);
		start = offset;
		offset = rawData.read(offset, L"=");
		if(offset >= start && rawData(offset))
		{
			key_value_t<text, text> &item = add();
			item.key = rawData.substr(start, offset - start);
			#ifdef _DEBUG
			assert(!wcschr(item.key, '&'));
			#endif
			offset ++;
			int buf_size = 100;
			text buf;
			buf.setLength(buf_size);
			int index = 0;
			while(rawData(offset))
			{
				buf[index ++] = rawData(offset);
				if(index == buf_size)
				{
					buf_size += 100;
					buf.setLength(buf_size);
				}
				if(rawData(offset) == glue)
				{
					if(rawData(offset + 1) == glue)
						offset ++;
					else
					{
						index --;
						break;
					}
				}
				offset ++;
			}
			buf[index] = 0;
			item.value = buf;
			if(rawData(offset) == glue)
				offset++;
		}
	}
}
//---------------------------------------------------------------------------
text dictionary_t::toString(const wchar_t glue) const
{
	text retv;
	int size = 0, count = this->count(), i;
	if(count == 0)
		return "";
	for (i = 0; i < count; i++) {
		key_value_t<text, text> &item = this->item(i);
		size += item.value.countOf(glue);
		size += item.key.length() + item.value.length() + 2;
	}
	retv.setLength(size);
	retv[0] = 0;
	int pos;
	wchar_t glue_str[] = {glue, 0};
	for (i=0; i<count; i++) {
		key_value_t<text, text> &item = this->item(i);
		wcscat(retv.data, item.key.data);
		wcscat(retv.data, L"=");
		int index = 0;
		pos = retv.length();
		while(item.value[index])
		{
			if(item.value[index] == glue)
				retv.data[pos ++] = glue;
			retv.data[pos ++] = item.value[index ++];
		}
		retv.data[pos] = 0;
		wcscat(retv.data, glue_str);
	}
	retv[size - 1] = 0;
	return retv;
}
//---------------------------------------------------------------------------
int dictionary_t::findKey(const text &key, bool matchCase) const
{
	int count = this->count();
	for (int i=0; i<count; i++) {
		key_value_t<text, text> &item = this->item(i);
		if(matchCase)
		{
			if(item.key == key)
				return i;
		}
		else
		{
			if(item.key / key)
				return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
bool dictionary_t::hasKey(const text &key, bool matchCase) const
{
	return findKey(key, matchCase) != -1;
}
//---------------------------------------------------------------------------
key_value_t<text, text>& dictionary_t::operator[] (text key)
{
	int index = findKey(key);
	if(index >= 0)
		return item(index);
	add().key = key;
	return lastItem();
}

//---------------------------------------------------------------------------
//key_value_t<text, text>& dictionary_t::operator() (text key) const
//{
//	int index = findKey(key);
//    assert(index != -1);
//	if(index >= 0)
//		return item(index);
//}
//---------------------------------------------------------------------------
text dictionary_t::keyValue(int index)
{
	key_value_t<text, text> &keyValueItem = item(index);
	return keyValueItem.key + "=" + keyValueItem.value;
}
//---------------------------------------------------------------------------
void dictionary_t::addKeyValue(text keyValue)
{
	int equal_pos = keyValue.find("=");
	if(equal_pos != -1)
	{
		key_value_t<text, text> &newItem = add();
		newItem.key = keyValue.substr(0, equal_pos);
		newItem.value = keyValue.substr(equal_pos + 1);
	}
}
//---------------------------------------------------------------------------
int array::compareProc(text &item1, text &item2)
{
	return item1.compare(item2);
}
//---------------------------------------------------------------------------
int array::sortAndRemoveDuplicates()
{
	sort();
	int remove_count = 0;
	for (int i = 0; i < count() - 1; i++) {
		if(item(i) == item(i + 1))
		{
			remove(i + 1);
			i --;
			remove_count ++;
		}
	}
	return remove_count;
}
//---------------------------------------------------------------------------
bool array::left_cmp(const wchar_t *str1, const wchar_t *str2)
{
	int pos = 0;
	while(str1[pos] && str2[pos] && str1[pos] == str2[pos]) pos++;
	return str2[pos] == 0;
}
//---------------------------------------------------------------------------
int array::find_ex(const text &text, bool matchCase) const
{
	int count = this->count();
	for(int index=0; index<count; index++)
	{
		if(matchCase)
		{
			if(item(index) == text)
				return index;
		}
		else
		{
			if(item(index) / text)
				return index;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
int array::include(const text &str)
{
	for (int i = 0; i < count(); i++) {
		if (str.contains(item(i))) {
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
//void array::tokenize(const wchar_t *delimiters, wchar_t *input,
//	void(*callback)(array &self, wchar_t*, wchar_t))
//{
//	wchar_t *save = NULL;
//	wchar_t delim;
//	assert(input);
//	wchar_t *item = wcstok(input, delimiters, &save, &delim);
//	while(item)
//	{
//		add() = (const wchar_t*)item;
//		if(callback)
//			callback(*this, item, delim);
//		item = wcstok(NULL, delimiters, &save, &delim);
//	}
//}
//---------------------------------------------------------------------------
array& array::load(text fileName)
{
	return loadFromFile(fileName);
}
//---------------------------------------------------------------------------
bool array::save(text fileName)
{
	return saveToFile(fileName);
}

array &array::loadFromFile(const text &fileName)
{
	clear();
	#if defined(__APPLE__) || defined(__ANDROID__)
	FILE *file = fopen((char*)fileName.toUtf8(), "rb");
	#else
	FILE *file = _wfopen(fileName, L"rb");
	#endif
	if(!file) return *this;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	unsigned char *buffer = new unsigned char[size + 2];
	fseek(file, 0, SEEK_SET);
	int readCount = fread(buffer, 1, size, file);
	fclose(file);
	if(readCount != size || size == 0)
	{
		delete [] buffer;
		return *this;
	}
	buffer[size] = 0;
	buffer[size + 1] = 0;
	bool isUnicode = (buffer[0] == 0xff) && (buffer[1] == 0xfe);
	bool isUTF8 = (buffer[0] == 0xef) && (buffer[1] == 0xbb) && (buffer[2] == 0xbf);
	text data;
	if(isUnicode)
		data = (const char16_t*)(buffer + 2);
	else if(isUTF8)
	{
		data = (const char*)(buffer + 3);
		#ifndef __APPLE__
		data = data.toUnicode();
		#endif
	}
	else
		data = (const char*)buffer;
	text glue;
	if(data.contains("\r\n"))
		glue = "\r\n";
	else
		glue = "\n";
	explode(glue, data);
	delete [] buffer;
	return *this;
}

bool array::saveToFile(const text &fileName)
{
	int len;
	char unicode[] = {(char)0xff, (char)0xfe};
	#if defined(__APPLE__) || defined(__ANDROID__)
	FILE *file = fopen((char*)fileName.toUtf8(), "wb");
	#elif defined(_Windows) || defined(__MINGW64__) || defined(__MINGW32__)
	FILE *file = _wfopen(fileName, L"wb");
	#endif

	if(file == NULL)
		return false;

	text data = implode(L"\r\n");
	len = data.length();
	char16_t *pData = new char16_t[len];
	for (int i=0; i<len; i++) {
		pData[i] = (char16_t)data.data[i];
	}

	fwrite(unicode, 1, 2, file);
	fwrite(pData, sizeof(char16_t), len, file);
	delete [] pData;
	fclose(file);

	return true;
}
//---------------------------------------------------------------------------
void array::addArray(array anArr)
{
	arrayof <text>::add(anArr);
}
//---------------------------------------------------------------------------
text array::toString(const wchar_t glue, bool ignore_empty_items) const
{
	text retv;
	int size = 0, count = this->count(), i;
	if(count == 0)
		return "";
	for (i = 0; i < count; i++) {
		text &item = this->item(i);
		if(ignore_empty_items && item.empty())
			continue;
		size += item.countOf(glue);
		size += item.length();
	}
	if(glue)
		size += count * (glue != 0) - 1;
	retv.setLength(size);
	retv[0] = 0;
	int pos = 0;
	for (i=0; i<count; i++) {
		text &item = this->item(i);
		if(ignore_empty_items && item.empty())
			continue;
		int index = 0;
		while(item.data[index])
		{
			retv.data[pos++] = item.data[index];
			index ++;
		}
		retv.data[pos] = glue;
		pos += glue != 0;
		if(pos < size)
			retv.data[pos] = 0;
	}
	if(size > 0)
		retv[size] = 0;
	return retv;
}
//---------------------------------------------------------------------------
text array::getDelimitedText(wchar_t delimiter)
{
	text retv;
	int size = 0, count = this->count(), i;
	if(count == 0)
		return "";
	for (i = 0; i < count; i++) {
		text &item = this->item(i);
		size += item.length();
		size += wcschr(item.data, delimiter) == NULL ? 0 : 2;
		size += wcschr(item.data, '"') == NULL ? 0 : 2;
	}
	retv.setLength(size);
	retv[0] = 0;
	int pos = 0;
	//wchar_t delim_str[] = {delimiter, 0};
	//wchar_t quote_str[] = {'"', 0};

	for (i = 0; i < count; i++) {
		text &item = this->item(i);
		bool contains_quote = wcschr(item.data, '"');
		bool contains_delim = wcschr(item.data, delimiter);
		if(contains_quote || contains_delim)
		{
			retv[pos ++] = '"';
			retv[pos] = 0;
			item = item.replace("\"", "\"\"");
		}
		wcscat(retv, item);
		pos += wcslen(item);
		if(contains_quote || contains_delim)
		{
			retv[pos ++] = '"';
			retv[pos] = 0;
		}
		if(i < count - 1)
		{
			retv[pos ++] = delimiter;
		}
	}
	retv[pos ++] = 0;
	return retv;
}

text array::briefStr()
{
	if(count() <= 3)
		return toString();
	return item(0) + ", " + item(1) + ", " + item(2) + ", ...";
}

array &array::operator +=(const array &arr)
{
    for(int i = 0; i < arr.count(); i++)
        add(arr.item(i));
    return *this;
}
//---------------------------------------------------------------------------
text array::toString(const wchar_t *glue) const
{
	return implode(glue);
}
//---------------------------------------------------------------------------
text array::implode(const wchar_t *glue) const
{
	text text;
	int icount = count();
	int glen = wcslen(glue);
	int size = 0;
	if (!icount)
		return "";
	int i;
	for (i = 0; i < icount; i++)
		size += item(i).length() + glen;
	text.resize(size);
	int pos = 0;
	for (i = 0; i < icount; i++) {
		wcscpy(text.data + pos, item(i).data);
		pos += wcslen(item(i).data);
		if (i < icount - 1) {
			wcscpy(text.data + pos, glue);
			pos += glen;
		}
	}
	text[size] = 0;
	return text;
}
//---------------------------------------------------------------------------
void array::fromString(const text &rawData, const wchar_t glue)
{
	int offset = 0;
	clear();
	text substr;
	int len = 0, len_max = 0;
	wchar_t chr;
	while(true)
	{
		if(len >= len_max)
		{
			len_max += 100;
			substr.setLength(len_max);
		}
		chr = rawData(offset);
		if(chr == '\\')
		{
			if(rawData(offset + 1) == '\\')
				chr = '\\';
            else if(rawData(offset + 1) == glue)
                chr = glue;
			offset ++;
			substr[len ++] = chr;
		}
        else if(chr == glue || chr == '\0')
		{
			substr[len] = 0;
			add() = substr;
			len = 0;
			if(!chr)
				break;
		}
		else
			substr[len ++] = chr;
		offset ++;
	}
}
//---------------------------------------------------------------------------
text& array::addBuffer(wchar_t *buffer, int offset, int len)
{
	text &item = add();
	item.setLength(len);
	wmemmove(item.data, buffer + offset, len);
	return item;
}
//---------------------------------------------------------------------------
void array::explode(const wchar_t *delimiter, const text &input)
{
	if (input.empty()) {
		return;
	}
	wchar_t *data = input;
	text ret;
	int index = 0, offset;
	int delim_len = wcslen(delimiter);
	start:
	offset = index;
	while (data[index] && !left_cmp(data + index, delimiter))
		index ++;
	//add() = (const wchar_t*)input.substr(offset, index - offset).data;
	addBuffer(input.data, offset, index - offset);

	if (data[index])
	{
		index += delim_len;
		goto start;
	}
}
//---------------------------------------------------------------------------
int array::find(const wchar_t *text) const
{
	return find_ex(text, true);
}
//---------------------------------------------------------------------------
int array::ifind(const wchar_t *text)
{
	return find_ex(text, false);
}
//---------------------------------------------------------------------------
bool array::contains(const wchar_t *text, bool matchCase)
{
	return find_ex(text, matchCase) != -1;
}
//---------------------------------------------------------------------------
int array::search(const text &substr, bool matchCase)
{
	int count = this->count();
	for(int index = 0; index < count; index ++)
	{
		if(matchCase)
		{
			if(item(index).contains(substr))
				return index;
		}
		else
		{
			if(item(index).ifind(substr) != -1)
				return index;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
array& array::operator << (text inst)
{
	add() = inst;
	return *this;
}
//---------------------------------------------------------------------------
array& array::operator << (array arr)
{
	add(arr);
	return *this;
}
//---------------------------------------------------------------------------
memory_stream_t::memory_stream_t(int size) : stream_t()
{
	m_position = 0;
	if(size)
		setLength(size);
}
//---------------------------------------------------------------------------
void memory_stream_t::write(void *data, int dataSize)
{
	m_position += dataSize;
	if(m_position > length())
		setLength(m_position);
	memcpy(data_t::data() + m_position - dataSize, data, dataSize);
}
//---------------------------------------------------------------------------
void memory_stream_t::write(int value)
{
	write(&value, sizeof(int));
}
//---------------------------------------------------------------------------
void memory_stream_t::write(short value)
{
	write(&value, sizeof(short));
}
//---------------------------------------------------------------------------
void memory_stream_t::write(char value)
{
	write(&value, sizeof(char));
}
//---------------------------------------------------------------------------
void memory_stream_t::write(const data_t &data)
{
	write(data.dataPtr(), data.length());
}
//---------------------------------------------------------------------------
void memory_stream_t::setPosition(int position)
{
	m_position = position;
}
//---------------------------------------------------------------------------
int memory_stream_t::position()
{
	return m_position;
}
//---------------------------------------------------------------------------
int memory_stream_t::read(void *data, int dataSize)
{
	m_position += dataSize;
	if(m_position > length())
	{
		m_position -= dataSize;
		return 0;
	}

	memcpy(data, data_t::data() + m_position - dataSize, dataSize);
	return dataSize;
}
//---------------------------------------------------------------------------
int memory_stream_t::readInt()
{
	int retv = 0;
	read(&retv, sizeof(int));
	return retv;
}

uint16_t memory_stream_t::readUInt16()
{
	uint16_t retv = 0;
	read(&retv, sizeof(uint16_t));
	return retv;
}

uint32_t memory_stream_t::readUInt32()
{
	uint32_t retv = 0;
	read(&retv, sizeof(uint32_t));
	return retv;
}
//---------------------------------------------------------------------------
unsigned char memory_stream_t::readByte()
{
	unsigned char retv;
	if(read(&retv, sizeof(unsigned char)))
		return retv;
	return 0;
}
//---------------------------------------------------------------------------
void memory_stream_t::clear()
{
	stream_t::clear();
	setLength(0);
}
//---------------------------------------------------------------------------
void data_t::invertBytes()
{
	unsigned char *pData = (unsigned char*) data();
	int count = length();
	for (int i = 0; i < count; i++) {
		pData[i] = ~pData[i] & 0xFF;
	}
}
//---------------------------------------------------------------------------
void data_t::reverseBytes()
{
	unsigned char *pData = (unsigned char*) data(), temp;
	int count = length();
	for (int i = 0; i < count / 2; i++) {
		temp = pData[i];
		pData[i] = pData[count - i - 1] & 0xFF;
		pData[count - i - 1] = temp & 0xFF;
	}
}
//---------------------------------------------------------------------------
//#ifdef _DEBUG
text text::getDebugString()
{
	//return text("length=[]\r\n[]") << length() << data;
	return data;
}
//---------------------------------------------------------------------------
text array::getDebugString()
{
	text retv;
	if(count())
	{
		for (int i = 0; i < count() && i <= 10; i++) {
			retv += item(i);
			if(i < count() - 1)
				retv += " , ";
		}
		if(count() > 10)
			retv += "...";
		return retv;
	}
	else
	{
		return "Empty";
	}
}
//---------------------------------------------------------------------------
text data_t::getDebugString()
{
	text retv;
	if(length())
	{
		int max = 10;
		for (int i = 0; i < length() && i < max; i++) {
			retv += text(operator [](i) & 255).toHex(2);
			if(i < length() - 1)
				retv += " , ";
		}
		if(length() > max)
			retv += "...";
		retv = retv + ((text) " (length=[])" << length());
		return retv;
	}
	else
	{
		return "Empty";
	}
}

void data_t::setData(const data_t &data)
{
	assign(data);
}

void data_t::write(const data_t &data)
{
	buffer_t<char>::write(data.dataPtr(), data.length());
}

void data_t::write(const void *pData, uint32_t size)
{
	buffer_t<char>::write(pData, size);
}

void data_t::write(uint32_t value)
{
	buffer_t<char>::write(&value, sizeof(int));
}

bool data_t::contains(const char *subStr, bool matchCase, bool unicode)
{
    return find(subStr, 0, matchCase, unicode) != -1;
}

//---------------------------------------------------------------------------
int dictionary_t::getInt(const text &key, int defVal)
{
	int index = findKey(key);
	if (index != -1) {
		return item(index).value.intValue();
	}
	return defVal;
}
//---------------------------------------------------------------------------
text dictionary_t::getDebugString()
{
	text retv;
	if(count())
	{
		for (int i = 0; i < count() && i <= 10; i++) {
			retv += item(i).key + "=" + item(i).value;
			if(i < count() - 1)
				retv += " , ";
		}
		if(count() > 10)
			retv += "...";
		return retv;
	}
	else
	{
		return "Empty";
	}
}

int dictionary_t::compareProc(key_value_t<text, text> &item1, key_value_t<text, text> &item2)
{
	if (mCompareProc)
		return mCompareProc(item1, item2);
	return item1.key.compare(item2.key);
}

void dictionary_t::sort(TCompareProc compareProc)
{
	mCompareProc = compareProc;
	arrayof< key_value_t<text, text> >::sort();
}
//---------------------------------------------------------------------------
data_t data_t::subdata(int start, int end)
{
	data_t retv(end - start);
	for (int i = start; i < end; i++) {
		retv[i - start] = operator [](i);
	}
	return retv;
}

void data_t::insert(const char *bytes, int pos)
{
	buffer_t<char>::insert(bytes, pos, strlen(bytes));
}

//---------------------------------------------------------------------------
#if !defined(__BORLANDC__) && !defined(_MSC_VER)
#include <sys/time.h>
#else
#include <time.h>
#endif
text text::random(int len)
{
	text rndStr;
	rndStr.setLength(len);
	srand (time(NULL));
	for (int t = 0; t < len; t++)
		rndStr[t] = (char)(rand() % ('z' - 'a') + 'a');
	return rndStr;
}
//---------------------------------------------------------------------------
#if defined (_Windows) && defined (__BORLANDC__)
#if __BORLANDC__ < 1800
extern "C" wchar_t* _stdcall SysAllocString(const wchar_t *psz);
#endif
wchar_t* text::getOleStr()
{
	return SysAllocString(data);
}
#endif
#ifdef __BORLANDC__
#pragma package(smart_init)
#endif
