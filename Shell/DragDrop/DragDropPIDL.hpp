// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dragdroppidl.pas' rev: 21.00

#ifndef DragdroppidlHPP
#define DragdroppidlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Dragdrop.hpp>	// Pascal unit
#include <Droptarget.hpp>	// Pascal unit
#include <Dropsource.hpp>	// Pascal unit
#include <Dragdropformats.hpp>	// Pascal unit
#include <Dragdropfile.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Shlobj.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dragdroppidl
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPIDLList;
class PASCALIMPLEMENTATION TPIDLList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::AnsiString operator[](int Index) { return Strings[Index]; }
	
private:
	Classes::TList* FList;
	Classes::TNotifyEvent FOnChanging;
	
protected:
	int __fastcall GetCount(void);
	Shlobj::PItemIDList __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, const Shlobj::PItemIDList Value);
	System::AnsiString __fastcall GetString(int Index);
	void __fastcall Changing(void);
	
public:
	__fastcall TPIDLList(void);
	__fastcall virtual ~TPIDLList(void);
	void __fastcall Add(Shlobj::PItemIDList Item)/* overload */;
	void __fastcall Add(System::AnsiString Item)/* overload */;
	void __fastcall Assign(TPIDLList* Source);
	void __fastcall Clear(void);
	__property int Count = {read=GetCount, nodefault};
	__property Shlobj::PItemIDList Items[int Index] = {read=GetItem, write=SetItem};
	__property System::AnsiString Strings[int Index] = {read=GetString/*, default*/};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
};


class DELPHICLASS TPIDLClipboardFormat;
class PASCALIMPLEMENTATION TPIDLClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	TPIDLList* FPIDLs;
	Dragdropfile::TUnicodeStrings* FFilenames;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	
public:
	__fastcall virtual TPIDLClipboardFormat(void);
	__fastcall virtual ~TPIDLClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property TPIDLList* PIDLs = {read=FPIDLs};
	__property Dragdropfile::TUnicodeStrings* Filenames = {read=FFilenames};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TPIDLClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TPIDLClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TPIDLDataFormat;
class PASCALIMPLEMENTATION TPIDLDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	TPIDLList* FPIDLs;
	Dragdropfile::TUnicodeStrings* FFilenames;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	__fastcall virtual TPIDLDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */;
	__fastcall virtual ~TPIDLDataFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property TPIDLList* PIDLs = {read=FPIDLs};
	__property Dragdropfile::TUnicodeStrings* Filenames = {read=FFilenames};
};


class DELPHICLASS TDropPIDLTarget;
class PASCALIMPLEMENTATION TDropPIDLTarget : public Droptarget::TCustomDropMultiTarget
{
	typedef Droptarget::TCustomDropMultiTarget inherited;
	
private:
	TPIDLDataFormat* FPIDLDataFormat;
	Dragdropfile::TFileMapDataFormat* FFileMapDataFormat;
	
protected:
	TPIDLList* __fastcall GetPIDLs(void);
	int __fastcall GetPIDLCount(void);
	Dragdropfile::TUnicodeStrings* __fastcall GetMappedNames(void);
	Dragdropfile::TUnicodeStrings* __fastcall GetFilenames(void);
	__property TPIDLList* PIDLs = {read=GetPIDLs};
	Shlobj::PItemIDList __fastcall DoGetPIDL(int Index);
	virtual int __fastcall GetPreferredDropEffect(void);
	
public:
	__fastcall virtual TDropPIDLTarget(Classes::TComponent* AOwner);
	__fastcall virtual ~TDropPIDLTarget(void);
	Shlobj::PItemIDList __fastcall GetFolderPIDL(void);
	Shlobj::PItemIDList __fastcall GetRelativeFilePIDL(int Index);
	Shlobj::PItemIDList __fastcall GetAbsoluteFilePIDL(int Index);
	__property int PIDLCount = {read=GetPIDLCount, nodefault};
	__property Dragdropfile::TUnicodeStrings* Filenames = {read=GetFilenames};
	__property Dragdropfile::TUnicodeStrings* MappedNames = {read=GetMappedNames};
};


class DELPHICLASS TDropPIDLSource;
class PASCALIMPLEMENTATION TDropPIDLSource : public Dropsource::TCustomDropMultiSource
{
	typedef Dropsource::TCustomDropMultiSource inherited;
	
private:
	TPIDLDataFormat* FPIDLDataFormat;
	Dragdropfile::TFileMapDataFormat* FFileMapDataFormat;
	
protected:
	Dragdropfile::TUnicodeStrings* __fastcall GetMappedNames(void);
	
public:
	__fastcall virtual TDropPIDLSource(Classes::TComponent* AOwner);
	__fastcall virtual ~TDropPIDLSource(void);
	void __fastcall CopyFolderPIDLToList(Shlobj::PItemIDList pidl);
	void __fastcall CopyFilePIDLToList(Shlobj::PItemIDList pidl);
	__property Dragdropfile::TUnicodeStrings* MappedNames = {read=GetMappedNames};
};


typedef Shlobj::PItemIDList __stdcall (*TILFindLastID)(Shlobj::PItemIDList Pidl);

typedef BOOL __stdcall (*TILRemoveLastID)(Shlobj::PItemIDList Pidl);

typedef Shlobj::PItemIDList __stdcall (*TILClone)(Shlobj::PItemIDList Pidl);

typedef Shlobj::PItemIDList __stdcall (*TILCloneFirst)(Shlobj::PItemIDList Pidl);

typedef BOOL __stdcall (*TILIsEqual)(Shlobj::PItemIDList Pidl1, Shlobj::PItemIDList Pidl2);

typedef Shlobj::PItemIDList __stdcall (*TILCombine)(Shlobj::PItemIDList Pidl1, Shlobj::PItemIDList Pidl2);

typedef System::Word __stdcall (*TILGetSize)(Shlobj::PItemIDList Pidl);

typedef Shlobj::PItemIDList __stdcall (*TILGetNext)(Shlobj::PItemIDList Pidl);

typedef void __stdcall (*TILFree)(Shlobj::PItemIDList Pidl);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TILFindLastID ILFindLastID;
extern PACKAGE TILRemoveLastID ILRemoveLastID;
extern PACKAGE TILClone ILClone;
extern PACKAGE TILCloneFirst ILCloneFirst;
extern PACKAGE TILIsEqual ILIsEqual;
extern PACKAGE TILCombine ILCombine;
extern PACKAGE TILGetSize ILGetSize;
extern PACKAGE TILGetNext ILGetNext;
extern PACKAGE TILFree ILFree;
extern PACKAGE bool __fastcall GetPIDLsFromData(void * Data, int Size, TPIDLList* PIDLs);
extern PACKAGE bool __fastcall GetPIDLsFromHGlobal(const unsigned HGlob, TPIDLList* PIDLs);
extern PACKAGE System::AnsiString __fastcall GetRootFolderPIDL(const Dragdropfile::TUnicodeStrings* Files)/* overload */;
extern PACKAGE System::AnsiString __fastcall GetRootFolderPIDL(const Classes::TStrings* Files)/* overload */;
extern PACKAGE bool __fastcall GetPIDLsFromFilenames(const Dragdropfile::TUnicodeStrings* Files, TPIDLList* PIDLs)/* overload */;
extern PACKAGE bool __fastcall GetPIDLsFromFilenames(const Classes::TStrings* Files, TPIDLList* PIDLs)/* overload */;
extern PACKAGE int __fastcall GetSizeOfPIDL(Shlobj::PItemIDList PIDL);
extern PACKAGE Shlobj::PItemIDList __fastcall CopyPIDL(Shlobj::PItemIDList PIDL);
extern PACKAGE Shlobj::PItemIDList __fastcall GetFullPIDLFromPath(const System::UnicodeString Path);
extern PACKAGE System::UnicodeString __fastcall GetFullPathFromPIDL(Shlobj::PItemIDList PIDL);
extern PACKAGE unsigned __fastcall ConvertFilesToShellIDList(const System::UnicodeString Path, Classes::TStrings* Files);
extern PACKAGE System::AnsiString __fastcall PIDLToString(Shlobj::PItemIDList pidl);
extern PACKAGE Shlobj::PItemIDList __fastcall StringToPIDL(const System::AnsiString PIDL);
extern PACKAGE System::AnsiString __fastcall JoinPIDLStrings(const System::AnsiString pidl1, const System::AnsiString pidl2);
extern PACKAGE _di_IShellFolder __fastcall GetShellFolderOfPath(const System::UnicodeString FolderPath);
extern PACKAGE Shlobj::PItemIDList __fastcall GetSubPIDL(_di_IShellFolder Folder, const System::UnicodeString Sub);
extern PACKAGE System::UnicodeString __fastcall GetPIDLDisplayName(_di_IShellFolder Folder, Shlobj::PItemIDList PIDL, unsigned Flags = (unsigned)(0x0));

}	/* namespace Dragdroppidl */
using namespace Dragdroppidl;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragdroppidlHPP
