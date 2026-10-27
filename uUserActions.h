//---------------------------------------------------------------------------

#ifndef uUserActionsH
#define uUserActionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmUserActions : public TForm
{
__published:	// IDE-managed Components
	TListBox *lbActions;
	TButton *btnRemove;
	TButton *btnEdit;
	TButton *btnClose;
	TButton *btnRun;
	TSpeedButton *btnUp;
	TSpeedButton *btnDown;
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall lbActionsDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmUserActions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserActions *frmUserActions;
//---------------------------------------------------------------------------
#endif
