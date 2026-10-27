//---------------------------------------------------------------------------

#ifndef uConsoleH
#define uConsoleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmConsole : public TForm
{
__published:	// IDE-managed Components
	TMemo *mCmd;
	TButton *btnRun;
	TButton *btnCancel;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmConsole(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConsole *frmConsole;
//---------------------------------------------------------------------------
#endif
