// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dragdropformats.pas' rev: 21.00

#ifndef DragdropformatsHPP
#define DragdropformatsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Dragdrop.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dragdropformats
{
//-- type declarations -------------------------------------------------------
typedef __int64 *PLargeint;

class DELPHICLASS TStreamList;
class PASCALIMPLEMENTATION TStreamList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	Classes::TStream* operator[](int Index) { return Streams[Index]; }
	
private:
	Classes::TStrings* FStreams;
	Classes::TNotifyEvent FOnChanging;
	
protected:
	Classes::TStream* __fastcall GetStream(int Index);
	int __fastcall GetCount(void);
	void __fastcall Changing(void);
	
public:
	__fastcall TStreamList(void);
	__fastcall virtual ~TStreamList(void);
	int __fastcall Add(Classes::TStream* Stream);
	int __fastcall AddNamed(Classes::TStream* Stream, System::UnicodeString Name);
	void __fastcall Delete(int Index);
	void __fastcall Clear(void);
	void __fastcall Assign(TStreamList* Value);
	__property int Count = {read=GetCount, nodefault};
	__property Classes::TStream* Streams[int Index] = {read=GetStream/*, default*/};
	__property Classes::TStrings* Names = {read=FStreams};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
};


class DELPHICLASS TNamedInterfaceList;
class PASCALIMPLEMENTATION TNamedInterfaceList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::_di_IInterface operator[](int Index) { return Items[Index]; }
	
private:
	Classes::TStrings* FList;
	Classes::TNotifyEvent FOnChanging;
	
protected:
	int __fastcall GetCount(void);
	System::UnicodeString __fastcall GetName(int Index);
	void __fastcall SetName(int Index, const System::UnicodeString Value);
	System::_di_IInterface __fastcall GetItem(int Index);
	void __fastcall Changing(void);
	
public:
	__fastcall TNamedInterfaceList(void);
	__fastcall virtual ~TNamedInterfaceList(void);
	int __fastcall Add(const System::_di_IInterface Item);
	int __fastcall AddNamed(const System::_di_IInterface Item, System::UnicodeString Name);
	void __fastcall Delete(int Index);
	void __fastcall Clear(void);
	void __fastcall Assign(TNamedInterfaceList* Value);
	__property System::_di_IInterface Items[int Index] = {read=GetItem/*, default*/};
	__property System::UnicodeString Names[int Index] = {read=GetName, write=SetName};
	__property int Count = {read=GetCount, nodefault};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
};


class DELPHICLASS TStorageInterfaceList;
class PASCALIMPLEMENTATION TStorageInterfaceList : public TNamedInterfaceList
{
	typedef TNamedInterfaceList inherited;
	
public:
	_di_IStorage operator[](int Index) { return Storages[Index]; }
	
protected:
	_di_IStorage __fastcall GetStorage(int Index);
	
public:
	__property _di_IStorage Storages[int Index] = {read=GetStorage/*, default*/};
public:
	/* TNamedInterfaceList.Create */ inline __fastcall TStorageInterfaceList(void) : TNamedInterfaceList() { }
	/* TNamedInterfaceList.Destroy */ inline __fastcall virtual ~TStorageInterfaceList(void) { }
	
};


class DELPHICLASS TFixedStreamAdapter;
class PASCALIMPLEMENTATION TFixedStreamAdapter : public Classes::TStreamAdapter
{
	typedef Classes::TStreamAdapter inherited;
	
private:
	bool FHasSeeked;
	
public:
	virtual HRESULT __stdcall Stat(/* out */ tagSTATSTG &statstg, int grfStatFlag);
	virtual HRESULT __stdcall Seek(__int64 dlibMove, int dwOrigin, /* out */ __int64 &libNewPosition);
	virtual HRESULT __stdcall Read(void * pv, int cb, System::PLongint pcbRead);
	virtual HRESULT __stdcall CopyTo(_di_IStream stm, __int64 cb, /* out */ __int64 &cbRead, /* out */ __int64 &cbWritten);
public:
	/* TStreamAdapter.Create */ inline __fastcall TFixedStreamAdapter(Classes::TStream* Stream, Classes::TStreamOwnership Ownership) : Classes::TStreamAdapter(Stream, Ownership) { }
	/* TStreamAdapter.Destroy */ inline __fastcall virtual ~TFixedStreamAdapter(void) { }
	
private:
	void *__IStream;	/* IStream */
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator _di_IStream()
	{
		_di_IStream intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IStream*(void) { return (IStream*)&__IStream; }
	#endif
	
};


class DELPHICLASS TMemoryList;
class PASCALIMPLEMENTATION TMemoryList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	void * operator[](int Index) { return Items[Index]; }
	
private:
	Classes::TList* FList;
	
protected:
	void * __fastcall Get(int Index);
	int __fastcall GetCount(void);
	
public:
	__fastcall TMemoryList(void);
	__fastcall virtual ~TMemoryList(void);
	int __fastcall Add(void * Item);
	void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	__property int Count = {read=GetCount, nodefault};
	__property void * Items[int Index] = {read=Get/*, default*/};
};


class DELPHICLASS TCustomSimpleClipboardFormat;
class PASCALIMPLEMENTATION TCustomSimpleClipboardFormat : public Dragdrop::TClipboardFormat
{
	typedef Dragdrop::TClipboardFormat inherited;
	
protected:
	virtual bool __fastcall DoGetData(const _di_IDataObject ADataObject, const tagSTGMEDIUM &AMedium);
	virtual bool __fastcall DoGetDataSized(const _di_IDataObject ADataObject, const tagSTGMEDIUM &AMedium, int Size);
	virtual bool __fastcall ReadData(void * Value, int Size) = 0 ;
	virtual bool __fastcall ReadDataInto(const _di_IDataObject ADataObject, const tagSTGMEDIUM &AMedium, void * Buffer, int Size);
	virtual bool __fastcall DoSetData(const tagFORMATETC &FormatEtcIn, tagSTGMEDIUM &AMedium);
	virtual bool __fastcall WriteData(void * Value, int Size) = 0 ;
	virtual int __fastcall GetSize(void) = 0 ;
	
public:
	__fastcall virtual TCustomSimpleClipboardFormat(void);
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomSimpleClipboardFormat(int Atymed) : Dragdrop::TClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomSimpleClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdrop::TClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TCustomSimpleClipboardFormat(void) { }
	
};


class DELPHICLASS TCustomAnsiStringClipboardFormat;
class PASCALIMPLEMENTATION TCustomAnsiStringClipboardFormat : public TCustomSimpleClipboardFormat
{
	typedef TCustomSimpleClipboardFormat inherited;
	
private:
	System::AnsiString FData;
	bool FTrimZeroes;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	System::AnsiString __fastcall GetString(void);
	void __fastcall SetString(const System::AnsiString Value);
	__property System::AnsiString Data = {read=FData, write=FData};
	
public:
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property bool TrimZeroes = {read=FTrimZeroes, write=FTrimZeroes, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TCustomAnsiStringClipboardFormat(void) : TCustomSimpleClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomAnsiStringClipboardFormat(int Atymed) : TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomAnsiStringClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomSimpleClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TCustomAnsiStringClipboardFormat(void) { }
	
};


class DELPHICLASS TAnsiStringClipboardFormat;
class PASCALIMPLEMENTATION TAnsiStringClipboardFormat : public TCustomAnsiStringClipboardFormat
{
	typedef TCustomAnsiStringClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Data;
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TAnsiStringClipboardFormat(void) : TCustomAnsiStringClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TAnsiStringClipboardFormat(int Atymed) : TCustomAnsiStringClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TAnsiStringClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomAnsiStringClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TAnsiStringClipboardFormat(void) { }
	
};


class DELPHICLASS TCustomStringListClipboardFormat;
class PASCALIMPLEMENTATION TCustomStringListClipboardFormat : public TCustomSimpleClipboardFormat
{
	typedef TCustomSimpleClipboardFormat inherited;
	
private:
	Classes::TStrings* FLines;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	Classes::TStrings* __fastcall GetLines(void);
	__property Classes::TStrings* Lines = {read=FLines};
	
public:
	__fastcall virtual TCustomStringListClipboardFormat(void);
	__fastcall virtual ~TCustomStringListClipboardFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomStringListClipboardFormat(int Atymed) : TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomStringListClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomSimpleClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TCustomDWORDClipboardFormat;
class PASCALIMPLEMENTATION TCustomDWORDClipboardFormat : public TCustomSimpleClipboardFormat
{
	typedef TCustomSimpleClipboardFormat inherited;
	
private:
	unsigned FValue;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	unsigned __fastcall GetValueDWORD(void);
	void __fastcall SetValueDWORD(unsigned Value);
	int __fastcall GetValueInteger(void);
	void __fastcall SetValueInteger(int Value);
	int __fastcall GetValueLongInt(void);
	void __fastcall SetValueLongInt(int Value);
	bool __fastcall GetValueBoolean(void);
	void __fastcall SetValueBoolean(bool Value);
	
public:
	virtual void __fastcall Clear(void);
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TCustomDWORDClipboardFormat(void) : TCustomSimpleClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomDWORDClipboardFormat(int Atymed) : TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomDWORDClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomSimpleClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TCustomDWORDClipboardFormat(void) { }
	
};


class DELPHICLASS TPreferredDropEffectClipboardFormat;
class PASCALIMPLEMENTATION TPreferredDropEffectClipboardFormat : public TCustomDWORDClipboardFormat
{
	typedef TCustomDWORDClipboardFormat inherited;
	
public:
	__classmethod System::Word __fastcall GetClassClipboardFormat();
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall HasData(void);
	__property int Value = {read=GetValueLongInt, write=SetValueLongInt, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TPreferredDropEffectClipboardFormat(void) : TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TPreferredDropEffectClipboardFormat(int Atymed) : TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TPreferredDropEffectClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TPreferredDropEffectClipboardFormat(void) { }
	
};


class DELPHICLASS TPerformedDropEffectClipboardFormat;
class PASCALIMPLEMENTATION TPerformedDropEffectClipboardFormat : public TCustomDWORDClipboardFormat
{
	typedef TCustomDWORDClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__classmethod virtual Dragdrop::TDataDirections __fastcall DataDirection();
	__property int Value = {read=GetValueLongInt, write=SetValueLongInt, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TPerformedDropEffectClipboardFormat(void) : TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TPerformedDropEffectClipboardFormat(int Atymed) : TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TPerformedDropEffectClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TPerformedDropEffectClipboardFormat(void) { }
	
};


class DELPHICLASS TLogicalPerformedDropEffectClipboardFormat;
class PASCALIMPLEMENTATION TLogicalPerformedDropEffectClipboardFormat : public TCustomDWORDClipboardFormat
{
	typedef TCustomDWORDClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__classmethod virtual Dragdrop::TDataDirections __fastcall DataDirection();
	__property int Value = {read=GetValueLongInt, write=SetValueLongInt, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TLogicalPerformedDropEffectClipboardFormat(void) : TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TLogicalPerformedDropEffectClipboardFormat(int Atymed) : TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TLogicalPerformedDropEffectClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TLogicalPerformedDropEffectClipboardFormat(void) { }
	
};


class DELPHICLASS TPasteSucceededClipboardFormat;
class PASCALIMPLEMENTATION TPasteSucceededClipboardFormat : public TCustomDWORDClipboardFormat
{
	typedef TCustomDWORDClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__classmethod virtual Dragdrop::TDataDirections __fastcall DataDirection();
	__property int Value = {read=GetValueLongInt, write=SetValueLongInt, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TPasteSucceededClipboardFormat(void) : TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TPasteSucceededClipboardFormat(int Atymed) : TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TPasteSucceededClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TPasteSucceededClipboardFormat(void) { }
	
};


class DELPHICLASS TInShellDragLoopClipboardFormat;
class PASCALIMPLEMENTATION TInShellDragLoopClipboardFormat : public TCustomDWORDClipboardFormat
{
	typedef TCustomDWORDClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property bool InShellDragLoop = {read=GetValueBoolean, write=SetValueBoolean, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TInShellDragLoopClipboardFormat(void) : TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TInShellDragLoopClipboardFormat(int Atymed) : TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TInShellDragLoopClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TInShellDragLoopClipboardFormat(void) { }
	
};


class DELPHICLASS TTargetCLSIDClipboardFormat;
class PASCALIMPLEMENTATION TTargetCLSIDClipboardFormat : public TCustomSimpleClipboardFormat
{
	typedef TCustomSimpleClipboardFormat inherited;
	
private:
	#pragma pack(push,1)
	GUID FCLSID;
	#pragma pack(pop)
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__classmethod virtual Dragdrop::TDataDirections __fastcall DataDirection();
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	__property GUID CLSID = {read=FCLSID, write=FCLSID};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TTargetCLSIDClipboardFormat(void) : TCustomSimpleClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TTargetCLSIDClipboardFormat(int Atymed) : TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TTargetCLSIDClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomSimpleClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TTargetCLSIDClipboardFormat(void) { }
	
};


class DELPHICLASS TDataStreamDataFormat;
class PASCALIMPLEMENTATION TDataStreamDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	TStreamList* FStreams;
	
public:
	__fastcall virtual TDataStreamDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */;
	__fastcall virtual ~TDataStreamDataFormat(void);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property TStreamList* Streams = {read=FStreams};
};


class DELPHICLASS TFeedbackDataFormat;
class PASCALIMPLEMENTATION TFeedbackDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	int FPreferredDropEffect;
	int FPerformedDropEffect;
	int FLogicalPerformedDropEffect;
	int FPasteSucceeded;
	bool FInShellDragLoop;
	bool FGotInShellDragLoop;
	#pragma pack(push,1)
	GUID FTargetCLSID;
	#pragma pack(pop)
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	void __fastcall SetInShellDragLoop(const bool Value);
	void __fastcall SetPasteSucceeded(const int Value);
	void __fastcall SetPerformedDropEffect(const int Value);
	void __fastcall SetPreferredDropEffect(const int Value);
	void __fastcall SetTargetCLSID(const GUID &Value);
	void __fastcall SetLogicalPerformedDropEffect(const int Value);
	
public:
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property int PreferredDropEffect = {read=FPreferredDropEffect, write=SetPreferredDropEffect, nodefault};
	__property int PerformedDropEffect = {read=FPerformedDropEffect, write=SetPerformedDropEffect, nodefault};
	__property int LogicalPerformedDropEffect = {read=FLogicalPerformedDropEffect, write=SetLogicalPerformedDropEffect, nodefault};
	__property int PasteSucceeded = {read=FPasteSucceeded, write=SetPasteSucceeded, nodefault};
	__property bool InShellDragLoop = {read=FInShellDragLoop, write=SetInShellDragLoop, nodefault};
	__property GUID TargetCLSID = {read=FTargetCLSID, write=SetTargetCLSID};
public:
	/* TCustomDataFormat.Create */ inline __fastcall virtual TFeedbackDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */ : Dragdrop::TCustomDataFormat(AOwner) { }
	/* TCustomDataFormat.Destroy */ inline __fastcall virtual ~TFeedbackDataFormat(void) { }
	
};


class DELPHICLASS TGenericDataFormat;
class PASCALIMPLEMENTATION TGenericDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	System::AnsiString FData;
	
protected:
	int __fastcall GetSize(void);
	void __fastcall DoSetData(const System::AnsiString Value);
	
public:
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	void __fastcall AddFormat(const System::UnicodeString AFormat);
	void __fastcall SetDataHere(const void *AData, int ASize);
	int __fastcall GetDataHere(void *AData, int ASize);
	__property System::AnsiString Data = {read=FData, write=DoSetData};
	__property int Size = {read=GetSize, nodefault};
public:
	/* TCustomDataFormat.Create */ inline __fastcall virtual TGenericDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */ : Dragdrop::TCustomDataFormat(AOwner) { }
	/* TCustomDataFormat.Destroy */ inline __fastcall virtual ~TGenericDataFormat(void) { }
	
};


class DELPHICLASS TGenericClipboardFormat;
class PASCALIMPLEMENTATION TGenericClipboardFormat : public TCustomAnsiStringClipboardFormat
{
	typedef TCustomAnsiStringClipboardFormat inherited;
	
private:
	System::UnicodeString FFormat;
	
protected:
	virtual void __fastcall SetClipboardFormatName(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetClipboardFormatName(void);
	virtual System::Word __fastcall GetClipboardFormat(void);
	
public:
	__classmethod virtual Dragdrop::TDataDirections __fastcall DataDirection();
	virtual bool __fastcall Assign(Dragdrop::TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TCustomDataFormat* Dest);
	__property Data;
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TGenericClipboardFormat(void) : TCustomAnsiStringClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TGenericClipboardFormat(int Atymed) : TCustomAnsiStringClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TGenericClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomAnsiStringClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TGenericClipboardFormat(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall GetMediumDataSize(const tagSTGMEDIUM &Medium);
extern PACKAGE _di_IStream __fastcall CreateIStreamFromIStorage(const _di_IStorage Storage);
extern PACKAGE _di_IStorage __fastcall CreateIStorageOnHGlobal(unsigned GlobalSource);

}	/* namespace Dragdropformats */
using namespace Dragdropformats;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragdropformatsHPP
