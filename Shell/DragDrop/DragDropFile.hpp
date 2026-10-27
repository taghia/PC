// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dragdropfile.pas' rev: 21.00

#ifndef DragdropfileHPP
#define DragdropfileHPP

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
#include <Dragdroptext.hpp>	// Pascal unit
#include <Shlobj.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dragdropfile
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAnsiStrings;
class PASCALIMPLEMENTATION TAnsiStrings : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
public:
	System::AnsiString operator[](int Index) { return Strings[Index]; }
	
private:
	int FUpdateCount;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnChanging;
	
protected:
	virtual int __fastcall GetCapacity(void);
	virtual void __fastcall SetCapacity(const int Value);
	virtual int __fastcall GetCount(void) = 0 ;
	virtual System::AnsiString __fastcall Get(int Index) = 0 ;
	System::AnsiString __fastcall GetTextStr(void);
	virtual void __fastcall Put(int Index, const System::AnsiString Value) = 0 ;
	void __fastcall SetTextStr(const System::AnsiString Value);
	__property int Capacity = {read=GetCapacity, write=SetCapacity, nodefault};
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	virtual void __fastcall Changed(void);
	virtual void __fastcall Changing(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	virtual int __fastcall Add(const System::AnsiString S);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	virtual int __fastcall IndexOf(const System::AnsiString S);
	virtual void __fastcall Insert(int Index, const System::AnsiString S) = 0 ;
	virtual void __fastcall Clear(void) = 0 ;
	virtual void __fastcall Delete(int Index) = 0 ;
	virtual void __fastcall Exchange(int Index1, int Index2);
	virtual void __fastcall Move(int CurIndex, int NewIndex);
	void __fastcall SaveToFile(const System::UnicodeString FileName);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	__property int Count = {read=GetCount, nodefault};
	__property System::AnsiString Strings[int Index] = {read=Get, write=Put/*, default*/};
	__property System::AnsiString Text = {read=GetTextStr, write=SetTextStr};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TAnsiStrings(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TAnsiStrings(void) : Classes::TPersistent() { }
	
};


class DELPHICLASS TAnsiStringList;
class PASCALIMPLEMENTATION TAnsiStringList : public TAnsiStrings
{
	typedef TAnsiStrings inherited;
	
private:
	typedef DynamicArray<System::AnsiString> _TAnsiStringList__1;
	
	
private:
	_TAnsiStringList__1 FStrings;
	int FCount;
	
protected:
	void __fastcall Grow(void);
	virtual int __fastcall GetCapacity(void);
	virtual void __fastcall SetCapacity(const int Value);
	virtual int __fastcall GetCount(void);
	virtual System::AnsiString __fastcall Get(int Index);
	virtual void __fastcall Put(int Index, const System::AnsiString Value);
	
public:
	virtual void __fastcall Insert(int Index, const System::AnsiString S);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int Index);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TAnsiStringList(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TAnsiStringList(void) : TAnsiStrings() { }
	
};


class DELPHICLASS TUnicodeStrings;
class PASCALIMPLEMENTATION TUnicodeStrings : public Classes::TPersistent
{
	typedef Classes::TPersistent inherited;
	
public:
	System::UnicodeString operator[](int Index) { return Strings[Index]; }
	
private:
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnChanging;
	int FUpdateCount;
	
protected:
	virtual int __fastcall GetCapacity(void);
	virtual void __fastcall SetCapacity(const int Value);
	virtual int __fastcall GetCount(void) = 0 ;
	virtual System::UnicodeString __fastcall Get(int Index) = 0 ;
	System::UnicodeString __fastcall GetTextStr(void);
	virtual void __fastcall Put(int Index, const System::UnicodeString Value) = 0 ;
	void __fastcall SetTextStr(const System::UnicodeString Value);
	__property int Capacity = {read=GetCapacity, write=SetCapacity, nodefault};
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	virtual void __fastcall Changed(void);
	virtual void __fastcall Changing(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	virtual int __fastcall Add(const System::UnicodeString S);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	virtual int __fastcall IndexOf(const System::UnicodeString S);
	virtual void __fastcall Insert(int Index, const System::UnicodeString S) = 0 ;
	virtual void __fastcall Clear(void) = 0 ;
	virtual void __fastcall Delete(int Index) = 0 ;
	virtual void __fastcall Exchange(int Index1, int Index2);
	virtual void __fastcall Move(int CurIndex, int NewIndex);
	void __fastcall SaveToFile(const System::UnicodeString FileName);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Strings[int Index] = {read=Get, write=Put/*, default*/};
	__property System::UnicodeString Text = {read=GetTextStr, write=SetTextStr};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TUnicodeStrings(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TUnicodeStrings(void) : Classes::TPersistent() { }
	
};


class DELPHICLASS TUnicodeStringList;
class PASCALIMPLEMENTATION TUnicodeStringList : public TUnicodeStrings
{
	typedef TUnicodeStrings inherited;
	
private:
	typedef DynamicArray<System::UnicodeString> _TUnicodeStringList__1;
	
	
private:
	_TUnicodeStringList__1 FStrings;
	int FCount;
	
protected:
	void __fastcall Grow(void);
	virtual int __fastcall GetCapacity(void);
	virtual void __fastcall SetCapacity(const int Value);
	virtual int __fastcall GetCount(void);
	virtual System::UnicodeString __fastcall Get(int Index);
	virtual void __fastcall Put(int Index, const System::UnicodeString Value);
	
public:
	virtual void __fastcall Insert(int Index, const System::UnicodeString S);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int Index);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TUnicodeStringList(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TUnicodeStringList(void) : TUnicodeStrings() { }
	
};


class DELPHICLASS TUnicodeStringsAdapter;
class PASCALIMPLEMENTATION TUnicodeStringsAdapter : public TUnicodeStrings
{
	typedef TUnicodeStrings inherited;
	
private:
	Classes::TStrings* FStrings;
	
protected:
	virtual int __fastcall GetCapacity(void);
	virtual int __fastcall GetCount(void);
	virtual System::UnicodeString __fastcall Get(int Index);
	virtual void __fastcall Put(int Index, const System::UnicodeString Value);
	
public:
	__fastcall TUnicodeStringsAdapter(Classes::TStrings* AStrings);
	virtual void __fastcall Insert(int Index, const System::UnicodeString S);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int Index);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TUnicodeStringsAdapter(void) { }
	
};


typedef TUnicodeStrings TFileStrings;

typedef TUnicodeStringList TFileStringList;

class DELPHICLASS TFileStringsAdapter;
class PASCALIMPLEMENTATION TFileStringsAdapter : public TUnicodeStrings
{
	typedef TUnicodeStrings inherited;
	
private:
	Classes::TStrings* FStrings;
	
protected:
	virtual int __fastcall GetCapacity(void);
	virtual int __fastcall GetCount(void);
	virtual System::UnicodeString __fastcall Get(int Index);
	virtual void __fastcall Put(int Index, const System::UnicodeString Value);
	
public:
	__fastcall TFileStringsAdapter(Classes::TStrings* AStrings);
	virtual void __fastcall Insert(int Index, const System::UnicodeString S);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int Index);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFileStringsAdapter(void) { }
	
};


class DELPHICLASS TFileClipboardFormat;
class PASCALIMPLEMENTATION TFileClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	TUnicodeStrings* FFiles;
	bool FWide;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	__property bool Wide = {read=FWide, nodefault};
	
public:
	__fastcall virtual TFileClipboardFormat(void);
	__fastcall virtual ~TFileClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property TUnicodeStrings* Files = {read=FFiles};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TAnsiFilenameClipboardFormat;
class PASCALIMPLEMENTATION TAnsiFilenameClipboardFormat : public Dragdroptext::TCustomAnsiTextClipboardFormat
{
	typedef Dragdroptext::TCustomAnsiTextClipboardFormat inherited;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	__property System::AnsiString Filename = {read=GetString, write=SetString};
public:
	/* TCustomAnsiTextClipboardFormat.Create */ inline __fastcall virtual TAnsiFilenameClipboardFormat(void) : Dragdroptext::TCustomAnsiTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TAnsiFilenameClipboardFormat(int Atymed) : Dragdroptext::TCustomAnsiTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TAnsiFilenameClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdroptext::TCustomAnsiTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TAnsiFilenameClipboardFormat(void) { }
	
};


class DELPHICLASS TUnicodeFilenameClipboardFormat;
class PASCALIMPLEMENTATION TUnicodeFilenameClipboardFormat : public Dragdroptext::TCustomUnicodeTextClipboardFormat
{
	typedef Dragdroptext::TCustomUnicodeTextClipboardFormat inherited;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	__property System::UnicodeString Filename = {read=GetText, write=SetText};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TUnicodeFilenameClipboardFormat(void) : Dragdroptext::TCustomUnicodeTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TUnicodeFilenameClipboardFormat(int Atymed) : Dragdroptext::TCustomUnicodeTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TUnicodeFilenameClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdroptext::TCustomUnicodeTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TUnicodeFilenameClipboardFormat(void) { }
	
};


typedef TUnicodeFilenameClipboardFormat TFilenameWClipboardFormat [[deprecated("Use TUnicodeFilenameClipboardFormat instead")]];

typedef TUnicodeFilenameClipboardFormat TFilenameClipboardFormat;

class DELPHICLASS TAnsiFilenameMapClipboardFormat;
class PASCALIMPLEMENTATION TAnsiFilenameMapClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	Classes::TStrings* FFileMaps;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	
public:
	__fastcall virtual TAnsiFilenameMapClipboardFormat(void);
	__fastcall virtual ~TAnsiFilenameMapClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property Classes::TStrings* FileMaps = {read=FFileMaps};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TAnsiFilenameMapClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TAnsiFilenameMapClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TUnicodeFilenameMapClipboardFormat;
class PASCALIMPLEMENTATION TUnicodeFilenameMapClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	TUnicodeStrings* FFileMaps;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	
public:
	__fastcall virtual TUnicodeFilenameMapClipboardFormat(void);
	__fastcall virtual ~TUnicodeFilenameMapClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property TUnicodeStrings* FileMaps = {read=FFileMaps};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TUnicodeFilenameMapClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TUnicodeFilenameMapClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


typedef TUnicodeFilenameMapClipboardFormat TFilenameMapWClipboardFormat [[deprecated("Use TUnicodeFilenameMapClipboardFormat instead")]];

typedef TUnicodeFilenameMapClipboardFormat TFilenameMapClipboardFormat;

class DELPHICLASS TFileMapDataFormat;
class PASCALIMPLEMENTATION TFileMapDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	TUnicodeStrings* FFileMaps;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	__fastcall virtual TFileMapDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */;
	__fastcall virtual ~TFileMapDataFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property TUnicodeStrings* FileMaps = {read=FFileMaps};
};


