// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dragdrop.pas' rev: 21.00

#ifndef DragdropHPP
#define DragdropHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------
#include <shldisp.h>
#ifndef NO_WIN32_LEAN_AND_MEAN
#error The NO_WIN32_LEAN_AND_MEAN symbol must be defined in your projects conditional defines
#endif
typedef System::DelphiInterface<IDropSource> _di_IDropSource;
typedef System::DelphiInterface<IEnumFORMATETC> _di_IEnumFORMATETC;
DECLARE_DINTERFACE_TYPE(IBindCtx)

namespace Dragdrop
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDragType { dtCopy, dtMove, dtLink };
#pragma option pop

typedef Set<TDragType, dtCopy, dtLink>  TDragTypes;

#pragma option push -b-
enum TDataDirection { ddRead, ddWrite };
#pragma option pop

typedef Set<TDataDirection, ddRead, ddWrite>  TDataDirections;

#pragma option push -b-
enum TConversionCapability { ccWriteToDataFormat, ccReadFromDataFormat };
#pragma option pop

typedef Set<TConversionCapability, ccWriteToDataFormat, ccReadFromDataFormat>  TConversionCapabilities;

class DELPHICLASS TInterfacedComponent;
class PASCALIMPLEMENTATION TInterfacedComponent : public Classes::TComponent
{
	typedef Classes::TComponent inherited;
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	HIDESBASE int __stdcall _AddRef(void);
	HIDESBASE int __stdcall _Release(void);
public:
	/* TComponent.Create */ inline __fastcall virtual TInterfacedComponent(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TInterfacedComponent(void) { }
	
private:
	void *__IInterface;	/* System::IInterface */
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IInterface*(void) { return (IInterface*)&__IInterface; }
	#endif
	
};


typedef TMetaClass* TDataFormatClass;

class DELPHICLASS TClipboardFormat;
class DELPHICLASS TCustomDataFormat;
class PASCALIMPLEMENTATION TClipboardFormat : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCustomDataFormat* FDataFormat;
	
protected:
	tagFORMATETC FFormatEtc;
	__fastcall virtual TClipboardFormat(int Atymed);
	__fastcall virtual TClipboardFormat(const tagFORMATETC &AFormatEtc);
	virtual bool __fastcall DoGetData(const _di_IDataObject ADataObject, const tagSTGMEDIUM &AMedium);
	virtual bool __fastcall DoSetData(const tagFORMATETC &FormatEtcIn, tagSTGMEDIUM &AMedium);
	virtual System::Word __fastcall GetClipboardFormat(void);
	virtual void __fastcall SetClipboardFormat(System::Word Value);
	virtual System::UnicodeString __fastcall GetClipboardFormatName(void);
	virtual void __fastcall SetClipboardFormatName(const System::UnicodeString Value);
	void __fastcall SetFormatEtc(const tagFORMATETC &Value);
	virtual int __fastcall GetValidMedia(const _di_IDataObject ADataObject);
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	__classmethod void __fastcall RegisterDataProvider(TDataFormatClass DataFormatClass, int Priority = 0x0);
	__classmethod void __fastcall RegisterDataConsumer(TDataFormatClass DataFormatClass);
	__classmethod void __fastcall RegisterDataConversion(TDataFormatClass DataFormatClass, int Priority = 0x0, TConversionCapabilities Capabilities = (TConversionCapabilities() << ccWriteToDataFormat << ccReadFromDataFormat ));
	
public:
	__fastcall virtual TClipboardFormat(void) = 0 ;
	__fastcall virtual ~TClipboardFormat(void);
	virtual bool __fastcall HasValidFormats(const _di_IDataObject ADataObject);
	virtual bool __fastcall AcceptFormat(const tagFORMATETC &AFormatEtc);
	virtual bool __fastcall GetData(const _di_IDataObject ADataObject);
	virtual bool __fastcall GetDataFromMedium(const _di_IDataObject ADataObject, tagSTGMEDIUM &AMedium);
	virtual bool __fastcall SetData(const _di_IDataObject ADataObject, const tagFORMATETC &FormatEtcIn, tagSTGMEDIUM &AMedium);
	bool __fastcall SetDataToMedium(const tagFORMATETC &FormatEtcIn, tagSTGMEDIUM &AMedium);
	virtual bool __fastcall Assign(TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(TCustomDataFormat* Dest);
	virtual void __fastcall Clear(void) = 0 ;
	virtual bool __fastcall HasData(void);
	__classmethod virtual void __fastcall RegisterFormat();
	__classmethod void __fastcall UnregisterClipboardFormat();
	__classmethod virtual TDataDirections __fastcall DataDirection();
	__property System::Word ClipboardFormat = {read=GetClipboardFormat, write=SetClipboardFormat, nodefault};
	__property System::UnicodeString ClipboardFormatName = {read=GetClipboardFormatName, write=SetClipboardFormatName};
	__property tagFORMATETC FormatEtc = {read=FFormatEtc};
	__property TCustomDataFormat* DataFormat = {read=FDataFormat, write=FDataFormat};
};


typedef TMetaClass* TClipboardFormatClass;

class DELPHICLASS TClipboardFormats;
class PASCALIMPLEMENTATION TClipboardFormats : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TClipboardFormat* operator[](int Index) { return Formats[Index]; }
	
private:
	Classes::TList* FList;
	bool FOwnsObjects;
	TCustomDataFormat* FDataFormat;
	
protected:
	TClipboardFormat* __fastcall DoGetFormat(int Index);
	int __fastcall GetCount(void);
	
public:
	__fastcall TClipboardFormats(TCustomDataFormat* ADataFormat, bool AOwnsObjects);
	__fastcall virtual ~TClipboardFormats(void);
	void __fastcall Clear(void);
	void __fastcall Assign(TClipboardFormats* Source);
	int __fastcall Add(TClipboardFormat* ClipboardFormat);
	TClipboardFormat* __fastcall FindFormat(System::Word ClipboardFormat)/* overload */;
	TClipboardFormat* __fastcall FindFormat(TClipboardFormatClass ClipboardFormatClass)/* overload */;
	TClipboardFormat* __fastcall GetFormat(System::Word ClipboardFormat)/* overload */;
	TClipboardFormat* __fastcall GetFormat(TClipboardFormatClass ClipboardFormatClass)/* overload */;
	__property TClipboardFormat* Formats[int Index] = {read=DoGetFormat/*, default*/};
	__property int Count = {read=GetCount, nodefault};
	__property TCustomDataFormat* DataFormat = {read=FDataFormat};
	__property bool OwnsObjects = {read=FOwnsObjects, write=FOwnsObjects, nodefault};
};


