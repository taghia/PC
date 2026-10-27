//---------------------------------------------------------------------------

#ifndef uRunH
#define uRunH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmRun : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *edtApp;
	TLabeledEdit *edtArg;
	TButton *btnRun;
	TButton *Button2;
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmRun(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRun *frmRun;
//---------------------------------------------------------------------------
#endif
