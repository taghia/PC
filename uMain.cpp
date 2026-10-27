// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "clipbrd.hpp"
#include "winutils.h"
#include "uRun.h"
#include "uChildLock.h"
#include "array.h"
#include "uTools.h"
#include "uAddBtn.h"
#include "uUserActions.h"
#include "text.h"
#include "shamsidate.h"
#include "uSearch.h"
#include <Dbt.h>
#include "uConsole.h"
#include "uRename.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

// ---------------------------------------------------------------------------
String quotedStr(String text) {
	return "\"" + text + "\"";
}
class TpcPage;
class TTab : public TTabSheet {
	void __fastcall onTabEnter(TObject *Sender) {
		TTab *tab = (TTab*)Sender;
		if (view->Directory == "")
			view->Directory = dir;
		if (frmMain->Focused())
			tab->SetFocus();
		if (view && view->Focused())
			view->TreeOptions->MiscOptions << toEditOnClick;
	}

	void __fastcall view_onEnter(TObject *Sender) {
	}

	void __fastcall onPathKeyPress(TObject *Sender, wchar_t &Key) {
		if (Key == VK_RETURN) {
			Key = 0;
			view->Directory = path->Text;
			view->SetFocus();
		}
	}

	void __fastcall onDriveClick(TObject* Sender, int index) {
		TGrpButtonItem *button = drive->Items->Items[index];
		view->Directory = button->Caption + ":\\";
		view->SetFocus();
	}

	void setActiveDrive() {
		String driveStr = view->Directory;
		driveStr = driveStr.LowerCase();
		for (int i = 0; i < drive->Items->Count; i++) {
			if (drive->Items->Items[i]->Caption.LowerCase() == driveStr[1]) {
				drive->ItemIndex = i;
				break;
			}
		}
	}

	String extractCaption(String dir) {
		if (dir.IsEmpty())
			return "[empty]";
		if (dir.LastChar()[0] == L'\\')
			dir.SetLength(dir.Length() - 1);
		if (dir.LastChar()[0] == ':')
			return dir;
		return ExtractFileName(dir);
	}

	void __fastcall onDirChange(TObject *Sender) {
		path->Text = view->Directory;
		setActiveDrive();
		setCaption();
		frmMain->updateNavigationBtns();
	}

	void __fastcall onPathButtonClick(TObject *Sender) {
		frmMain->popPath->Tag = (int)view;
	}
	text m_dir;
	text get_dir()
	{
		if(view->Directory.Length()) return view->Directory;
		return m_dir;
	}
public:
	__property text dir = {read=get_dir, write=m_dir};
	TTab() : TTabSheet((TComponent*)NULL) {
		// OnEnter = onTabEnter;
		OnShow = onTabEnter;
	}

	void setCaption(String dir = "") {
		String display;
		if (dir == "")
			dir = view->Directory;
		TIcon *icon = getFileIcon(dir, &display);
		if (ImageIndex > -1)
			PageControl->Images->ReplaceIcon(ImageIndex, icon);
		else
			ImageIndex = PageControl->Images->AddIcon(icon);
		delete icon;
		// Caption = extractCaption(view->Directory);
		Caption = display == "" ? dir : display;
	}

	void __fastcall path_onMouseActivate(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y, int HitTest,
		TMouseActivate &MouseActivate) {
		TButtonedEdit *btn = (TButtonedEdit*)Sender;
		frmMain->popPath->Tag = (int)((TTab*)btn->Parent)->view;
	}

	void __fastcall contextMenuCmdCallback(TNamespace* Namespace, WideString Verb,
		int MenuItemID, bool &Handled) {
		text help = Namespace->ContextMenuItemHelp(MenuItemID);
		if(help.contains("Ejects")) {
			this->view->globalMon->deleteRemovables();
			Application->ProcessMessages();
		}
	}
	void __fastcall contextMenuAfterCmdCallback(TNamespace* Namespace, WideString Verb,
		int MenuItemID, bool Successful)
	{
		text help = Namespace->ContextMenuItemHelp(MenuItemID);
		if(help.contains("Ejects")){
			if(TFileView::globalMon) TFileView::globalMon->refresh();
			SendMessage(Application->MainForm->Handle, WM_DEVICECHANGE, DBT_DEVICEREMOVECOMPLETE, 0);
		}
	}

	void __fastcall onContextPopup(System::TObject* Sender,
		const Types::TPoint &MousePos, bool &Handled) {
		int index = drive->IndexOfButtonAt(MousePos.x, MousePos.y);
		TGrpButtonItem *button = drive->Items->Items[index];
		TNamespace *ns = new TNamespace(button->Caption + ":\\");
		GetCursorPos(&MousePos);
		ns->ShowContextMenu(drive, &contextMenuCmdCallback, NULL,
			&contextMenuAfterCmdCallback, (TPoint*) & MousePos, 0, "");
		delete ns;
	}

	void createDriveButtons() {
		int count = getDrivesCount();
		drive->Items->Clear();
		drive->TabStop = false;
		drive->Height = 20;
		drive->ButtonHeight = 18;
		drive->ButtonWidth = 40;
		drive->OnButtonClicked = onDriveClick;
		drive->ButtonOptions << gboGroupStyle;
		drive->OnContextPopup = onContextPopup;
		if (!drive->Images) {
			drive->Images = new TImageList(this);
			drive->Images->DrawingStyle = dsTransparent;
			drive->Images->ColorDepth = cd32Bit;
		}
		drive->Images->Clear();

		for (int di = 0; di < count; di++) {
			TGrpButtonItem* item = drive->Items->Add();

			char driveStr[] = {
				getDriveStr(di), ':', '\\', 0
			};
			item->Caption = driveStr[0];
			// TIcon *icon = getShellIcon(getDriveIconIndex(driveStr));
			TIcon *icon = getFileIcon(driveStr);
			int iconIndex = drive->Images->AddIcon(icon);
			delete icon;
			item->ImageIndex = iconIndex;
			// item->Hint = getDriveLabel(item->Caption);
		}
	}

	void __fastcall onChange(TBaseVirtualTree* Sender, PVirtualNode Node)
	{
		frmMain->updateStatusBar();
	}

	void __fastcall onMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y) {
	}

	void create(String dir) {
		ImageIndex = -1;
		this->dir = dir;
		drive = new TButtonGroup(this);
		drive->Parent = this;
		drive->BevelInner = bvNone;
		drive->BevelOuter = bvNone;
		drive->BorderStyle = bsNone;
		createDriveButtons();

		path = new TButtonedEdit(this);
		path->Parent = this;
		path->Align = alTop;
		path->Height = 20;
		path->TabStop = 0;
		path->Images = frmMain->ilPath; //new TImageList(this);
		path->Images->ColorDepth = cd32Bit;
		path->OnKeyPress = onPathKeyPress;
		path->OnMouseActivate = path_onMouseActivate;
		// path->OnRightButtonClick = onPathButtonClick;
		//TIcon *icon = getShellIcon(133);
		path->RightButton->ImageIndex = 0; //path->Images->AddIcon(icon);
		//delete icon;
		path->RightButton->Visible = true;
		path->RightButton->DropDownMenu = frmMain->popPath;
		// path->BorderStyle = bsNone;
		path->AlignWithMargins = true;
		path->Margins->Left = 0;
		path->Margins->Right = 0;
		// path->RightButton->DropDownMenu = new TPopupMenu(this);
		// for (int m=0; m<frmMain->popPath->Items->Count; m++) {
		// TMenuItem *mi = new TMenuItem(path->RightButton->DropDownMenu);
		// mi->Caption = frmMain->popPath->Items->Items[m]->Caption;
		// mi->OnClick = frmMain->popPath->Items->Items[m]->OnClick;
		// path->RightButton->DropDownMenu->Items->Add(mi);
		// }
		// path->RightButton->DropDownMenu->Tag = (int)this;

		drive->Align = alTop;

		view = new TFileView(this);
		view->Align = alClient;
		view->Parent = this;
		view->onDirChange = onDirChange;
		view->onNotify = frmMain->onNotify;
		view->OnEnter = frmMain->onViewEnter;
		view->OnExit = frmMain->onViewExit;
		view->OnMouseUp = onMouseUp;
		view->OnFocusChanged = frmMain->onFocusChanged;
		view->OnKeyPress = frmMain->onKeyPress;
		view->OnKeyDown = frmMain->onKeyDown;
		view->OnKeyUp = frmMain->onKeyUp;
		view->OnChange = onChange;
	}

	TFileView *view;
	TButtonGroup *drive;
	TButtonedEdit *path;

	void load(TIniFile *ini, String section) {
		String dir = ini->ReadString(section, "dir", "C:\\");
		if (dir == "")
			dir = "C:\\";
		create(dir);
		setCaption(dir);
	}

	void save(TIniFile *ini, String section) {
		String dir = view->Directory;
		if (dir == "")
			dir = this->dir;
		ini->WriteString(section, "dir", dir);
	}
};

// ---------------------------------------------------------------------------
// #include <shlwapi.h>
// #pragma link "shlwapi.lib"
class TpcPage : public TPcArray<TTab> {
private:
	TTab *activeTab;

public:
	TTab *tab() {
		return(TTab*)page->ActivePage;
	}

	void __fastcall onContextPopup(System::TObject* Sender,
		const Types::TPoint &MousePos, bool &Handled) {
		Handled = 1;
		activeTab = 0;
		activeTab = NULL;
		for (int pi = 0; pi < page->PageCount; pi++) {
			TRect rect = page->TabRect(pi);
			if (PtInRect(rect, MousePos)) {
				Handled = 0;
				activeTab = (TTab*)page->Pages[pi];
			}
		}
	}

	void __fastcall closeTabCmd(System::TObject* Sender) {
		if (page->PageCount > 1)
			closeTab(activeTab);
	}

	TPageControl *page;

	TpcPage(TPageControl *page);

	void addTab(String dir, bool activate = false) {
		TTab &tab = add();
		tab.PageControl = page;
		tab.Parent = page;
		tab.create(dir);
		// tab.OnMouseDown = onMouseUp;
		if (activate)
			page->ActivePage = &tab;
		tab.setCaption(dir);
	}

	void closeTab(TTab *tab = NULL) {
		if (count <= 1)
			return;
		if (!tab)
			tab = (TTab*)page->ActivePage;
		tab->Parent = NULL;
		remove(*tab);
	}

	void save(TIniFile *ini) {
		ini->WriteInteger(page->Name, "TabCount", count);
		for (int ti = 0; ti < count; ti++) {
			String section = page->Name + "-Tab" + String(ti);
			items[ti].save(ini, section);
		}
	}

	void load(TIniFile *ini) {
		int tabCount = ini->ReadInteger(page->Name, "TabCount", 1);
		if (tabCount == 0)
			tabCount = 1;
		for (int ti = 0; ti < tabCount; ti++) {
			String section = page->Name + "-Tab" + String(ti);
			TTab &tab = add();
			tab.Parent = page;
			tab.PageControl = page;
			tab.Tag = ti;
			tab.load(ini, section);
		}
	}

	TFileView* active() {
		for (int ti = 0; ti < count; ti++) {
			if (items[ti].view->Focused())
				return items[ti].view;
		}
		return NULL;
	}

	void setNoActivate(bool value) {
		for (int ti = 0; ti < count; ti++) {
			TWindow(items[ti].view->Handle).NoActivate = value;
		}
	}

	void updateDrives() {
		for (int ti = 0; ti < count; ti++) {
			items[ti].createDriveButtons();
			// if(!PathFileExistsW(items[ti].view->Directory.c_str()))
			if (!DirectoryExists(items[ti].dir)) {
				if (count == 1)
					items[ti].view->Directory = "C:\\";
				else {
					TTab &tab = items[ti];
					closeTab(&tab);
					ti--;
				}
			}
		}
	}
};

TpcPage::TpcPage(TPageControl *pageControl) : TPcArray<TTab>()
{
	page = pageControl;
	page->TabStop = false;
	page->Images = new TImageList(page);
	page->Images->ColorDepth = cd32Bit;
	page->PopupMenu = new TPopupMenu(page);
	TMenuItem *mi = new TMenuItem(page->PopupMenu);
	mi->OnClick = closeTabCmd;
	mi->Caption = "Close Tab";
	mi->ShortCut = TextToShortCut("Ctrl+F4");
	page->PopupMenu->Items->Add(mi);
	mi = new TMenuItem(page->PopupMenu);
	mi->Action = frmMain->actNewTab;
	page->PopupMenu->Items->Add(mi);
	page->OnContextPopup = onContextPopup;
}

// ---------------------------------------------------------------------------
class TpcToolBar : public TToolBar {
private:
	bool updating;
public:
	__fastcall TpcToolBar(TComponent* owner) : TToolBar(owner)
	{
		updating = false;
	}
	__fastcall ~TpcToolBar(){}
	virtual void __fastcall AlignControls(Controls::TControl* AControl, Types::TRect &Rect)
	{
		//if(updating) return;
		TToolBar::AlignControls(AControl, Rect);
	}
	virtual void __fastcall Invalidate(void)
	{
		if(updating) return;
		TToolBar::Invalidate();
	}
	void beginUpdate();
	void endUpdate();
};
// ---------------------------------------------------------------------------
class TpcButton : public TToolButton {
protected:
	DYNAMIC void __fastcall Click(void)
	{
		TToolButton::Click();
	}
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight)
	{
		TToolButton::SetBounds(ALeft, ATop, AWidth, AHeight);
    }

public:
	__fastcall TpcButton(TComponent *owner) : TToolButton(owner)
	{

	}
	void beginUpdate()
	{
		BeginUpdate();
	}
	void endUpdate()
	{
		EndUpdate();
	}
};
// ---------------------------------------------------------------------------
void TpcToolBar::beginUpdate()
{
	updating = true;
//	for (int bi=0; bi<ButtonCount; bi++) {
//		TpcButton *btn = (TpcButton*)Buttons[bi];
//		btn->beginUpdate();
//	}
}
// ---------------------------------------------------------------------------
void TpcToolBar::endUpdate()
{
	updating = false;
//	for (int bi=0; bi<ButtonCount; bi++) {
//		TpcButton *btn = (TpcButton*)Buttons[bi];
//		btn->endUpdate();
//	}
	Invalidate();
	Realign();
}
// ---------------------------------------------------------------------------
class TUserAction : public TAction {
	String getFolderPath(int clsid) {
		wchar_t path[MAX_PATH];
		//SHGetSpecialFolderPathW(frmMain->Handle, path, clsid, false);
		SHGetFolderPathW(frmMain->Handle, clsid, NULL, SHGFP_TYPE_CURRENT, path);
		return path;
	}

	void set_path(text path) {
		m_path = path;
		if(path.contains("%"))
			clsid = frmMain->getCLSID(path.subfind("%", "%"));
		else
			clsid = 0;
	}

	text get_path() {
		if (clsid)
		{
			return m_path.replace("%", "%", getFolderPath(clsid), true);
		}
		return m_path;
	}

	String get_clsid_path() {
		return m_path;
	}

	text m_path;
	TStringList *slAccept;
	void set_accept(text value)
	{
		slAccept->Delimiter = ';';
		slAccept->DelimitedText = value;
		slAccept->Sort();
	}
	text get_accept()
	{
		if(!slAccept->Count) slAccept->Add("*.*");
		return slAccept->DelimitedText;
	}
public:
	TUserAction() : TAction(NULL) {
		asButton = true;
		clsid = 0;
		button = 0;
		separator = false;
		m_accept = "*.*";
		acceptFile = true;
		acceptFolder = true;
		slAccept = new TStringList;
	}
	__fastcall ~TUserAction() {
		delete slAccept;
		if (button) {
			button->Action = NULL;
			button->Parent = NULL;
			delete button;
		}
	}
	// int iconIndex;
	int clsid;
	String name;
	String category;
	bool asButton;
	bool separator;
	text m_accept;
	bool acceptFile, acceptFolder;
	bool isFileAccepted(text file)
	{
		file = file.lowercase();
		for (int i = 0; i < slAccept->Count; i++) {
			text pattern = slAccept->Strings[i];
			if(pattern == "*.*") pattern = "*";
			if(file.wciCompare(pattern.lowercase())) return true;
		}
		return false;
	}
	__property text path = {
		write = set_path, read = get_path
	};
	__property String clsid_path = {
		read = get_clsid_path
	};
	__property text accept = {
		read = get_accept, write=set_accept
	};
	TpcButton *button;


	String cmdLine;
};
// ---------------------------------------------------------------------------
text extractFace(text file)
{
	return ChangeFileExt(ExtractFileName(ExcludeTrailingBackslash(file)), "");
}
// ---------------------------------------------------------------------------
text renderParam(text param, bool exec_prompt = true)
{
	bool activeAvailable = frmMain->activeView()->getFileCount()
		&& frmMain->activeView()->FocusedNode;
	bool inactiveAvailable = frmMain->inactiveView()->getFileCount()
		&& frmMain->inactiveView()->FocusedNode;

	text prompt = param.subfind("%PROMPT(", ")");
	if (!prompt.empty() && exec_prompt) {
		prompt = InputBox("Power Commander", prompt, "");
	}
	param = param.replace("%PROMPT(", ")%", prompt, true);

//	TStringList *items = new TStringList;
//	frmMain->activeView()->GetSelectList(items, true);
    array list = frmMain->activeView()->getSelectList(true);
	text delim = param.subfind("%FILES(", ")");
	//items->Delimiter = ' ' ;
	//items->DelimitedText;
    if(delim.empty())
		param = param.replace("%FILES%", list.getDelimitedText(' '));
    else
		param = param.replace("%FILES(", ")%", list.implode(delim), true);

	param = param.replace("%SDATE%", text(TShamsiDate(Now()).ShamsiString).replace("/", "-"));
	param = param.replace("%DATE%", text(Now().DateString()).replace("/", "-"));

	param = param.replace("%DIRFACE%", extractFace(frmMain->activeView()->Directory));

	text suffix = param.subfind("%DIR(", ")%");
    if(suffix.empty())
		param = param.replace("%DIR%", frmMain->activeView()->Directory);
    else
    	param = param.replace("%DIR(", ")%", list.implode(suffix) + suffix);

	param = param.replace("%DIR2%",	frmMain->inactiveView()->Directory);
	if (activeAvailable) {
		param = param.replace("%FILE%",	quotedStr(frmMain->activeView()->PathFileName));
		if(list.count())
		{
			if(frmMain->activeView()->FileObject->IsDirectory())
				param = param.replace("%FACE%", ExtractFileName(list[0]));
			else
				param = param.replace("%FACE%", extractFace(list[0]));
		}
	}
	if (inactiveAvailable) {
		param = param.replace("%FILE2%", frmMain->inactiveView()->PathFileName);
	}

	//delete list;
	return param;
}
// ---------------------------------------------------------------------------
class TIconLoader : public TThread
{
private:
protected:
	void __fastcall Execute()
	{
		indexes.Length = dirList->Count;
		hints.Length = dirList->Count;
		for (int di=0; di<dirList->Count; di++) {
			String dir = dirList->Strings[di];
			String hint;
			TIcon *icon = getFileIcon(dir, &hint);
			indexes[di] = imageList->AddIcon(icon);
			hints[di] = hint;
			delete icon;
		}
	}
public:
	TImageList *imageList;
	TStringList *dirList;
	DynamicArray<int> indexes;
	DynamicArray<String> hints;
	__fastcall TIconLoader(TImageList *il) : TThread(true)
	{
		FreeOnTerminate = true;
		imageList = il;
		dirList = new TStringList;
	}
	__fastcall ~TIconLoader()
	{
		delete dirList;
	}
};
// ---------------------------------------------------------------------------
class TUserActions : public TPcArray<TUserAction> {
private:
public:
	TpcToolBar *toolbar;
	TActionList *actionList;
	TpcButton *activeButton;
	bool loading;
	bool modified;
	TStringList *categories;
	void __fastcall onActionExecute(TBasicAction *Action, bool &Handled);
	TUserActions(TpcToolBar *toolbar) {
		loading = false;
		modified = false;
		actionList = frmMain->userActions;
		// ;
		this->toolbar = toolbar;
		toolbar->Images = new TImageList(toolbar);
		actionList->Images = toolbar->Images;
		actionList->OnExecute = onActionExecute;
		toolbar->Images->ColorDepth = cd32Bit;
		toolbar->ShowHint = true;
		activeButton = 0;
		categories = new TStringList;
	}

	~TUserActions() {
		delete categories;
	}

	void __fastcall onContextPopup(System::TObject* Sender,
		const Types::TPoint &MousePos, bool &Handled) {
		activeButton = (TpcButton*)Sender;
	}

