// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Droptarget.pas' rev: 21.00

#ifndef DroptargetHPP
#define DroptargetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Dragdrop.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Activex.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Commctrl.hpp>	// Pascal unit
#include <Extctrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------
#include <shldisp.h>

namespace Droptarget
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TControlList;
class PASCALIMPLEMENTATION TControlList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	Controls::TWinControl* operator[](int AIndex) { return Controls[AIndex]; }
	
private:
	Classes::TList* FList;
	Controls::TWinControl* __fastcall GetControl(int AIndex);
	int __fastcall GetCount(void);
	
protected:
	int __fastcall Add(Controls::TWinControl* AControl);
	void __fastcall Insert(int Index, Controls::TWinControl* AControl);
	void __fastcall Remove(Controls::TWinControl* AControl);
	void __fastcall Delete(int AIndex);
	
public:
	__fastcall TControlList(void);
	__fastcall virtual ~TControlList(void);
	int __fastcall IndexOf(Controls::TWinControl* AControl);
	__property int Count = {read=GetCount, nodefault};
	__property Controls::TWinControl* Controls[int AIndex] = {read=GetControl/*, default*/};
};


#pragma option push -b-
enum TScrollDirection { sdUp, sdDown, sdLeft, sdRight };
#pragma option pop

typedef Set<TScrollDirection, sdUp, sdRight>  TScrollDirections;

typedef TScrollDirections TScrolDirections [[deprecated]];

typedef void __fastcall (__closure *TDropTargetScrollEvent)(System::TObject* Sender, const Types::TPoint &Point, TScrollDirections &Scroll, int &Interval);

typedef Set<Forms::TScrollBarKind, sbHorizontal, sbVertical>  TScrollBars;

typedef void __fastcall (__closure *TDropTargetEvent)(System::TObject* Sender, Classes::TShiftState ShiftState, const Types::TPoint &APoint, int &Effect);

struct TMouseSample
{
	
public:
	unsigned Time;
	Types::TPoint Pos;
};


