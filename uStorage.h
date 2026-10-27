//---------------------------------------------------------------------------

#ifndef uStorageH
#define uStorageH
//---------------------------------------------------------------------------
#include "MPShellUtilities.hpp"
#include "windows.h"
#include "text.h"
//---------------------------------------------------------------------------
class TStorageItem
{
protected:
public:
	text name;
	DWORD attributes;
	FILETIME creationTime;
	FILETIME modifyTime;
	__int64 size;
	bool isDot();

	TStorageItem()
	{

	}
};
//---------------------------------------------------------------------------
typedef arrayof<TStorageItem> TStorageItems;
//---------------------------------------------------------------------------
class TStorage
{
protected:
public:
	TStorage()
	{
	}
	virtual ~TStorage()
	{
		OutputDebugStringA("Super");
	}
	virtual TStorageItems getItems(text path, DWORD attributes) = 0;
	virtual bool deleteItems(array items) = 0;
	virtual bool renameItem(text oldName, text newName) = 0;
	virtual data_t download(text itemName) = 0;
	virtual bool upload(text itemName, data_t data) = 0;
	virtual bool copy(array items, text dstPath) = 0;
};
//---------------------------------------------------------------------------
class THdStorage
{
protected:
	TNamespaceArray createNamespaceArray(array files);
	TNamespace *getRootNamespace(int index);
	void freeNamespaceArray(TNamespaceArray &nsArr);
	TNamespace *m_RootNamespace;
public:
	THdStorage();
	virtual ~THdStorage();
	virtual TStorageItems getItems(text path, DWORD attributes);
	virtual bool deleteItems(array items);
	virtual bool renameItem(text oldName, text newName);
	virtual data_t download(text itemName);
	virtual bool upload(text itemName, data_t data);
	virtual bool copy(array items, text dstPath);
};
//---------------------------------------------------------------------------
TStorage* createStorageFromPath(text path);
//---------------------------------------------------------------------------
#endif