	void __fastcall onExecute(TObject *Sender) {
		SetCurrentDir(ExtractFilePath(Application->ExeName));
		TUserAction *action = (TUserAction*)Sender;
		String params = renderParam(action->cmdLine);
		if (FileExists(action->path))
			ShellExecuteW(frmMain->Handle, L"open", action->path,
				params.c_str(), L"", SW_NORMAL);
		else
			frmMain->activeView()->Directory = action->path;
	}
	void exchange(int index1, int index2)
	{
		TPcArray<TUserAction>::exchange(index1, index2);
		updateToolbar();
		modified = true;
	}
	void remove(TUserAction &act)
	{
		toolbar->beginUpdate();
		TPcArray<TUserAction>::remove(act);
		toolbar->endUpdate();
		updateToolbar();
		modified = true;
	}
	void addAction(String name, String path, String cmdLine, int shortcut,
		bool asButton, bool separator, bool acceptFile, bool acceptFolder, String accept, String category) {
		TUserAction &item = add();
		item.name = name;
		item.path = path;
		item.cmdLine = cmdLine;
		item.ShortCut = shortcut;
		item.path = path;
		item.ActionList = actionList;
		item.OnExecute = onExecute;
		item.Caption = name;
		item.asButton = asButton;
		item.separator = separator;
		item.acceptFile = acceptFile;
		item.acceptFolder = acceptFolder;
		item.accept = accept;
		item.category = category;
		modified = true;
	}
	void __fastcall onImagesLoaded(TObject *sender)
	{
		TIconLoader *iconLoader = (TIconLoader*)sender;
		for (int ai = 0; ai < count; ai++) {
			TUserAction &act = items[count - ai - 1];
			act.ImageIndex = iconLoader->indexes[ai];
			act.Hint = iconLoader->hints[ai];
		}
		LockWindowUpdate(NULL);
		loading = false;
		toolbar->Visible = true;
		frmMain->btnActions->Enabled = true;
		//toolbar->Realign();
	}
	TMenuItem *addCategory(TMenuItem *parent, String name, int &lastCategory)
	{
		for (int i=0; i<parent->Count; i++) {
			if(!parent->Items[i]->Caption.CompareIC(name)) return parent->Items[i];
		}
		TMenuItem *mi = new TMenuItem(parent);
		if(lastCategory == -1) {
			parent->Add(mi);
		} else {
			parent->Insert(lastCategory + 1, mi);
		}
		lastCategory = parent->IndexOf(mi);

		mi->Caption = name;
		categories->Add(name);
		return mi;
    }
	bool updateToolsMenuVisibility(TMenuItem *parent)
	{
		bool hasVisibleItem = false;
		for (int i = 0; i < parent->Count; i++) {
			TMenuItem *mi = parent->Items[i];
			if (mi->Count) {
				mi->Visible = updateToolsMenuVisibility(mi);
			}
			else if (mi->Caption == "-") {
				mi->Visible = false;
			}
			else if (mi->Action) {
				TUserAction *action = (TUserAction*)mi->Action;
				mi->Visible = FileExists(action->path) ||
					DirectoryExists(action->path);
			}
			else {
				mi->Visible = true;
			}
			if (mi->Visible)
				hasVisibleItem = true;
		}

		bool visibleBefore = false;
		for (int i = 0; i < parent->Count; i++) {
			TMenuItem *mi = parent->Items[i];
			if (mi->Caption != "-") {
				if (mi->Visible)
					visibleBefore = true;
				continue;
			}
			bool visibleAfter = false;
			for (int j = i + 1; j < parent->Count; j++) {
				if (parent->Items[j]->Caption != "-" &&
					parent->Items[j]->Visible) {
					visibleAfter = true;
					break;
				}
			}
			mi->Visible = visibleBefore && visibleAfter;
		}
		return hasVisibleItem;
	}
	void __fastcall onToolsPopup(TObject *Sender)
	{
		TPopupMenu *popup = (TPopupMenu*)Sender;
		updateToolsMenuVisibility(popup->Items);
	}
	void updateToolbar()
	{
		if(GetKeyState(VK_CONTROL) < 0) return;
		TIconLoader *iconLoader = new TIconLoader((TImageList*)actionList->Images);
		iconLoader->OnTerminate = onImagesLoaded;
		frmMain->btnActions->Enabled = false;
		LockWindowUpdate(frmMain->Handle);
		actionList->Images->Clear();
		toolbar->beginUpdate();
		for (int ai = 0; ai < count; ai++) {
			TUserAction &act = items[ai];
			if (act.button) {
				act.button->Parent = NULL;
				delete act.button;
				act.button = 0;
			}
		}
		//
		for (int ai = 0; ai < count; ai++) {
			TUserAction &act = items[count - ai - 1];

			String dispName;
			iconLoader->dirList->Add(act.path);
			bool actAvailable = FileExists(act.path) || DirectoryExists(act.path);
			if(!act.path.leftIs("\\\\") && !actAvailable)
				continue;
			if (!act.asButton)
				continue;

			TpcButton *btn = new TpcButton(NULL);
			btn->AutoSize = true;
			btn->PopupMenu = frmMain->popSpec;
			btn->OnContextPopup = onContextPopup;
			act.button = btn;
			if (act.separator) {
				btn->Style = tbsSeparator;
				btn->AutoSize = false;
				btn->Width = 8;
				btn->Caption = "<Separator>";
			}
			else
				btn->Action = &act;
			btn->Parent = toolbar;

		}
		TPopupMenu *popup = frmMain->btnActions->DropdownMenu;
		if (!popup) {
			popup = new TPopupMenu(toolbar);
			popup->Images = actionList->Images;
		}
		frmMain->btnActions->DropdownMenu = popup;
		popup->OnPopup = onToolsPopup;
		popup->Items->Clear();
		categories->Clear();
		int lastCategory = -1;
		for (int ai = 0; ai < count; ai++) {
			TUserAction &action = items[ai];
			if (action.asButton)
				continue;
			TMenuItem *mi = new TMenuItem(popup);
			if (!ai)
				mi->Default = true;
			if (action.separator)
				mi->Caption = "-";
			else
				mi->Action = (TBasicAction*) & action;

			TMenuItem *base = popup->Items;
			if(action.category != "") {
				base = addCategory(popup->Items, action.category, lastCategory);
			}
			base->Add(mi);
		}
		frmMain->statusBar->Top = 2000;
		if(!loading) {
			loading = true;
			iconLoader->Start();
		}
	}

	void load(TIniFile *ini) {
		SetCurrentDir(ExtractFilePath(Application->ExeName));
		int count = ini->ReadInteger("SpecFolders", "Count", 0);
		for (int fi = 0; fi < count; fi++) {
			String path = ini->ReadString("SpecFolder" + String(fi), "path",
				"");
			String name = ini->ReadString("SpecFolder" + String(fi), "name",
				"");
			String cmdline = text(ini->ReadString("SpecFolder" + String(fi),
				"cmdline", "")).replace("$", "\"");
			int shortcut = ini->ReadInteger("SpecFolder" + String(fi),
				"shortcut", 0);
			bool asButton = ini->ReadBool("SpecFolder" + String(fi),
				"asButton", 1);
			bool separator = ini->ReadBool("SpecFolder" + String(fi),
				"separator", 0);
			bool acceptFile = ini->ReadBool("SpecFolder" + String(fi),
				"acceptFile", 0);
			bool acceptFolder = ini->ReadBool("SpecFolder" + String(fi),
				"acceptFolder", 0);
			String accept = ini->ReadString("SpecFolder" + String(fi),
				"accept", "*.*");
			String category = ini->ReadString("SpecFolder" + String(fi),
				"category", "");
			addAction(name, path, cmdline, shortcut, asButton, separator, acceptFile, acceptFolder, accept, category);
		}
		modified = false;
		updateToolbar();
	}

	void save(TIniFile *ini) {
		if(!modified) return;
		ini->WriteInteger("SpecFolders", "Count", count);
		for (int fi = 0; fi < count; fi++) {
			TUserAction &item = items[fi];
			ini->WriteString("SpecFolder" + String(fi), "path",
				item.clsid_path);
			ini->WriteString("SpecFolder" + String(fi), "name", item.name);
			ini->WriteString("SpecFolder" + String(fi), "cmdline", text(item.cmdLine).replace("\"", "$"));
			ini->WriteInteger("SpecFolder" + String(fi), "shortcut",
				item.ShortCut);
			ini->WriteBool("SpecFolder" + String(fi), "asButton",
				item.asButton);
			ini->WriteBool("SpecFolder" + String(fi), "separator",
				item.separator);
			ini->WriteBool("SpecFolder" + String(fi), "acceptFile",
				item.acceptFile);
			ini->WriteBool("SpecFolder" + String(fi), "acceptFolder",
				item.acceptFolder);
			ini->WriteString("SpecFolder" + String(fi), "accept",
				item.accept);
			ini->WriteString("SpecFolder" + String(fi), "category",
				item.category);
		}
	}
};
TUserActions *specFolders;
// ---------------------------------------------------------------------------
TpcPage *pageL, *pageR;

TpcPage *activePage() {
	return pageL->active() ? pageL : pageR;
}

TUserAction* Get(int i) {
	return((TUserAction*)specFolders->actionList->Actions[i]);
}

