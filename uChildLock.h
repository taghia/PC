//---------------------------------------------------------------------------

#ifndef uChildLockH
#define uChildLockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmChildLock : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TTimer *Timer;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmChildLock(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChildLock *frmChildLock;
//---------------------------------------------------------------------------
#endif
