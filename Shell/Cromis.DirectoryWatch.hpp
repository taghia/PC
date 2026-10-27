// CodeGear C++Builder
// Copyright (c) 1995, 2013 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Cromis.DirectoryWatch.pas' rev: 25.00 (Windows)

#ifndef Cromis_DirectorywatchHPP
#define Cromis_DirectorywatchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.SyncObjs.hpp>	// Pascal unit
#include <System.DateUtils.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cromis
{
namespace Directorywatch
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TWatchOption : unsigned char { woFileName, woDirName, woAttributes, woSize, woLastWrite, woLastAccess, woCreation, woSecurity };

typedef System::Set<TWatchOption, TWatchOption::woFileName, TWatchOption::woSecurity>  TWatchOptions;

enum DECLSPEC_DENUM TWatchAction : unsigned char { waAdded, waRemoved, waModified, waRenamedOld, waRenamedNew };

typedef System::Set<TWatchAction, TWatchAction::waAdded, TWatchAction::waRenamedNew>  TWatchActions;

typedef void __fastcall (__closure *TFileChangeNotifyEvent)(System::TObject* const Sender, const TWatchAction Action, const System::UnicodeString FileName);

typedef void __fastcall (__closure *TOnError)(System::TObject* const Sender, const int ErrorCode, const System::UnicodeString ErrorMessage);

class DELPHICLASS TDirectoryWatch;
class PASCALIMPLEMENTATION TDirectoryWatch : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TWatchOptions FWatchOptions;
	TWatchActions FWatchActions;
	bool FWatchSubTree;
	System::Classes::TThread* FWatchThread;
	int FBufferSize;
	HWND FWndHandle;
	System::UnicodeString FDirectory;
	NativeUInt FAbortEvent;
	TOnError FOnError;
	System::Classes::TNotifyEvent FOnChange;
	TFileChangeNotifyEvent FOnNotify;
	void __fastcall WatchWndProc(Winapi::Messages::TMessage &Msg);
	void __fastcall SetDirectory(const System::UnicodeString Value);
	void __fastcall SetWatchOptions(const TWatchOptions Value);
	void __fastcall SetWatchActions(const TWatchActions Value);
	void __fastcall SetWatchSubTree(const bool Value);
	void __fastcall DeallocateHWnd(HWND Wnd);
	int __fastcall MakeFilter(void);
	
protected:
	virtual void __fastcall Change(void);
	void __fastcall AllocWatchThread(void);
	void __fastcall ReleaseWatchThread(void);
	void __fastcall RestartWatchThread(void);
	virtual void __fastcall Notify(const int Action, const System::UnicodeString FileName);
	
public:
	__fastcall TDirectoryWatch(void);
	__fastcall virtual ~TDirectoryWatch(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	bool __fastcall Running(void);
	__property bool WatchSubTree = {read=FWatchSubTree, write=SetWatchSubTree, nodefault};
	__property TWatchOptions WatchOptions = {read=FWatchOptions, write=SetWatchOptions, nodefault};
	__property TWatchActions WatchActions = {read=FWatchActions, write=SetWatchActions, nodefault};
	__property int BufferSize = {read=FBufferSize, write=FBufferSize, nodefault};
	__property System::UnicodeString Directory = {read=FDirectory, write=SetDirectory};
	__property TFileChangeNotifyEvent OnNotify = {read=FOnNotify, write=FOnNotify};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TOnError OnError = {read=FOnError, write=FOnError};
};


//-- var, const, procedure ---------------------------------------------------
static const System::Word cShutdownTimeout = System::Word(0xbb8);
static const System::Int8 cFileWaitTimeout = System::Int8(0x0);
extern DELPHI_PACKAGE void __fastcall WaitForFileReady(const System::UnicodeString FileName, const unsigned Timeout = (unsigned)(0x0));
}	/* namespace Directorywatch */
}	/* namespace Cromis */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_CROMIS_DIRECTORYWATCH)
using namespace Cromis::Directorywatch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_CROMIS)
using namespace Cromis;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Cromis_DirectorywatchHPP
