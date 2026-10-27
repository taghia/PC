// ---------------------------------------------------------------------------

#ifndef fileviewH
#define fileviewH
// ---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include "VirtualTrees.hpp"
#include <shlobj.h>       // DROPFILES declaration
#include "dargdrop.h"
#include "MPShellUtilities.hpp"
#include "DirMon.h"
#include "shamsidate.h"
#include "Cromis.DirectoryWatch.hpp"
#include "uStorage.h"
// ---------------------------------------------------------------------------
#define colName 0
#define colSize 1
#define colType 2
#define colDateModified 3
#define colDateCreated 4
#define colAttribute 5
// ---------------------------------------------------------------------------
#define WM_SHOWCONTEXTMENU WM_USER + 1
// ---------------------------------------------------------------------------

typedef void __fastcall (__closure *TSearchNewDirEvent)(System::TObject* Sender, String dir);

class TSortParams {
public:
	TSortParams() {
		SortColumn = colName;
		SortDirection = 1;
	}

	int SortColumn;
	int SortDirection;
};

typedef int(*TSortProc)(void*i1, void*i2, TSortParams & params);
int CompareProc(void*i1, void*i2, TSortParams & params);
LRESULT CALLBACK HeaderProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

void swap(void *v[], int i, int j) {
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void QuickSort(void *v[], int left, int right, TSortProc compare,
	TSortParams &params) {
	int i, last;
	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (compare(v[i], v[left], params) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	QuickSort(v, left, last - 1, compare, params);
	QuickSort(v, last + 1, right, compare, params);
}

// ---------------------------------------------------------------------------
template<class T>class TArrayItem {
protected:
	unsigned int refCount;

public:
	TArrayItem() {
		refCount = 0;
	}

	virtual void addRef() {
		refCount++;
	}

	virtual void release() {
		refCount--;
		if (!refCount)
			delete(T*)this;
	}
};

// ---------------------------------------------------------------------------
template<class T>class TBaseArray {
private:
	int get_count() {
		return m_items->Count;
	}

	T* get_items(int index) {
		return(T*)m_items->Items[index];
	}

	TObject *get_objects(int index) {
		return(TObject*)items[index];
	}

	TSortProc m_compare;

	void set_compare(TSortProc value) {
		m_compare = value;
	}

protected:
	TList *m_items;

	void free(int index) {
		items[index]->release();
		// ((T*)m_items->Items[index])->release();
	}

public:
	TBaseArray() {
		m_items = new TList;
	}

	~TBaseArray() {
		clear();
		delete m_items;
	}

	void clear() {
		for (int t = 0; t < m_items->Count; t++)
			free(t);
		m_items->Clear();
	}

	void remove(int index) {
		free(index);
		m_items->Delete(index);
	}

	void remove(T* item) {
		int index = indexOf(item);
		remove(index);
	}

	void remove(TBaseArray<T> * items) {
		for (int i = 0; i < items->count; i++)
			remove(items->items[i]);
	}

	T* add() {
		T *instance = new T;
		add(instance);
		return instance;
	}

	void add(T* item) {
		item->addRef();
		m_items->Add(item);
	}

	int indexOf(T* item) {
		return m_items->IndexOf(item);
	}

	void exchange(int index1, int index2) {
		m_items->Exchange(index1, index2);
	}

	void quickSort(int left, int right, TSortParams &params) {
		int i = left;
		int j = right;
		void *pivot = m_items->Items[(left + right) / 2];
		while (i <= j) {
			while (m_compare(m_items->Items[i], pivot, params) < 0)
				i++;
			while (m_compare(m_items->Items[j], pivot, params) > 0)
				j--;
			if (i <= j) {
				m_items->Exchange(i, j);
				i++;
				j--;
			}
		}
		if (left < j)
			quickSort(left, j, params);
		if (i < right)
			quickSort(i, right, params);
	}

	void sort(TSortParams &params) {
		if (count > 1)
			quickSort(0, count - 1, params);
	}

	__property int count = {
		read = get_count
	};
	__property TSortProc compare = {
		read = m_compare, write = set_compare
	};
	__property T* items[int index] = {
		read = get_items
	};
};

// ---------------------------------------------------------------------------
enum TDateKind {
	dkModified, dkCreated, dkAccessed
};

// ---------------------------------------------------------------------------
enum TModifyType {
	mtNone, mtNew, mtSize, mtAttribute, mtCreationTime, mtLastWriteTime,
	mtModifyName
};

// ---------------------------------------------------------------------------
class TFileObject : public WIN32_FIND_DATAW, public TArrayItem<TFileObject> {
private:
	String GetFileName() {
		return(String)cFileName;
	}

	void SetFileName(String name) {
		wcscpy(cFileName, name.w_str());
	}

public:
	HICON hIcon;
	String Path;
	String Description;
	__int64 id;
	bool ShellInfoExtracted;
	bool selected;

	// TModifyType modifyType;
	TFileObject() {
		hIcon = NULL;
		ShellInfoExtracted = false;
		// modifyType = mtNone;
		id = 0;
		selected = 0;
	}

	~TFileObject() {
		if (hIcon)
			DestroyIcon(hIcon);
	}

	TDateTime GetVclDateTime(TDateKind type);

	bool IsDirectory() {
		return (dwFileAttributes & faDirectory) && !IsDot();
	}

	bool IsDot() {
		//return cFileName[0] == L'.';
		return IsSingleDot() || IsDoubleDot();
	}

	bool IsSingleDot() {
		return cFileName[0] == '.' && cFileName[1] == 0;
	}

	bool IsDoubleDot() {
		return cFileName[0] == '.' && cFileName[1] == '.';
	}

	__int64 GetSize() {
		return nFileSizeLow + (nFileSizeHigh << 16);
	}

	bool isHidden() {
		return dwFileAttributes & faHidden;
	}

	String GetAttribute() {
		String str;
		if (dwFileAttributes & faReadOnly)
			str = str + "R";
		if (dwFileAttributes & faArchive)
			str = str + "A";
		if (dwFileAttributes & faSysFile)
			str = str + "S";
		if (dwFileAttributes & faHidden)
			str = str + "H";
		if (dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
			str = str + "C";
		if (dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
			str = str + "T";
		if (dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
			str = str + "E";
		if (dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)
			str = str + "O";
		if (str == L"")
			str = "None";

		return str;
	}

	String GetFormattedSize() {
		int digits = 2;
		String unit;
		unit = "B";
		long per = 1;
		long double size = Size;
		if (size > 1024 && size < 1024 * 1024) {
			unit = "KB";
			per = 1024;
		}

		if (size >= 1024 * 1024 && size < 1024 * 1024 * 1024) {
			per = 1024 * 1024;
			unit = "MB";
		}
		if (size >= 1024 * 1024 * 1024) {
			per = 1024 * 1024 * 1024;
			unit = "GB";
		}

		size = (__int64)(size * digits);
		size = size / per;
		size = size / digits;

		return (String)(double)RoundTo(size, -digits) + " " + unit;
	}

	String GetExt() {
		return ExtractFileExt(FileName).LowerCase();
	}
	String GetDate(TDateKind type);
	String GetDateTime(TDateKind type, bool shamsi = false);
	String GetFace();

	__property String FileName = {
		read = GetFileName, write = SetFileName
	};
	__property __int64 Size = {
		read = GetSize
	};
	__property String Attribute = {
		read = GetAttribute
	};
	__property String FormattedSize = {
		read = GetFormattedSize
	};
	__property String Date[TDateKind type] = {
		read = GetDate
	};
	__property String DateTime[TDateKind type][bool shamsi] = {
		read = GetDateTime
	};
	__property String Ext = {
		read = GetExt
	};
};

// ---------------------------------------------------------------------------
class TFileObjectArray : public TBaseArray<TFileObject> {
public:
	int indexOf(String fileName);
};

class TFolderState : public TArrayItem<TFolderState> {
public:
	String dir;
	int offsetY;
	String name;
	int sortColumn;
	int sortDir;

	TFolderState() {
		offsetY = 0;
		sortColumn = colName;
		sortDir = 1;
	}
};
// ---------------------------------------------------------------------------
class TFolderStates {
public:
	TBaseArray<TFolderState> *m_States;

	void SetState(String dir, TFolderState* value);
	TFolderState* GetState(String dir);
	TFolderStates();
	~TFolderStates();
	__property TFolderState* States[String dir] = {
		read = GetState, write = SetState
	};
};
// ---------------------------------------------------------------------------
class TInt64 : public TArrayItem<TInt64>
{
public:
	__int64 value;
};
// ---------------------------------------------------------------------------
class TInt64Array : TBaseArray<TInt64>
{
public:
	void addItem(__int64 value)
	{
		add()->value = value;
	}
	int find(__int64 value)
	{
		for (int i=0; i<count; i++) {
			if(items[i]->value == value) return i;
		}
		return -1;
    }
};
// ---------------------------------------------------------------------------
class TString : public TArrayItem<TString>
{
public:
	String value;
};
// ---------------------------------------------------------------------------
class THistory : public TBaseArray<TString>
{
public:
	bool lock;
	THistory(){
		pos = -1;
		lock = false;
	}
	~THistory(){
    }
	TString* find(String dir)
	{
		for (int i=0; i<count; i++) {
			if(items[i]->value == dir) return items[i];
		}
		return NULL;
	}
	int pos;
	String forward()
	{
		if(!canForward()) return "";
		pos++;
		return items[pos]->value;
	}
	String backward(){
		if(!canBackward()) return "";
		pos--;
		return items[pos]->value;
	}
	bool canForward(){
		return pos + 1 < count;
	}
	bool canBackward(){
		return pos > 0;
	}
	void addItem(String dir)
	{
		if(lock) return;
		if(pos + 1 < count)
		{
			pos ++;
			items[pos]->value = dir;
			while(pos + 1 < count) {
				remove(pos + 1);
			}
		}
		else{
			add()->value = dir;
			pos++;
		}
	}

};
// ---------------------------------------------------------------------------
class TpcStrings : public TBaseArray<TString>
{
private:
protected:

};
// ---------------------------------------------------------------------------
class TNotification : public TArrayItem<TNotification> {
public:
	String fileName1;
	String fileName2;
	TFileOperation action;
};

// ---------------------------------------------------------------------------
class TNotifications : public TBaseArray<TNotification> {
public:
};

// ---------------------------------------------------------------------------
class THotObject : public TArrayItem<THotObject> {
private:

public:
	THotObject() {
		id = 0;
		modifyType = mtNone;
		time = GetTickCount();
	}

	~THotObject() {
	}

	__int64 id;
	TModifyType modifyType;
	int time;

	bool expired() {
		return GetTickCount() - time > 60000 * 5; // 5 min
	}
};

// ---------------------------------------------------------------------------
class THotObjects : public TBaseArray<THotObject> {
private:

public:
	THotObjects() {
	}

	~THotObjects() {
	}

	void clean() {
		for (int i = 0; i < count; i++) {
			if (items[i]->expired()) {
				remove(i);
				i--;
			}
		}
	}

	int find(__int64 id, int begin) {
		for (int i = begin; i < count; i++) {
			if (items[i]->id == id)
				return i;
		}
		return -1;
	}
};

// ---------------------------------------------------------------------------

class TFileView;
class TMonItem : public TArrayItem<TMonItem>
{
public:
	TFileView *view;
	TFileDealMethod onChange;
	TMonItem()
	{
		view = NULL;
		onChange = NULL;
	}
};
// ---------------------------------------------------------------------------
class TMonItems : public TBaseArray<TMonItem>
{
public:

};
// ---------------------------------------------------------------------------
int getDrivesCount();
char getDriveStr(int index);
// ---------------------------------------------------------------------------
class TGlobalMon : public TArrayItem <TGlobalMon>
{
private:
	bool get_active()
	{
		for (int i=0; i<notifers.Length; i++) {
			return notifers[i]->Actived;
		}
		return false;
	}
	void set_active(bool value)
	{
		for (int i=0; i<notifers.Length; i++) {
			notifers[i]->Actived = value;
			notifers[i]->WatchedDir;
		}
	}
public:
	DynamicArray<TDirMon*> notifers;
	TMonItems mons;
	TGlobalMon();
	void __fastcall onChange(TFileOperation FileOperation,
		const UnicodeString FileName1, const UnicodeString FileName2);
	void refresh();
	void free()
	{
		for (int i=0; i<notifers.Length; i++) {
			notifers[i]->Actived = false;
			delete notifers[i];
		}
		notifers.Length = 0;
	}
	~TGlobalMon()
	{
		free();
	}
	void deleteItem(int index)
	{
		delete notifers[index];
		for (int i=index; i<notifers.Length - 1; i++) {
			notifers[i] = notifers[i + 1];
		}
		notifers.Length = notifers.Length - 1;
	}
	void deleteRemovables()
	{
		for (int i=0; i<notifers.Length; i++) {
			char drive[] = {notifers[i]->WatchedDir[1], ':', '\\', '\0'};
			if(GetDriveType(drive) == DRIVE_REMOVABLE)
			{
				notifers[i]->Actived = false;
				notifers[i]->WatchedDir = "C:\\";
				notifers[i]->Actived = true;
				deleteItem(i);
			}
		}
	}
	__property bool active = {read=get_active, write=set_active};
};
// ---------------------------------------------------------------------------
#include "text.h"
enum TParamType {
	ptNone = 0,
	ptText = 1,
	ptSize = 2,
	ptDate = 4,
	ptContent = 8,
	ptBuffer = 16
	//ptPattern = 32,
};

class TSearchParam : public TArrayItem <TSearchParam>
{
private:
	text m_text, m_content;

	__int64 sizeToInt(text size)
	{
		if(size.empty()) return -1;
		txt::text num = size.read(0, L"mkgb-] ", NULL);
		txt::text unit = size.read(num.length(), L"-] ", NULL);
		if(unit == L"") unit = "mb";
		int zoom = 1;
		if(unit == "kb") zoom = 1024;
		else if(unit == "mb") zoom = 1024 * 1024;
		else if(unit == "gb") zoom = 1024 * 1024 * 1024;
		return num.intValue() * zoom;
	}
	void set_text(text value)
	{
		m_content = value.subfind("\"", "\"");
		value = value.lowercase();
		txt::text range = value.subfind("[", "]");
		txt::text min = range.read(0, L"-", NULL);
		txt::text max = range.subfind("-");
		sizeMin = sizeToInt(min);
		sizeMax = sizeToInt(max);
		txt::text buf = value.subfind("<", ">");
		if(buf.length())
		{
			buffer = new BYTE[buf.length()];
			int bi;
			for (bi=0; bi<buf.length()/2; bi++) {
				wchar_t str[] = {'0', 'x', buf[bi*2], buf[bi*2 + 1], 0};
				buffer[bi] = StrToInt(str);
			}
			buffer[bi] = 0;
			bufferLen = bi;
		}
		txt::text date = value.subfind("{", "}");
		txt::text date1 = date.read(0, L"-", NULL);
		txt::text date2 = date.subfind("-");

		Sysutils::FormatSettings.ShortDateFormat = "Y M D";
		if(date1.empty())
			dateMin.Val = -1;
		else
			dateMin = StrToDate(date1);
		if(date2.empty())
			dateMax.Val = -1;
		else
			dateMax = StrToDate(date2);

		value = value.replace("[", "]", "");
		value = value.replace("'", "'", "");
		value = value.replace("\"", "\"", "");
		value = value.replace("<", ">", "");
		value = value.replace("{", "}", "");
		m_text = value.trim();

		//if(!m_text.contains("*")) m_text = "*" + m_text + "*";
		type = TParamType(::ptNone);
		if(m_text.length())
			type = TParamType(type | ptText);
		if(sizeMin != -1 || sizeMax != -1)
			type = TParamType(type | ptSize);
		if(dateMin.Val != -1 || dateMax.Val != -1)
			type = TParamType(type | ptDate);
		if(m_content.length())
			type = TParamType(type | ptContent);
		if(buffer)
			type = TParamType(type | ptBuffer);
	}
	void set_content(text value)
	{
		m_content = value.lowercase();
	}
public:
	BYTE *buffer;
	int bufferLen;
	__int64 sizeMin;
	__int64 sizeMax;
	TDateTime dateMin;
	TDateTime dateMax;
	TParamType type;
	TSearchParam()
	{
		buffer = 0;
		bufferLen = 0;
		sizeMin = sizeMax = -1;
		dateMin = dateMax = -1;
	}
	~TSearchParam()
	{
		if(buffer) delete [] buffer;
	}
	__property txt::text text = {read=m_text, write=set_text};
	__property txt::text content = {read=m_content, write=set_content};
};
// ---------------------------------------------------------------------------
class TSearchParams : public TBaseArray <TSearchParam>
{
private:
public:
	String dir;
	TSearchParams()
	{

	}
	~TSearchParams()
	{

    }
};
// ---------------------------------------------------------------------------
class PACKAGE TFileView : public TVirtualStringTree {
private:
	//bool
	void ShowLastError();

	String FDirectory;

	String __fastcall GetDirectory();
	void __fastcall SetDirectory(String value);
	DWORD EnumFiles();

	TFileObjectArray *Files;

	void __fastcall SetAttribute(DWORD value);

	DWORD FAttribute;

	String GetPathFileName(int index = -1);
	String GetFileName(int index = -1);
	void SetFileName(String name);
	TFileObject* GetFileObject(int index = -1);

	int nIconSize;

	TFileObject *objectOf(TVirtualNode *node) {
		if (!node)
			return NULL;
		int *data = (int*)GetNodeData(node);
		return(TFileObject*) * data;
	}

	TVirtualTreeColumn *getColumnHeaderAt(TPoint point) {
		for (int ci = 0; ci < Header->Columns->Count; ci++) {
			TRect rect = Header->Columns->Items[ci]->GetRect();
			if (PtInRect(rect, point))
				return Header->Columns->Items[ci];
		}
		return NULL;
	}

	TSortParams SortParams;
	TColor sortColor;
	TFolderStates folderStates;
	THistory history;

	TVirtualNode *getNode(int index) {
		int pos = 0;
		TVirtualNode *ret = GetFirst();
		if (index == 0)
			return ret;
		do {
			pos++;
			ret = GetNext(ret);
		}
		while (ret && pos < index);
		return ret;
	}

	TVirtualNode *getNodeByID(__int64 id) {
		TVirtualNode *node = GetFirst();
		while (node) {
			if (objectOf(node)->id == id)
				return node;
			node = GetNext(node);
		}
		return NULL;
	}

	void invalidateAll() {
		TVirtualNode *node = GetFirst();
		while (node) {
			node->States >> vsInitialized;
			InvalidateNode(node);
			node = GetNext(node);
		}
	}

	TVirtualNode *getNodeByFileName(String name) {
		TVirtualNode *node = GetFirst();
		while (node) {
			if (!WideCompareText(objectOf(node)->FileName, name))
				return node;
			node = GetNext(node);
		}
		return NULL;
	}
	void Execute(String params = "", int index = -1);
	void selectByType();
	TNamespace *GetRootNamespace();

	TNamespace *m_RootNamespace;

	TNamespaceArray CreateNamespaceArray(TStringList *files);
	TNamespaceArray CreateRootNamespaceArray(String root="");

	TNamespaceArray m_NamespaceArray;

	TNamespaceArray GetNamespaceArray();
	TFileObjectArray *GetSelectedObjects();

	TFileObjectArray m_selectedObjects;

	void FreeNamespaceArray();

	TDirMon *DirMon;

	void __fastcall OnMonDirChange(TFileOperation FileOperation,
		const UnicodeString FileName1, const UnicodeString FileName2);
	void ApplyNotifications();
	static bool lockUpdate;

	TNotifications *Notifications;
	int lastNotifyTime;
	int notifyDelay;
	TTimer *notiftTimer;
	void __fastcall onTimerNotify(TObject *Sender);

	__int64 getFileID(String fileName);

	THotObjects hotObjects;

	void GetFileInfo(String pathFileName, TFileObject *item);
	TModifyType DetectModifyType(TFileObject *oldObj, TFileObject *newObj);
	bool IsNewObject(TFileObject* object);
	__int64 SysTimeAsSeconds(SYSTEMTIME systime);
	__int64 GetFileDateAsSeconds(FILETIME &filetime);

	TIcon *m_backIcon;

	void __fastcall SetBackIcon(TIcon* value);

	bool DblClicked;

	DYNAMIC void __fastcall DblClickUp(void);
	virtual void __fastcall HandleMouseDown(Messages::TWMMouse &Message,
		THitInfo &HitInfo);
	DYNAMIC void __fastcall MouseDown(TMouseButton Button, TShiftState Shift,
		int X, int Y);
	DYNAMIC void __fastcall MouseUp(TMouseButton Button, TShiftState Shift,
		int X, int Y);
//	void __fastcall Change(void){
//		frmMain->updateStatusBar();
//	}

	bool m_bExecute;

	TStringList *getDataObjectFiles() {
		IDataObject *dataObject = DragManager->DataObject;
		FORMATETC fmtetc = {
			CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
		};
		STGMEDIUM stgmed;
		if (dataObject->GetData(&fmtetc, &stgmed) == S_OK) {
			HDROP data = (HDROP)GlobalLock(stgmed.hGlobal);
			m_files->Clear();
			getClipboardFiles(data, m_files);
			GlobalUnlock(stgmed.hGlobal);
			ReleaseStgMedium(&stgmed);
		}
		return m_files;
	}

	void getClipboardFiles(HDROP hdrop, TStringList *list) {
		WCHAR buf[MAX_PATH];
		int count = DragQueryFileW(hdrop, 0xFFFFFFFF, buf, MAX_PATH);
		for (int t = 0; t < count; t++) {
			DragQueryFileW(hdrop, t, buf, MAX_PATH);
			list->Add(buf);
		}
	}
	void copy(TStringList *src, String Des, HWND parent);
	bool lockShellExtract;
	void search(TSearchParams *params, String path);
	bool rightDrag;
	void __fastcall onDropAction(TObject *sender);
	TPopupMenu *popDrop;
	String m_copyDst;
protected:
	TStringEditLink *editLink;
	TStorage *storage;

	DYNAMIC void __fastcall DblClick(void);

	virtual void __fastcall PaintSelectionRectangle(TCanvas* Target, int WindowOrgX,
		const Types::TRect &SelectionRect, const Types::TRect &TargetRect)
	{
		if(GetAsyncKeyState(VK_RBUTTON) < 0) return;
		TVirtualStringTree::PaintSelectionRectangle(Target, WindowOrgX,
			SelectionRect, TargetRect);
	}
	// DYNAMIC void __fastcall Click(void);
	virtual void __fastcall DoInitNode(PVirtualNode Parent, PVirtualNode Node,
		TVirtualNodeInitStates &InitStates) {
		TFileObject *obj = Files->items[Node->Index];
		int *data = (int*)GetNodeData(Node);
		*data = (int)obj;
		// memcpy(data, obj, sizeof(int));
	}

	virtual _di_IVTEditLink __fastcall DoCreateEditor(PVirtualNode Node,
		TColumnIndex Column) {
//		if(ignoreEdit) {
//			CancelEditNode();
//			return NULL;
//		}
		TFileObject *obj = Files->items[Node->Index];
		if (obj->IsDoubleDot()) {
			CancelEditNode();
			return NULL;
		}
		IVTEditLink *result;
		editLink = new TStringEditLink;
		editLink->QueryInterface(__uuidof(IVTEditLink), (void**) & result);
		return result;
	}

	virtual void __fastcall DoEdit(void)
	{
		TVirtualStringTree::DoEdit();
		if(FileObject->IsDirectory()) return;
		editLink->Edit->SelStart = 0;
		String file = editLink->Edit->Text;
		String ext = ExtractFileExt(file);
		editLink->Edit->SelLength = file.Length() - ext.Length();
	}

	virtual bool __fastcall DoEndEdit(void) {
		TFileObject *obj = objectOf(FocusedNode);
//		if (RenameFile(PathFileName, Directory + editLink->Edit->Text))
		if (storage->renameItem(PathFileName, Directory + editLink->Edit->Text))
			obj->FileName = editLink->Edit->Text;
		return TVirtualStringTree::DoEndEdit();
	}

	virtual void __fastcall DoGetText(PVirtualNode Node, TColumnIndex Column,
		TVSTTextType TextType, System::UnicodeString &Text) {
		TFileObject *obj = objectOf(Node);
		extractShellInfo(obj);
		switch(Column) {
			case colName:
				Text = obj->cFileName;
				break;
			case colSize:
				if (!obj->IsDirectory())
					Text = obj->FormattedSize;
				else
					Text = "";
				break;
			case colType:
				Text = obj->Description;
				break;
			case colDateModified:
				Text = obj->DateTime[dkModified][useShamsiDate];
				break;
			case colDateCreated:
				Text = obj->DateTime[dkCreated][useShamsiDate];
				break;
			case colAttribute:
				Text = obj->Attribute;
				break;
		}
	}

	virtual void __fastcall DoPaintText(PVirtualNode Node,
		Graphics::TCanvas* const Canvas, TColumnIndex Column,
		TVSTTextType TextType) {
		TFileObject *obj = objectOf(Node);
		bool inSelectRect = Node->States.Contains(vsSelected)
			&& Column == colName;
		if (!inSelectRect && obj->isHidden() && Column == colName)
			Canvas->Font->Color = hiddenColor;
		int begin = 0;
	start:
		Canvas->Font->Style = Canvas->Font->Style >> fsUnderline;
		int index = hotObjects.find(obj->id, begin);
		begin = index + 1;
		if (index != -1) {
			THotObject *obj = hotObjects.items[index];
			switch(obj->modifyType) {
			case mtNew:
				if (Column == colName)
					Canvas->Font->Style = TFontStyles() << fsBold;
				goto start;
			case mtSize:
				if (Column == colSize)
					Canvas->Font->Color = clRed;
				goto start;
			case mtAttribute:
				if (Column == colAttribute)
					Canvas->Font->Color = clRed;
				goto start;
			case mtCreationTime:
				if (Column == colDateCreated)
					Canvas->Font->Color = clRed;
				break;
			case mtLastWriteTime:
				if (Column == colDateModified)
					Canvas->Font->Color = clRed;
				break;
			case mtModifyName:
				if (!inSelectRect && Column == colName)
					Canvas->Font->Color = clRed;
				break;
			}
		}
		if (IsNewObject(obj) && Column == colName)
			Canvas->Font->Style = TFontStyles() << fsBold;
		TVirtualStringTree::DoPaintText(Node, Canvas, Column, TextType);
	}

	virtual void __fastcall DoAfterCellPaint(Graphics::TCanvas* Canvas,
		PVirtualNode Node, TColumnIndex Column, const Types::TRect &CellRect) {
		if (Column == 0) {
			TFileObject *obj = objectOf(Node);
			HICON hIcon = obj->hIcon;
			if (obj->IsDot() && obj->IsDirectory())
				hIcon = backIcon->Handle;
			DrawIconEx(Canvas->Handle, CellRect.left + 4, CellRect.top, hIcon,
				nIconSize, nIconSize, NULL, NULL, DI_NORMAL);
		}
	}

	void __fastcall HeaderClick(TVTHeader* Sender, TColumnIndex Column,
		TMouseButton Button, TShiftState Shift, int X, int Y) {
		TVirtualTreeColumn *column = Sender->Columns->Items[Column];

		if (Header->SortColumn == column->Index)
			Header->SortDirection = Header->SortDirection == sdAscending ?
				sdDescending : sdAscending;
		else
		{
			Header->SortColumn = column->Index;
			if(column->Text == "Size" || column->Text == "Modified" || column->Text == "Created")
				Header->SortDirection = sdDescending;
			else
				Header->SortDirection = sdAscending;
		}
		SortParams.SortColumn = Header->SortColumn;
		SortParams.SortDirection = Header->SortDirection == sdAscending ?
			+1 : -1;
		Files->sort(SortParams);
		RootNodeCount = 0;
		RootNodeCount = Files->count;
		for (int ci=0; ci<Header->Columns->Count; ci++) {
			Header->Columns->Items[ci]->Color = clWhite;
		}
		column->Color = sortColor;
		if(GetFirst()) {
			FocusedNode = GetFirst();
			AddToSelection(FocusedNode);
		}
	}
	DYNAMIC void __fastcall KeyPress(wchar_t &Key);
	DYNAMIC void __fastcall KeyDown(WORD &Key, TShiftState Shift);
	DYNAMIC void __fastcall KeyUp(WORD &Key, TShiftState Shift);
	virtual bool __fastcall DoDragOver(System::TObject* Source,
		Classes::TShiftState Shift, Controls::TDragState State,
		const Types::TPoint &Pt, TDropMode Mode, int &Effect);
	virtual void __fastcall DoDragDrop(System::TObject* Source,
		_di_IDataObject DataObject, TFormatArray Formats,
		Classes::TShiftState Shift, const Types::TPoint &Pt,
		int &Effect, TDropMode Mode);

	TStringList *m_files;

	HDROP CreateHDrop(TStringList *files);

	::TDataObject *dataObject;

	virtual bool __fastcall DoBeforeDrag(PVirtualNode Node,	TColumnIndex Column) {
		TFileObject *obj = objectOf(Node);
		return !obj->IsDot();
	}

	virtual void __fastcall DoGetUserClipboardFormats(Virtualtrees::TFormatEtcArray &Formats) {
	}

	virtual _di_IDataObject __fastcall DoCreateDataObject(void)
	{
		TreeOptions->MiscOptions >> toEditOnClick;
		dataObject = new TDataObject;
		dataObject->AddRef();
		FORMATETC etc = {
			CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
		};
		dataObject->m_vfmtetc.push_back(etc);
		GetSelectList(m_files);
		dataObject->set_hglobal(CreateHDrop(m_files));
		return dataObject;
	}

	virtual void __fastcall DragFinished() {
		TVirtualStringTree::DragFinished();
		if (dataObject)
			dataObject->Release();
		rightDrag = false;
	}

	virtual bool __fastcall DoFocusChanging(PVirtualNode OldNode,
		PVirtualNode NewNode, TColumnIndex OldColumn,
		TColumnIndex NewColumn) {
		return true;
	}

	virtual void __fastcall DoFocusChange(PVirtualNode Node,
		TColumnIndex Column) {
		TVirtualStringTree::DoFocusChange(Node, Column);
	}

	virtual void __fastcall DoChange(PVirtualNode Node) {
		// updateSelectState();
		TVirtualStringTree::DoChange(Node);
//		OffsetX = 0;
	}

	void __fastcall onBeforeAutoFitColumn(TVTHeader* Sender, TColumnIndex Column, TSmartAutoFitType &SmartAutoFitType, bool &Allowed)
	{
		lockShellExtract = true;
	}
	void __fastcall onAfterAutoFitColumn(TVTHeader* Sender, TColumnIndex Column)
	{
		if(Sender->Columns->Items[Column]->Width > ClientWidth)
			Sender->Columns->Items[Column]->Width = ClientWidth;
		lockShellExtract = false;
	}

	virtual void __fastcall DoHotChange(PVirtualNode Old, PVirtualNode New)
	{
		//Canvas->Font->Color = clRed;
	}

	virtual void __fastcall HandleIncrementalSearch(System::Word CharCode)
	{
		if(CharCode == '\r') CharCode = 0;
		if(GetAsyncKeyState(VK_SHIFT) < 0) CharCode = 0;
		if(GetAsyncKeyState(VK_CONTROL) < 0) CharCode = 0;
		if(GetAsyncKeyState(VK_MENU) < 0) CharCode = 0;
		TVirtualStringTree::HandleIncrementalSearch(CharCode);
	}

	virtual int __fastcall DoIncrementalSearch(PVirtualNode Node,
		const System::UnicodeString Text)
	{
		String str = Files->items[Node->Index]->FileName;
		str = str.SubString(1, Text.Length());
		return str.CompareIC(Text);
		// int ret = TVirtualStringTree::DoIncrementalSearch(Node, Text);
		// return ret;
	}

	CRITICAL_SECTION criticalSection;

	void __fastcall on1Param(System::TObject* Sender, unsigned Flags,
		System::UnicodeString Path1);
	void __fastcall wndProc(Messages::TMessage &Message);

public:
	__fastcall TFileView(TComponent* Owner);
	__fastcall ~TFileView();

	TNotifyEvent onDirChange, onNotify;
	static TGlobalMon *globalMon;
	static bool useShamsiDate;
	void copy();
	void doCopy(text dst);
	void paste(String dst = "");
	void cut();
	void refresh();
	void remark();
	void selectAll();
	void forward(){
		history.lock = true;
		Directory = history.forward();
		history.lock = false;
	}
	void backward(){
		history.lock = true;
		Directory = history.backward();
		history.lock = false;
	}
	bool canForward()
	{
		return history.canForward();
	}
	bool canBackward()
	{
		return history.canBackward();
	}
	void up();
	void showShellInfo();
	bool canUp()
	{
        return Directory.Length() > 1 && ExcludeTrailingBackslash(Directory).LastChar()[0] != ':';
    }
	void deleteSelected();
	void search(TSearchParams *params);
	bool itemFound(TFileObject *obj, TSearchParams *params);
	void stopSearch()
	{
        bStopSearch = true;
    }
	bool searchMode, bStopSearch;
	TSearchNewDirEvent onSearchNewDir;
	TNotifyEvent onItemFound;
	int find(String fileName)
	{
		for (int i = 0; i < Files->count; i++) {
			if(!WideCompareText(Files->items[i]->FileName, fileName))
				return i;
		}
		return -1;
	}
	void go(String pathFileName)
	{
		Directory = ExtractFileDir(pathFileName);
		int index = find(ExtractFileName(pathFileName));
		if(index != -1)
		{
			UnselectNodes(GetFirst(), GetLast());
			FocusedNode = getNode(index);
			AddToSelection(FocusedNode);
		}
    }

	void GetSelectList(TStringList *items, bool path = true);
	array getSelectList(bool path);

	void extractShellInfo(TFileObject *obj) {
		if (obj->ShellInfoExtracted || obj->IsDot() || lockShellExtract)
			return;

		int uFlag;
		bool larg = false;
		if (larg)
			uFlag = SHGFI_LARGEICON;
		else
			uFlag = SHGFI_SMALLICON;
		uFlag |= SHGFI_ICON | SHGFI_TYPENAME | SHGFI_DISPLAYNAME;
		SHFILEINFOW psfi;
		String file;
		if(obj->Path == "")
			file = Directory + obj->cFileName;
		else
			file = obj->Path + obj->cFileName;
		SHGetFileInfoW(file.w_str(), 0, &psfi, 200, uFlag);
		obj->hIcon = psfi.hIcon;
		obj->Description = psfi.szTypeName;
		obj->ShellInfoExtracted = true;
		obj->id = getFileID(file);
	}

	String extraMenuCaption;
	TPopupMenu *extraMenu;
	TColor hiddenColor;

	int getFileCount() {
		return Files->count;
	}

	int getSelectedCount() {
		return SelectedCount;
	}
	__property String Directory = {
		read = GetDirectory, write = SetDirectory
	};
	void reload();
	__property DWORD Attribute = {
		read = FAttribute, write = SetAttribute
	};
	__property String PathFileName[int index] = {
		read = GetPathFileName
	};
	__property String FileName[int index] = {
		read = GetFileName
	};
	__property TFileObject* FileObject[int index] = {
		read = GetFileObject
	};
	__property TNamespaceArray NamespaceArray = {
		read = GetNamespaceArray
	};
	__property TNamespace *RootNamespace = {
		read = GetRootNamespace
	};
	__property TIcon *backIcon = {
		read = m_backIcon, write = SetBackIcon
	};
	void showContextMenu(TPoint point = Point(-1, -1));

__published:
};
bool TFileView::lockUpdate = false;
TGlobalMon *TFileView::globalMon = new TGlobalMon;
bool TFileView::useShamsiDate = true;
class TUpdateLock
{
protected:
	TFileView *view;
public:
	TUpdateLock(TFileView *view)
	{
		this->view = view;
		view->BeginUpdate();
	}
	~TUpdateLock()
	{
		view->EndUpdate();
    }
};
// ---------------------------------------------------------------------------
#endif