class DELPHICLASS TFileDataFormat;
class PASCALIMPLEMENTATION TFileDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	TUnicodeStrings* FFiles;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	__fastcall virtual TFileDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */;
	__fastcall virtual ~TFileDataFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property TUnicodeStrings* Files = {read=FFiles};
};


class DELPHICLASS TFileGroupDescriptorCustomClipboardFormat;
class PASCALIMPLEMENTATION TFileGroupDescriptorCustomClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	void *FBuffer;
	
protected:
	void * __fastcall GetFileDescriptor(int Index);
	int __fastcall GetCount(void);
	void __fastcall SetCount(const int Value);
	virtual System::UnicodeString __fastcall GetFilename(int Index) = 0 ;
	virtual void __fastcall SetFilename(int Index, const System::UnicodeString Value) = 0 ;
	virtual int __fastcall GetBufferSize(int Count) = 0 ;
	virtual int __fastcall GetSize(void);
	void __fastcall CopyFrom(void * Source);
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	__property void * FileGroupDescriptor = {read=FBuffer};
	__property void * FileDescriptors[int Index] = {read=GetFileDescriptor};
	
public:
	__fastcall virtual ~TFileGroupDescriptorCustomClipboardFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property int Count = {read=GetCount, write=SetCount, nodefault};
	__property System::UnicodeString Filenames[int Index] = {read=GetFilename, write=SetFilename};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TFileGroupDescriptorCustomClipboardFormat(void) : Dragdropformats::TCustomSimpleClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileGroupDescriptorCustomClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileGroupDescriptorCustomClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TAnsiFileGroupDescriptorClipboardFormat;
class PASCALIMPLEMENTATION TAnsiFileGroupDescriptorClipboardFormat : public TFileGroupDescriptorCustomClipboardFormat
{
	typedef TFileGroupDescriptorCustomClipboardFormat inherited;
	
protected:
	System::AnsiString __fastcall GetAnsiFilename(int Index);
	void __fastcall SetAnsiFilename(int Index, const System::AnsiString Value);
	HIDESBASE Shlobj::PFileDescriptorA __fastcall GetFileDescriptor(int Index);
	Shlobj::PFileGroupDescriptorA __fastcall GetFileGroupDescriptor(void);
	virtual int __fastcall GetBufferSize(int Count);
	virtual System::UnicodeString __fastcall GetFilename(int Index);
	virtual void __fastcall SetFilename(int Index, const System::UnicodeString Value);
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	HIDESBASE void __fastcall CopyFrom(Shlobj::PFileGroupDescriptorA AFileGroupDescriptor);
	__property Shlobj::PFileGroupDescriptorA FileGroupDescriptor = {read=GetFileGroupDescriptor};
	__property Shlobj::PFileDescriptorA FileDescriptors[int Index] = {read=GetFileDescriptor};
	__property System::AnsiString Filenames[int Index] = {read=GetAnsiFilename, write=SetAnsiFilename};
public:
	/* TFileGroupDescriptorCustomClipboardFormat.Destroy */ inline __fastcall virtual ~TAnsiFileGroupDescriptorClipboardFormat(void) { }
	
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TAnsiFileGroupDescriptorClipboardFormat(void) : TFileGroupDescriptorCustomClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TAnsiFileGroupDescriptorClipboardFormat(int Atymed) : TFileGroupDescriptorCustomClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TAnsiFileGroupDescriptorClipboardFormat(const tagFORMATETC &AFormatEtc) : TFileGroupDescriptorCustomClipboardFormat(AFormatEtc) { }
	
};


struct TFileGroupDescriptorW
{
	
public:
	unsigned cItems;
	StaticArray<_FILEDESCRIPTORW, 1> fgd;
};


typedef TFileGroupDescriptorW *PFileGroupDescriptorW;

class DELPHICLASS TUnicodeFileGroupDescriptorClipboardFormat;
class PASCALIMPLEMENTATION TUnicodeFileGroupDescriptorClipboardFormat : public TFileGroupDescriptorCustomClipboardFormat
{
	typedef TFileGroupDescriptorCustomClipboardFormat inherited;
	
protected:
	System::UnicodeString __fastcall GetUnicodeFilename(int Index);
	void __fastcall SetUnicodeFilename(int Index, const System::UnicodeString Value);
	HIDESBASE Shlobj::PFileDescriptorW __fastcall GetFileDescriptor(int Index);
	PFileGroupDescriptorW __fastcall GetFileGroupDescriptor(void);
	virtual int __fastcall GetBufferSize(int Count);
	virtual System::UnicodeString __fastcall GetFilename(int Index);
	virtual void __fastcall SetFilename(int Index, const System::UnicodeString Value);
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	HIDESBASE void __fastcall CopyFrom(PFileGroupDescriptorW AFileGroupDescriptor);
	__property PFileGroupDescriptorW FileGroupDescriptor = {read=GetFileGroupDescriptor};
	__property Shlobj::PFileDescriptorW FileDescriptors[int Index] = {read=GetFileDescriptor};
	__property System::UnicodeString Filenames[int Index] = {read=GetUnicodeFilename, write=SetUnicodeFilename};
public:
	/* TFileGroupDescriptorCustomClipboardFormat.Destroy */ inline __fastcall virtual ~TUnicodeFileGroupDescriptorClipboardFormat(void) { }
	
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TUnicodeFileGroupDescriptorClipboardFormat(void) : TFileGroupDescriptorCustomClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TUnicodeFileGroupDescriptorClipboardFormat(int Atymed) : TFileGroupDescriptorCustomClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TUnicodeFileGroupDescriptorClipboardFormat(const tagFORMATETC &AFormatEtc) : TFileGroupDescriptorCustomClipboardFormat(AFormatEtc) { }
	
};


typedef TUnicodeFileGroupDescriptorClipboardFormat TFileGroupDescriptorWClipboardFormat [[deprecated("Use TUnicodeFileGroupDescriptorClipboardFormat instead")]];

typedef TUnicodeFileGroupDescriptorClipboardFormat TFileGroupDescriptorClipboardFormat;

class DELPHICLASS TFileContentsClipboardFormat;
class PASCALIMPLEMENTATION TFileContentsClipboardFormat : public Dragdropformats::TCustomAnsiStringClipboardFormat
{
	typedef Dragdropformats::TCustomAnsiStringClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__fastcall virtual TFileContentsClipboardFormat(void);
	__property Data;
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileContentsClipboardFormat(int Atymed) : Dragdropformats::TCustomAnsiStringClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileContentsClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomAnsiStringClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TFileContentsClipboardFormat(void) { }
	
};


class DELPHICLASS TFileContentsStreamClipboardFormat;
class PASCALIMPLEMENTATION TFileContentsStreamClipboardFormat : public Dragdrop::TClipboardFormat
{
	typedef Dragdrop::TClipboardFormat inherited;
	
private:
	Dragdropformats::TStreamList* FStreams;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	
public:
	__fastcall virtual TFileContentsStreamClipboardFormat(void);
	__fastcall virtual ~TFileContentsStreamClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall GetData(const _di_IDataObject DataObject);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	__property Dragdropformats::TStreamList* Streams = {read=FStreams};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileContentsStreamClipboardFormat(int Atymed) : Dragdrop::TClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileContentsStreamClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdrop::TClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TFileContentsStreamOnDemandClipboardFormat;
typedef void __fastcall (__closure *TOnGetStreamEvent)(TFileContentsStreamOnDemandClipboardFormat* Sender, int Index, /* out */ _di_IStream &AStream);

class PASCALIMPLEMENTATION TFileContentsStreamOnDemandClipboardFormat : public Dragdrop::TClipboardFormat
{
	typedef Dragdrop::TClipboardFormat inherited;
	
private:
	TOnGetStreamEvent FOnGetStream;
	bool FGotData;
	bool FDataRequested;
	
protected:
	virtual bool __fastcall DoSetData(const tagFORMATETC &AFormatEtcIn, tagSTGMEDIUM &AMedium);
	
public:
	__fastcall virtual TFileContentsStreamOnDemandClipboardFormat(void);
	__fastcall virtual ~TFileContentsStreamOnDemandClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall GetData(const _di_IDataObject DataObject);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	virtual bool __fastcall Assign(Dragdrop::TCustomDataFormat* Source);
	_di_IStream __fastcall GetStream(int Index);
	__property TOnGetStreamEvent OnGetStream = {read=FOnGetStream, write=FOnGetStream};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileContentsStreamOnDemandClipboardFormat(int Atymed) : Dragdrop::TClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileContentsStreamOnDemandClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdrop::TClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TFileContentsStorageClipboardFormat;
class PASCALIMPLEMENTATION TFileContentsStorageClipboardFormat : public Dragdrop::TClipboardFormat
{
	typedef Dragdrop::TClipboardFormat inherited;
	
private:
	Dragdropformats::TStorageInterfaceList* FStorages;
	
protected:
	virtual bool __fastcall DoSetData(const tagFORMATETC &AFormatEtcIn, tagSTGMEDIUM &AMedium);
	
public:
	__fastcall virtual TFileContentsStorageClipboardFormat(void);
	__fastcall virtual ~TFileContentsStorageClipboardFormat(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall GetData(const _di_IDataObject DataObject);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	__property Dragdropformats::TStorageInterfaceList* Storages = {read=FStorages};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TFileContentsStorageClipboardFormat(int Atymed) : Dragdrop::TClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TFileContentsStorageClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdrop::TClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TVirtualFileStreamDataFormat;
class PASCALIMPLEMENTATION TVirtualFileStreamDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	Dragdropformats::TMemoryList* FFileDescriptors;
	Classes::TStrings* FFileNames;
	TFileContentsStreamOnDemandClipboardFormat* FFileContentsClipboardFormat;
	TAnsiFileGroupDescriptorClipboardFormat* FAnsiFileGroupDescriptorClipboardFormat;
	TUnicodeFileGroupDescriptorClipboardFormat* FUnicodeFileGroupDescriptorClipboardFormat;
	bool FHasContents;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	void __fastcall SetFileNames(const Classes::TStrings* Value);
	TOnGetStreamEvent __fastcall GetOnGetStream(void);
	void __fastcall SetOnGetStream(const TOnGetStreamEvent Value);
	Shlobj::PFileDescriptorW __fastcall GetFileDescriptor(int Index);
	
public:
	__fastcall virtual TVirtualFileStreamDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */;
	__fastcall virtual ~TVirtualFileStreamDataFormat(void);
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property Shlobj::PFileDescriptorW FileDescriptors[int Index] = {read=GetFileDescriptor};
	__property Classes::TStrings* FileNames = {read=FFileNames, write=SetFileNames};
	__property TFileContentsStreamOnDemandClipboardFormat* FileContentsClipboardFormat = {read=FFileContentsClipboardFormat};
	__property TAnsiFileGroupDescriptorClipboardFormat* AnsiFileGroupDescriptorClipboardFormat = {read=FAnsiFileGroupDescriptorClipboardFormat};
	__property TUnicodeFileGroupDescriptorClipboardFormat* UnicodeFileGroupDescriptorClipboardFormat = {read=FUnicodeFileGroupDescriptorClipboardFormat};
	__property TUnicodeFileGroupDescriptorClipboardFormat* FileGroupDescriptorClipboardFormat = {read=FUnicodeFileGroupDescriptorClipboardFormat};
	__property TOnGetStreamEvent OnGetStream = {read=GetOnGetStream, write=SetOnGetStream};
};


class DELPHICLASS TDropFileTarget;
class PASCALIMPLEMENTATION TDropFileTarget : public Droptarget::TCustomDropMultiTarget
{
	typedef Droptarget::TCustomDropMultiTarget inherited;
	
private:
	TFileDataFormat* FFileFormat;
	TFileMapDataFormat* FFileMapFormat;
	
protected:
	TUnicodeStrings* __fastcall GetFiles(void);
	TUnicodeStrings* __fastcall GetMappedNames(void);
	virtual int __fastcall GetPreferredDropEffect(void);
	
public:
	__fastcall virtual TDropFileTarget(Classes::TComponent* AOwner);
	__fastcall virtual ~TDropFileTarget(void);
	__property TUnicodeStrings* Files = {read=GetFiles};
	__property TUnicodeStrings* MappedNames = {read=GetMappedNames};
	__property OptimizedMove = {default=1};
};


class DELPHICLASS TDropFileSource;
class PASCALIMPLEMENTATION TDropFileSource : public Dropsource::TCustomDropMultiSource
{
	typedef Dropsource::TCustomDropMultiSource inherited;
	
private:
	TFileDataFormat* FFileFormat;
	TFileMapDataFormat* FFileMapFormat;
	TUnicodeStrings* __fastcall GetFiles(void);
	TUnicodeStrings* __fastcall GetMappedNames(void);
	
protected:
	void __fastcall SetFiles(TUnicodeStrings* AFiles);
	void __fastcall SetMappedNames(TUnicodeStrings* ANames);
	
public:
	__fastcall virtual TDropFileSource(Classes::TComponent* AOwner);
	__fastcall virtual ~TDropFileSource(void);
	__property TUnicodeStrings* Files = {read=GetFiles, write=SetFiles};
	__property TUnicodeStrings* MappedNames = {read=GetMappedNames, write=SetMappedNames};
};


//-- var, const, procedure ---------------------------------------------------
static const Word FD_PROGRESSUI = 0x4000;
extern PACKAGE bool __fastcall ReadFilesFromHGlobal(const unsigned HGlob, TUnicodeStrings* Files)/* overload */;
extern PACKAGE bool __fastcall ReadFilesFromHGlobal(const unsigned HGlob, Classes::TStrings* Files)/* overload */;
extern PACKAGE bool __fastcall ReadFilesFromData(void * Data, int Size, TUnicodeStrings* Files)/* overload */;
extern PACKAGE bool __fastcall ReadFilesFromData(void * Data, int Size, Classes::TStrings* Files)/* overload */;
extern PACKAGE bool __fastcall ReadFilesFromZeroList(const void * Data, int Size, bool Wide, TUnicodeStrings* Files)/* overload */;
extern PACKAGE bool __fastcall ReadFilesFromZeroList(const void * Data, int Size, bool Wide, Classes::TStrings* Files)/* overload */;
extern PACKAGE bool __fastcall WriteFilesToZeroList(void * Data, int Size, bool Wide, const TUnicodeStrings* Files)/* overload */;
extern PACKAGE bool __fastcall WriteFilesToZeroList(void * Data, int Size, bool Wide, const Classes::TStrings* Files)/* overload */;

}	/* namespace Dragdropfile */
using namespace Dragdropfile;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragdropfileHPP
