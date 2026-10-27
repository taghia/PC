//---------------------------------------------------------------------------


#pragma hdrstop

#include "uStorage.h"

//---------------------------------------------------------------------------
TStorage* createStorageFromPath(text path)
{
	if(path[1] == ':')
		return new THdStorage;
	return NULL;
}
//---------------------------------------------------------------------------
bool TStorageItem::isDot()
{
	return name[0] == L'.';
}
//---------------------------------------------------------------------------
THdStorage::THdStorage()
{

}
//---------------------------------------------------------------------------
THdStorage::~THdStorage()
{
	OutputDebugStringA("Sub");
}
//---------------------------------------------------------------------------
TStorageItems THdStorage::getItems(text path, DWORD attributes)
{
	TStorageItems retv;
	HANDLE hfind = 0;
	bool result = true;
	WIN32_FIND_DATAW data;

	do
	{
		if(!hfind)
			hfind = FindFirstFileW(path + "*.*", &data);
		else
			result = FindNextFileW(hfind, &data);
		if (result && !(data.cFileName[0] == L'.' && (data.cFileName[1] == 0 || data.cFileName[1] == '.')) &&
			(data.dwFileAttributes & attributes) && hfind != (void*)-1)
		{
			TStorageItem &item = retv.add();
			item.name = data.cFileName;
			item.attributes = data.dwFileAttributes;
			item.creationTime = data.ftCreationTime;
			item.modifyTime = data.ftLastWriteTime;
			item.size = (data.nFileSizeHigh << 16) + data.nFileSizeLow;
		}
	}
	while(result);
	FindClose(hfind);

	return retv;
}
//---------------------------------------------------------------------------
TNamespaceArray THdStorage::createNamespaceArray(array files)
{
	TNamespaceArray retv;
	retv.Length = files.count();
	for (int i = 0; i < files.count(); i++) {
		retv[i] = new TNamespace(files[i]);
	}
	return retv;
}
//---------------------------------------------------------------------------
TNamespace* THdStorage::getRootNamespace(int index)
{
//	if (m_RootNamespace)
//		m_RootNamespace->Free();
//	m_RootNamespace = 0;
//
//	if (FileObject && !i->IsDot())
//		m_RootNamespace = new TNamespace(PathFileName);
//	if (!m_RootNamespace)
//		m_RootNamespace = new TNamespace(Directory);
	return m_RootNamespace;
}
//---------------------------------------------------------------------------
bool THdStorage::deleteItems(array items)
{
	return runFileOperation(items, FO_DELETE);
}
//---------------------------------------------------------------------------
void THdStorage::freeNamespaceArray(TNamespaceArray &nsArr)
{
	for (int i = 0; i < nsArr.Length; i++)
		nsArr[i]->Free();
	nsArr.Length = 0;
}
//---------------------------------------------------------------------------
bool THdStorage::renameItem(text oldName, text newName)
{
	return RenameFile(oldName, newName);
}
//---------------------------------------------------------------------------
bool THdStorage::copy(array items, text dstPath)
{
	return runFileOperation(items, FO_COPY, dstPath);
}
//---------------------------------------------------------------------------
bool THdStorage::runFileOperation(array items, UINT operation, text dstPath)
{
	if (!items.count())
		return false;

	int fromLength = 1;
	for (int i = 0; i < items.count(); i++)
		fromLength += items[i].length() + 1;

	wchar_t *from = new wchar_t[fromLength];
	wchar_t *fromPos = from;
	for (int i = 0; i < items.count(); i++) {
		int itemLength = items[i].length();
		memcpy(fromPos, items[i].data, itemLength * sizeof(wchar_t));
		fromPos += itemLength;
		*fromPos++ = 0;
	}
	*fromPos = 0;

	wchar_t *to = NULL;
	if (operation != FO_DELETE) {
		int toLength = dstPath.length();
		to = new wchar_t[toLength + 2];
		memcpy(to, dstPath.data, toLength * sizeof(wchar_t));
		to[toLength] = 0;
		to[toLength + 1] = 0;
	}

	SHFILEOPSTRUCTW fileOp;
	ZeroMemory(&fileOp, sizeof(fileOp));
	fileOp.hwnd = GetActiveWindow();
	fileOp.wFunc = operation;
	fileOp.pFrom = from;
	fileOp.pTo = to;
	if (operation == FO_DELETE) {
		if (GetKeyState(VK_SHIFT) >= 0)
			fileOp.fFlags |= FOF_ALLOWUNDO;
	}
	else {
		fileOp.fFlags |= FOF_NOCONFIRMMKDIR;
	}

	int result = SHFileOperationW(&fileOp);
	delete [] to;
	delete [] from;
	return result == 0 && !fileOp.fAnyOperationsAborted;
}
//---------------------------------------------------------------------------
data_t THdStorage::download(text itemName)
{
	data_t file;
	file.loadFromFile(itemName);
	return file;
}
//---------------------------------------------------------------------------
bool THdStorage::upload(text itemName, data_t data)
{
	data.saveToFile(itemName);
	return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#pragma package(smart_init)