class DELPHICLASS TDragDropComponent;
class DELPHICLASS TDataFormats;
class PASCALIMPLEMENTATION TDragDropComponent : public TInterfacedComponent
{
	typedef TInterfacedComponent inherited;
	
protected:
	TDataFormats* FDataFormats;
	__property TDataFormats* DataFormats = {read=FDataFormats};
	
public:
	virtual void __fastcall GetCompatibleClipboardFormats(const TDataFormatClass DataFormatClass, TClipboardFormats* ClipboardFormats);
public:
	/* TComponent.Create */ inline __fastcall virtual TDragDropComponent(Classes::TComponent* AOwner) : TInterfacedComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDragDropComponent(void) { }
	
};


#pragma option push -b-
enum TDataFormatDirection { dfdConsumer, dfdProvider };
#pragma option pop

class PASCALIMPLEMENTATION TCustomDataFormat : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TClipboardFormats* FCompatibleFormats;
	TDataFormats* FFormatList;
	TDragDropComponent* FOwner;
	Classes::TNotifyEvent FOnChanging;
	
protected:
	bool __fastcall SupportsFormat(TClipboardFormat* ClipboardFormat);
	void __fastcall DoOnChanging(System::TObject* Sender);
	virtual void __fastcall Changing(void);
	void __fastcall CreateCompatibleFormatsList(void);
	__classmethod virtual void __fastcall RegisterCompatibleFormats();
	__classmethod void __fastcall RegisterDataProvider(TClipboardFormatClass ClipboardFormatClass, int Priority = 0x0);
	__classmethod void __fastcall RegisterDataConsumer(TClipboardFormatClass ClipboardFormatClass);
	__classmethod void __fastcall RegisterDataConversion(TClipboardFormatClass ClipboardFormatClass, int Priority = 0x0, TConversionCapabilities Capabilities = (TConversionCapabilities() << ccWriteToDataFormat << ccReadFromDataFormat ));
	TClipboardFormats* __fastcall GetCompatibleFormats(void);
	__property TDataFormats* FormatList = {read=FFormatList};
	
public:
	__fastcall virtual TCustomDataFormat(TDragDropComponent* AOwner)/* overload */;
	__fastcall TCustomDataFormat [[deprecated("Use Create(TDataFormatDirection) instead of Create(nil)")]](void * Dummy)/* overload */;
	__fastcall virtual TCustomDataFormat(TDataFormatDirection Direction)/* overload */;
	__fastcall virtual ~TCustomDataFormat(void);
	virtual void __fastcall Clear(void) = 0 ;
	virtual bool __fastcall Assign(TClipboardFormat* Source);
	virtual bool __fastcall AssignTo(TClipboardFormat* Dest);
	virtual bool __fastcall GetData(_di_IDataObject DataObject);
	virtual bool __fastcall HasData(void) = 0 ;
	virtual bool __fastcall NeedsData(void);
	virtual bool __fastcall HasValidFormats(const _di_IDataObject ADataObject);
	virtual bool __fastcall AcceptFormat(const tagFORMATETC &FormatEtc);
	__classmethod void __fastcall RegisterDataFormat();
	__classmethod void __fastcall UnregisterDataFormat();
	__property TClipboardFormats* CompatibleFormats = {read=GetCompatibleFormats};
	__property TDragDropComponent* Owner = {read=FOwner};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
};


class PASCALIMPLEMENTATION TDataFormats : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TCustomDataFormat* operator[](int Index) { return Formats[Index]; }
	
private:
	Classes::TList* FList;
	
protected:
	TCustomDataFormat* __fastcall GetFormat(int Index);
	int __fastcall GetCount(void);
	
public:
	__fastcall TDataFormats(void);
	__fastcall virtual ~TDataFormats(void);
	virtual int __fastcall Add(TCustomDataFormat* DataFormat);
	virtual int __fastcall IndexOf(TCustomDataFormat* DataFormat);
	virtual void __fastcall Remove(TCustomDataFormat* DataFormat);
	__property TCustomDataFormat* Formats[int Index] = {read=GetFormat/*, default*/};
	__property int Count = {read=GetCount, nodefault};
};


class DELPHICLASS TDataFormatClasses;
class PASCALIMPLEMENTATION TDataFormatClasses : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FList;
	
private:
	__classmethod TDataFormatClasses* __fastcall Instance();
	
protected:
	static TDataFormatClass __fastcall GetFormat(int Index);
	static int __fastcall GetCount();
	
public:
	__fastcall TDataFormatClasses(void);
	__fastcall virtual ~TDataFormatClasses(void);
	__classmethod int __fastcall Add(TDataFormatClass DataFormat);
	__classmethod void __fastcall Remove(TDataFormatClass DataFormat);
	/* static */ __property TDataFormatClass Formats[int Index] = {read=GetFormat};
	/* static */ __property int Count = {read=GetCount, nodefault};
};


#pragma option push -b-
enum TDragDropTier { ddtSource, ddtTarget };
#pragma option pop

class DELPHICLASS TDataFormatMap;
class PASCALIMPLEMENTATION TDataFormatMap : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FList;
	
protected:
	int __fastcall FindMap(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass);
	void __fastcall Sort(void);
	__classmethod TDataFormatMap* __fastcall Instance();
	
