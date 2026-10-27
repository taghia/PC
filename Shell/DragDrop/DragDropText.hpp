// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dragdroptext.pas' rev: 21.00

#ifndef DragdroptextHPP
#define DragdroptextHPP

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
#include <Activex.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dragdroptext
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TCustomAnsiTextClipboardFormat;
class PASCALIMPLEMENTATION TCustomAnsiTextClipboardFormat : public Dragdropformats::TCustomAnsiStringClipboardFormat
{
	typedef Dragdropformats::TCustomAnsiStringClipboardFormat inherited;
	
protected:
	virtual int __fastcall GetSize(void);
	__property System::AnsiString Text = {read=GetString, write=SetString};
	
public:
	__fastcall virtual TCustomAnsiTextClipboardFormat(void);
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomAnsiTextClipboardFormat(int Atymed) : Dragdropformats::TCustomAnsiStringClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomAnsiTextClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomAnsiStringClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TCustomAnsiTextClipboardFormat(void) { }
	
};


class DELPHICLASS TCustomUnicodeTextClipboardFormat;
class PASCALIMPLEMENTATION TCustomUnicodeTextClipboardFormat : public Dragdropformats::TCustomSimpleClipboardFormat
{
	typedef Dragdropformats::TCustomSimpleClipboardFormat inherited;
	
private:
	System::UnicodeString FText;
	
protected:
	virtual bool __fastcall ReadData(void * Value, int Size);
	virtual bool __fastcall WriteData(void * Value, int Size);
	virtual int __fastcall GetSize(void);
	System::UnicodeString __fastcall GetText(void);
	void __fastcall SetText(const System::UnicodeString Value);
	__property System::UnicodeString Text = {read=FText, write=FText};
	
public:
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TCustomUnicodeTextClipboardFormat(void) : Dragdropformats::TCustomSimpleClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCustomUnicodeTextClipboardFormat(int Atymed) : Dragdropformats::TCustomSimpleClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCustomUnicodeTextClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomSimpleClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TCustomUnicodeTextClipboardFormat(void) { }
	
};


typedef TCustomUnicodeTextClipboardFormat TCustomWideTextClipboardFormat [[deprecated("Use TCustomUnicodeTextClipboardFormat instead")]];

typedef TCustomUnicodeTextClipboardFormat TCustomTextClipboardFormat;

class DELPHICLASS TAnsiTextClipboardFormat;
class PASCALIMPLEMENTATION TAnsiTextClipboardFormat : public TCustomAnsiTextClipboardFormat
{
	typedef TCustomAnsiTextClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Text;
public:
	/* TCustomAnsiTextClipboardFormat.Create */ inline __fastcall virtual TAnsiTextClipboardFormat(void) : TCustomAnsiTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TAnsiTextClipboardFormat(int Atymed) : TCustomAnsiTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TAnsiTextClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomAnsiTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TAnsiTextClipboardFormat(void) { }
	
};


class DELPHICLASS TUnicodeTextClipboardFormat;
class PASCALIMPLEMENTATION TUnicodeTextClipboardFormat : public TCustomUnicodeTextClipboardFormat
{
	typedef TCustomUnicodeTextClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Text;
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TUnicodeTextClipboardFormat(void) : TCustomUnicodeTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TUnicodeTextClipboardFormat(int Atymed) : TCustomUnicodeTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TUnicodeTextClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomUnicodeTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TUnicodeTextClipboardFormat(void) { }
	
};


typedef TUnicodeTextClipboardFormat TTextClipboardFormat;

class DELPHICLASS TOEMTextClipboardFormat;
class PASCALIMPLEMENTATION TOEMTextClipboardFormat : public TCustomAnsiTextClipboardFormat
{
	typedef TCustomAnsiTextClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Text;
public:
	/* TCustomAnsiTextClipboardFormat.Create */ inline __fastcall virtual TOEMTextClipboardFormat(void) : TCustomAnsiTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TOEMTextClipboardFormat(int Atymed) : TCustomAnsiTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TOEMTextClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomAnsiTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TOEMTextClipboardFormat(void) { }
	
};


class DELPHICLASS TRichTextClipboardFormat;
class PASCALIMPLEMENTATION TRichTextClipboardFormat : public TCustomAnsiTextClipboardFormat
{
	typedef TCustomAnsiTextClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Text;
public:
	/* TCustomAnsiTextClipboardFormat.Create */ inline __fastcall virtual TRichTextClipboardFormat(void) : TCustomAnsiTextClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TRichTextClipboardFormat(int Atymed) : TCustomAnsiTextClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TRichTextClipboardFormat(const tagFORMATETC &AFormatEtc) : TCustomAnsiTextClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TRichTextClipboardFormat(void) { }
	
};


class DELPHICLASS TCSVClipboardFormat;
class PASCALIMPLEMENTATION TCSVClipboardFormat : public Dragdropformats::TCustomStringListClipboardFormat
{
	typedef Dragdropformats::TCustomStringListClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	__property Lines;
public:
	/* TCustomStringListClipboardFormat.Create */ inline __fastcall virtual TCSVClipboardFormat(void) : Dragdropformats::TCustomStringListClipboardFormat() { }
	/* TCustomStringListClipboardFormat.Destroy */ inline __fastcall virtual ~TCSVClipboardFormat(void) { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TCSVClipboardFormat(int Atymed) : Dragdropformats::TCustomStringListClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TCSVClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomStringListClipboardFormat(AFormatEtc) { }
	
};


class DELPHICLASS TLocaleClipboardFormat;
class PASCALIMPLEMENTATION TLocaleClipboardFormat : public Dragdropformats::TCustomDWORDClipboardFormat
{
	typedef Dragdropformats::TCustomDWORDClipboardFormat inherited;
	
public:
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual bool __fastcall HasData(void);
	__property unsigned Locale = {read=GetValueDWORD, write=SetValueDWORD, nodefault};
public:
	/* TCustomSimpleClipboardFormat.Create */ inline __fastcall virtual TLocaleClipboardFormat(void) : Dragdropformats::TCustomDWORDClipboardFormat() { }
	
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TLocaleClipboardFormat(int Atymed) : Dragdropformats::TCustomDWORDClipboardFormat(Atymed) { }
	/* TClipboardFormat.CreateFormatEtc */ inline __fastcall virtual TLocaleClipboardFormat(const tagFORMATETC &AFormatEtc) : Dragdropformats::TCustomDWORDClipboardFormat(AFormatEtc) { }
	
public:
	/* TClipboardFormat.Destroy */ inline __fastcall virtual ~TLocaleClipboardFormat(void) { }
	
};


class DELPHICLASS TTextDataFormat;
class PASCALIMPLEMENTATION TTextDataFormat : public Dragdrop::TCustomDataFormat
{
	typedef Dragdrop::TCustomDataFormat inherited;
	
private:
	System::UnicodeString FUnicodeText;
	System::AnsiString FAnsiText;
	bool FNeedAnsi;
	bool FNeedUnicode;
	unsigned FLocale;
	
protected:
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	System::AnsiString __fastcall GetAnsiText(void);
	void __fastcall SetAnsiText(const System::AnsiString Value);
	System::UnicodeString __fastcall GetUnicodeText(void);
	void __fastcall SetUnicodeText(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetText(void);
	void __fastcall SetText(const System::UnicodeString Value);
	unsigned __fastcall GetLocale(void);
	void __fastcall SetLocale(const unsigned Value);
	int __fastcall GetCodePage(void);
	__property int CodePage = {read=GetCodePage, nodefault};
	
public:
	virtual bool __fastcall Assign(Dragdrop::TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(Dragdrop::TClipboardFormat* Dest);
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
	__property System::AnsiString AnsiText = {read=GetAnsiText, write=SetAnsiText};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property System::UnicodeString UnicodeText = {read=GetUnicodeText, write=SetUnicodeText};
	__property unsigned Locale = {read=GetLocale, write=SetLocale, nodefault};
public:
	/* TCustomDataFormat.Create */ inline __fastcall virtual TTextDataFormat(Dragdrop::TDragDropComponent* AOwner)/* overload */ : Dragdrop::TCustomDataFormat(AOwner) { }
	/* TCustomDataFormat.Destroy */ inline __fastcall virtual ~TTextDataFormat(void) { }
	
};


class DELPHICLASS TDropTextTarget;
class PASCALIMPLEMENTATION TDropTextTarget : public Droptarget::TCustomDropMultiTarget
{
	typedef Droptarget::TCustomDropMultiTarget inherited;
	
private:
	TTextDataFormat* FTextFormat;
	
protected:
	System::UnicodeString __fastcall GetText(void);
	System::AnsiString __fastcall GetAnsiText(void);
	unsigned __fastcall GetLocale(void);
	System::UnicodeString __fastcall GetUnicodeText(void);
	
public:
	__fastcall virtual TDropTextTarget(Classes::TComponent* AOwner);
	__fastcall virtual ~TDropTextTarget(void);
	__property System::UnicodeString Text = {read=GetText};
	__property System::AnsiString AnsiText = {read=GetAnsiText};
	__property System::UnicodeString UnicodeText = {read=GetUnicodeText};
	__property unsigned Locale = {read=GetLocale, nodefault};
};


class DELPHICLASS TDropTextSource;
class PASCALIMPLEMENTATION TDropTextSource : public Dropsource::TCustomDropMultiSource
{
	typedef Dropsource::TCustomDropMultiSource inherited;
	
private:
	TTextDataFormat* FTextFormat;
	
protected:
	System::UnicodeString __fastcall GetText(void);
	System::AnsiString __fastcall GetAnsiText(void);
	unsigned __fastcall GetLocale(void);
	System::UnicodeString __fastcall GetUnicodeText(void);
	void __fastcall SetText(const System::UnicodeString Value);
	void __fastcall SetAnsiText(const System::AnsiString Value);
	void __fastcall SetLocale(const unsigned Value);
	void __fastcall SetUnicodeText(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDropTextSource(Classes::TComponent* aOwner);
	__fastcall virtual ~TDropTextSource(void);
	__property System::AnsiString AnsiText = {read=GetAnsiText, write=SetAnsiText};
	__property System::UnicodeString UnicodeText = {read=GetUnicodeText, write=SetUnicodeText};
	
__published:
	__property unsigned Locale = {read=GetLocale, write=SetLocale, default=0};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall IsRTF(const System::UnicodeString s);
extern PACKAGE System::AnsiString __fastcall MakeRTF(const System::UnicodeString s);

}	/* namespace Dragdroptext */
using namespace Dragdroptext;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragdroptextHPP
