// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dropsource.pas' rev: 21.00

#ifndef DropsourceHPP
#define DropsourceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Dragdrop.hpp>	// Pascal unit
#include <Dragdropformats.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------
#include <shldisp.h>

namespace Dropsource
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDragResult { drDropCopy, drDropMove, drDropLink, drCancel, drOutMemory, drAsync, drUnknown };
#pragma option pop

typedef void __fastcall (__closure *TDropEvent)(System::TObject* Sender, Dragdrop::TDragType DragType, bool &ContinueDrop);

typedef void __fastcall (__closure *TAfterDropEvent)(System::TObject* Sender, TDragResult DragResult, bool Optimized);

typedef void __fastcall (__closure *TFeedbackEvent)(System::TObject* Sender, int Effect, bool &UseDefaultCursors);

typedef void __fastcall (__closure *TDropDataEvent)(System::TObject* Sender, const tagFORMATETC &FormatEtc, /* out */ tagSTGMEDIUM &Medium, bool &Handled);

typedef void __fastcall (__closure *TPasteEvent)(System::TObject* Sender, TDragResult Action, bool DeleteOnPaste);

typedef void __fastcall (__closure *TGetDragImageEvent)(System::TObject* Sender, const Dragdrop::_di_IDragSourceHelper DragSourceHelper, bool &Handled);

class DELPHICLASS TCustomDropSource;
class PASCALIMPLEMENTATION TCustomDropSource : public Dragdrop::TDragDropComponent
{
	typedef Dragdrop::TDragDropComponent inherited;
	
private:
	Dragdrop::TDragTypes FDragTypes;
	int FFeedbackEffect;
	TDropEvent FOnDrop;
	TAfterDropEvent FOnAfterDrop;
	TFeedbackEvent FOnFeedback;
	TDropDataEvent FOnGetData;
	TDropDataEvent FOnSetData;
	TPasteEvent FOnPaste;
	TGetDragImageEvent FOnGetDragImage;
	Controls::TImageList* FImages;
	bool FShowImage;
	int FImageIndex;
	Types::TPoint FImageHotSpot;
	Dragdrop::_di_IDragSourceHelper FDragSourceHelper;
	bool FAllowAsync;
	bool FRequestAsync;
	bool FAsyncSourceTransfer;
	bool FAsyncTargetTransfer;
	_di_IDataObject FAsyncDataObject;
	_di_IDropSource FAsyncDropSource;
	unsigned FAsyncTargetEvent;
	bool FDragInProgress;
	
protected:
	__property int FeedbackEffect = {read=FFeedbackEffect, write=FFeedbackEffect, nodefault};
	HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed, int grfKeyState);
	HRESULT __stdcall GiveFeedback(int dwEffect);
	HRESULT __stdcall GetData(const tagFORMATETC &FormatEtcIn, /* out */ tagSTGMEDIUM &Medium);
	HRESULT __stdcall GetDataHere(const tagFORMATETC &FormatEtc, /* out */ tagSTGMEDIUM &Medium);
	HRESULT __stdcall QueryGetData(const tagFORMATETC &FormatEtc);
	HRESULT __stdcall GetCanonicalFormatEtc(const tagFORMATETC &FormatEtc, /* out */ tagFORMATETC &FormatEtcout);
	HRESULT __stdcall SetData(const tagFORMATETC &FormatEtc, tagSTGMEDIUM &Medium, BOOL fRelease);
	HRESULT __stdcall EnumFormatEtc(int dwDirection, /* out */ _di_IEnumFORMATETC &EnumFormatEtc);
	HRESULT __stdcall dAdvise(const tagFORMATETC &FormatEtc, int advf, const _di_IAdviseSink advsink, /* out */ int &dwConnection);
	HRESULT __stdcall dUnadvise(int dwConnection);
	HRESULT __stdcall EnumdAdvise(/* out */ _di_IEnumSTATDATA &EnumAdvise);
	HRESULT __stdcall EndOperation(HRESULT hResult, const _di_IBindCtx pbcReserved, unsigned dwEffects);
	HRESULT __stdcall GetAsyncMode(/* out */ BOOL &pfIsOpAsync);
	HRESULT __stdcall InOperation(/* out */ BOOL &pfInAsyncOp);
	HRESULT __stdcall SetAsyncMode(BOOL fDoOpAsync);
	HRESULT __stdcall StartOperation(const _di_IBindCtx pbcReserved);
	virtual HRESULT __fastcall DoGetData(const tagFORMATETC &FormatEtcIn, /* out */ tagSTGMEDIUM &Medium) = 0 ;
	virtual HRESULT __fastcall DoSetData(const tagFORMATETC &FormatEtc, tagSTGMEDIUM &Medium);
	virtual bool __fastcall HasFormat(const tagFORMATETC &FormatEtc) = 0 ;
	virtual _di_IEnumFORMATETC __fastcall GetEnumFormatEtc(int dwDirection) = 0 ;
	virtual TDragResult __fastcall DoExecute(void);
	virtual void __fastcall DataChanging(System::TObject* Sender);
	virtual bool __fastcall CutOrCopyToClipboard(void);
	virtual void __fastcall DoOnPaste(TDragResult Action, bool DeleteOnPaste);
	void __fastcall SetImages(const Controls::TImageList* Value);
	void __fastcall SetImageIndex(const int Value);
	void __fastcall SetPoint(int Index, int Value);
	int __fastcall GetPoint(int Index);
	virtual int __fastcall GetPerformedDropEffect(void);
	virtual int __fastcall GetLogicalPerformedDropEffect(void);
	virtual void __fastcall SetPerformedDropEffect(const int Value);
	virtual int __fastcall GetPreferredDropEffect(void);
	virtual void __fastcall SetPreferredDropEffect(const int Value);
	virtual bool __fastcall GetInShellDragLoop(void);
	virtual GUID __fastcall GetTargetCLSID(void);
	virtual void __fastcall SetInShellDragLoop(const bool Value);
	bool __fastcall GetLiveDataOnClipboard(void);
	void __fastcall SetAllowAsync(const bool Value);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual bool __fastcall GetDragImage(void);
	bool __fastcall GetDragImageFromImageList(void);
	__property Dragdrop::_di_IDragSourceHelper DragSourceHelper = {read=FDragSourceHelper};
	
public:
	__fastcall virtual TCustomDropSource(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDropSource(void);
	virtual TDragResult __fastcall Execute(bool Asynchronous)/* overload */;
	TDragResult __fastcall Execute(void)/* overload */;
	virtual bool __fastcall CutToClipboard(void);
	virtual bool __fastcall CopyToClipboard(void);
	virtual void __fastcall FlushClipboard(void);
	virtual void __fastcall EmptyClipboard(void);
	__property int PreferredDropEffect = {read=GetPreferredDropEffect, write=SetPreferredDropEffect, nodefault};
	__property int PerformedDropEffect = {read=GetPerformedDropEffect, write=SetPerformedDropEffect, nodefault};
	__property int LogicalPerformedDropEffect = {read=GetLogicalPerformedDropEffect, nodefault};
	__property bool InShellDragLoop = {read=GetInShellDragLoop, write=SetInShellDragLoop, nodefault};
	__property GUID TargetCLSID = {read=GetTargetCLSID};
	__property bool LiveDataOnClipboard = {read=GetLiveDataOnClipboard, nodefault};
	__property bool AsyncTransfer = {read=FAsyncTargetTransfer, nodefault};
	__property bool DragInProgress = {read=FDragInProgress, nodefault};
	
__published:
	__property Dragdrop::TDragTypes DragTypes = {read=FDragTypes, write=FDragTypes, nodefault};
	__property TFeedbackEvent OnFeedback = {read=FOnFeedback, write=FOnFeedback};
	__property TDropEvent OnDrop = {read=FOnDrop, write=FOnDrop};
	__property TAfterDropEvent OnAfterDrop = {read=FOnAfterDrop, write=FOnAfterDrop};
	__property TDropDataEvent OnGetData = {read=FOnGetData, write=FOnGetData};
	__property TDropDataEvent OnSetData = {read=FOnSetData, write=FOnSetData};
	__property TPasteEvent OnPaste = {read=FOnPaste, write=FOnPaste};
	__property TGetDragImageEvent OnGetDragImage = {read=FOnGetDragImage, write=FOnGetDragImage};
	__property Controls::TImageList* Images = {read=FImages, write=SetImages};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, default=-1};
	__property bool ShowImage = {read=FShowImage, write=FShowImage, default=0};
	__property int ImageHotSpotX = {read=GetPoint, write=SetPoint, index=1, default=16};
	__property int ImageHotSpotY = {read=GetPoint, write=SetPoint, index=2, default=16};
	__property bool AllowAsyncTransfer = {read=FAllowAsync, write=SetAllowAsync, default=0};
private:
	void *__IAsyncOperation2;	/* Dragdrop::IAsyncOperation2 */
	void *__IDataObject;	/* IDataObject */
	void *__IDropSource;	/* IDropSource */
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator Dragdrop::_di_IAsyncOperation2()
	{
		Dragdrop::_di_IAsyncOperation2 intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IAsyncOperation2*(void) { return (IAsyncOperation2*)&__IAsyncOperation2; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator _di_IDataObject()
	{
		_di_IDataObject intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IDataObject*(void) { return (IDataObject*)&__IDataObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator _di_IDropSource()
	{
		_di_IDropSource intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IDropSource*(void) { return (IDropSource*)&__IDropSource; }
	#endif
	
};


class DELPHICLASS TCustomDropMultiSource;
class PASCALIMPLEMENTATION TCustomDropMultiSource : public TCustomDropSource
{
	typedef TCustomDropSource inherited;
	
private:
	Dragdropformats::TFeedbackDataFormat* FFeedbackDataFormat;
	Dragdrop::TRawDataFormat* FRawDataFormat;
	
protected:
	virtual HRESULT __fastcall DoGetData(const tagFORMATETC &FormatEtcIn, /* out */ tagSTGMEDIUM &Medium);
	virtual HRESULT __fastcall DoSetData(const tagFORMATETC &FormatEtc, tagSTGMEDIUM &Medium);
	virtual bool __fastcall HasFormat(const tagFORMATETC &FormatEtc);
	virtual _di_IEnumFORMATETC __fastcall GetEnumFormatEtc(int dwDirection);
	virtual int __fastcall GetPerformedDropEffect(void);
	virtual int __fastcall GetLogicalPerformedDropEffect(void);
	virtual int __fastcall GetPreferredDropEffect(void);
	virtual void __fastcall SetPerformedDropEffect(const int Value);
	virtual void __fastcall SetPreferredDropEffect(const int Value);
	virtual bool __fastcall GetInShellDragLoop(void);
	virtual void __fastcall SetInShellDragLoop(const bool Value);
	virtual GUID __fastcall GetTargetCLSID(void);
	void __fastcall DoOnSetData(Dragdrop::TCustomDataFormat* DataFormat, Dragdrop::TClipboardFormat* ClipboardFormat);
	
public:
	__fastcall virtual TCustomDropMultiSource(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDropMultiSource(void);
	virtual void __fastcall GetCompatibleClipboardFormats(const Dragdrop::TDataFormatClass DataFormatClass, Dragdrop::TClipboardFormats* ClipboardFormats);
	__property DataFormats;
};


class DELPHICLASS TDropEmptySource;
class PASCALIMPLEMENTATION TDropEmptySource : public TCustomDropMultiSource
{
	typedef TCustomDropMultiSource inherited;
	
public:
	/* TCustomDropMultiSource.Create */ inline __fastcall virtual TDropEmptySource(Classes::TComponent* AOwner) : TCustomDropMultiSource(AOwner) { }
	/* TCustomDropMultiSource.Destroy */ inline __fastcall virtual ~TDropEmptySource(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TDragResult __fastcall DropEffectToDragResult(int DropEffect);

}	/* namespace Dropsource */
using namespace Dropsource;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DropsourceHPP
