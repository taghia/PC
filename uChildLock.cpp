//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uChildLock.h"
#include "winutils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmChildLock *frmChildLock;
//---------------------------------------------------------------------------
__fastcall TfrmChildLock::TfrmChildLock(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmChildLock::FormShow(TObject *Sender)
{
	Timer->Enabled = 1;
	BlockInput(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmChildLock::TimerTimer(TObject *Sender)
{
	TWindow wnd;
	wnd.CaptureForeground();
	if(!wnd.SameProcess(Handle))
	{
		BlockInput(false);
		Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChildLock::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer->Enabled = 0;
}
//---------------------------------------------------------------------------

