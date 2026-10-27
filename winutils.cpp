//---------------------------------------------------------------------------
#pragma hdrstop

#include "winutils.h"
#include <Richedit.h>
#include <Forms.hpp>
//---------------------------------------------------------------------------
TWindow::TWindow(){Init();}
TWindow::TWindow(const TWindow &win)
{
	Init();
	FHandle = win.Handle;
}
TWindow::TWindow(HWND hWnd){Init(); Handle = hWnd;}
TWindow::TWindow(TWindow* pWnd){Init(); if(pWnd) Handle = pWnd->Handle;}
TWindow::TWindow(int hWnd){Init(); Handle = (HWND)hWnd;}
//TWindow::TWindow(Forms::TForm* form){Handle = form->Handle;}

//---------------------------------------------------------------------------
HINSTANCE hUser32 = NULL;

TWindow::~TWindow()
{
	Free();
}
//---------------------------------------------------------------------------
void TWindow::SetHandle(HWND handle)
{
	FHandle = handle;
}
//---------------------------------------------------------------------------
TWindow& TWindow::Find(WCHAR* lpClassName, WCHAR* lpWindowName)
{
	Handle = FindWindowW(lpClassName, lpWindowName);
	return *this;
}
//---------------------------------------------------------------------------
void TWindow::SetText(WideString text)
{
	::SendMessageW(Handle, WM_SETTEXT, 0, (LPARAM)text.c_bstr());
}
//---------------------------------------------------------------------------
WideString TWindow::GetText()
{
/*	int len = SendMessageW(Handle, WM_GETTEXTLENGTH, 0, 0);
	WCHAR *text = new WCHAR[len + 1];
	SendMessageW(Handle, WM_GETTEXT, len + 1, (LPARAM)text);
	WideString result = WideString(text);
	delete [] text;
	return WideString(text);*/
	int len = ::SendMessageW(Handle, WM_GETTEXTLENGTH, 0, 0);
	WideString text;
	if(len)
	{
		text.SetLength(len);
		::SendMessageW(Handle, WM_GETTEXT, len + 1, (LPARAM)text.c_bstr());
	}
	return text;
}
//---------------------------------------------------------------------------
void TWindow::Init()
{
	FHandle = NULL;
	FWindowLong = 0;
	FWinProc = 0;
	FChilds = 0;
	Index = 0;
	FCanvas = 0;
}
//---------------------------------------------------------------------------
void TWindow::SetWindowLong(int index, long newLong)
{
	::SetWindowLong(FHandle, index, newLong);
}
//---------------------------------------------------------------------------
void TWindow::SetStyle(long style)
{
	WindowLong[GWL_STYLE] = style;
}
//---------------------------------------------------------------------------
long TWindow::GetStyle()
{
	return WindowLong[GWL_STYLE];
}
//---------------------------------------------------------------------------
void TWindow::SetWinProc(long proc)
{
	WindowLong[GWL_WNDPROC] = proc;
}
//---------------------------------------------------------------------------
long TWindow::GetWindowLong(int index)
{
	return ::GetWindowLong(FHandle, index);
}
//---------------------------------------------------------------------------
TWindow::TWindow(WCHAR* lpClassName, WCHAR* lpWindowName)
{
	Init();
	Find(lpClassName, lpWindowName);
}
//---------------------------------------------------------------------------
void TWindow::EnumChildWindows()
{
	FChilds->Clear();
	::EnumChildWindows(Handle, (WNDENUMPROC)EnumWindowsProc, (long)(void*)FChilds);
}
//---------------------------------------------------------------------------
int TWindow::GetChildsCount()
{
	if(!FChilds)
	{
		FChilds = new TList;
		EnumChildWindows();
	}
	return FChilds->Count;
}
//---------------------------------------------------------------------------
TWindow TWindow::GetChilds(int index)
{
	if(!FChilds)
	{
		FChilds = new TList;
		EnumChildWindows();
	}
	TWindow* pWnd = (TWindow*)FChilds->Items[index];
	return pWnd->Handle;
}
//---------------------------------------------------------------------------
TWindow TWindow::GetChildByClass(String className)
{
	return FindChild(className.c_str(), NULL);
}
//---------------------------------------------------------------------------
TWindow TWindow::GetChildByClassIndex(String className, int index)
{
	return FindChild(className.c_str(), NULL, index);
}
//---------------------------------------------------------------------------
BOOL CALLBACK TWindow::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TList *list = (TList*)lParam;
	char caption[100];
	char classname[100];
	if(hwnd)
	{
		GetWindowTextA(hwnd, caption, 100);
		::GetClassNameA(hwnd, classname, 100);
		TWindow *window = new TWindow(hwnd);
		window->Index = list->Count;
		list->Add((TObject*)window);
		return true;
	}
	return true;
}
//---------------------------------------------------------------------------
String TComboBoxWindow::GetComboBoxText()
{
	char text[1000];
	SendMessage(CB_GETLBTEXT, 0, (LPARAM)text);
	return (AnsiString)text;
}
//---------------------------------------------------------------------------
String TComboBoxWindow::GetItem(int index)
{
	CHAR text[1000];
	SendMessage(CB_GETLBTEXT, (WPARAM)index, (LPARAM)text);
	return (String)text;
}
//---------------------------------------------------------------------------
void TComboBoxWindow::SetComboBoxText(String text)
{
	Childs[0].Text = text;
}
//---------------------------------------------------------------------------
int TComboBoxWindow::GetComboBoxIndex()
{
	return SendMessage(CB_GETCURSEL, 0, 0);
}
//---------------------------------------------------------------------------
void TComboBoxWindow::SetComboBoxIndex(int index)
{
	SendMessage(CB_SETCURSEL, index, 0);
}
//---------------------------------------------------------------------------
int TComboBoxWindow::FindItem(String item)
{
	return SendMessage(CB_FINDSTRING, -1, (LPARAM)item.c_str());
}
//---------------------------------------------------------------------------
int TComboBoxWindow::SelectString(String item, int index)
{
	return SendMessage(CB_SELECTSTRING, index, (LPARAM)item.c_str());
}
//---------------------------------------------------------------------------
DWORD TWindow::SendMessage(DWORD message, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(Handle, message, wParam, lParam);
}
//---------------------------------------------------------------------------
DWORD TWindow::PostMessage(DWORD message, WPARAM wParam, LPARAM lParam)
{
	return ::PostMessage(Handle, message, wParam, lParam);
}
//---------------------------------------------------------------------------
void TWindow::SetVisible(bool visible)
{
	if(visible)
		ShowWindow(Handle, SW_SHOW);
	else
		ShowWindow(Handle, SW_HIDE);
}
//---------------------------------------------------------------------------
bool TWindow::GetVisible()
{
	return IsWindowVisible(Handle);
}
//---------------------------------------------------------------------------
bool TWindow::operator == (int handle)
{
	return Handle == (HWND)handle;
}
//---------------------------------------------------------------------------
bool TWindow::operator != (int handle)
{
	return Handle != (HWND)handle;
}
//---------------------------------------------------------------------------
bool TWindow::operator == (HWND handle)
{
	return Handle == handle;
}
//---------------------------------------------------------------------------
bool TWindow::operator != (HWND handle)
{
	return Handle != handle;
}
//---------------------------------------------------------------------------
TWindow TWindow::GetChildByParentClassIndex(String className, int index)
{
	int c = 0;
	for (int t=0; t<ChildsCount; t++)
	{
		if(!AnsiCompareText(Childs[t].Parent.ClassName, className) && (c++==index))
		{
			return Childs[t];
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
__fastcall TWindow::operator String() const
{
	return IntToHex((int)Handle, 8);
}
//---------------------------------------------------------------------------
__fastcall TWindow::operator HWND() const
{
	return Handle;
}
//---------------------------------------------------------------------------
TCanvas* TWindow::GetCanvas()
{
	if(!FCanvas)
	{
		FCanvas = new TCanvas;
		FCanvas->Handle = GetDCEx(Handle, 0, 0);
	}
	return FCanvas;
}
//---------------------------------------------------------------------------
void TWindow::Highlight()
{
	HDC hDC = GetDC(HWND_DESKTOP);
	DrawFocusRect(hDC, &Rect);
	ReleaseDC(Handle, hDC);
}
//---------------------------------------------------------------------------
TWindow TWindow::GetParent()
{
	return ::GetParent(Handle);
//eturn (HWND)WindowLong[GWL_HWNDPARENT];
}
//---------------------------------------------------------------------------
bool TWindow::SameProcess(HWND hWnd)
{
	return FHandle && (ProcessID == TWindow(hWnd).ProcessID);
}
//---------------------------------------------------------------------------
void TWindow::SetParent(TWindow pWnd)
{
	::SetParent(Handle, pWnd.Handle);
}
//---------------------------------------------------------------------------
int TWindow::GetWidth()
{
	return Rect.Width();
}
//---------------------------------------------------------------------------
void TWindow::SetWidth(int width)
{
	SetWindowPos(Handle, 0, 0, 0, width, Rect.Height(), SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOREPOSITION);
}
//---------------------------------------------------------------------------
int TWindow::GetHeight()
{
	return Rect.Height();
}
//---------------------------------------------------------------------------
void TWindow::SetHeight(int height)
{
	SetWindowPos(Handle, 0, 0, 0, Rect.Width(), height, SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOREPOSITION);
}
//---------------------------------------------------------------------------
void TWindow::GetHandleFromCursor()
{
	POINT cp;
	::GetCursorPos(&cp);
	Handle = WindowFromPoint(cp);
}
//---------------------------------------------------------------------------
void TWindow::SendCommand(DWORD command)
{
	SendMessage(WM_COMMAND, command, 0);
}
//---------------------------------------------------------------------------
void TWindow::PostCommand(DWORD command)
{
	PostMessage(WM_COMMAND, command, 0);
}
//---------------------------------------------------------------------------
Types::TRect TComboBoxWindow::GetComboBoxDroppedControlRect()
{
	RECT rect;
	SendMessage(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&rect);
	return Types::TRect(rect);
}
//---------------------------------------------------------------------------
COMBOBOXINFO TComboBoxWindow::GetComboBoxInfo()
{
	COMBOBOXINFO cbi;
	cbi.cbSize = sizeof(COMBOBOXINFO);
	::GetComboBoxInfo(Handle, &cbi);
	return cbi;
}
//---------------------------------------------------------------------------
TWindow TWindow::Search(LPCSTR lpSubClassName, LPCSTR lpSubWindowName, int index)
{
	TWindow all;
	bool resultCaption, resultClass;
	int count = 0;
	for (int t=0; t<all.ChildsCount; t++)
	{
		resultClass = (lpSubClassName == NULL) || all.Childs[t].ClassName.Pos(lpSubClassName);
		resultCaption = (lpSubWindowName == NULL) || all.Childs[t].Text.Pos(lpSubWindowName);
		if(resultClass && resultCaption)
		{
			if(index == count)
			{
				FHandle = all.Childs[t].Handle;
				return all.Childs[t];
			}
			count++;
		}
	}
	FHandle = NULL;
	return *this;
}
//---------------------------------------------------------------------------
void TWindow::Free()
{
	if(FChilds)
	{
		for (int t=0; t<FChilds->Count; t++)
			delete (TWindow*)FChilds->Items[t];
		delete FChilds;
		FChilds = NULL;
	}
	if(FCanvas)
	{
		ReleaseDC(Handle, FCanvas->Handle);
		delete FCanvas;
		FCanvas = NULL;
	}
}
//---------------------------------------------------------------------------
void TWindow::Refresh()
{
	Free();
}

int (*_InternalGetWindowText)(HWND, LPWSTR, int) = NULL;
WideString __fastcall TWindow::GetInternalText()
{
	if(!hUser32) hUser32 = LoadLibraryW(L"user32.dll");
	_InternalGetWindowText = (int (*)(HWND, LPWSTR, int))GetProcAddress(hUser32, "InternalGetWindowText");
	wchar_t text[1024];
	int len = _InternalGetWindowText(Handle, text, 1024);
	if(len) return WideString(text);
	return WideString("");
}

WINDOWINFO __fastcall TWindow::GetWindowInfo()
{
	WINDOWINFO wi;
	wi.cbSize = sizeof(WINDOWINFO);
	::GetWindowInfo(Handle, &wi);
	return wi;
	//TODO: Add your source code here
}

void __fastcall TWindow::SetEnable(bool value)
{
	SendMessage(WM_ENABLE, value, 0);
}
bool __fastcall TWindow::GetEnable()
{
	return IsWindowEnabled(Handle);
}

//---------------------------------------------------------------------------
initialization
{
}
//---------------------------------------------------------------------------
finalization
{
	if(hUser32) FreeLibrary(hUser32);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool __fastcall TWindow::GetIsUnicode()
{
	return IsWindowUnicode(Handle);
}

void TWindow::SwitchToThisWindow(bool fAltTab)
{
	::SwitchToThisWindow(Handle, fAltTab);
}

//---------------------------------------------------------------------------
TWindow __fastcall TWindow::GetChildBySize(int width, int height)
{
	bool result_w, result_h;
	HWND hWnd = NULL;
	TWindow result;
	do
	{
		hWnd = FindWindowEx(Handle, hWnd, NULL, NULL);
		result = hWnd;
		result_w = (width == -1) || (result.Width == width);
		result_h = (height == -1) || (result.Height == height);
		if(result_w && result_h) return result;
	}
	while(hWnd);
	return NULL;
}
//---------------------------------------------------------------------------
TWindow __fastcall TWindow::GetChildByRect(Types::TRect rect)
{
	HWND hWnd = NULL;
	do
	{
		hWnd = FindWindowEx(Handle, hWnd, NULL, NULL);
		if(TWindow(hWnd).Rect == rect) return hWnd;
	}
	while(hWnd);
	return NULL;
}
//---------------------------------------------------------------------------
int TWindow::GetCtrlID()
{
	return GetDlgCtrlID(Handle);
}
//---------------------------------------------------------------------------
TWindow __fastcall TWindow::GetChildByCtrlID(int value)
{
	for (int i=0; i<ChildsCount; i++) {
		if(Childs[i].CtrlID == value) return Childs[i];
	}
	return 0;
}
//---------------------------------------------------------------------------

void __fastcall TWindow::SetRect(Types::TRect value)
{
	SetWindowPos(Handle, 0, value.left, value.top, value.Width(), value.Height(), SWP_NOZORDER);
}
Types::TRect __fastcall TWindow::GetRect()
{
	Types::TRect rect;
	GetWindowRect(Handle, &rect);
	return rect;
}

Types::TRect __fastcall TWindow::GetClientRect()
{
	Types::TRect rect;
	::GetClientRect(Handle, &rect);
	return rect;
}

String __fastcall TWindow::GetClassName()
{
	wchar_t temp[500];
	if(!::GetClassNameW(Handle, temp, 500))
		return "";
	return String(temp);
}

DWORD __fastcall TWindow::GetThreadID()
{
	return GetWindowThreadProcessId(Handle, 0);
}

DWORD __fastcall TWindow::GetProcessID()
{
	DWORD processID;
	GetWindowThreadProcessId(Handle, &processID);
	return processID;
}

TWindow TWindow::GetDlgItem(int nIDDlgItem)
{
	return ::GetDlgItem(Handle, nIDDlgItem);
}

TWindow TWindow::SearchChild(char* className, char* caption, int index)
{
	bool cls_res, cap_res;
	int c = 0;
	for (int t=0; t<ChildsCount; t++)
	{
		cls_res = !AnsiCompareStr(className, Childs[t].ClassName) || (className == NULL);
		cap_res = !AnsiCompareStr(caption, Childs[t].Text) || (caption == NULL);
		if(cls_res && cap_res && c++ == index)
			return Childs[t];
	}
	return NULL;
}

TWindow TWindow::FindChild(wchar_t* className, wchar_t* caption, int index)
{
	HWND hWnd = NULL;
	int c = 0;
	do
	{
		hWnd = FindWindowExW(Handle, hWnd, className, caption);
	}
	while(hWnd && c++ < index);
	return hWnd;
}

void TWindow::SetForegroundWindow()
{
	::SetForegroundWindow(Handle);
}

bool __fastcall TWindow::GetIsWindow()
{
	return ::IsWindow(Handle);
}

TWindow __fastcall TWindow::GetRoot()
{
	return GetAncestor(Handle, GA_ROOT);
}

TWindow __fastcall TWindow::GetRootOwner()
{
	return GetAncestor(Handle, GA_ROOTOWNER);
}

TWindow TWindow::SearchChildByRect(Types::TRect rect)
{
	for (int t=0; t<ChildsCount; t++)
		if(Childs[t].Rect == rect) return Childs[t];
	return NULL;
}

TWindow TWindow::SearchChildBySize(int width, int height, int index)
{
	int c = 0;
	for (int t=0; t<ChildsCount; t++)
		if(Childs[t].Rect.Width() == width &&
			Childs[t].Rect.Height() == height && c++ == index)
			return Childs[t];
	return NULL;
}

TWindow TWindow::SearchChildByCtrlID(int id)
{
	for (int t=0; t<ChildsCount; t++)
		if(Childs[t].CtrlID == id)
			return Childs[t];
	return NULL;
}

TWindow TComboBoxWindow::operator =(TWindow rhw)
{
	Free();
	Handle = rhw.Handle;
	return *this;
}  

int TComboBoxWindow::AddString(AnsiString item)
{
	return SendMessage(CB_ADDSTRING, 0, (LPARAM)item.c_str());
}

int TComboBoxWindow::Delete(int index)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)index, 0);
}

int __fastcall TComboBoxWindow::GetCount()
{
	return SendMessage(CB_GETCOUNT, 0, 0);
}

void TWindow::operator = (HWND handle)
{
	Free();
	Handle = handle;
}

void TWindow::operator = (int handle)
{
	Free();
	Handle = (HWND)handle;
}

void TWindow::operator = (TWindow* pWin)
{
	Free();
	if(pWin) Handle = pWin->Handle;
}

void TWindow::operator = (TWindow pWin)
{
	Free();
	Handle = pWin.Handle;
}

void TWindow::CaptureCurrentFocus()
{
	GUITHREADINFO info;
	info.cbSize = sizeof(GUITHREADINFO);
	GetGUIThreadInfo(0, &info);
	Handle = info.hwndFocus;
}

void TWindow::CaptureForeground()
{
	GUITHREADINFO info;
	info.cbSize = sizeof(GUITHREADINFO);
	GetGUIThreadInfo(0, &info);
	Handle = info.hwndFocus;
}

TComboBoxWindow::TComboBoxWindow(TWindow wnd) : TWindow(wnd)
{
}

TComboBoxWindow::TComboBoxWindow()
{
}

void TWindow::SetWindowLongItem(int index, int item, bool value)
{
	if(!value)
	    WindowLong[index] = WindowLong[index] & (~item);
	else
		WindowLong[index] = WindowLong[index] | item;
}
bool TWindow::GetWindowLongItem(int index, int item)
{
	return WindowLong[index] & item;
}

void TWindow::HandleFormProcessID(DWORD pid)
{
	TWindow all;
	for (int i = 0; i < all.ChildsCount; i++)
	{
		if(all.Childs[i].ProcessID == pid)
		{
			Handle = all.Childs[i].Handle;
			return;
		}
	}
	Handle = NULL;
}
//------------------------------------------------------------------------------
WideString TEditWindow::GetSelText()
{
	int start=SelStart;
	int end=SelEnd;
	WideString ws=Text;
	if( ::SendMessageW(Handle,EM_GETOPTIONS,0,0)!=0 ) //RichEdid only
	{
		//ws=ws.ReplaceAll("\r\n","\n");
	}
	return ws.SubString(start+1,end-start);
}
//------------------------------------------------------------------------------
void TEditWindow::SetSelText(WideString value)
{
	::SendMessageW(Handle, EM_REPLACESEL, true, (LPARAM)value.c_bstr());
}
//------------------------------------------------------------------------------
int TEditWindow::GetLineStart()
{
	return ::SendMessageW(Handle, EM_LINEINDEX , -1, 0);
}
//------------------------------------------------------------------------------
WideString TEditWindow::GetLineText()
{
	wchar_t buffer[500];
	buffer[0]=500;
	int start=0, end=0;
	::SendMessageW(Handle, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	int indexStartLine=::SendMessageW(Handle, EM_LINEFROMCHAR, start, 0);
	int indexEndLine=::SendMessageW(Handle, EM_LINEFROMCHAR, end, 0);
	if( indexStartLine!=indexEndLine ) return L"";
	int len=::SendMessageW(Handle, EM_GETLINE, indexStartLine, (LPARAM)buffer);
	buffer[len]=0;
	return WideString(buffer);
}
//------------------------------------------------------------------------------
int TEditWindow::GetSelStart()
{
	int start=0, end=0;
	::SendMessageW(Handle, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	/*if( SendMessageW(Handle,EM_GETOPTIONS,0,0)!=0 ) //RichEdid only
	{
		int indexStartLine=SendMessageW(Handle,EM_LINEFROMCHAR,start,0);
		int indexEndLine=SendMessageW(Handle,EM_LINEFROMCHAR,end,0);
		if( indexStartLine!=indexEndLine )
		{
			start+=indexStartLine;
			end+=indexEndLine;
		}
	}*/
	return start;
}
//------------------------------------------------------------------------------
int TEditWindow::GetSelEnd()
{
	int start=0, end=0;
	::SendMessageW(Handle, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	/*if( SendMessageW(Handle,EM_GETOPTIONS,0,0)!=0 ) //RichEdid only
	{
		int indexStartLine=SendMessageW(Handle,EM_LINEFROMCHAR,start,0);
		int indexEndLine=SendMessageW(Handle,EM_LINEFROMCHAR,end,0);
		if( indexStartLine!=indexEndLine )
		{
			start+=indexStartLine;
			end+=indexEndLine;
		}
	}*/
	return end;
}
//------------------------------------------------------------------------------
void TEditWindow::SetSel(int start, int end)
{
	/*if( SendMessageW(Handle,EM_GETOPTIONS,0,0)!=0 ) //RichEdid only
	{
		int indexStartLine=SendMessageW(Handle,EM_LINEFROMCHAR,start,0);
		int indexEndLine=SendMessageW(Handle,EM_LINEFROMCHAR,end,0);
		if( indexStartLine!=indexEndLine )
		{
			start-=indexStartLine;
			end-=indexEndLine;
		}
	}*/
	::SendMessageW(Handle,EM_SETSEL,start,end);
}
//------------------------------------------------------------------------------
TEditWindow::TEditWindow(HWND hWnd)
{
	Handle = hWnd;
}
//------------------------------------------------------------------------------
TEditWindow::~TEditWindow()
{
}
//------------------------------------------------------------------------------
AnsiString TEditWindow::GetFontName()
{
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	HFONT hFont = (HFONT)SendMessage(WM_GETFONT, NULL, NULL);
	GetObject(hFont, sizeof(LOGFONT), &lf);
	return lf.lfFaceName;
}

void TEditWindow::Paste()
{
	SendMessage(WM_PASTE, WM_NULL, NULL);
}

DWORD TComboBoxWindow::GetItemData(int index)
{
	return SendMessage((UINT)CB_GETITEMDATA, index, 0);
}
void TComboBoxWindow::SetItemData(int index, DWORD value)
{
	SendMessage((UINT)CB_SETITEMDATA, index, value);
}

bool TWindow::GetStayOnTop()
{
	return StyleEx & WS_EX_TOPMOST;
}
void TWindow::SetStayOnTop(bool value)
{
	SetWindowPos(Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}

void TWindow::SetStyleEx(long style)
{
	WindowLong[GWL_EXSTYLE] = style;
}
long TWindow::GetStyleEx()
{
	return WindowLong[GWL_EXSTYLE];
}

#include <Richedit.h>
AnsiString TEditWindow::GetRichFontName()
{
	//HANDLE filemapping=CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,sizeof(CHARFORMAT),"TestMirEmad");

	CHARFORMAT cf;
	ZeroMemory(&cf,sizeof(CHARFORMAT));
	cf.cbSize=sizeof(CHARFORMAT);
	//
	SIZE_T count;
	//
	HANDLE hPrrocess=OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,FALSE,ProcessID);
	LPVOID pMem=VirtualAllocEx(hPrrocess,NULL,sizeof(CHARFORMAT),MEM_COMMIT,PAGE_READWRITE);
	WriteProcessMemory(hPrrocess,pMem,&cf,sizeof(CHARFORMAT),&count);
	::SendMessage(Handle,EM_GETCHARFORMAT,SCF_SELECTION,(LPARAM)pMem);
	ReadProcessMemory(hPrrocess,pMem,&cf,sizeof(CHARFORMAT),&count);
	VirtualFreeEx(hPrrocess,pMem,0,MEM_RELEASE);
	CloseHandle(hPrrocess);
	return cf.szFaceName;
}
//------------------------------------------------------------------------------
bool TWindow::GetNoActivate()
{
	return WindowLongItem[GWL_EXSTYLE][WS_EX_NOACTIVATE];
}
//------------------------------------------------------------------------------
void TWindow::SetNoActivate(bool value)
{
	WindowLongItem[GWL_EXSTYLE][WS_EX_NOACTIVATE] = value;
}
//------------------------------------------------------------------------------
TWindow TWindow::DeepSearchChild(char* className, char* caption, int index)
{
	bool cls_res, cap_res;
	TWindow result;
	for (int i=0; i<ChildsCount; i++) {
		TWindow wnd = Childs[i];
		if(wnd.ChildsCount)
		{
			result = wnd.DeepSearchChild(className, caption, index);
			if(result) return result;
		}
		cls_res = !AnsiCompareStr(className, wnd.ClassName) || (className == NULL);
		cap_res = !AnsiCompareStr(caption, wnd.Text) || (caption == NULL);
		if(cls_res && cap_res) return wnd;
	}
	return NULL;
}
//------------------------------------------------------------------------------
String TWindow::GetBrefInfo()
{
	String className = ClassName;
	String text = Text;
	if(text.Length())
		text = className + " \"" + text + "\"";
	else
		text = className;

	text += " 0x" + (String)(*this) + " ID:" + (String)CtrlID;
	return text;
}
//------------------------------------------------------------------------------
/*
int TComboBoxWindow::SearchItem(String item)
{
	for (int i=0; i<Count; i++) {
		if(Item[i] == item) return i;
	}
	return -1;
}*/
//------------------------------------------------------------------------------

