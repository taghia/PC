//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "FileView.h"
#include <ButtonGroup.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <AppEvnts.hpp>
#include <ToolWin.hpp>
#include <CategoryButtons.hpp>
#include <Buttons.hpp>
#include <StdActns.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TpcToolBar;
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *panL;
	TPanel *panR;
	TSplitter *Splitter;
	TActionList *ActionList;
	TPopupMenu *popPath;
	TMenuItem *miCopyPath;
	TMenuItem *miCopyNamePath;
	TMenuItem *miCopyName;
	TMenuItem *miCopyCPath;
	TMenuItem *CopyCPathName1;
	TStatusBar *statusBar;
	TAction *actJump;
	TAction *actMove;
	TAction *actCopy;
	TAction *actDuplicate;
	TAction *acrRun;
	TApplicationEvents *ApplicationEvents;
	TPageControl *pcL;
	TPageControl *pcR;
	TAction *actNewTab;
	TAction *actCloseTab;
	TAction *actAddBtn;
	TPopupMenu *popSpec;
	TMenuItem *AddButton1;
	TMenuItem *miRemoveButton;
	TActionList *userActions;
	TFileOpenWith *FileOpenWith1;
	TMenuItem *miAllActions;
	TAction *actNewDir;
	TAction *actTools;
	TAction *actBackward;
	TAction *actForward;
	TToolBar *tbTop;
	TImageList *ImageList;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TAction *actUp;
	TAction *actCopyPath;
	TMenuItem *miEditUserBtn;
	TAction *actDelete;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TAction *actCut;
	TAction *actPaste;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TAction *actCopyToClipboard;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TToolButton *btnActions;
	TMenuItem *AddSeparator1;
	TAction *actSearch;
	TImageList *ilPath;
	TToolButton *ToolButton10;
	TAction *actRefresh;
	TToolButton *ToolButton11;
	TTimer *TimerDateUpdate;
	TPopupMenu *popDateType;
	TMenuItem *miUseShamsiDate;
	TAction *actShowShellInfo;
	TToolButton *ToolButton12;
	TToolButton *ToolButton13;
	TAction *actConsole;
	TAction *actGroupRename;
	TAction *actInternalDelete;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall driveRContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall miCopyPathClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtPathLKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall miCopyNamePathClick(TObject *Sender);
	void __fastcall miCopyNameClick(TObject *Sender);
	void __fastcall miCopyCPathClick(TObject *Sender);
	void __fastcall CopyCPathName1Click(TObject *Sender);
	void __fastcall ApplicationEventsActivate(TObject *Sender);
	void __fastcall ApplicationEventsDeactivate(TObject *Sender);
	void __fastcall actJumpExecute(TObject *Sender);
	void __fastcall actMoveExecute(TObject *Sender);
	void __fastcall actCopyExecute(TObject *Sender);
	void __fastcall actDuplicateExecute(TObject *Sender);
	void __fastcall acrRunExecute(TObject *Sender);
	void __fastcall actNewTabExecute(TObject *Sender);
	void __fastcall actCloseTabExecute(TObject *Sender);
	void __fastcall actAddBtnExecute(TObject *Sender);
	void __fastcall miRemoveButtonClick(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall miEditUserBtnClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall actNewDirExecute(TObject *Sender);
	void __fastcall actToolsExecute(TObject *Sender);
	void __fastcall actBackwardExecute(TObject *Sender);
	void __fastcall actForwardExecute(TObject *Sender);
	void __fastcall actUpExecute(TObject *Sender);
	void __fastcall actCopyPathExecute(TObject *Sender);
	void __fastcall actDeleteExecute(TObject *Sender);
	void __fastcall actCutExecute(TObject *Sender);
	void __fastcall actPasteExecute(TObject *Sender);
	void __fastcall actCopyToClipboardExecute(TObject *Sender);
	void __fastcall AddSeparator1Click(TObject *Sender);
	void __fastcall popSpecPopup(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall actSearchExecute(TObject *Sender);
	void __fastcall actRefreshExecute(TObject *Sender);
	void __fastcall TimerDateUpdateTimer(TObject *Sender);
	void __fastcall miUseShamsiDateClick(TObject *Sender);
	void __fastcall actShowShellInfoExecute(TObject *Sender);
	void __fastcall ApplicationEventsException(TObject *Sender, Exception *E);
	void __fastcall actConsoleExecute(TObject *Sender);
	void __fastcall actGroupRenameExecute(TObject *Sender);
	void __fastcall actInternalDeleteExecute(TObject *Sender);

private:	// User declarations
	MESSAGE void __fastcall WMDeviceChange(TMessage &msg);
	MESSAGE void __fastcall WMHotKey(TMessage &msg);
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_DEVICECHANGE, TMessage, WMDeviceChange);
		VCL_MESSAGE_HANDLER(WM_HOTKEY, TMessage, WMHotKey);
	END_MESSAGE_MAP(TForm);
	TFileView *vActive, *vInactive;
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
	TFileView* createFileView(TPageControl *parent);
	void createDriveButtons(TButtonGroup *group);
	void __fastcall onDriveClick(TObject* sender, int index);
	void setActiveDrive(String drive, TButtonGroup *group);
	TFileView *activeView();
	TFileView *inactiveView();
	void __fastcall onDirChange(TObject *Sender);
	void load();
	void save();
	void saveFV(::TPage *page, TIniFile *ini);
	void loadFV(::TPage *page, TIniFile *ini);
	void __fastcall onChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall onSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall onNotify(TObject *Sender);
	void loadSpecButtons();
	void __fastcall onSpecBtnClick(TObject *Sender);
	void addTab(TPageControl *page, String dir);
	TFileView *viewL();
	TFileView *viewR();
	void loadSpecFolders(TIniFile *ini);
	void saveSpecFolders(TIniFile *ini);
	void __fastcall onSpecPopup(TObject *Sender, TPoint &MousePos,  bool &Handled);
	void updateStatusBar();
	void __fastcall onViewEnter(TObject *Sender);
	void __fastcall onViewExit(TObject *Sender);
	void __fastcall onKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall onKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall onFocusChanged(TBaseVirtualTree* Sender, PVirtualNode Node, TColumnIndex Column);
	getCLSID(String id);
	void __fastcall test(TObject *Sender);
	void __fastcall editActionClick(TObject *Sender);
	void __fastcall removeActionClick(TObject *Sender);
	void __fastcall runActionClick(TObject *Sender);
	void updateNavigationBtns();
	void __fastcall actionUp(TObject *Sender);
	void __fastcall actionDown(TObject *Sender);
	void __fastcall onFindTarget(TObject *Sender);
	//bool actionsModified;
	TpcToolBar *tbSpecFolders;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