class DELPHICLASS TCustomDropTarget;
class PASCALIMPLEMENTATION TCustomDropTarget : public Dragdrop::TDragDropComponent
{
	typedef Dragdrop::TDragDropComponent inherited;
	
private:
	_di_IDataObject FDataObject;
	Dragdrop::TDragTypes FDragTypes;
	bool FGetDataOnEnter;
	TDropTargetEvent FOnEnter;
	TDropTargetEvent FOnDragOver;
	Classes::TNotifyEvent FOnLeave;
	TDropTargetEvent FOnDrop;
	TDropTargetEvent FOnGetDropEffect;
	TDropTargetScrollEvent FOnScroll;
	TControlList* FTargets;
	bool FMultiTarget;
	bool FOptimizedMove;
	Controls::TWinControl* FTarget;
	Controls::TImageList* FImages;
	unsigned FDragImageHandle;
	bool FShowImage;
	Types::TPoint FImageHotSpot;
	Dragdrop::_di_IDropTargetHelper FDropTargetHelper;
	Types::TPoint FLastPoint;
	TScrollBars FScrollBars;
	Extctrls::TTimer* FScrollTimer;
	bool FAutoScroll;
	Types::TRect FNoScrollZone;
	bool FCustomScrollZone;
	TMouseSample FMouseSample;
	TMouseSample FMouseNextSample;
	bool FIsAsync;
	Classes::TNotifyEvent FOnEndAsyncTransfer;
	Classes::TNotifyEvent FOnStartAsyncTransfer;
	bool FAllowAsync;
	bool FAutoRegister;
	bool FEnabled;
	void __fastcall SetNoScrollZone(const Types::TRect &Value);
	
protected:
	HRESULT __stdcall DragEnter(const _di_IDataObject DataObj, int grfKeyState, const Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragOver(int grfKeyState, const Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragLeave(void);
	HRESULT __stdcall Drop(const _di_IDataObject dataObj, int grfKeyState, const Types::TPoint pt, int &dwEffect);
	virtual void __fastcall DoEnter(Classes::TShiftState ShiftState, const Types::TPoint &Point, int &Effect);
	virtual void __fastcall DoDragOver(Classes::TShiftState ShiftState, const Types::TPoint &Point, int &Effect);
	virtual void __fastcall DoDrop(Classes::TShiftState ShiftState, const Types::TPoint &Point, int &Effect);
	virtual void __fastcall DoLeave(void);
	virtual void __fastcall DoOnPaste(int &Effect);
	virtual void __fastcall DoScroll(const Types::TPoint &Point, TScrollDirections &Scroll, int &Interval);
	virtual bool __fastcall GetData(int Effect);
	virtual bool __fastcall DoGetData(void) = 0 ;
	virtual void __fastcall ClearData(void) = 0 ;
	virtual int __fastcall GetValidDropEffect(Classes::TShiftState ShiftState, const Types::TPoint &pt, int dwEffect);
	virtual int __fastcall GetPreferredDropEffect(void);
	virtual bool __fastcall SetPerformedDropEffect(int Effect);
	virtual bool __fastcall SetPasteSucceeded(int Effect);
	void __fastcall DoRegister(Controls::TWinControl* ATarget);
	void __fastcall DoUnregister(Controls::TWinControl* ATarget);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	Controls::TWinControl* __fastcall GetTarget(void);
	void __fastcall SetTarget(const Controls::TWinControl* Value);
	void __fastcall DoAutoScroll(System::TObject* Sender);
	bool __fastcall SampleMouse(const Types::TPoint &MousePos, bool First = false);
	void __fastcall SetShowImage(bool Show);
	void __fastcall SetDataObject(_di_IDataObject Value);
	void __fastcall DoEndAsyncTransfer(System::TObject* Sender);
	__property Dragdrop::_di_IDropTargetHelper DropTargetHelper = {read=FDropTargetHelper};
	__property bool CustomScrollZone = {read=FCustomScrollZone, write=FCustomScrollZone, nodefault};
	
public:
	__fastcall virtual TCustomDropTarget(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDropTarget(void);
	void __fastcall Register(Controls::TWinControl* ATarget);
	void __fastcall Unregister(Controls::TWinControl* ATarget = (Controls::TWinControl*)(0x0));
	virtual Controls::TWinControl* __fastcall FindTarget(const Types::TPoint &p);
	Controls::TWinControl* __fastcall FindNearestTarget(const Types::TPoint &p);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual bool __fastcall HasValidFormats(const _di_IDataObject ADataObject) = 0 ;
	virtual int __fastcall PasteFromClipboard(void);
	virtual bool __fastcall CanPasteFromClipboard(void);
	virtual void __fastcall ResetScrollZone(void);
	virtual void __fastcall GetCompatibleClipboardFormats(const Dragdrop::TDataFormatClass DataFormatClass, Dragdrop::TClipboardFormats* ClipboardFormats);
	__property _di_IDataObject DataObject = {read=FDataObject};
	__property TControlList* Targets = {read=FTargets};
	__property Types::TRect NoScrollZone = {read=FNoScrollZone, write=SetNoScrollZone};
	__property bool AsyncTransfer = {read=FIsAsync, nodefault};
	
__published:
	__property Dragdrop::TDragTypes DragTypes = {read=FDragTypes, write=FDragTypes, nodefault};
	__property bool GetDataOnEnter = {read=FGetDataOnEnter, write=FGetDataOnEnter, default=0};
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property TDropTargetEvent OnEnter = {read=FOnEnter, write=FOnEnter};
	__property TDropTargetEvent OnDragOver = {read=FOnDragOver, write=FOnDragOver};
	__property Classes::TNotifyEvent OnLeave = {read=FOnLeave, write=FOnLeave};
	__property TDropTargetEvent OnDrop = {read=FOnDrop, write=FOnDrop};
	__property TDropTargetEvent OnGetDropEffect = {read=FOnGetDropEffect, write=FOnGetDropEffect};
	__property TDropTargetScrollEvent OnScroll = {read=FOnScroll, write=FOnScroll};
	__property Classes::TNotifyEvent OnStartAsyncTransfer = {read=FOnStartAsyncTransfer, write=FOnStartAsyncTransfer};
	__property Classes::TNotifyEvent OnEndAsyncTransfer = {read=FOnEndAsyncTransfer, write=FOnEndAsyncTransfer};
	__property bool ShowImage = {read=FShowImage, write=SetShowImage, default=1};
	__property Controls::TWinControl* Target = {read=GetTarget, write=SetTarget};
	__property bool MultiTarget = {read=FMultiTarget, write=FMultiTarget, default=0};
	__property bool AutoRegister = {read=FAutoRegister, write=FAutoRegister, default=1};
	__property bool AutoScroll = {read=FAutoScroll, write=FAutoScroll, default=1};
	__property bool OptimizedMove = {read=FOptimizedMove, write=FOptimizedMove, default=0};
	__property bool AllowAsyncTransfer = {read=FAllowAsync, write=FAllowAsync, default=0};
private:
	void *__IDropTarget;	/* IDropTarget */
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	operator _di_IDropTarget()
	{
		_di_IDropTarget intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IDropTarget*(void) { return (IDropTarget*)&__IDropTarget; }
	#endif
	
};


class DELPHICLASS TDropTarget;
class PASCALIMPLEMENTATION TDropTarget [[deprecated("Use TCustomDropTarget instead")]] : public TCustomDropTarget
{
	typedef TCustomDropTarget inherited;
	
public:
	/* TCustomDropTarget.Create */ inline __fastcall virtual TDropTarget(Classes::TComponent* AOwner) : TCustomDropTarget(AOwner) { }
	/* TCustomDropTarget.Destroy */ inline __fastcall virtual ~TDropTarget(void) { }
	
};


class DELPHICLASS TDropDummy;
class PASCALIMPLEMENTATION TDropDummy : public TCustomDropTarget
{
	typedef TCustomDropTarget inherited;
	
protected:
	virtual void __fastcall ClearData(void);
	virtual bool __fastcall DoGetData(void);
	
public:
	virtual bool __fastcall HasValidFormats(const _di_IDataObject ADataObject);
public:
	/* TCustomDropTarget.Create */ inline __fastcall virtual TDropDummy(Classes::TComponent* AOwner) : TCustomDropTarget(AOwner) { }
	/* TCustomDropTarget.Destroy */ inline __fastcall virtual ~TDropDummy(void) { }
	
};


typedef void __fastcall (__closure *TAcceptFormatEvent)(System::TObject* Sender, const Dragdrop::TCustomDataFormat* DataFormat, bool &Accept);

class DELPHICLASS TCustomDropMultiTarget;
class PASCALIMPLEMENTATION TCustomDropMultiTarget : public TCustomDropTarget
{
	typedef TCustomDropTarget inherited;
	
private:
	TAcceptFormatEvent FOnAcceptFormat;
	
protected:
	virtual void __fastcall ClearData(void);
	virtual bool __fastcall DoGetData(void);
	virtual void __fastcall DoAcceptFormat(const Dragdrop::TCustomDataFormat* DataFormat, bool &Accept);
	__property TAcceptFormatEvent OnAcceptFormat = {read=FOnAcceptFormat, write=FOnAcceptFormat};
	
public:
	__fastcall virtual TCustomDropMultiTarget(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDropMultiTarget(void);
	virtual bool __fastcall HasValidFormats(const _di_IDataObject ADataObject);
	__property DataFormats;
};


class DELPHICLASS TDropEmptyTarget;
class PASCALIMPLEMENTATION TDropEmptyTarget : public TCustomDropMultiTarget
{
	typedef TCustomDropMultiTarget inherited;
	
public:
	/* TCustomDropMultiTarget.Create */ inline __fastcall virtual TDropEmptyTarget(Classes::TComponent* AOwner) : TCustomDropMultiTarget(AOwner) { }
	/* TCustomDropMultiTarget.Destroy */ inline __fastcall virtual ~TDropEmptyTarget(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Droptarget */
using namespace Droptarget;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DroptargetHPP
