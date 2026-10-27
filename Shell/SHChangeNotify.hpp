// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Shchangenotify.pas' rev: 21.00

#ifndef ShchangenotifyHPP
#define ShchangenotifyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Comobj.hpp>	// Pascal unit
#include <Shlobj.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Shchangenotify
{
//-- type declarations -------------------------------------------------------
struct NOTIFYREGISTER
{
	
public:
	_ITEMIDLIST *pidlPath;
	bool bWatchSubtree;
};


typedef NOTIFYREGISTER *PNOTIFYREGISTER;

#pragma option push -b-
enum TTextCase { tcAsIs, tcUppercase, tcLowercase };
#pragma option pop

typedef void __fastcall (__closure *TOneParmEvent)(System::TObject* Sender, unsigned Flags, System::UnicodeString Path1);

typedef void __fastcall (__closure *TTwoParmEvent)(System::TObject* Sender, unsigned Flags, System::UnicodeString Path1, System::UnicodeString Path2);

typedef void __fastcall (__closure *TEndSessionQueryEvent)(System::TObject* Sender, bool &CanEndSession);

class DELPHICLASS TSHChangeNotify;
class PASCALIMPLEMENTATION TSHChangeNotify : public Classes::TComponent
{
	typedef Classes::TComponent inherited;
	
private:
	TTextCase fTextCase;
	bool fHardDriveOnly;
	int NotifyCount;
	HWND NotifyHandle;
	StaticArray<NOTIFYREGISTER, 26> NotifyArray;
	_di_IMalloc AllocInterface;
	int PrevMsg;
	System::UnicodeString prevpath1;
	System::UnicodeString prevpath2;
	int fMessageNo;
	TTwoParmEvent fAssocChanged;
	TOneParmEvent fAttributes;
	TOneParmEvent fCreate;
	TOneParmEvent fDelete;
	TOneParmEvent fDriveAdd;
	TOneParmEvent fDriveAddGUI;
	TOneParmEvent fDriveRemoved;
	TOneParmEvent fMediaInserted;
	TOneParmEvent fMediaRemoved;
	TOneParmEvent fMkDir;
	TOneParmEvent fNetShare;
	TOneParmEvent fNetUnshare;
	TTwoParmEvent fRenameFolder;
	TTwoParmEvent fRenameItem;
	TOneParmEvent fRmDir;
	TOneParmEvent fServerDisconnect;
	TOneParmEvent fUpdateDir;
	TOneParmEvent fUpdateImage;
	TOneParmEvent fUpdateItem;
	TEndSessionQueryEvent fEndSessionQuery;
	Classes::TWndMethod OwnerWindowProc;
	void __fastcall SetMessageNo(int value);
	void __fastcall WndProc(Messages::TMessage &msg);
	
protected:
	void __fastcall QueryEndSession(Messages::TMessage &msg);
	
public:
	__fastcall virtual TSHChangeNotify(Classes::TComponent* AOwner);
	__fastcall virtual ~TSHChangeNotify(void);
	void __fastcall Execute(void);
	void __fastcall Stop(void);
	
__published:
	__property int MessageNo = {read=fMessageNo, write=SetMessageNo, default=1024};
	__property TTextCase TextCase = {read=fTextCase, write=fTextCase, default=0};
	__property bool HardDriveOnly = {read=fHardDriveOnly, write=fHardDriveOnly, default=1};
	__property TTwoParmEvent OnAssocChanged = {read=fAssocChanged, write=fAssocChanged};
	__property TOneParmEvent OnAttributes = {read=fAttributes, write=fAttributes};
	__property TOneParmEvent OnCreate = {read=fCreate, write=fCreate};
	__property TOneParmEvent OnDelete = {read=fDelete, write=fDelete};
	__property TOneParmEvent OnDriveAdd = {read=fDriveAdd, write=fDriveAdd};
	__property TOneParmEvent OnDriveAddGUI = {read=fDriveAddGUI, write=fDriveAddGUI};
	__property TOneParmEvent OnDriveRemoved = {read=fDriveRemoved, write=fDriveRemoved};
	__property TOneParmEvent OnMediaInserted = {read=fMediaInserted, write=fMediaInserted};
	__property TOneParmEvent OnMediaRemoved = {read=fMediaRemoved, write=fMediaRemoved};
	__property TOneParmEvent OnMkDir = {read=fMkDir, write=fMkDir};
	__property TOneParmEvent OnNetShare = {read=fNetShare, write=fNetShare};
	__property TOneParmEvent OnNetUnshare = {read=fNetUnshare, write=fNetUnshare};
	__property TTwoParmEvent OnRenameFolder = {read=fRenameFolder, write=fRenameFolder};
	__property TTwoParmEvent OnRenameItem = {read=fRenameItem, write=fRenameItem};
	__property TOneParmEvent OnRmDir = {read=fRmDir, write=fRmDir};
	__property TOneParmEvent OnServerDisconnect = {read=fServerDisconnect, write=fServerDisconnect};
	__property TOneParmEvent OnUpdateDir = {read=fUpdateDir, write=fUpdateDir};
	__property TOneParmEvent OnUpdateImage = {read=fUpdateImage, write=fUpdateImage};
	__property TOneParmEvent OnUpdateItem = {read=fUpdateItem, write=fUpdateItem};
	__property TEndSessionQueryEvent OnEndSessionQuery = {read=fEndSessionQuery, write=fEndSessionQuery};
};


//-- var, const, procedure ---------------------------------------------------
static const ShortInt SHCNF_ACCEPT_INTERRUPTS = 0x1;
static const ShortInt SHCNF_ACCEPT_NON_INTERRUPTS = 0x2;
static const Word SHCNF_NO_PROXY = 0x8000;
extern PACKAGE unsigned lib;
extern PACKAGE void __fastcall Register(void);
extern PACKAGE HWND __stdcall ChangeNotifyRegister(HWND hWnd, int dwFlags, unsigned wEventMask, unsigned uMsg, int cItems, PNOTIFYREGISTER lpItems);
extern PACKAGE bool __stdcall ChangeNotifyDeregister(HWND hWnd);
extern PACKAGE HRESULT __stdcall CreateFromPath(void * Path, Shlobj::PItemIDList PIDL, unsigned &Attributes);

}	/* namespace Shchangenotify */
using namespace Shchangenotify;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ShchangenotifyHPP
