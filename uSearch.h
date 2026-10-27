//---------------------------------------------------------------------------

#ifndef uSearchH
#define uSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "fileview.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSearch : public TForm
{
__published:	// IDE-managed Components
	TPanel *panTop;
	TLabeledEdit *edtStr;
	TButton *btnStart;
	TButton *btnStop;
	TStatusBar *StatusBar;
	TButton *Button1;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnStartClick(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSearch(TComponent* Owner);
	TStringList *target;
	TFileView *view;
	void __fastcall onSearchNewDir(TObject *Sender, String dir);
	void __fastcall onItemFound(TObject *Sender);
	TNotifyEvent onFindTarget;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSearch *frmSearch;
//---------------------------------------------------------------------------
#endif
