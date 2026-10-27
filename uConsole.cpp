//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uConsole.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmConsole *frmConsole;
//---------------------------------------------------------------------------
__fastcall TfrmConsole::TfrmConsole(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConsole::FormShow(TObject *Sender)
{
	mCmd->SetFocus();
}
//---------------------------------------------------------------------------
