//---------------------------------------------------------------------------

#ifndef winutilsH
#define winutilsH
//----------------------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Shlwapi.h>
#include <Shellapi.h>
#include <WSDLIntf.hpp>
#include <winbase.h>
#include <wchar.h>
#include <stdio.h>
#include <Graphics.hpp>

#pragma link "winutils"

#ifndef initialization
#define initialization class __initialization{public:__initialization();}__TEMP;__initialization::__initialization()
#define finalization class __finalization{public:~__finalization();}__TEMPF;__finalization::~__finalization()
#endif
//----------------------------------------------------------------------------------------
//class TForm;

class TWindow
{
private:
	HWND FHandle;
	void SetHandle(HWND handle);
	void Init();
	long FWindowLong;
	void SetWindowLong(int index, long newLong);
	long GetWindowLong(int index);
	void SetWindowLongItem(int index, int item, bool value);
	bool GetWindowLongItem(int index, int item);
//	long FStyle;
	void SetStyle(long style);
	long GetStyle();
	void SetStyleEx(long style);
	long GetStyleEx();
	long FWinProc;
	void SetWinProc(long proc);
	TWindow GetParent();
	void SetParent(TWindow pWnd);
	void SetText(WideString text);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	TWindow GetChilds(int index);
	TWindow GetChildByClass(String className);
	TWindow GetChildByClassIndex(String className, int index);
	TWindow GetChildByParentClassIndex(String className, int index);
	TList *FChilds;
	void EnumChildWindows();
	int GetChildsCount();
	WideString GetText();
	void SetVisible(bool visible);
	bool GetVisible();
	TCanvas *FCanvas;
	TCanvas *GetCanvas();
	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);
	WideString __fastcall GetInternalText();
	WINDOWINFO __fastcall GetWindowInfo();
	void __fastcall SetEnable(bool value);
	bool __fastcall GetEnable();
	bool __fastcall GetIsUnicode();
	TWindow __fastcall GetChildBySize(int width, int height);
	TWindow __fastcall GetChildByRect(Types::TRect rect);
	int GetCtrlID();
	TWindow __fastcall GetChildByCtrlID(int value);
	void __fastcall SetRect(Types::TRect value);
	Types::TRect __fastcall GetRect();
	Types::TRect __fastcall GetClientRect();
	String __fastcall GetClassName();
	DWORD __fastcall GetThreadID();
	DWORD __fastcall GetProcessID();
	bool __fastcall GetIsWindow();
	TWindow __fastcall GetChildByText(AnsiString text);
	TWindow __fastcall GetRoot();
	TWindow __fastcall GetRootOwner();
	bool GetStayOnTop();
	void SetStayOnTop(bool value);
	bool GetNoActivate();
	void SetNoActivate(bool value);
protected:
	void Free();

public:
	TWindow();
	TWindow(HWND hWnd);
	TWindow(TWindow* pWnd);
	TWindow(const TWindow &win);
	TWindow(int hWnd);
	TWindow SearchChild(char* className, char* caption, int index = 0);
	TWindow DeepSearchChild(char* className, char* caption, int index = 0);
	TWindow SearchChildBySize(int width, int height, int index = 0);
	TWindow FindChild(wchar_t* className, wchar_t* caption, int index = 0);
	void GetHandleFromCursor();
	~TWindow();
	TWindow(WCHAR* lpClassName, WCHAR* lpWindowName);
	int Index;
	DWORD SendMessage(DWORD message, WPARAM wParam, LPARAM lParam);
	DWORD PostMessage(DWORD message, WPARAM wParam, LPARAM lParam);
	bool operator == (int handle);
	bool operator != (int handle);
	bool operator == (HWND handle);
	bool operator != (HWND handle);
	void operator = (HWND handle);
	void operator = (int handle);
	void operator = (TWindow* pWin);
	void operator = (TWindow pWin);
	__fastcall operator String() const;
	__fastcall operator HWND() const;
	void Highlight();
	bool SameProcess(HWND hWnd);
	void SendCommand(DWORD command);
	void PostCommand(DWORD command);
	TWindow& Find(WCHAR* lpClassName, WCHAR* lpWindowName);
	TWindow Search(LPCSTR lpSubClassName, LPCSTR lpSubWindowName, int index = 0);
	void Refresh();
	void SwitchToThisWindow(bool fAltTab);
	TWindow GetDlgItem(int nIDDlgItem);
	void SetForegroundWindow();
	TWindow SearchChildByRect(Types::TRect);
	TWindow SearchChildByCtrlID(int id);
	void CaptureForeground();
	void CaptureCurrentFocus();
	void HandleFormProcessID(DWORD pid);
	String GetBrefInfo();

	__property HWND Handle = {read=FHandle, write=SetHandle};
	__property WideString Text = {read=GetText, write=SetText};
	__property long WindowLong[int index] = {read=GetWindowLong, write=SetWindowLong};
    __property bool WindowLongItem[int index][int item] = {read=GetWindowLongItem, write=SetWindowLongItem};
	__property long Style = {read=GetStyle, write=SetStyle};
	__property long StyleEx = {read=GetStyleEx, write=SetStyleEx};
	__property long WinProc = {read=FWinProc, write=SetWinProc};
	__property TWindow Parent = {read=GetParent, write=SetParent};
	__property TWindow Childs[int index] = {read=GetChilds};
	__property TWindow ChildByClass[String className] = {read=GetChildByClass};
	__property TWindow ChildByClassIndex[String className][int index] = {read=GetChildByClassIndex};
	__property TWindow ChildByParentClassIndex[String className][int index] = {read=GetChildByParentClassIndex};
	__property TWindow ChildBySize[int width][int height] = {read=GetChildBySize};
	__property TWindow ChildByRect[Types::TRect rect] = {read=GetChildByRect};
	__property TWindow ChildByCtrlID[int ctrlID] = {read=GetChildByCtrlID};
	__property int ChildsCount = {read=GetChildsCount};
	__property bool Visible = {read=GetVisible, write=SetVisible};
	__property TCanvas *Canvas = {read=GetCanvas};
	__property int Width = {read=GetWidth, write=SetWidth};
	__property int Height = {read=GetHeight, write=SetHeight};
	__property WideString InternalText  = { read=GetInternalText };
	__property WINDOWINFO WindowInfo  = { read=GetWindowInfo };
	__property bool Enable  = { read=GetEnable, write=SetEnable };
	__property bool IsUnicode  = { read=GetIsUnicode };
	__property int CtrlID  = { read=GetCtrlID };
	__property AnsiString ClassName  = { read=GetClassName };
	__property Types::TRect Rect  = { read=GetRect, write=SetRect };
	__property Types::TRect ClientRect  = { read=GetClientRect};
	__property DWORD ThreadID  = { read=GetThreadID };
	__property DWORD ProcessID  = { read=GetProcessID };
	__property bool IsWindow  = { read=GetIsWindow };
	__property TWindow ChildByText[AnsiString text]  = { read=GetChildByText };
	__property TWindow Root  = { read=GetRoot };
	__property TWindow RootOwner  = { read=GetRootOwner };
	__property bool StayOnTop  = { read=GetStayOnTop, write=SetStayOnTop };
	__property bool NoActivate  = { read=GetNoActivate, write=SetNoActivate };
};
//---------------------------------------------------------------------------
class TComboBoxWindow : public TWindow
{
private:
	String GetComboBoxText();
	void SetComboBoxText(String text);
	int GetComboBoxIndex();
	void SetComboBoxIndex(int index);
	Types::TRect GetComboBoxDroppedControlRect();
	COMBOBOXINFO GetComboBoxInfo();
	int __fastcall GetCount();
	DWORD GetItemData(int index);
	void SetItemData(int index, DWORD value);
	String GetItem(int index);

public:
	TComboBoxWindow();
	TComboBoxWindow(TWindow wnd);
	TWindow operator =(TWindow rhw);
	int AddString(AnsiString item);
	int Delete(int index);
	int FindItem(String item);
	int SelectString(String item, int index=-1);
	int Search(String item);
	__property String Text = {read=GetComboBoxText, write=SetComboBoxText};
	__property int ItemIndex = {read=GetComboBoxIndex, write=SetComboBoxIndex};
	__property Types::TRect DroppedControlRect = {read=GetComboBoxDroppedControlRect};
	__property COMBOBOXINFO ComboBoxInfo = {read=GetComboBoxInfo};
	__property int Count  = { read=GetCount };
	__property DWORD ItemData[int index] = { read=GetItemData, write=SetItemData };
	__property String Item[int index] = { read=GetItem };
};

class TEditWindow : public TWindow
{
private:
	WideString GetSelText();
	void SetSelText(WideString value);
	int GetSelStart();
	int GetSelEnd();
	int GetLineStart();
	WideString GetLineText();
	AnsiString GetRichFontName();
	AnsiString GetFontName();

public:
	TEditWindow(HWND hWnd = NULL);
	TEditWindow(const TEditWindow &wnd):TWindow(wnd){};
	~TEditWindow();
	void SetSel(int start, int end);
	void Paste();
	__property WideString SelText = { read=GetSelText, write=SetSelText };
	__property int SelStart = { read=GetSelStart };
	__property int SelEnd = { read=GetSelEnd };
	__property int LineStart = { read=GetLineStart };
	__property WideString LineText = { read=GetLineText };
	__property AnsiString FontName = { read=GetFontName };
	__property AnsiString RichFontName = { read=GetRichFontName };
};
#endif