public:
	__fastcall TDataFormatMap(void);
	__fastcall virtual ~TDataFormatMap(void);
	void __fastcall Add(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass, int Priority = 0x0, TConversionCapabilities Capabilities = (TConversionCapabilities() << ccWriteToDataFormat << ccReadFromDataFormat ));
	void __fastcall Delete(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass);
	void __fastcall DeleteByClipboardFormat(TClipboardFormatClass ClipboardFormatClass);
	void __fastcall DeleteByDataFormat(TDataFormatClass DataFormatClass);
	__classmethod void __fastcall GetClipboardFormats(const TDataFormatClass DataFormatClass, TClipboardFormats* ClipboardFormats, TDragDropTier Tier);
	bool __fastcall CanMap(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass);
	void __fastcall RegisterFormatMap(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass, int Priority = 0x0, TConversionCapabilities Capabilities = (TConversionCapabilities() << ccWriteToDataFormat << ccReadFromDataFormat ));
	void __fastcall UnregisterFormatMap(TDataFormatClass DataFormatClass, TClipboardFormatClass ClipboardFormatClass);
};


class DELPHICLASS TDataFormatAdapter;
class PASCALIMPLEMENTATION TDataFormatAdapter : public Classes::TComponent
{
	typedef Classes::TComponent inherited;
	
private:
	TDragDropComponent* FDragDropComponent;
	TCustomDataFormat* FDataFormat;
	TDataFormatClass FDataFormatClass;
	System::UnicodeString FDataFormatClassName;
	bool FEnabled;
	
protected:
	System::UnicodeString __fastcall GetDataFormatName(void);
	void __fastcall SetDataFormatName(const System::UnicodeString Value);
	void __fastcall SetDataFormatClass(const TDataFormatClass Value);
	void __fastcall SetDragDropComponent(const TDragDropComponent* Value);
	bool __fastcall GetEnabled(void);
	void __fastcall SetEnabled(const bool Value);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TDataFormatAdapter(Classes::TComponent* AOwner);
	__fastcall virtual ~TDataFormatAdapter(void);
	__property TDataFormatClass DataFormatClass = {read=FDataFormatClass, write=SetDataFormatClass};
	__property TCustomDataFormat* DataFormat = {read=FDataFormat};
	
__published:
	__property TDragDropComponent* DragDropComponent = {read=FDragDropComponent, write=SetDragDropComponent};
	__property System::UnicodeString DataFormatName = {read=GetDataFormatName, write=SetDataFormatName};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, default=1};
};


struct _SHDRAGIMAGE;
typedef _SHDRAGIMAGE *PSHDRAGIMAGE;

#pragma pack(push,1)
struct _SHDRAGIMAGE
{
	
public:
	#pragma pack(push,8)
	tagSIZE sizeDragImage;
	#pragma pack(pop)
	#pragma pack(push,8)
	Types::TPoint ptOffset;
	#pragma pack(pop)
	HBITMAP hbmpDragImage;
	unsigned crColorKey;
};
#pragma pack(pop)


typedef _SHDRAGIMAGE TSHDRAGIMAGE;

typedef _SHDRAGIMAGE SHDRAGIMAGE;

__interface IDropTargetHelper;
typedef System::DelphiInterface<IDropTargetHelper> _di_IDropTargetHelper;
__interface  INTERFACE_UUID("{4657278B-411B-11D2-839A-00C04FD918D0}") IDropTargetHelper  : public System::IInterface 
{
	
public:
	virtual HRESULT __stdcall DragEnter(HWND hwndTarget, const _di_IDataObject DataObj, Types::TPoint &pt, int dwEffect) = 0 ;
	virtual HRESULT __stdcall DragLeave(void) = 0 ;
	virtual HRESULT __stdcall DragOver(Types::TPoint &pt, int dwEffect) = 0 ;
	virtual HRESULT __stdcall Drop(const _di_IDataObject DataObj, Types::TPoint &pt, int dwEffect) = 0 ;
	virtual HRESULT __stdcall Show(BOOL Show) = 0 ;
};

__interface IDragSourceHelper;
typedef System::DelphiInterface<IDragSourceHelper> _di_IDragSourceHelper;
__interface  INTERFACE_UUID("{DE5BF786-477A-11D2-839D-00C04FD918D0}") IDragSourceHelper  : public System::IInterface 
{
	
public:
	virtual HRESULT __stdcall InitializeFromBitmap(_SHDRAGIMAGE &shdi, const _di_IDataObject DataObj) = 0 ;
	virtual HRESULT __stdcall InitializeFromWindow(HWND hwnd, Types::TPoint &pt, const _di_IDataObject DataObj) = 0 ;
};

__interface IAsyncOperation;
typedef System::DelphiInterface<IAsyncOperation> _di_IAsyncOperation;
__interface  INTERFACE_UUID("{3D8B0590-F691-11D2-8EA9-006097DF5BD4}") IAsyncOperation  : public System::IInterface 
{
	
public:
	virtual HRESULT __stdcall SetAsyncMode(BOOL fDoOpAsync) = 0 ;
	virtual HRESULT __stdcall GetAsyncMode(/* out */ BOOL &pfIsOpAsync) = 0 ;
	virtual HRESULT __stdcall StartOperation(const _di_IBindCtx pbcReserved) = 0 ;
	virtual HRESULT __stdcall InOperation(/* out */ BOOL &pfInAsyncOp) = 0 ;
	virtual HRESULT __stdcall EndOperation(HRESULT hResult, const _di_IBindCtx pbcReserved, unsigned dwEffects) = 0 ;
};

__interface IAsyncOperation2;
typedef System::DelphiInterface<IAsyncOperation2> _di_IAsyncOperation2;
__interface  INTERFACE_UUID("{3D8B0590-F691-11D2-8EA9-006097DF5BD4}") IAsyncOperation2  : public IAsyncOperation 
{
	
};

class DELPHICLASS TRawDataFormat;
class PASCALIMPLEMENTATION TRawDataFormat : public TCustomDataFormat
{
	typedef TCustomDataFormat inherited;
	
public:
	virtual void __fastcall Clear(void);
	virtual bool __fastcall HasData(void);
	virtual bool __fastcall NeedsData(void);
public:
	/* TCustomDataFormat.Create */ inline __fastcall virtual TRawDataFormat(TDragDropComponent* AOwner)/* overload */ : TCustomDataFormat(AOwner) { }
	/* TCustomDataFormat.Destroy */ inline __fastcall virtual ~TRawDataFormat(void) { }
	
};


class DELPHICLASS TRawClipboardFormat;
class PASCALIMPLEMENTATION TRawClipboardFormat : public TClipboardFormat
{
	typedef TClipboardFormat inherited;
	
private:
	tagSTGMEDIUM FMedium;
	
protected:
	virtual bool __fastcall DoGetData(const _di_IDataObject ADataObject, const tagSTGMEDIUM &AMedium);
	virtual bool __fastcall DoSetData(const tagFORMATETC &FormatEtcIn, tagSTGMEDIUM &AMedium);
	virtual void __fastcall SetClipboardFormatName(const System::UnicodeString Value);
	virtual System::Word __fastcall GetClipboardFormat(void);
	System::AnsiString __fastcall GetString(void);
	void __fastcall SetString(const System::AnsiString Value);
	
public:
	__fastcall virtual TRawClipboardFormat(void);
	__fastcall virtual ~TRawClipboardFormat(void);
	__fastcall virtual TRawClipboardFormat(const tagFORMATETC &AFormatEtc);
	virtual bool __fastcall Assign(TCustomDataFormat* Source);
	virtual bool __fastcall AssignTo(TCustomDataFormat* Dest);
	virtual void __fastcall Clear(void);
	void __fastcall ClearData(void);
	virtual bool __fastcall HasData(void);
	bool __fastcall NeedsData(void);
	bool __fastcall CopyFromStgMedium(const tagSTGMEDIUM &AMedium);
	bool __fastcall CopyToStgMedium(tagSTGMEDIUM &AMedium);
	__property tagSTGMEDIUM Medium = {read=FMedium, write=FMedium};
	__property System::AnsiString AsString = {read=GetString, write=SetString};
protected:
	/* TClipboardFormat.CreateFormat */ inline __fastcall virtual TRawClipboardFormat(int Atymed) : TClipboardFormat(Atymed) { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define DragDropSuiteVersion  (5.000000E+00)
static const ShortInt DragDropSuiteVersionMajor = 0x5;
static const ShortInt DragDropSuiteVersionMinor = 0x0;
static const ShortInt UnicodeBoost = -1;
static const ShortInt AnsiBoost = 0x0;
extern PACKAGE GUID CLSID_DragDropHelper;
#define SID_DragDropHelper L"{4657278A-411B-11d2-839A-00C04FD918D0}"
extern PACKAGE GUID IID_IDropTargetHelper;
#define SID_IDropTargetHelper L"{4657278B-411B-11d2-839A-00C04FD918D0}"
extern PACKAGE GUID IID_IDragSourceHelper;
#define SID_IDragSourceHelper L"{DE5BF786-477A-11d2-839D-00C04FD918D0}"
extern PACKAGE GUID IID_IAsyncOperation;
#define SID_IAsyncOperation L"{3D8B0590-F691-11D2-8EA9-006097DF5BD4}"
extern PACKAGE _di_IMalloc ShellMalloc;
extern PACKAGE System::UnicodeString DragDropComponentPalettePage;
extern PACKAGE int DragDropScrollInset;
extern PACKAGE int DragDropScrollDelay;
extern PACKAGE int DragDropScrollInterval;
extern PACKAGE int DragDropScrollMaxVelocity;
extern PACKAGE int DragDropScrollVelocitySample;
extern PACKAGE int DragDropDragDelay;
extern PACKAGE int DragDropDragDelayMax;
extern PACKAGE bool DragDropAutoDrag;
extern PACKAGE int DragDropDragMinDistance;
extern PACKAGE bool DragDropShutdown;
extern PACKAGE System::AnsiString sDragDropCopyright;
extern PACKAGE System::WideChar * __fastcall WStrLCopy(System::WideChar * Dest, const System::WideChar * Source, unsigned MaxLen);
extern PACKAGE System::WideChar * __fastcall WStrPLCopy(System::WideChar * Dest, const System::WideString Source, unsigned MaxLen);
extern PACKAGE void __fastcall _RaiseLastWin32Error(void);
extern PACKAGE bool __fastcall DropEffectToDragType(int DropEffect, TDragType &DragType);
extern PACKAGE int __fastcall DragTypesToDropEffect(TDragTypes DragTypes);
extern PACKAGE bool __fastcall DragDetectPlus(Controls::TWinControl* Control)/* overload */;
extern PACKAGE bool __fastcall DragDetectPlus(Controls::TWinControl* Control, const Types::TPoint &Position)/* overload */;
extern PACKAGE bool __fastcall DragDetectPlus(unsigned Handle)/* overload */;
extern PACKAGE bool __fastcall DragDetectPlus(unsigned Handle, const Types::TPoint &Position)/* overload */;
extern PACKAGE Types::TPoint __fastcall ClientPtToWindowPt(unsigned Handle, const Types::TPoint &pt);
extern PACKAGE Classes::TShiftState __fastcall KeysToShiftStatePlus(System::Word Keys);
extern PACKAGE int __fastcall ShiftStateToDropEffect(Classes::TShiftState Shift, int AllowedEffects, bool Fallback);
extern PACKAGE bool __fastcall CopyStgMedium(const tagSTGMEDIUM &SrcMedium, tagSTGMEDIUM &DstMedium);
extern PACKAGE System::UnicodeString __fastcall GetClipboardFormatNameStr(System::Word Value);

}	/* namespace Dragdrop */
using namespace Dragdrop;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragdropHPP
