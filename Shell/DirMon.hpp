// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dirmon.pas' rev: 21.00

#ifndef DirmonHPP
#define DirmonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dirmon
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFileOperation { foAdded, foRemoved, foModified, foRenamed };
#pragma option pop

typedef void __fastcall (__closure *TFileDealMethod)(TFileOperation FileOperation, const System::UnicodeString FileName1, const System::UnicodeString FileName2);

#pragma option push -b-
enum TNotifyFilter { nfFileNameChange, nfDirNameChange, nfAttributeChange, nfSizeChange, nfWriteChange, nfAccessChange, nfCreationDateChange, nfSecurityChange };
#pragma option pop

typedef Set<TNotifyFilter, nfFileNameChange, nfSecurityChange>  TNotifyFilters;

typedef StaticArray<System::Byte, 4096> TNotificationBuffer;

struct TFileNotifyInformation;
typedef TFileNotifyInformation *PFileNotifyInformation;

struct TFileNotifyInformation
{
	
public:
	unsigned NextEntryOffset;
	unsigned Action;
	unsigned FileNameLength;
	StaticArray<System::WideChar, 1> FileName;
};


class DELPHICLASS TShellChangeThread;
class PASCALIMPLEMENTATION TShellChangeThread : public Classes::TThread
{
	typedef Classes::TThread inherited;
	
private:
	bool FActived;
	unsigned FDirectoryHandle;
	_RTL_CRITICAL_SECTION FCS;
	TFileDealMethod FChangeEvent;
	System::UnicodeString FDirectory;
	bool FWatchSubTree;
	unsigned FCompletionPort;
	_OVERLAPPED FOverlapped;
	unsigned FNotifyOptionFlags;
	unsigned FBytesWritten;
	TNotificationBuffer FNotificationBuffer;
	
protected:
	virtual void __fastcall Execute(void);
	void __fastcall DoIOCompletionEvent(void);
	bool __fastcall ResetReadDirctory(void);
	void __fastcall Lock(void);
	void __fastcall Unlock(void);
	
public:
	__fastcall virtual TShellChangeThread(TFileDealMethod ChangeEvent);
	__fastcall virtual ~TShellChangeThread(void);
	void __fastcall SetDirectoryOptions(System::UnicodeString Directory, bool Actived, bool WatchSubTree, unsigned NotifyOptionFlags);
	__property TFileDealMethod ChangeEvent = {read=FChangeEvent, write=FChangeEvent};
};


class DELPHICLASS TDirMon;
class PASCALIMPLEMENTATION TDirMon : public Classes::TComponent
{
	typedef Classes::TComponent inherited;
	
private:
	bool FActived;
	System::UnicodeString FWatchedDir;
	TShellChangeThread* FThread;
	TFileDealMethod FOnChange;
	bool FWatchSubTree;
	TNotifyFilters FFilters;
	void __fastcall SetWatchedDir(const System::UnicodeString Value);
	void __fastcall SetWatchSubTree(const bool Value);
	void __fastcall SetOnChange(const TFileDealMethod Value);
	void __fastcall SetFilters(const TNotifyFilters Value);
	unsigned __fastcall NotifyOptionFlags(void);
	void __fastcall SetActived(const bool Value);
	
protected:
	void __fastcall Change(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	
public:
	__fastcall virtual TDirMon(Classes::TComponent* AOwner);
	__fastcall virtual ~TDirMon(void);
	
__published:
	__property bool Actived = {read=FActived, write=SetActived, nodefault};
	__property System::UnicodeString WatchedDir = {read=FWatchedDir, write=SetWatchedDir};
	__property bool WatchSubTree = {read=FWatchSubTree, write=SetWatchSubTree, nodefault};
	__property TNotifyFilters NotifyFilters = {read=FFilters, write=SetFilters, nodefault};
	__property TFileDealMethod OnChange = {read=FOnChange, write=SetOnChange};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dirmon */
using namespace Dirmon;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DirmonHPP