// ---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner)
{
	Wow64DisableWow64FsRedirection(NULL);

//	TStringList *items = new TStringList;
//	items->Add("AB");
//	items->Add("\"");
//	items->Add(" ");
//	array arr;
//	arr << "AB" << "\"" << " ";
//	text str = arr.getDelimitedText(' ');
//	items->Delimiter = ' ';
//	if(str == items->DelimitedText)
//		ShowMessage(items->DelimitedText);


//	TStringList *s = new TStringList;
//    s->Add("A'B");
//    s->Add("B\"X");
//    s->Text;
//    ShowMessage(s->DelimitedText);
//    exit(0);
//	TStorage* storage = createStorageFromPath("C:\\");
//	TStorageItems items = storage->getItems("C:\\", faAnyFile);
//	items.count();
//	array arr;
//	arr << "D:\\!Mht\\Temp\\cloud\\StorageDemo\\CloudStorageDemo.dproj.local";
	//storage->deleteItems(arr);
	//storage->copy(arr, "");

	SetErrorMode(SEM_FAILCRITICALERRORS);
	pageL = new ::TpcPage(pcL);
	pageR = new ::TpcPage(pcR);
	tbSpecFolders = new TpcToolBar(NULL);
	tbSpecFolders->Visible = false;
	tbSpecFolders->Parent = frmMain;
	tbSpecFolders->Align = alBottom;
	tbSpecFolders->AlignWithMargins = true;
	tbSpecFolders->Margins->Top = 0;
	tbSpecFolders->Margins->Bottom = 0;
	tbSpecFolders->ButtonHeight = 7;
	tbSpecFolders->ButtonWidth = 0;
	tbSpecFolders->HideClippedButtons = true;
	tbSpecFolders->List = true;
	tbSpecFolders->PopupMenu = popSpec;
	tbSpecFolders->ShowCaptions = true;
	tbSpecFolders->ShowHint = true;
	specFolders = new TUserActions(tbSpecFolders);
	RegisterHotKey(Handle, 0, MOD_CONTROL | MOD_ALT, VK_INSERT);
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender) {
	Application->Title = Caption;
	vActive = vInactive = NULL;
	load();
	onNotify(0);
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender) {
	panR->Width = (frmMain->ClientWidth - Splitter->Width) / 2;
	statusBar->Top = 2000;
}
// ---------------------------------------------------------------------------
void TfrmMain::createDriveButtons(TButtonGroup *group) {
	int count = getDrivesCount();
	group->Items->Clear();
	group->TabStop = false;
	group->Height = 20;
	group->ButtonHeight = 18;
	group->ButtonWidth = 40;
	group->OnButtonClicked = onDriveClick;
	group->ButtonOptions << gboGroupStyle;
	if (!group->Images) {
		group->Images = new TImageList(Owner);
		group->Images->DrawingStyle = dsTransparent;
		group->Images->ColorDepth = cd32Bit;
	}
	group->Images->Clear();

	for (int di = 0; di < count; di++) {
		TGrpButtonItem* item = group->Items->Add();
		char drive[] = {
			getDriveStr(di), ':', 0
		};
		item->Caption = drive[0];
		TIcon *icon = getShellIcon(getDriveIconIndex(drive));
		int iconIndex = group->Images->AddIcon(icon);
		delete icon;
		item->ImageIndex = iconIndex;
		// item->Hint = getDriveLabel(item->Caption);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onDriveClick(TObject* sender, int index) {
	TButtonGroup *group = (TButtonGroup*)sender;
	TGrpButtonItem *button = group->Items->Items[index];
	TFileView *fileView = (TFileView*)group->Tag;
	fileView->Directory = button->Caption + ":\\";
	fileView->SetFocus();
}

// ---------------------------------------------------------------------------
void TfrmMain::setActiveDrive(String drive, TButtonGroup *group) {
	drive = drive.LowerCase();
	for (int i = 0; i < group->Items->Count; i++) {
		if (group->Items->Items[i]->Caption.LowerCase() == drive[1]) {
			group->ItemIndex = i;
			break;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::driveRContextPopup(TObject *Sender, TPoint &MousePos,
	bool &Handled) {
	TButtonGroup *group = (TButtonGroup*)Sender;
	int index = group->IndexOfButtonAt(MousePos.x, MousePos.y);
	TGrpButtonItem *button = group->Items->Items[index];
	TNamespace *ns = new TNamespace(button->Caption + ":\\");
	GetCursorPos(&MousePos);
	ns->ShowContextMenu(group, 0, 0, 0, &MousePos, 0, "");
	delete ns;
}

// ---------------------------------------------------------------------------
TFileView *TfrmMain::activeView() {
	return vActive;
	// return pageL->active() ? ((TTab*)pcL->ActivePage)->view : ((TTab*)pcR->ActivePage)->view;
}

// ---------------------------------------------------------------------------
TFileView *TfrmMain::inactiveView() {
	return vActive->Parent->Parent->Name == "pcL" ? ((TTab*)pcR->ActivePage)
		->view : ((TTab*)pcL->ActivePage)->view;
}

// ---------------------------------------------------------------------------
text getIniFileName()
{
	wchar_t comp[50];
	DWORD size = sizeof(comp);
	//GetUserNameW(user, &size);
	GetComputerNameW(comp, &size);
	return text(Application->ExeName).replace(".exe", (text)"-" + comp + ".ini");
}

void TfrmMain::load() {
	TIniFile *ini = new TIniFile(getIniFileName());
	TFileView::useShamsiDate = ini->ReadBool("Options", "", true);
	miUseShamsiDate->Checked = TFileView::useShamsiDate;
	pageL->load(ini);
	pageR->load(ini);
	specFolders->load(ini);
	// tbSpecFolders->Align = alNone;
	tbSpecFolders->Top = 100;
	// tbSpecFolders->Align = alBottom;
	delete ini;
}

// ---------------------------------------------------------------------------
void TfrmMain::save() {
	TIniFile *ini = new TIniFile(getIniFileName());
	ini->WriteBool("Options", "", TFileView::useShamsiDate);
	pageL->save(ini);
	pageR->save(ini);
	specFolders->save(ini);
	delete ini;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action) {
	Hide();
	save();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::edtPathLKeyPress(TObject *Sender, wchar_t &Key) {
	if (Key == VK_RETURN) {
		TEdit *edt = (TEdit*)Sender;
		Key = 0;
		TFileView *fv = (TFileView*)edt->Tag;
		fv->Directory = edt->Text;
		fv->SetFocus();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miCopyNamePathClick(TObject *Sender) {
	TFileView *view = (TFileView*)popPath->Tag;
	if(!view->FileObject) return;
	Clipboard()->AsText = view->PathFileName;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miCopyNameClick(TObject *Sender) {
	TFileView *view = (TFileView*)popPath->Tag;
	if(!view->FileObject) return;
	Clipboard()->AsText = view->FileName;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miCopyCPathClick(TObject *Sender) {
	TFileView *view = (TFileView*)popPath->Tag;
//	if(!view->FileObject) return;
	String path = view->Directory;
	TReplaceFlags flags;
	flags << rfReplaceAll;
	path = StringReplace(path, "\\", "\\\\", flags);
	Clipboard()->AsText = "\"" + path + "\"";
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miCopyPathClick(TObject *Sender) {
	TFileView *view = (TFileView*)popPath->Tag;
	Clipboard()->AsText = view->Directory;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::CopyCPathName1Click(TObject *Sender) {
	TFileView *view = (TFileView*)popPath->Tag;
	if(!view->FileObject) return;
	String path = view->PathFileName;
	TReplaceFlags flags;
	flags << rfReplaceAll;
	path = StringReplace(path, "\\", "\\\\", flags);
	Clipboard()->AsText = "\"" + path + "\"";
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onSelectItem(TObject *Sender, TListItem *Item, bool Selected) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ApplicationEventsActivate(TObject *Sender) {
	// if(GetKeyState(VK_LBUTTON) >= 0)
	{
		// TWindow(Handle).NoActivate = false;
		// Beep(300, 99);
	}
	// pageL->setNoActivate(false);
	// pageR->setNoActivate(false);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ApplicationEventsDeactivate(TObject *Sender) {
	TWindow(Handle).NoActivate = true;
	// Beep(300, 99);
	// pageL->setNoActivate(true);
	// pageR->setNoActivate(true);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actJumpExecute(TObject *Sender) {
	if (pageL->active())
		viewR()->Directory = viewL()->Directory;
	else
		viewL()->Directory = viewR()->Directory;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onNotify(TObject *Sender) {
	int index = statusBar->Panels->Count - 1;
	statusBar->Panels->Items[index]->Text = getDiskQuery();
}
// ---------------------------------------------------------------------------
bool isPicture(String ext) {
	String pext = ".jpg.jpeg.gif.tif.dib.pcx.tif.bmp.png";
	return pext.LowerCase().Pos(ext.LowerCase());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actMoveExecute(TObject *Sender) {
	activeView()->cut();
	inactiveView()->paste();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actCopyExecute(TObject *Sender) {
	activeView()->doCopy(inactiveView()->Directory);
	inactiveView()->refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::actDuplicateExecute(TObject *Sender) {
	activeView()->doCopy(activeView()->Directory);
	activeView()->refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::acrRunExecute(TObject *Sender) {
	frmRun->edtApp->Text = activeView()->PathFileName;
	if (frmRun->ShowModal() == mrOk) {
		ShellExecuteW(Handle, L"open", frmRun->edtApp->Text.c_str(),
			frmRun->edtArg->Text.c_str(), L"", SW_NORMAL);
	}
}

// ---------------------------------------------------------------------------
TFileView *TfrmMain::viewL() {
	return((TTab*)pcL->ActivePage)->view;
}

TFileView *TfrmMain::viewR() {
	return((TTab*)pcR->ActivePage)->view;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actNewTabExecute(TObject *Sender) {
	String dir = activeView()->PathFileName;
	if (!DirectoryExists(dir))
		dir = activeView()->Directory;
	activePage()->addTab(dir);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actCloseTabExecute(TObject *Sender) {
	activePage()->closeTab();
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actAddBtnExecute(TObject *Sender) {
	frmAddBtn->shortcut->HotKey = 0;
	frmAddBtn->edtName->Text = activeView()->FileName;
	frmAddBtn->edtPath->Text = activeView()->PathFileName;
	frmAddBtn->edtCmdLine->Text = "";
	frmAddBtn->chAsButton->Checked = true;
	frmAddBtn->chSeparator->Checked = false;
	frmAddBtn->chFile->Checked = true;
	frmAddBtn->chFolder->Checked = true;
	frmAddBtn->edtFileType->Text = "*.*";
	frmAddBtn->cmbCategory->Items->Clear();
	frmAddBtn->cmbCategory->Items->AddStrings(specFolders->categories);
	if (frmAddBtn->ShowModal() != mrOk)
		return;
	specFolders->addAction(frmAddBtn->edtName->Text, frmAddBtn->edtPath->Text,
		frmAddBtn->edtCmdLine->Text, frmAddBtn->shortcut->HotKey,
		frmAddBtn->chAsButton->Checked, frmAddBtn->chSeparator->Checked,
		frmAddBtn->chFile->Checked, frmAddBtn->chFolder->Checked,
		frmAddBtn->edtFileType->Text, frmAddBtn->cmbCategory->Text);
	specFolders->updateToolbar();
	save();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onSpecPopup(TObject *Sender, TPoint &MousePos,
	bool &Handled) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miRemoveButtonClick(TObject *Sender) {
	TUserAction &act = *(TUserAction*)specFolders->activeButton->Action;
	specFolders->remove(act);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::WMDeviceChange(TMessage &msg) {
	if(msg.WParam == DBT_DEVICEREMOVECOMPLETE || msg.WParam == DBT_DEVICEARRIVAL) {
		pageL->updateDrives();
		pageR->updateDrives();
	}
	if (msg.WParam == DBT_DEVICEARRIVAL) {
		// activeView()->PathFileName);
		if(TFileView::globalMon) TFileView::globalMon->refresh();
		DEV_BROADCAST_HDR *hdr = (DEV_BROADCAST_HDR*)msg.LParam;
		if (hdr->dbch_devicetype == DBT_DEVTYP_VOLUME) {
			DEV_BROADCAST_VOLUME *vol = (DEV_BROADCAST_VOLUME*)hdr;
			for (int i = 0; i < 32; i++) {
				if ((1 << i) == (int)vol->dbcv_unitmask) {
					wchar_t drv[] = {
						i + 'A', ':', '\\', 0
					};
					pageL->addTab(drv, true);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------
void TfrmMain::updateStatusBar() {
	if (!activeView())
		return;
	statusBar->Panels->Items[0]->Text = String(activeView()->getFileCount())
		+ " objects";
	statusBar->Panels->Items[1]->Text = String
		(activeView()->getSelectedCount()) + " selected objects";
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onViewEnter(TObject *Sender) {
	vActive = (TFileView*)Sender;

	updateStatusBar();
	updateNavigationBtns();
	if (activeView()->FileObject)
		Application->Title = activeView()->FileName;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onViewExit(TObject *Sender) {
	// vInactive = (TFileView*)Sender;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onKeyPress(TObject *Sender, wchar_t &Key) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onChange(TObject *Sender, TListItem *Item,
	TItemChange Change) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	//updateStatusBar();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::onFocusChanged(TBaseVirtualTree* Sender,
	PVirtualNode Node, TColumnIndex Column) {
	if (activeView() && activeView()->FileObject)
		Application->Title = activeView()->FileName;
	//updateStatusBar();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ApplicationEventsMessage(tagMSG &Msg, bool &Handled) {
	if (Msg.message == WM_LBUTTONUP || Msg.message == WM_NCLBUTTONUP) {
		POINT point;
		GetCursorPos(&point);
		HWND hWnd = WindowFromPoint(point);
		TWindow forg;
		forg.CaptureForeground();
		if(forg.SameProcess(Handle)) return;
		if (TWindow(hWnd).SameProcess(Handle) && !Application->ModalLevel)
			SetForegroundWindow(frmMain->Handle);
	}
}

// ---------------------------------------------------------------------------
void loadActionsIntoList() {
	int index = frmUserActions->lbActions->ItemIndex;
	frmUserActions->lbActions->Items->BeginUpdate();
	frmUserActions->lbActions->Clear();
	for (int ai = 0; ai < specFolders->count; ai++) {
		TUserAction &act = specFolders->items[ai];
		String item = act.name;
		if (act.separator)
			item = "----------------------";
		if (act.ShortCut)
			item += " (" + ShortCutToText(act.ShortCut) + ")";
		if (act.asButton)
			item += L" ●";
		frmUserActions->lbActions->AddItem(item, (TObject*) & act);
	}
	if(index < frmUserActions->lbActions->Count)
		frmUserActions->lbActions->ItemIndex = index;
	frmUserActions->lbActions->Items->EndUpdate();
}

// ---------------------------------------------------------------------------
bool __fastcall editAction(TUserAction &act) {
	frmAddBtn->edtName->Text = act.name;
	frmAddBtn->edtPath->Text = act.clsid_path;
	frmAddBtn->edtCmdLine->Text = act.cmdLine;
	frmAddBtn->shortcut->HotKey = act.ShortCut;
	frmAddBtn->chAsButton->Checked = act.asButton;
	frmAddBtn->chSeparator->Checked = act.separator;
	frmAddBtn->cmbCategory->Text = act.category;
	frmAddBtn->cmbCategory->Items->Clear();
	frmAddBtn->cmbCategory->Items->AddStrings(specFolders->categories);

	frmAddBtn->chFile->Checked = act.acceptFile;
	frmAddBtn->chFolder->Checked = act.acceptFolder;
	frmAddBtn->edtFileType->Text = act.accept;

	if (frmAddBtn->ShowModal() != mrOk)
		return false;
	act.Caption = frmAddBtn->edtName->Text;
	act.name = act.Caption;
	act.path = frmAddBtn->edtPath->Text;
	act.cmdLine = frmAddBtn->edtCmdLine->Text;
	act.ShortCut = frmAddBtn->shortcut->HotKey;
	act.button->Caption = act.name;
	act.asButton = frmAddBtn->chAsButton->Checked;
	act.separator = frmAddBtn->chSeparator->Checked;
	act.acceptFile = frmAddBtn->chFile->Checked;
	act.acceptFolder = frmAddBtn->chFolder->Checked;
	act.accept = frmAddBtn->edtFileType->Text;
	act.category = frmAddBtn->cmbCategory->Text;
	specFolders->updateToolbar();
	specFolders->modified = true;

	loadActionsIntoList();
	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::miEditUserBtnClick(TObject *Sender) {
	if (!specFolders->activeButton)
		return;
	TUserAction &act = *(TUserAction*)specFolders->activeButton->Action;
	editAction(act);
}

// ---------------------------------------------------------------------------
TfrmMain::getCLSID(String id) {
	struct clsid {
		char *name;
		int id;
	};

	clsid all[] = { {
			"FLAG_CREATE", CSIDL_FLAG_CREATE
		}, {
			"ADMINTOOLS", CSIDL_ADMINTOOLS
		}, {
			"ALTSTARTUP", CSIDL_ALTSTARTUP
		}, {
			"APPDATA", CSIDL_APPDATA
		}, {
			"BITBUCKET", CSIDL_BITBUCKET
		}, {
			"CDBURN_AREA", CSIDL_CDBURN_AREA
		}, {
			"COMMON_ADMINTOOLS", CSIDL_COMMON_ADMINTOOLS
		}, {
			"COMMON_ALTSTARTUP", CSIDL_COMMON_ALTSTARTUP
		}, {
			"COMMON_APPDATA", CSIDL_COMMON_APPDATA
		}, {
			"COMMON_DESKTOPDIRECTORY", CSIDL_COMMON_DESKTOPDIRECTORY
		}, {
			"COMMON_DOCUMENTS", CSIDL_COMMON_DOCUMENTS
		}, {
			"COMMON_FAVORITES", CSIDL_COMMON_FAVORITES
		}, {
			"COMMON_MUSIC", CSIDL_COMMON_MUSIC
		}, {
			"COMMON_PICTURES", CSIDL_COMMON_PICTURES
		}, {
			"COMMON_PROGRAMS", CSIDL_COMMON_PROGRAMS
		}, {
			"COMMON_STARTMENU", CSIDL_COMMON_STARTMENU
		}, {
			"COMMON_STARTUP", CSIDL_COMMON_STARTUP
		}, {
			"COMMON_TEMPLATES", CSIDL_COMMON_TEMPLATES
		}, {
			"COMMON_VIDEO", CSIDL_COMMON_VIDEO
		}, {
			"COMPUTERSNEARME", CSIDL_COMPUTERSNEARME
		}, {
			"CONNECTIONS", CSIDL_CONNECTIONS
		}, {
			"CONTROLS", CSIDL_CONTROLS
		}, {
			"COOKIES", CSIDL_COOKIES
		}, {
			"DESKTOP", CSIDL_DESKTOP
		}, {
			"DESKTOPDIRECTORY", CSIDL_DESKTOPDIRECTORY
		}, {
			"DRIVES", CSIDL_DRIVES
		}, {
			"FAVORITES", CSIDL_FAVORITES
		}, {
			"FLAG_DONT_UNEXPAND", CSIDL_FLAG_DONT_UNEXPAND
		}, {
			"FLAG_DONT_VERIFY", CSIDL_FLAG_DONT_VERIFY
		}, {
			"FONTS", CSIDL_FONTS
		}, {
			"HISTORY", CSIDL_HISTORY
		}, {
			"INTERNET", CSIDL_INTERNET
		}, {
			"INTERNET_CACHE", CSIDL_INTERNET_CACHE
		}, {
			"LOCAL_APPDATA", CSIDL_LOCAL_APPDATA
		}, {
			"MYDOCUMENTS", CSIDL_MYDOCUMENTS
		}, {
			"MYMUSIC", CSIDL_MYMUSIC
		}, {
			"MYPICTURES", CSIDL_MYPICTURES
		}, {
			"MYVIDEO", CSIDL_MYVIDEO
		}, {
			"NETHOOD", CSIDL_NETHOOD
		}, {
			"NETWORK", CSIDL_NETWORK
		}, {
			"PERSONAL", CSIDL_PERSONAL
		},
		// {"PLAYLISTS", CSIDL_PLAYLISTS},
		{
			"PRINTERS", CSIDL_PRINTERS
		}, {
			"PRINTHOOD", CSIDL_PRINTHOOD
		}, {
			"PROFILE", CSIDL_PROFILE
		}, {
			"PROGRAM_FILES", CSIDL_PROGRAM_FILES
		}, {
			"PROGRAM_FILES_COMMON", CSIDL_PROGRAM_FILES_COMMON
		}, {
			"PROGRAMS", CSIDL_PROGRAMS
		}, {
			"RECENT", CSIDL_RECENT
		}, {
			"RESOURCES", CSIDL_RESOURCES
		},
		// {"SAMPLE_MUSIC", CSIDL_SAMPLE_MUSIC},
		// {"SAMPLE_PLAYLISTS", CSIDL_SAMPLE_PLAYLISTS},
		// {"SAMPLE_PICTURES", CSIDL_SAMPLE_PICTURES},
		// {"SAMPLE_VIDEOS", CSIDL_SAMPLE_VIDEOS},
		{
			"SENDTO", CSIDL_SENDTO
		}, {
			"STARTMENU", CSIDL_STARTMENU
		}, {
			"STARTUP", CSIDL_STARTUP
		}, {
			"SYSTEM", CSIDL_SYSTEM
		}, {
			"TEMPLATES", CSIDL_TEMPLATES
		}, {
			"WINDOWS", CSIDL_WINDOWS
		}
	};
	int count = sizeof(all) / sizeof(clsid);
	for (int i = 0; i < count; i++) {
		if (id == all[i].name)
			return all[i].id;
	}
	return 0;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender) {
	delete pageL;
	delete pageR;
	delete specFolders;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::editActionClick(TObject *Sender) {
	int index = frmUserActions->lbActions->ItemIndex;
	if (index == -1)
		return;
	TUserAction &act = *(TUserAction*)frmUserActions->lbActions->Items->Objects
		[index];
	editAction(act);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::removeActionClick(TObject *Sender) {
	int index = frmUserActions->lbActions->ItemIndex;
	if (index == -1)
		return;
	int id = MessageBoxA(frmUserActions->Handle, "delete selected action?",
		"Warning", MB_YESNO | MB_ICONWARNING);
	if (id != IDYES)
		return;
	TUserAction &act = *(TUserAction*)frmUserActions->lbActions->Items->Objects
		[index];
	specFolders->remove(act);
	specFolders->updateToolbar();
	loadActionsIntoList();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::runActionClick(TObject *Sender) {
	int index = frmUserActions->lbActions->ItemIndex;
	if (index == -1)
		return;
	TUserAction &act = *(TUserAction*)frmUserActions->lbActions->Items->Objects
		[index];
	act.Execute();
	frmUserActions->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actNewDirExecute(TObject *Sender) {
	String dir;
	String root = activeView()->Directory;
	int n = 2;
	String base;
	if(TFileView::useShamsiDate)
		base = TShamsiDate(Now()).ShamsiString;
	else
		base = Now().DateString();
	base = text(base).replace("/", "-");
	dir = base;
	start:
	if (DirectoryExists(root + dir)) {
		dir = base + " (" + String(n) + ")";
		n++;
		goto start;
	}
	if (InputQuery("New Folder", "Enter Folder Name", dir)) {
		dir = root + dir;
		//CreateDir(dir);
		ForceDirectories(dir);
		activeView()->go(dir);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actionUp(TObject *Sender)
{
	int move = 1;
	if(GetKeyState(VK_CONTROL) < 0) move = 5;
	tbSpecFolders->beginUpdate();
	for (int t=0; t<move; t++) {
		int index = frmUserActions->lbActions->ItemIndex;
		if (index - 1 < 0 || index == -1)
			return;
		specFolders->exchange(index, index - 1);
		frmUserActions->lbActions->Items->Exchange(index, index - 1);
	}
	tbSpecFolders->endUpdate();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actionDown(TObject *Sender)
{
	int move = 1;
	if(GetKeyState(VK_CONTROL) < 0) move = 5;
	tbSpecFolders->beginUpdate();
	for (int t=0; t<move; t++) {
		int index = frmUserActions->lbActions->ItemIndex;
		if (index + 1 >= frmUserActions->lbActions->Count || index == -1)
			return;
		specFolders->exchange(index, index + 1);
		frmUserActions->lbActions->Items->Exchange(index, index + 1);
	}
	tbSpecFolders->endUpdate();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actToolsExecute(TObject *Sender) {
	frmUserActions->btnEdit->OnClick = editActionClick;
	frmUserActions->btnRemove->OnClick = removeActionClick;
	frmUserActions->btnRun->OnClick = runActionClick;
	frmUserActions->btnUp->OnClick = actionUp;
	frmUserActions->btnDown->OnClick = actionDown;
	loadActionsIntoList();
	frmUserActions->ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actBackwardExecute(TObject *Sender) {
	if (!activeView()->IsEditing())
		activeView()->backward();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actForwardExecute(TObject *Sender) {
	if (!activeView()->IsEditing())
		activeView()->forward();
}

// ---------------------------------------------------------------------------
void TfrmMain::updateNavigationBtns() {
	actForward->Enabled =  activeView() && activeView()->canForward();
	actBackward->Enabled = activeView() && activeView()->canBackward();
	actUp->Enabled = activeView() && activeView()->canUp();
}

void __fastcall TfrmMain::actUpExecute(TObject *Sender) {
	if (!activeView()->IsEditing())
		activeView()->up();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::actCopyPathExecute(TObject *Sender) {
	if(!activeView()->FileObject) return;
	Clipboard()->AsText = activeView()->PathFileName;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::actDeleteExecute(TObject *Sender)
{
	activeView()->deleteSelected();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::actCutExecute(TObject *Sender) {
	activeView()->cut();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::actPasteExecute(TObject *Sender) {
	activeView()->paste();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actCopyToClipboardExecute(TObject *Sender) {
	activeView()->copy();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmMain::AddSeparator1Click(TObject *Sender) {
	specFolders->addAction("Separator", "", "", 0, true, true, true, true, "", "");
	specFolders->updateToolbar();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::popSpecPopup(TObject *Sender) {
	miEditUserBtn->Visible = specFolders->activeButton;
	miRemoveButton->Visible = specFolders->activeButton;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMain::FormActivate(TObject *Sender) {
	TimerDateUpdateTimer(0);
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::actSearchExecute(TObject *Sender)
{
	frmSearch->target->Clear();
	frmSearch->target->Add(activeView()->Directory);
	frmSearch->onFindTarget = onFindTarget;
	frmSearch->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::onFindTarget(TObject *Sender)
{
	activeView()->go(frmSearch->view->PathFileName);
}

void __fastcall TfrmMain::actRefreshExecute(TObject *Sender)
{
	activeView()->reload();
	inactiveView()->reload();
	onNotify(0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TimerDateUpdateTimer(TObject *Sender)
{
	String date = Now().DateString();
	if(TFileView::useShamsiDate)
		date = TShamsiDate(Now()).ShamsiString;
	statusBar->Panels->Items[2]->Text = date;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miUseShamsiDateClick(TObject *Sender)
{
	TFileView::useShamsiDate = miUseShamsiDate->Checked;
	activeView()->Repaint();
	inactiveView()->Repaint();
	TimerDateUpdateTimer(0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actShowShellInfoExecute(TObject *Sender)
{
	activeView()->showShellInfo();
}
//---------------------------------------------------------------------------
void __fastcall TUserActions::onActionExecute(TBasicAction *Action, bool &Handled)
{
	Handled = true;
	TUserAction *action = (TUserAction*)Action;
	bool isDir = true;
	text fileName;
	if(frmMain->activeView()->FileObject) {
		fileName = frmMain->activeView()->FileName;
		isDir = frmMain->activeView()->FileObject->IsDirectory();
		if(isDir && !action->acceptFolder && !action->cmdLine.IsEmpty() && !Action->ActionComponent) return;
	}
	int shortcut = action->ShortCut;
	if(shortcut == 0 || Action->ActionComponent) {
		Action->ActionComponent = NULL;
		Action->OnExecute(Action);
	}
	else {
		for (int ai=0; ai<specFolders->count; ai++) {
			TUserAction &action = specFolders->items[ai];
			if(action.ShortCut != shortcut) continue;
			bool accept = isDir && action.acceptFolder;
			accept |= action.acceptFile && action.isFileAccepted(fileName);
			accept |= action.cmdLine.IsEmpty();
			if(!accept) continue;
			action.OnExecute(&action);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WMHotKey(TMessage &msg)
{
	BlockInput(true);
	Beep(500, 200);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ApplicationEventsException(TObject *Sender, Exception *E)

{
;
}
//---------------------------------------------------------------------------
//arrayof<DWORD> instances;
void __fastcall TfrmMain::actConsoleExecute(TObject *Sender)
{
	STARTUPINFOA si;
	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_NORMAL;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	char pathbuf[MAX_PATH];
	_searchenv("CMD.EXE", "PATH", pathbuf);
	text dir = activeView()->Directory;
	array sets;
	sets << "3F" << "8F" << "07";
	text param;

	//
	static int index = 0;
//	int index = 0;
//	while(index < instances.count()){
//		HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, 0, instances[index]);
//		DWORD pid = GetProcessId(handle);
//		DWORD count;
//		GetProcessHandleCount(handle, &count);
//		if(!count) {
//			instances.remove(index);
//			break;
//		}
//		index++;
//	}
	param = param.print(L"/T:%s", sets[index % sets.count()]);
	index++;
	//index ++;
	CreateProcessA(pathbuf, param.t_str(), NULL, NULL, true, 0, NULL, dir.c_str(), &si, &pi);
	//instances << pi.dwProcessId;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGroupRenameExecute(TObject *Sender)
{
	array items = activeView()->getSelectList(false);

	if(items.count() > 1)
	{
		frmRename->items = items;
		frmRename->dir = activeView()->Directory;
		if(frmRename->edtPat->Text.IsEmpty())
			frmRename->edtPat->Text = extractFace(items[0]) + " %i" + activeView()->FileObject->Ext;
		frmRename->applyPattern();
		frmRename->ShowModal();
	}
	else
		activeView()->Perform(WM_KEYDOWN, VK_F2, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actInternalDeleteExecute(TObject *Sender)
{
	array items = activeView()->getSelectList(true);

    if(MessageDlg("Do you want to delete selected files?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0, mbNo) == IDYES)
    {
    	array::it it = items.getIterator();
        while(!it.atEnd())
        	DeleteFileA(it.next());
    }
}
//---------------------------------------------------------------------------

